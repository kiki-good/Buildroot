/*
 * Parallel xz decoder written to optimise the decompress of files in tmpfs
 *
 * Author: Ben Gray <ben.gray@sky.uk>
 *
 * This util process xz streams in separate processes to utilise multi-core
 * systems to speed up the decompression process.  In addition it uses mmap
 * rather than file read/write to also speed up reading and writing files
 * to tmpfs/ramfs filesystems.
 *
 * Doing this speeds up decompression of large files by roughly a ratio of
 * the number of cores it can utilise. However to be effective it needs at
 * least the same number of streams in the files as cores on the system.
 *
 * [ref http://tukaani.org/xz/xz-file-format-1.0.4.txt]
 *
 * XZ STREAMS
 * ----------
 * The xz file format allows for 'streams', typically a file will only have
 * one stream, but it is legal for multiple streams to be present.  The easiest
 * way to create a file with multiple streams is simply to concatenate multiple
 * xz files together.
 *
 * For example the following can be used to split a file into multiple streams
 *
 *    split --number=1/2 FILE | xz -9 -c - > FILE.xz.001
 *    split --number=2/2 FILE | xz -9 -c - > FILE.xz.002
 *    cat FILE.xz.001 FILE.xz.002 > FILE.xz
 *
 * Now FILE.xz can be read by standard xz tools (i.e. xzcat, xz, etc), but if
 * decompressed by this tool is will use two cores to extract the two streams
 * in parallel.
 *
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "xz.h"

#ifndef PATH_MAX
#  define PATH_MAX 1024
#endif

#define ARRAY_SIZE(x)           (sizeof(x) / sizeof(x[0]))




/**
 * struct bunxz_stream_ctx - Stream context
 * @in:         Beginning of the input stream, typically this would be an
 *              mmapped pointer to the start of the stream within a file.
 * @in_size:    Size of the input stream.
 * @out:        Beginning of the output buffer. typically this would be an
 *              mmapped pointer to the start of the output within a file.
 * @out_size:   The maximum number of bytes that can be written to the output
 *              buffer / file.
 *
 */
struct bunxz_stream_ctx {
	const uint8_t *in;
	size_t in_size;

	uint8_t *out;
	size_t out_size;
};


/**
 * bunxz_stream() - Decompresses a stream
 * @ctx    The stream context, contains the input and output details.
 *
 * Decompresses a single stream into the supplied buffer (mmap'ed file).
 *
 * Returns 0 on success and -1 on failure.
 */
static int bunxz_stream(const struct bunxz_stream_ctx* ctx)
{
	struct xz_buf b;
	struct xz_dec *s;
	enum xz_ret ret;
	const char *msg;


	/*
	 * Support up to 64 MiB dictionary. The actually needed memory
	 * is allocated once the headers have been parsed.
	 */
	s = xz_dec_init(XZ_DYNALLOC, 1 << 26);
	if (s == NULL) {
		msg = "Memory allocation failed\n";
		goto error;
	}

	b.in = ctx->in;
	b.in_pos = 0;
	b.in_size = ctx->in_size;
	b.out = ctx->out;
	b.out_pos = 0;
	b.out_size = ctx->out_size;

	while (true) {

		ret = xz_dec_run(s, &b);
		if (ret == XZ_OK)
			continue;

#ifdef XZ_DEC_ANY_CHECK
		if (ret == XZ_UNSUPPORTED_CHECK) {
			fputs("Unsupported check; not verifying "
			      "file integrity\n", stderr);
			continue;
		}
#endif

		switch (ret) {
			case XZ_STREAM_END:
				xz_dec_end(s);
				return 0;

			case XZ_MEM_ERROR:
				msg = "Memory allocation failed\n";
				goto error;

			case XZ_MEMLIMIT_ERROR:
				msg = "Memory usage limit reached\n";
				goto error;

			case XZ_FORMAT_ERROR:
				msg = "Not a .xz file\n";
				goto error;

			case XZ_OPTIONS_ERROR:
				msg = "Unsupported options in the .xz headers\n";
				goto error;

			case XZ_DATA_ERROR:
			case XZ_BUF_ERROR:
				msg = "File is corrupt\n";
				goto error;

			default:
				msg = "Bug!\n";
				goto error;
		}
	}

error:
	xz_dec_end(s);
	fputs(msg, stderr);
	return -1;
}

/**
 * get_nprocs() - simple implementation of the GNU equivalent function
 *
 * Returns the number of processors currently available in the system.
 *
 */
static int get_nprocs()
{
	int fd;
	char buf[4096];
	ssize_t rd;
	char *ln;
	int ncpus = 0;

	fd = open("/proc/stat", O_CLOEXEC | O_RDONLY);
	if (fd < 0)
		return 1;

	rd = read(fd, buf, sizeof(buf) - 1);
	if (rd < 0) {
		close(fd);
		return 1;
	}

	buf[rd] = '\0';
	close(fd);

	ln = strtok(buf, "\n");
	while (ln) {
		if (strncmp(ln, "cpu", 3) != 0)
			break;
		else if (isdigit(ln[3]))
			ncpus++;

		ln = strtok(NULL, "\n");
	}

	return (ncpus > 0) ? ncpus : 1;
}

/**
 * bunxz_process_streams() - processes the streams in parallel
 * @streams:    The array of streams to process.
 * @nstreams:   The number of streams in the source file.
 *
 * The streams are processed in their own process as oppose to a thread as
 * klibc lacks clone / pthread calls - because the library itself is not thread
 * safe.
 *
 * However in reality the lzma / xz functions don't need klibc functions so
 * we could use the clone syscall .... however that involves writing arm
 * asm for handling the jump, it's not difficult, but also not trivial.
 *
 */
static void bunxz_process_streams(struct bunxz_stream_ctx *streams,
                                  size_t nstreams)
{
	int ncpus;
	pid_t pid;
	int status;
	size_t i, j, n, per_cpu;

	struct _tsk_streams {
		pid_t pid;
		const struct bunxz_stream_ctx *streams;
		size_t nstreams;
	} tsk_streams[16];


	ncpus = get_nprocs();
	if (ncpus > ARRAY_SIZE(tsk_streams))
		ncpus = ARRAY_SIZE(tsk_streams);


	/*
	 * Work out how many streams to give each cpu, this (obviously) may not be
	 * the same number for each core.
	 */
	per_cpu = nstreams / ncpus;
	for (i = 0; i < ncpus; i++)
		tsk_streams[i].nstreams = per_cpu;
	for (i = 0; i < (nstreams % ncpus); i++)
		tsk_streams[i].nstreams++;

	for (i = 0, n = 0; i < ncpus; i++) {
		tsk_streams[i].streams = streams + n;
		n += tsk_streams[i].nstreams;
	}


	/*
	 * Spawn a process per core and give it a bunch of streams to process
	 */
	for (i = 0; i < ncpus; i++) {

		tsk_streams[i].pid = -1;
		if (tsk_streams[i].nstreams == 0)
			continue;

		pid = fork();
		if (pid < 0) {
			fprintf(stderr, "fork failed? (%d - %s)\n", errno, strerror(errno));
			break;

		} else if (pid == 0) {

			/* Within child so perform the decomp */
			for (j = 0; j < tsk_streams[i].nstreams; j++) {
				if (bunxz_stream(&tsk_streams[i].streams[j]) != 0)
					exit(EXIT_FAILURE);

				msync(tsk_streams[i].streams[j].out,
					  tsk_streams[i].streams[j].out_size,
					  MS_SYNC);
			}

			exit(EXIT_SUCCESS);

		} else {
			tsk_streams[i].pid = pid;
		}
	}


	/*
	 * Wait for all child tasks to complete
	 */
	for (i = 0; i < ncpus; i++) {
		if (tsk_streams[i].pid > 0) {
			if (waitpid(tsk_streams[i].pid, &status, 0) < 0) {
				fprintf(stderr, "waitpid failed? (%d - %s)\n", errno,
				        strerror(errno));
			} else if (!WIFEXITED(status)) {
				fprintf(stderr, "pid %d didn't terminate?\n",
				        tsk_streams[i].pid);
			} else if (WEXITSTATUS(status) != EXIT_SUCCESS) {
				fprintf(stderr, "pid %d failed to decode\n",
				        tsk_streams[i].pid);
			}
		}
	}

}

/**
 * bunxz_decode_num() - Decodes a variable length number
 * @buf:       Pointer to the start of th integer
 * @size_max:  The maximum number of bytes in the integer
 * @num:       The number parsed.
 *
 * Returns the number of bytes consumed, or 0 on error.
 *
 * This is a copy'n'paste from the xz file format standard, available here
 * http://tukaani.org/xz/xz-file-format-1.0.4.txt
 *
 * From the RFC:
 *
 *   |   Multibyte integers of static length, such as CRC values,
 *   |   are stored in little endian byte order (least significant
 *   |   byte first).
 *   |
 *   |   When smaller values are more likely than bigger values (for
 *   |   example file sizes), multibyte integers are encoded in a
 *   |   variable-length representation:
 *   |     - Numbers in the range [0, 127] are copied as is, and take
 *   |       one byte of space.
 *   |     - Bigger numbers will occupy two or more bytes. All but the
 *   |       last byte of the multibyte representation have the highest
 *   |       (eighth) bit set.
 *   |
 *   |   For now, the value of the variable-length integers is limited
 *   |   to 63 bits, which limits the encoded size of the integer to
 *   |   nine bytes. These limits may be increased in the future if
 *   |   needed.
 *   |
 *   |   The following C code illustrates encoding and decoding of
 *   |   variable-length integers. The functions return the number of
 *   |   bytes occupied by the integer (1-9), or zero on error.
 *
 */
static size_t bunxz_decode_num(const uint8_t *buf, size_t size_max,
                               uint64_t *num)
{
	if (size_max == 0)
		return 0;

	if (size_max > 9)
		size_max = 9;

	*num = buf[0] & 0x7F;
	size_t i = 0;

	while (buf[i++] & 0x80) {
		if (i >= size_max || buf[i] == 0x00)
			return 0;

		*num |= (uint64_t)(buf[i] & 0x7F) << (i * 7);
	}

	return i;
}

/**
 * bunxz_process_index() - Process the index field of a stream.
 * @in:                Pointer to the start of the index filed
 * @size:              The size of the index filed (in bytes)
 * @block_size:        Pointer to a variable to store the size of all the blocks
 * @uncompressed_size: Pointer to a variable to store the uncompressed size
 *                     of the stream
 *
 * Iterates over all the index records and returns the size of all the blocks
 * and their uncompressed size.
 *
 * From the RFC:
 *
 *   +-----------------+===================+
 *   | Index Indicator | Number of Records |
 *   +-----------------+===================+
 *
 *        +=================+===============+-+-+-+-+
 *   ---> | List of Records | Index Padding | CRC32 |
 *        +=================+===============+-+-+-+-+
 *
 *
 *
 */
static int bunxz_process_index(const uint8_t *in, size_t size,
                               size_t *block_size,
                               size_t *uncompressed_size)
{
	size_t n;
	uint32_t crc;
	uint64_t i, nrecs;
	uint64_t blksz;
	uint64_t uncompsz;

	*block_size = 0;
	*uncompressed_size = 0;

	if ((size & 0x3) || (size < 8)) {
		fprintf(stderr, "Invalid size of index field\n");
		return -1;
	}

	/* Calculate the CRC32 first, we could skip if really trying to speed up */
	crc = xz_crc32(in, (size - 4), 0);
	if (crc != *((const uint32_t*)(in + (size - 4)))) {
		fprintf(stderr, "Invalid index CRC32 field\n");
		return -1;
	}

	/* Sanity check the 'Index Indicator' is 0x00 */
	if (*in++ != 0x00) {
		fprintf(stderr, "Invalid size of index indicator field\n");
		return -1;
	}

	/* Read the number of indexes */
	size -= 5;
	n = bunxz_decode_num(in, size, &nrecs);
	if (n == 0) {
		fprintf(stderr, "Error decoding index indicator field\n");
		return -1;
	}

	in += n;
	size -= n;

	/* Process every record */
	for (i = 0; i < nrecs; i++) {

		n = bunxz_decode_num(in, size, &blksz);
		if (n == 0) {
			fprintf(stderr, "Error decoding unpadded size field of"
			        " index %llu\n", i);
			return -1;
		}

		*block_size += ((blksz - 1) & ~0x3ULL) + 4;

		in += n;
		size -= n;

		n = bunxz_decode_num(in, size, &uncompsz);
		if (n == 0) {
			fprintf(stderr, "Error decoding uncompressed size field of"
			        " index %llu\n", i);
			return -1;
		}

		*uncompressed_size += uncompsz;

		in += n;
		size -= n;
	}

	/* If everything worked then we can have at most only 3 bytes of padding */
	if (size > 3) {
		fprintf(stderr, "Error to much padding after processing index\n");
		return -1;
	}

	return 0;
}

/**
 * bunxz_parse() - Parses a xz file finding the stream locations
 * @in:          Pointer to the first byte of the file
 * @in_size:     The size of the input file
 * @streams:     Array of stream buffers that are populated by this function
 * @max_stream:  The max streams in the streams array
 *
 * Tries to find the location of the stream(s) within the file by reading
 * backwards through the file.  It's not possible to read forward as the
 * stream header doesn't contain the size.
 *
 * Returns the number of streams found, it can be greater than the max_streams
 * argument. On error -1 is returned.
 *
 * From the RFC:
 *
 *   A standalone .xz files consist of one or more Streams which may
 *   have Stream Padding between or after them:
 *
 *   +========+================+========+================+
 *   | Stream | Stream Padding | Stream | Stream Padding | ...
 *   +========+================+========+================+
 *
 *   The sizes of Stream and Stream Padding are always multiples
 *   of four bytes, thus the size of every valid .xz file MUST be
 *   a multiple of four bytes.
 *
 *
 *
 */
static ssize_t bunxz_parse(const uint8_t *in, size_t in_size,
                           struct bunxz_stream_ctx* streams,
                           size_t max_streams)
{
	const uint32_t HEADER1_MAGIC = 0x587a37fdUL;
	const uint32_t HEADER1_MASK = 0xffffffffUL;
	const uint32_t HEADER2_MAGIC = 0x0000005aU;
	const uint32_t HEADER2_MASK = 0x0000ffffUL;

	const uint32_t FOOTER_MAGIC = 0x5a590000U;
	const uint32_t FOOTER_MASK = 0xffff0000U;

	const uint32_t *in32 = (const uint32_t*)in;
	const uint32_t *pin32;
	const uint32_t *pfooter32;
	uint32_t bkward_size32;
	uint32_t crc;
	size_t blksz;
	size_t uncompsz;
	size_t nstreams = 0;
	int ret;

	if ((in_size < 32) || (in_size & 0x3)) {
		fprintf(stderr, "Input file size %zu invalid\n", in_size);
		return -1;
	}

	pin32 = in32 + ((in_size / 4) - 1);
	while (pin32 >= (in32 + 2)) {

		if ((*pin32-- & FOOTER_MASK) == FOOTER_MAGIC) {


			/*
			 * Check the CRC32 of the footer
			 */
			crc = xz_crc32((const uint8_t*)pin32, 6, 0);
			if (*(pin32 - 1) != crc)
				continue;

			/* 
			 * Store the footer position so can calculate the size of the stream
			 */
			pfooter32 = (pin32 + 2);

			/*
			 * Found the magic bytes of the footer, which should be formatted
			 * like so
			 *
			 *    +-+-+-+-+---+---+---+---+-------+------+----------+---------+
			 *    | CRC32 | Backward Size | Stream Flags | Footer Magic Bytes |
			 *    +-+-+-+-+---+---+---+---+-------+------+----------+---------+
			 *
			 */
			bkward_size32 = *pin32--;

			if (bkward_size32 >= (pin32 - in32)) {
				fprintf(stderr, "Invalid backwards size %u "
				        "(space %zd)\n", bkward_size32, (pin32 - in32));
				return -1;
			}

			/* 
			 * Process the index fields, returning the total size of all the
			 * compressed blocks and the total uncompressed size of the stream.
			 */
			pin32 -= (bkward_size32 + 1);
			ret = bunxz_process_index((const uint8_t*)pin32,
			                          (bkward_size32 + 1) * 4,
			                          &blksz, &uncompsz);
			if (ret != 0)
				return -1;
			if (((blksz / 4) + 3) > (pin32 - in32)) {
				fprintf(stderr, "Invalid block size %zu (space %zd)\n",
				        blksz, ((pin32 - in32) * 4));
				return -1;
			}

			/*
			 * Now skip back further, over the blocks and we should end up
			 * at the stream header
			 */
			pin32 -= (blksz / 4) + 3;
			if ((((*(pin32 + 0)) & HEADER1_MASK) != HEADER1_MAGIC) ||
				(((*(pin32 + 1)) & HEADER2_MASK) != HEADER2_MAGIC) ) {
				fprintf(stderr, "Invalid stream header magic\n");
				return -1;
			}

			/*
			 * If we arrived here then we parsed the stream successifully so
			 * store the start position and size of the compressed stream and
			 * the expected output decompressed size
			 */
			if (streams && (nstreams < max_streams)) {
				streams[nstreams].in = (const uint8_t*)pin32;
				streams[nstreams].in_size = (pfooter32 - pin32) * 4;
				streams[nstreams].out = NULL;
				streams[nstreams].out_size = uncompsz;
			}

			nstreams++;
		}
	}

	return nstreams;
}

static char *progname;

static const struct option long_options[] = {
	{ "help",    no_argument,       NULL, 'h' },
	{ "version", no_argument,       NULL, 'V' },
	{ "input",   required_argument, NULL, 'i' },
	{ "output",  required_argument, NULL, 'o' },
	{ "delete",  no_argument,       NULL, 'd' },
	{ NULL,      0,                 NULL,  0  }
};

static void usage(FILE *f)
{
	fprintf(f, "usage: %s -i <input> -o <output>\n\
  -h --help                  Print this help and exit\n\
  -V --version               Display this program's version number\n\
  -i --input=file            Input .xz compressed file\n\
  -o --output=file           Output decompress file to create\n",
			progname);
	exit(f == stderr ? EXIT_FAILURE : EXIT_SUCCESS);
}


int main(int argc, char **argv)
{
	int c;
	int longindex;
	char in_fpath[PATH_MAX] = "\0";
	int in_fd = -1;
	void *in_fp = NULL;
	struct stat st;
	char out_fpath[PATH_MAX] = "\0";
	int out_fd = -1;
	void *out_fp = NULL;
	ssize_t nstreams, i;
	struct bunxz_stream_ctx streams[64];
	size_t total_uncompsz = 0, off;

	progname = argv[0];

	while ((c = getopt_long(argc, argv, "hVi:o:", long_options, &longindex)) != -1) {
		switch (c) {
			case 'h':
				usage(stdout);
				break;
			case 'V':
				printf("%s: v1.0\n", progname);
				exit(EXIT_SUCCESS);
				break;
			case 'i':
				strcpy(in_fpath, (char*)optarg);
				break;
			case 'o':
				strcpy(out_fpath, (char*)optarg);
				break;
			default:
				usage(stderr);
				break;
		}
	}

	/* Requires both an input and output file */
	if (!strlen(in_fpath) || !strlen(out_fpath))
		usage(stderr);


	/* Open the input file and mmap it */
	in_fd = open(in_fpath, O_CLOEXEC | O_RDONLY);
	if (in_fd < 0) {
		fprintf(stderr, "Failed to open '%s' (%d - %s)\n", in_fpath, errno,
		        strerror(errno));
		return EXIT_FAILURE;
	}

	if (fstat(in_fd, &st) < 0) {
		fprintf(stderr, "Failed to get the size of '%s' (%d - %s)\n", in_fpath,
		        errno, strerror(errno));
		goto error;
	}

	in_fp = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, in_fd, 0);
	if (in_fp == MAP_FAILED) {
		fprintf(stderr, "Failed to mmap '%s' (%d - %s)\n", in_fpath,
		        errno, strerror(errno));
		goto error;
	}


	/* Create the CRC 32/64 tables before starting to process the file. */
	xz_crc32_init();
#ifdef XZ_USE_CRC64
	xz_crc64_init();
#endif

	/*
	 * Now try and parse the file to get the number of streams, their
	 * positions within the file and their uncompressed size.
	 */
	nstreams = bunxz_parse(in_fp, st.st_size, streams, ARRAY_SIZE(streams));
	if (nstreams < 1) {
		fprintf(stderr, "Failed to parse xz file '%s'\n", in_fpath);
		goto error;
	}
	if (nstreams > ARRAY_SIZE(streams)) {
		fprintf(stderr, "File contains to many streams\n");
		goto error;
	}

	total_uncompsz = 0;
	for (i = 0; i < nstreams; i++)
		total_uncompsz += streams[i].out_size;


	/* Create the output file of the entire uncompressed size and mmap it */
	out_fd = open(out_fpath, O_CLOEXEC | O_RDWR | O_CREAT, 0644);
	if (out_fd < 0) {
		fprintf(stderr, "Failed to open '%s' (%d - %s)\n", out_fpath, errno,
		        strerror(errno));
		goto error;
	}

	if (ftruncate(out_fd, total_uncompsz) < 0) {
		fprintf(stderr, "Failed to resize '%s' to %zu bytes (%d - %s)\n",
		        out_fpath, total_uncompsz, errno, strerror(errno));
		goto error;
	}

	out_fp = mmap(NULL, total_uncompsz, PROT_READ | PROT_WRITE, MAP_SHARED, out_fd, 0);
	if (out_fp == MAP_FAILED) {
		fprintf(stderr, "Failed to mmap '%s' (%d - %s)\n", out_fpath,
		        errno, strerror(errno));
		goto error;
	}


	/* Assign the output buffer pointers for all the streams */
	off = 0;
	for (i = (nstreams - 1); i >= 0; i--) {
		streams[i].out = ((uint8_t*)out_fp) + off;
		off += streams[i].out_size;
	}

	/* Process the streams in parallel */
	bunxz_process_streams(streams, nstreams);

	/* Clean up the in and out files */
	munmap(in_fp, st.st_size);
	close(in_fd);
	munmap(out_fp, total_uncompsz);
	close(out_fd);

	return 0;

error:
	if (in_fp != MAP_FAILED)
		munmap(in_fp, st.st_size);
	if (in_fd >= 0)
		close(in_fd);

	if (out_fp != MAP_FAILED)
		munmap(out_fp, total_uncompsz);
	if (out_fd >= 0)
		close(out_fd);


	return EXIT_SUCCESS;
}
