/* upstart
 *
 * conf.c - configuration management
 *
 * Copyright  2009,2010,2011,2012,2013 Canonical Ltd.
 * Author: Scott James Remnant <scott@netsplit.com>.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif /* HAVE_CONFIG_H */


#include <sys/types.h>
#include <sys/stat.h>

#include <errno.h>
#include <libgen.h>
#include <string.h>
#include <unistd.h>

#include <nih/macros.h>
#include <nih/alloc.h>
#include <nih/list.h>
#include <nih/hash.h>
#include <nih/string.h>
#include <nih/io.h>
#include <nih/file.h>
#include <nih/watch.h>
#include <nih/logging.h>
#include <nih/error.h>
#include <nih/errors.h>

#include "parse_job.h"
#include "parse_conf.h"
#include "conf.h"
#include "errors.h"
#include "paths.h"
#include "environ.h"

/* Prototypes for static functions */
static int  conf_source_reload_file    (ConfSource *source)
	__attribute__ ((warn_unused_result));
static int  conf_source_reload_dir     (ConfSource *source)
	__attribute__ ((warn_unused_result));

static int  conf_file_filter           (ConfSource *source, const char *path,
					int is_dir);
static int  conf_dir_filter            (ConfSource *source, const char *path,
					int is_dir);
static void conf_create_modify_handler (ConfSource *source, NihWatch *watch,
					const char *path,
					struct stat *statbuf);
static void conf_delete_handler        (ConfSource *source, NihWatch *watch,
					const char *path);
static int  conf_file_visitor          (ConfSource *source,
					const char *dirname, const char *path,
					struct stat *statbuf)
	__attribute__ ((warn_unused_result));

static int  conf_reload_path           (ConfSource *source, const char *path,
					const char *override_path)
	__attribute__ ((warn_unused_result));

static inline int  is_conf_file        (const char *path)
	__attribute__ ((warn_unused_result));

static inline int is_conf_file_std     (const char *path)
	__attribute__ ((warn_unused_result));

static inline int is_conf_file_override(const char *path)
	__attribute__ ((warn_unused_result));

static inline char *toggle_conf_name   (const void *parent, const char *path)
	__attribute__ ((warn_unused_result));

static inline char * conf_to_job_name  (const char *source_path,
                                        const char *conf_path)
	__attribute__ ((warn_unused_result));

static char * conf_get_best_override   (const char *name,
                                        const ConfSource *last_source)
	__attribute__ ((warn_unused_result));

/**
 * user_mode:
 *
 * If TRUE, upstart runs in user session mode.
 **/
int user_mode = FALSE;

/**
 * session_file:
 *
 * Full path to file containing UPSTART_SESSION details (only set when
 * user_mode in operation).
 *
 * File is created on startup and removed on clean shutdown.
 **/
const char *session_file = NULL;

/**
 * conf_sources:
 *
 * This list holds the list of known sources of configuration; each item
 * is a ConfSource structure.  The order of this list dictates the priority
 * of the sources, with the first one having the highest priority.
 **/
NihList *conf_sources = NULL;

extern json_object *json_conf_sources;

/**
 * is_conf_file_std:
 * @path: path to check.
 *
 * Determine if specified path contains a legitimate
 * configuration file name.
 *
 * Returns: TRUE if @path contains a valid configuration file name,
 * else FALSE.
 *
 **/
static inline int
is_conf_file_std (const char *path)
{
	nih_assert (path != NULL);

	char *ptr = strrchr (path, '.');

	if (ptr && IS_CONF_EXT_STD (ptr))
		return TRUE;

	return FALSE;
}

/**
 * is_conf_file_override:
 * @path: path to check.
 *
 * Determine if specified path contains a legitimate
 * override file name.
 *
 * Returns: TRUE if @path contains a valid override file name,
 * else FALSE.
 *
 **/
static inline int
is_conf_file_override (const char *path)
{
	nih_assert (path != NULL);

	char *ptr = strrchr (path, '.');

	if (ptr && IS_CONF_EXT_OVERRIDE (ptr))
		return TRUE;

	return FALSE;
}

/**
 * is_conf_file:
 * @path: path to check.
 *
 * Determine if specified path contains a legitimate
 * configuration file or override file name.
 *
 * Returns: TRUE if @path contains a valid configuration
 * file or override file name, else FALSE.
 *
 **/
static inline int
is_conf_file (const char *path)
{
	nih_assert (path != NULL);

	char *ptr = strrchr (path, '.');

	if (ptr && (ptr > path) && (ptr[-1] != '/') && IS_CONF_EXT (ptr))
		return TRUE;

	return FALSE;
}

/**
 * conf_to_job_name:
 * @source_path: path to ConfSource
 * @conf_path: path to configuration file
 *
 * Constructs the job name for a given @conf_path. Removes
 * @source_path directory name from the front of @conf_path and
 * extension from the end.
 *
 * Returns: newly-allocated name.
 *
 **/
static inline char *
conf_to_job_name (const char * source_path, const char * conf_path)
{
	const char *start, *end;
	char       *name = NULL;
	int        source_len;

	nih_assert (source_path != NULL);
	nih_assert (conf_path != NULL);

	start = conf_path;
	source_len = strlen (source_path);

	if (! strncmp (start, source_path, source_len))
		start += source_len;

	while (*start == '/')
		start++;

	end = strrchr (start, '.');
	if (end && IS_CONF_EXT (end))
		name = NIH_MUST (nih_strndup (NULL, start, end - start));
	else
		name = NIH_MUST (nih_strdup (NULL, start));

	return name;
}


/**
 * conf_get_best_override:
 * @conf_file: conf_file object
 *
 * Given a @conf_file iterate over all config sources & find the
 * first applicable override file. It will not look for override files
 * beyond the @conf_file's ConfSource.
 *
 * Returns: newly allocated path to override file or NULL.
 **/
static char *
conf_get_best_override (const char *name, const ConfSource *last_source)
{
	char         *try_path=NULL;
	struct stat   statbuf;

	nih_assert (name != NULL);
	nih_assert (last_source != NULL);

	NIH_LIST_FOREACH (conf_sources, iter) {

		ConfSource *source = (ConfSource *)iter;

		/* Look at directories only */
		if (source->type == CONF_FILE)
			continue;

		/* Reclaim memory */
		if (try_path)
			nih_free (try_path);

		/* construct path */
		try_path = NIH_MUST (nih_sprintf (NULL, "%s/%s%s", source->path, name, CONF_EXT_OVERRIDE));

		/* Found it! */
		if (lstat (try_path, &statbuf) == 0 && S_ISREG (statbuf.st_mode))
			return try_path;

		/* Warning, you have reached the end of the conveyor!
		 * Ignore overrides beyond .conf itself.
		 */
		if (source == last_source)
			break;
	}

	if (try_path)
		nih_free (try_path);

	return NULL;
}


/**
 * Convert a configuration file name to an override file name and vice
 * versa.
 *
 * For example, if @path is "foo.conf", this function will return
 * "foo.override", whereas if @path is "foo.override", it will return
 * "foo.conf".
 *
 * @parent: parent of returned path,
 * @path: path to a configuration file.
 *
 * Returns: newly allocated toggled path, or NULL on error.
 **/
static inline char *
toggle_conf_name (const void     *parent,
		 const char     *path)
{
	char *new_path;
	char *ext;
	char *new_ext;
	size_t len;

	ext = strrchr (path, '.');
	if (!ext)
		return NULL;

	new_ext = IS_CONF_EXT_STD (ext)
		? CONF_EXT_OVERRIDE
		: CONF_EXT_STD;

	len = strlen (new_ext);

	new_path = NIH_MUST (nih_strndup (parent, path, (ext - path) + len));

	memcpy (new_path + (ext - path), new_ext, len);

	return new_path;
}


/**
 * conf_init:
 *
 * Initialise the conf_sources list.
 **/
void
conf_init (void)
{
	if (! conf_sources)
		conf_sources = NIH_MUST (nih_list_new (NULL));
}

/**
 * conf_destroy:
 *
 * Clear: the conf_sources list.
 **/
void
conf_destroy (void)
{
	if (conf_sources)
		nih_free (conf_sources);
}

/**
 * conf_source_new:
 * @parent: parent of new block,
 * @path: path to source,
 * @type: type of source.
 *
 * Allocates and returns a new ConfSource structure for the given @path;
 * @type indicates whether this @path is a file or directory and what type
 * of files are within the directory.
 *
 * The returned structure is automatically added to the conf_sources list.
 *
 * Configuration is not parsed immediately, instead you must call
 * conf_source_reload() on this source to set up any watches and load the
 * current configuration.  Normally you would set up all of the sources and
 * then call conf_reload() which will load them all.
 *
 * If @parent is not NULL, it should be a pointer to another allocated
 * block which will be used as the parent for this block.  When @parent
 * is freed, the returned block will be freed too.
 *
 * Returns: newly allocated ConfSource structure or NULL if
 * insufficient memory.
 **/
ConfSource *
conf_source_new (const void     *parent,
		 const char     *path,
		 ConfSourceType  type)
{
	ConfSource *source;

	nih_assert (path != NULL);

	conf_init ();

	source = nih_new (parent, ConfSource);
	if (! source)
		return NULL;

	nih_list_init (&source->entry);

	source->path = nih_strdup (source, path);
	if (! source->path) {
		nih_free (source);
		return NULL;
	}

	source->type = type;
	source->watch = NULL;
	source->session = NULL;

	source->flag = FALSE;
	source->files = nih_hash_string_new (source, 0);
	if (! source->files) {
		nih_free (source);
		return NULL;
	}

	nih_alloc_set_destructor (source, nih_list_destroy);

	nih_list_add (conf_sources, &source->entry);

	return source;
}

/**
 * conf_file_new:
 * @source: configuration source,
 * @path: path to file.
 *
 * Allocates and returns a new ConfFile structure for the given @source,
 * with @path indicating which file it is.
 *
 * The returned structure is automatically placed in the @source's files hash
 * and the flag of the returned ConfFile will be set to that of the @source.
 *
 * Returns: newly allocated ConfFile structure or NULL if insufficient memory.
 **/
ConfFile *
conf_file_new (ConfSource *source,
	       const char *path)
{
	ConfFile *file;

	nih_assert (source != NULL);
	nih_assert (path != NULL);

	file = nih_new (source, ConfFile);
	if (! file)
		return NULL;

	nih_list_init (&file->entry);

	file->path = nih_strdup (file, path);
	if (! file->path) {
		nih_free (file);
		return NULL;
	}

	file->source = source;
	file->flag = source->flag;
	file->data = NULL;

	nih_alloc_set_destructor (file, conf_file_destroy);

	nih_hash_add (source->files, &file->entry);

	return file;
}


/**
 * conf_reload:
 *
 * Reloads configuration sources.
 *
 * Watches on new configuration sources are established so that future
 * changes will be automatically detected with inotify.  Then for both
 * new and existing sources, the current state is parsed.
 *
 * All ConfFiles are recreated as part of the reload. If the JobClass
 * associated with a ConfSource has no Job instances, the JobClass is
 * recreated and added to the job_classes hash.
 *
 * However, if a JobClass has running instances at reload time, although
 * a new ConfSource *and* a new JobClass are created, the new JobClass
 * (called the "best") will *NOT* be added to the job_classes hash until
 * the last running instance has finished. At this point, the "registered"
 * JobClass will be removed from the hash (when job_class_reconsider()
 * is called by job_change_state()) and replaced by the "best" (newest)
 * JobClass.
 *
 * Any errors are logged through the usual mechanism, and not returned,
 * since some configuration may have been parsed; and it's possible to
 * parse no configuration without error.
 **/
void
conf_reload (void)
{
	conf_init ();

	NIH_LIST_FOREACH (conf_sources, iter) {
		ConfSource *source = (ConfSource *)iter;

		if (conf_source_reload (source) < 0) {
			NihError *err;

			err = nih_error_get ();
			if (err->number != ENOENT)
				nih_error ("%s: %s: %s", source->path,
					_("Unable to load configuration"),
					err->message);
			nih_free (err);
		}
	}
}

/**
 * conf_source_reload:
 * @source: configuration source to reload.
 *
 * Reloads the given configuration @source.
 *
 * If not already established, an inotify watch is created so that future
 * changes to this source are automatically detected and parsed.  For files,
 * this watch is actually on the parent directory, since we need to watch
 * out for editors that rename over the top, etc.
 *
 * We then parse the current state of the source.  The flag member is
 * toggled first, and this is propagated to all new and modified files and
 * items that we find as a result of parsing.  Once done, we scan for
 * anything with the wrong flag, and delete them.
 *
 * Returns: zero on success, negative value on raised error.
 **/
int
conf_source_reload (ConfSource *source)
{
	NihList deleted;
	int     ret;

	nih_assert (source != NULL);

	nih_info (_("Loading configuration from %s"), source->path);

	/* Toggle the flag so we can detect deleted files and items. */
	source->flag = (! source->flag);

	/* Reload the source itself. */
	switch (source->type) {
	case CONF_FILE:
		ret = conf_source_reload_file (source);
		break;
	case CONF_DIR:
	case CONF_JOB_DIR:
		ret = conf_source_reload_dir (source);
		break;
	default:
		nih_assert_not_reached ();
	}

	/* Scan for files that have been deleted since the last time we
	 * reloaded; these are simple to detect, as they will have the wrong
	 * flag.
	 *
	 * We take them out of the files list and then we can delete the
	 * attached jobs and free the file.  We can't just do this from
	 * the one loop because to delete the jobs, we need to be able
	 * to iterate the sources and files.
	 */
	nih_list_init (&deleted);
	NIH_HASH_FOREACH_SAFE (source->files, iter) {
		ConfFile *file = (ConfFile *)iter;

		if (file->flag != source->flag)
			nih_list_add (&deleted, &file->entry);
	}
	NIH_LIST_FOREACH_SAFE (&deleted, iter) {
		ConfFile *file = (ConfFile *)iter;

		nih_info (_("Handling deletion of %s"), file->path);
		nih_unref (file, source);
	}

	return ret;
}

/**
 * conf_source_reload_file:
 * @source: configuration source to reload.
 *
 * Reloads the configuration file specified by @source.
 *
 * If not already established, an inotify watch is created on the parent
 * directory so that future changes to the file are automatically detected
 * and parsed.  It is the parent directory because we need to watch out for
 * editors that rename over the top, etc.
 *
 * Returns: zero on success, negative value on raised error.
 **/
static int
conf_source_reload_file (ConfSource *source)
{
	NihError *err = NULL;
	nih_local char *override_path = NULL;

	struct stat statbuf;

	nih_assert (source != NULL);
	nih_assert (source->type == CONF_FILE);

	/* this function should only be called for standard
	 * configuration files.
	 */
	if (! source->watch) {
		nih_local char *dpath = NULL;
		char           *dname;

		dpath = NIH_MUST (nih_strdup (NULL, source->path));
		dname = dirname (dpath);

		source->watch = nih_watch_new (source, dname, FALSE, FALSE,
					       (NihFileFilter)conf_file_filter,
					       (NihCreateHandler)conf_create_modify_handler,
					       (NihModifyHandler)conf_create_modify_handler,
					       (NihDeleteHandler)conf_delete_handler,
					       source);

		/* If successful mark the file descriptor close-on-exec,
		 * otherwise stash the error for comparison with a later
		 * failure to parse the file.
		 */
		if (source->watch) {
			nih_io_set_cloexec (source->watch->fd);
		} else {
			err = nih_error_steal ();
		}
	}

	/* Parse the file itself.  If this fails, then we can discard the
	 * inotify error, since this one will be better.
	 */
	if (conf_reload_path (source, source->path, NULL) < 0) {
		if (err)
			nih_free (err);

		return -1;
	}

	/* We were able to parse the file, but were not able to set up an
	 * inotify watch.  This isn't critical, so we just warn about it,
	 * unless this is simply that inotify isn't supported, in which case
	 * we do nothing.
	 */
	if (err) {
		if (err->number != ENOSYS)
			nih_warn ("%s: %s: %s", source->path,
				  _("Unable to watch configuration file"),
				  err->message);

		nih_free (err);
	}

	if (! is_conf_file_std (source->path))
		return 0;

	override_path = toggle_conf_name (NULL, source->path);

	if (lstat (override_path, &statbuf) != 0)
		return 0;

	nih_debug ("Updating configuration for %s from %s",
		  source->path, override_path);
	if (conf_reload_path (source, source->path, override_path) < 0) {
		if (err)
			nih_free (err);

		return -1;
	}

	return 0;
}

/**
 * conf_source_reload_dir:
 * @source: configuration source to reload.
 *
 * Reloads the configuration directory specified by @source.
 *
 * If not already established, an inotify watch is created on the directory
 * so that future changes to the structure or files within it are
 * automatically parsed.  This has the side-effect of parsing the current
 * tree.
 *
 * Otherwise we walk the tree ourselves and parse all files that we find,
 * propagating the value of the flag member to all files so that deletion
 * can be detected by the calling function.
 *
 * Returns: zero on success, negative value on raised error.
 **/
static int
conf_source_reload_dir (ConfSource *source)
{
	NihError *err = NULL;

	nih_assert (source != NULL);
	nih_assert (source->type != CONF_FILE);

	if (! source->watch) {
		source->watch = nih_watch_new (source, source->path,
					       TRUE, TRUE,
					       (NihFileFilter)conf_dir_filter,
					       (NihCreateHandler)conf_create_modify_handler,
					       (NihModifyHandler)conf_create_modify_handler,
					       (NihDeleteHandler)conf_delete_handler,
					       source);

		/* If successful, the directory tree will have been walked
		 * already; so just mark the file descriptor close-on-exec
		 * and return; otherwise we'll try and walk ourselves, so
		 * stash the error for comparison.
		 */
		if (source->watch) {
			nih_io_set_cloexec (source->watch->fd);
			return 0;
		} else {
			err = nih_error_steal ();
		}
	}

	/* We're either performing a mandatory reload, or we failed to set
	 * up an inotify watch; walk the directory tree the old fashioned
	 * way.  If this fails too, then we can discard the inotify error
	 * since this one will be better.
	 */
	if (nih_dir_walk (source->path, (NihFileFilter)conf_dir_filter,
			  (NihFileVisitor)conf_file_visitor, NULL,
			  source) < 0) {
		if (err)
			nih_free (err);

		return -1;
	}

	/* We were able to walk the directory, but were not able to set up
	 * an inotify watch.  This isn't critical, so we just warn about it,
	 * unless this is simply that inotify isn't supported, in which case
	 * we do nothing.
	 */
	if (err) {
		if (err->number != ENOSYS)
			nih_warn ("%s: %s: %s", source->path,
				  _("Unable to watch configuration directory"),
				  err->message);

		nih_free (err);
	}

	return 0;
}


/**
 * conf_file_filter:
 * @source: configuration source,
 * @path: path to check,
 * @is_dir: TRUE if @path is a directory.
 *
 * When we watch the parent directory of a file for changes, we receive
 * notification about all changes to that directory.  We only care about
 * those that affect the path in @source, and the path that we're watching,
 * so we use this function to filter out all others.
 *
 * Returns: FALSE if @path matches @source, TRUE otherwise.
 **/
static int
conf_file_filter (ConfSource *source,
		  const char *path,
		  int         is_dir)
{
	nih_assert (source != NULL);
	nih_assert (path != NULL);

	if (! strcmp (source->path, path))
		return FALSE;

	if (! strcmp (source->watch->path, path))
		return FALSE;

	return TRUE;
}

/**
 * conf_dir_filter:
 * @source: configuration source,
 * @path: path to check,
 * @is_dir: TRUE of @path is a directory.
 *
 * This is the file filter used for the jobs directory, we only care
 * about paths with particular extensions (see IS_CONF_EXT).
 *
 * Directories that match the nih_file_ignore() function are also ignored.
 *
 * Returns: FALSE if @path ends in ".conf" or ".override",
 * or is the original source, TRUE otherwise.
 **/
static int
conf_dir_filter (ConfSource *source,
		 const char *path,
		 int         is_dir)
{
	nih_assert (source != NULL);
	nih_assert (path != NULL);

	if (! strcmp (source->path, path))
		return FALSE;

	if (is_dir)
		return nih_file_ignore (NULL, path);

	if (is_conf_file (path))
		return FALSE;

	return TRUE;
}

/**
 * conf_load_path_with_override:
 * @source: configuration source
 * @conf_path: path to config file
 *
 * Loads given @conf_path as a config file in a given @source. Then it
 * finds an override file. If an override file is found it applies it
 * as well.
 **/
static void
conf_load_path_with_override (ConfSource *source,
			      const char *conf_path)
{
	int                     ret = 0;
	const char   *error_path = NULL;
	char      *override_path = NULL;
	nih_local char *job_name = NULL;

	nih_assert (source != NULL);
	nih_assert (conf_path != NULL);

	/* reload conf file */
	nih_debug ("Loading configuration file %s", conf_path);
	ret = conf_reload_path (source, conf_path, NULL);
	if (ret < 0) {
		error_path = conf_path;
		goto error;
	}

	job_name = conf_to_job_name (source->path, conf_path);
	override_path = conf_get_best_override (job_name, source);
	if (! override_path)
		return;

	/* overlay override settings */
	nih_debug ("Loading override file %s for %s", conf_path, override_path);
	ret = conf_reload_path (source, conf_path, override_path);
	if (ret < 0) {
		error_path = override_path;
		goto error;
	}
	nih_free (override_path);
	return;

error:
	{
		NihError *err;

		err = nih_error_get ();
		nih_error ("%s: %s: %s", error_path,
			   _("Error while loading configuration file"),
			   err->message);
		nih_free (err);
		if (override_path)
			nih_free (override_path);
		return;
	}
}


/**
 * conf_create_modify_handler:
 * @source: configuration source,
 * @watch: NihWatch for source,
 * @path: full path to modified file,
 * @statbuf: stat of @path.
 *
 * This function will be called whenever a file is created in a directory
 * that we're watching, moved into the directory we're watching, or is
 * modified.  This works for both directory and file sources, since the
 * watch for the latter is on the parent and filtered to only return the
 * path that we're interested in.
 *
 * After checking that it was a regular file that was changed, we reload it;
 * we expect this to fail sometimes since the file may be only partially
 * written.
 **/
static void
conf_create_modify_handler (ConfSource  *source,
			    NihWatch    *watch,
			    const char  *path,
			    struct stat *statbuf)
{
	ConfFile *file = NULL;
	char *config_path = NULL;
	nih_local char *job_name = NULL;

	nih_assert (source != NULL);
	nih_assert (watch != NULL);
	nih_assert (path != NULL);

	/* note that symbolic links are ignored */
	if (statbuf && ! S_ISREG (statbuf->st_mode))
		return;

	/* ignore non-config file changes */
	if (! is_conf_file (path))
		return;

        /* For config file, load it and it's override file */
	if (is_conf_file_std (path)) {
		conf_load_path_with_override (source, path);
		return;
	}

	/* For override files, reload all matching conf+override combos */
	job_name = conf_to_job_name (source->path, path);
	NIH_LIST_FOREACH (conf_sources, iter) {
		ConfSource *source = (ConfSource *)iter;

		if (source->type == CONF_FILE)
			continue;

		config_path = NIH_MUST (nih_sprintf (NULL, "%s/%s%s", source->path, job_name, CONF_EXT_STD));
		file = (ConfFile *)nih_hash_lookup (source->files, config_path);
		if (file) {
			/* Find its override file and reload both */
			conf_load_path_with_override (source, config_path);
		}
		nih_free (config_path);
	}

	return;
}

/**
 * conf_delete_handler:
 * @source: configuration source,
 * @watch: NihWatch for source,
 * @path: full path to deleted file.
 *
 * This function will be called whenever a file is removed or moved out
 * of a directory that we're watching.  This works for both directory and
 * file sources, since the watch for the latter is on the parent and
 * filtered to only return the path that we're interested in.
 *
 * We lookup the file in our hash table, and if we can find it, perform
 * the usual deletion of it.
 **/
static void
conf_delete_handler (ConfSource *source,
		     NihWatch   *watch,
		     const char *path)
{
	ConfFile *file;
	nih_local char *new_path = NULL;

	nih_assert (source != NULL);
	nih_assert (watch != NULL);
	nih_assert (path != NULL);

	/* Lookup the file in the source.  If we haven't parsed it, this
	 * could actually mean that it was the top-level directory itself
	 * that was deleted, in which case we free the watch, otherwise
	 * it's probably a directory or something, so just ignore it.
	 */
	file = (ConfFile *)nih_hash_lookup (source->files, path);
	/* Note we have to be careful to consider deletion of directories too.
	 * This is handled implicitly by the override check which will return
	 * false if passed a directory in this case.
	 */
	if (! file && ! is_conf_file_override (path)) {
		if (! strcmp (watch->path, path)) {
			nih_warn ("%s: %s", source->path,
				  _("Configuration directory deleted"));
			nih_unref (source->watch, source);
			source->watch = NULL;
		}

		return;
	}

	/* non-override files (and directories) are the simple case, so handle
	 * them and leave.
	 */
	if (! is_conf_file_override (path)) {
		nih_unref (file, source);
		return;
	}

	/* Deleting override file is about the same as changing one.
	 * We need to iterate across all matching jobs and reload them
	 * with new "best" override file, if any.
	 */
	nih_debug ("Reloading configuration for matching configs on deletion of override (%s)",
		   path);
	conf_create_modify_handler (source, watch, path, NULL);
}

/**
 * conf_file_visitor:
 * @source: configuration source,
 * @dirname: top-level directory being walked,
 * @path: path found in directory,
 * @statbuf: stat of @path.
 *
 * This function is called when walking a directory tree for each file
 * found within it.
 *
 * After checking that it's a regular file, we reload it.
 *
 * Returns: always zero.
 **/
static int
conf_file_visitor (ConfSource  *source,
		   const char  *dirname,
		   const char  *path,
		   struct stat *statbuf)
{
	nih_assert (source != NULL);
	nih_assert (dirname != NULL);
	nih_assert (path != NULL);
	nih_assert (statbuf != NULL);

	if (! S_ISREG (statbuf->st_mode))
		return 0;

	if (is_conf_file_std (path))
		conf_load_path_with_override (source, path);
	
	return 0;      
}


/**
 * conf_reload_path:
 * @source: configuration source,
 * @path: path of conf file to be reloaded.
 * @override_path: if not NULL and @path refers to a path associated with @source,
 * overlay the contents of @path into the existing @source entry for
 * @path. If FALSE, discard any existing knowledge of @path.
 *
 * This function is used to parse the file at @path (or @override_path) in the
 * context of the given configuration @source.  Necessary ConfFile structures
 * are allocated and attached to @source as appropriate.  CONF_FILE sources
 * always have a single ConfFile when the file exists.
 *
 * If the file has been parsed before, then the existing item is deleted and
 * freed if the file fails to load, or after the new item has been parsed.
 * Items are only reused between reloads if @override_path is
 * non-NULL.
 *
 * Physical errors are returned, parse errors are not.
 *
 * Returns: zero on success, negative value on raised error.
 **/
static int
conf_reload_path (ConfSource *source,
		  const char *path,
		  const char *override_path)
{
	ConfFile       *file = NULL;
	ConfFile       *orig = NULL;
	nih_local char *buf = NULL;
	nih_local char *name = NULL;
	size_t          len, pos, lineno;
	NihError       *err = NULL;
	const char     *path_to_load;

	nih_assert (source != NULL);
	nih_assert (path != NULL);

	path_to_load = (override_path ? override_path : path);

	/* If there is no corresponding override file, look up the old
	 * conf file in memory, and then free it. In cases of failure,
	 * we discard it anyway, so there's no particular reason
	 * to keep it around anymore.
	 *
	 * Notes:
	 *
	 * - If @override_path has been specified, do not free the file
	 *   if found, since we want to _update_ the existing entry.
	 * - Freeing a ConfFile does _not_ necessarily free its associated
	 *   JobClass.
	 */
	orig = (ConfFile *)nih_hash_lookup (source->files, path);
	if (! override_path && orig) {
		/* Found an existing ConfFile. We will free this, but
		 * just not yet since iff that ConfFiles associated JobClass
		 * does not have any running instances, freeing the
		 * ConfFile will cause the original JobClass associated
		 * with this ConfFile to be destroyed. But if the JobClass
		 * had referenced any events via it's 'start on' EventOperator tree, 
		 * the JobClasses destruction could lead to the Events
		 * being destroyed _before_ the about-to-be-created
		 * replacement JobClass gets a chance to reference those
		 * same events (assuming its 'start on' EventOperator tree
		 * contains nodes specifying the same event names as
		 * those in the original JobClasses).
		 *
		 * As such, we simply remove the ConfFile from its
		 * parent ConfSources hash, create the new ConfFile and
		 * JobClass, give the new JobClass a chance to be the
		 * registered JobClass, and finally allow the original
		 * ConfFile to be destroyed.
		 *
		 * If this is not done, reloading a configuration
		 * mid-way through the boot sequence could lead to a
		 * hung system as the new JobClasses will wait forever
		 * for events to be emitted that have already been
		 * destroyed.
		 */
		nih_list_remove (&orig->entry);
	}

	/* Read the file into memory for parsing, if this fails we don't
	 * bother creating a new ConfFile structure for it and bail out
	 * now.
	 */
	buf = nih_file_read (NULL, path_to_load, &len);
	if (! buf) {
		if (! override_path && orig) {
			/* Failed to reload the file from disk in all
			 * likelihood because the configuration file was
			 * deleted.
			 *
			 * Allow the ConfFile to be cleaned up taking
			 * its JobClass (and possibly events that
			 * JobClass was referencing) with it.
			 */
			nih_unref (orig, source);
		}

		return -1;
	}

	/* Create a new ConfFile structure (if no @override_path specified) */
	file = (ConfFile *)nih_hash_lookup (source->files, path);
	if (! file)
		file = NIH_MUST (conf_file_new (source, path));

	pos = 0;
	lineno = 1;

	switch (source->type) {
	case CONF_FILE:
	case CONF_DIR:
		/* Simple file of options; usually no item attached to it. */
		if (override_path) {
			nih_debug ("Updating configuration for %s from %s",
					path, override_path);
		} else {
			nih_debug ("Loading configuration from %s %s",
					(source->type == CONF_DIR ? "directory" : "file"), path);
		}

		if (parse_conf (file, buf, len, &pos, &lineno) < 0)
			err = nih_error_get ();

		break;
	case CONF_JOB_DIR:

		name = conf_to_job_name (source->path, path);

		/* Create a new job item and parse the buffer to produce
		 * the job definition.
		 */
		if (override_path) {
			nih_debug ("Updating %s (%s) with %s",
					name, path, override_path);
		} else {
			nih_debug ("Loading %s from %s", name, path);
		}

		file->job = parse_job (NULL, source->session, file->job,
				name, buf, len, &pos, &lineno);

		/* Allow the original ConfFile which has now been replaced to be
		 * destroyed which will also cause the original JobClass to be
		 * freed.
		 */
		if (file->job) {
			job_class_consider (file->job);
		} else {
			err = nih_error_get ();
		}

		break;
	default:
		nih_assert_not_reached ();
	}

	/* Finally, allow the original ConfFile to be destroyed without
	 * affecting the new JobClass.
	 */
	if (! override_path && orig)
		nih_unref (orig, source);

	/* Deal with any parsing errors that occurred; we don't consider
	 * these to be hard failures, which means we can warn about them
	 * here and give the path and line number along with the warning.
	 */
	if (err) {
		switch (err->number) {
		case NIH_CONFIG_EXPECTED_TOKEN:
		case NIH_CONFIG_UNEXPECTED_TOKEN:
		case NIH_CONFIG_TRAILING_SLASH:
		case NIH_CONFIG_UNTERMINATED_QUOTE:
		case NIH_CONFIG_UNTERMINATED_BLOCK:
		case NIH_CONFIG_UNKNOWN_STANZA:
		case PARSE_ILLEGAL_INTERVAL:
		case PARSE_ILLEGAL_EXIT:
		case PARSE_ILLEGAL_UMASK:
		case PARSE_ILLEGAL_NICE:
		case PARSE_ILLEGAL_OOM:
		case PARSE_ILLEGAL_LIMIT:
		case PARSE_EXPECTED_EVENT:
		case PARSE_EXPECTED_OPERATOR:
		case PARSE_EXPECTED_VARIABLE:
		case PARSE_MISMATCHED_PARENS:
			nih_error ("%s:%zi: %s", path_to_load, lineno, err->message);
			nih_free (err);
			err = NULL;
			break;
		}
	}

	/* If we had any unknown error from parsing the file, raise it again
	 * and return an error condition.
	 */
	if (err)
		return -1;

	return 0;
}


/**
 * conf_file_destroy:
 * @file: configuration file to be destroyed.
 *
 * Handles the replacement and deletion of a configuration file, ensuring
 * that @file is removed from the containing linked list and that the item
 * attached to it is destroyed if not currently in use.
 *
 * Normally used or called from an nih_alloc() destructor so that the list
 * item is automatically removed from its containing list when freed.
 *
 * Returns: zero.
 **/
int
conf_file_destroy (ConfFile *file)
{
	nih_assert (file != NULL);

	nih_list_destroy (&file->entry);

	switch (file->source->type) {
	case CONF_FILE:
	case CONF_DIR:
		break;
	case CONF_JOB_DIR:
		if (! file->job)
			break;

		/* Mark the job to be deleted when it stops, in case
		 * it cannot be deleted here.
		 */
		file->job->deleted = TRUE;

		/* Check whether the job is the current one with that name;
		 * if it is, try and replace it.  If it wasn't the current
		 * job, or isn't after replacement, we can free it now.
		 */
		if (job_class_reconsider (file->job)) {
			nih_debug ("Destroyed unused job %s", file->job->name);
			nih_free (file->job);
		}

		break;
	default:
		nih_assert_not_reached ();
	}

	return 0;
}


/**
 * conf_select_job:
 * @name: name of job class to locate,
 * @session: session class name belongs to.
 *
 * Select the best available class of a job named @name from the registered
 * configuration sources.
 *
 * Returns: Best available job class or NULL if none available.
 **/
JobClass *
conf_select_job (const char *name, const Session *session)
{
	nih_assert (name != NULL);

	conf_init ();

	NIH_LIST_FOREACH (conf_sources, iter) {
		ConfSource *source = (ConfSource *)iter;

		if (source->type != CONF_JOB_DIR)
			continue;

		if (source->session != session)
			continue;

		NIH_HASH_FOREACH (source->files, file_iter) {
			ConfFile *file = (ConfFile *)file_iter;

			if (! file->job)
				continue;

			if (! strcmp (file->job->name, name))
				return file->job;
		}
	}

	return NULL;
}

/**
 * conf_source_serialise:
 * @source: ConfSource to serialise.
 *
 * Convert @source into a JSON representation for serialisation.
 * Caller must free returned value using json_object_put().
 *
 * Returns: JSON-serialised ConfSource object, or NULL on error.
 **/
json_object *
conf_source_serialise (const ConfSource *source)
{
	json_object      *json;
	json_object      *json_files;
	int               session_index;

	nih_assert (source);
	nih_assert (conf_sources);

	json = json_object_new_object ();
	if (! json)
		return NULL;

	json_files = json_object_new_array ();
	if (! json_files)
		goto error;

	session_index = session_get_index (source->session);
	if (session_index < 0)
		goto error;

	if (! state_set_json_int_var (json, "session", session_index))
		goto error;

	if (! state_set_json_string_var_from_obj (json, source, path))
		goto error;

	if (! state_set_json_enum_var (json,
				conf_source_type_enum_to_str,
				"type", source->type))
		goto error;

	/* 'watch' does not need to be serialised - it gets recreated
	 * when conf_source_new() is called on deserialisation.
	 */

	if (! state_set_json_int_var_from_obj (json, source, flag))
		goto error;

	/* Add array of ConfFile names to represent the files hash */
	NIH_HASH_FOREACH (source->files, file_iter) {
		ConfFile *file = (ConfFile *)file_iter;
		json_object *json_conf_file;

		json_conf_file = conf_file_serialise (file);
		if (! json_conf_file)
			goto error;

		json_object_array_add (json_files, json_conf_file);
	}

	json_object_object_add (json, "conf_files", json_files);

	return json;

error:
	json_object_put (json);
	return NULL;
}

/**
 * conf_source_serialise_all:
 *
 * Convert existing ConfSource objects to JSON representation.
 *
 * Returns: JSON object containing array of ConfSource objects,
 * or NULL on error.
 **/
json_object *
conf_source_serialise_all (void)
{
	json_object *json;

	conf_init ();

	json = json_object_new_array ();
	if (! json)
		return NULL;

	NIH_LIST_FOREACH (conf_sources, iter) {
		json_object  *json_source;
		ConfSource   *source = (ConfSource *)iter;

		json_source = conf_source_serialise (source);

		if (! json_source)
			goto error;

		json_object_array_add (json, json_source);
	}

	return json;

error:
	json_object_put (json);
	return NULL;
}

/**
 * conf_source_deserialise:
 * @parent: parent,
 * @json: JSON-serialised ConfSource object to deserialise.
 *
 * Create ConfSource from provided JSON and add to the
 * conf sources list.
 *
 * Returns: ConfSource object, or NULL on error.
 **/
ConfSource *
conf_source_deserialise (void *parent, json_object *json)
{
	ConfSource      *source = NULL;
	ConfSourceType   type = -1;
	Session         *session;
	int              session_index = -1;
	nih_local char  *path = NULL;

	nih_assert (json);

	if (! state_check_json_type (json, object))
		goto error;

	if (! state_get_json_int_var (json, "session", session_index))
		goto error;

	if (session_index < 0)
		goto error;

	session = session_from_index (session_index);

	if (! state_get_json_string_var_strict (json, "path", NULL, path))
		goto error;

	if (! state_get_json_enum_var (json,
				conf_source_type_str_to_enum,
				"type", type))
		goto error;

	source = conf_source_new (parent, path, type);
	if (! source)
		goto error;

	source->session = session;

	if (! state_get_json_int_var_to_obj (json, source, flag))
		goto error;

	if (conf_file_deserialise_all (source, json) < 0)
		goto error;

	return source;

error:
	if (source)
		nih_free (source);

	return NULL;
}

/**
 * conf_source_deserialise_all:
 *
 * @json: root of JSON-serialised state.
 *
 * Convert JSON representation of ConfSources back into ConfSource objects.
 *
 * Returns: 0 on success, -1 on error.
 **/
int
conf_source_deserialise_all (json_object *json)
{
	ConfSource *source = NULL;

	nih_assert (json);

	conf_init ();

	nih_assert (NIH_LIST_EMPTY (conf_sources));

	if (! json_object_object_get_ex (json, "conf_sources", &json_conf_sources))
		goto error;

	if (! state_check_json_type (json_conf_sources, array))
		goto error;

	for (int i = 0; i < json_object_array_length (json_conf_sources); i++) {
		json_object  *json_source;

		json_source = json_object_array_get_idx (json_conf_sources, i);
		if (! json_source)
			goto error;

		if (! state_check_json_type (json_source, object))
			goto error;

		source = conf_source_deserialise (NULL, json_source);

		if (! source)
			continue;
	}

	return 0;

error:
	if (source)
		nih_free (source);

	return -1;
}

/**
 * conf_source_type_enum_to_str:
 *
 * @type: ConfSourceType.
 *
 * Convert ConfSourceType to a string representation.
 *
 * Returns: string representation of @type, or NULL if not known.
 **/
const char *
conf_source_type_enum_to_str (ConfSourceType type)
{
	state_enum_to_str (CONF_FILE, type);
	state_enum_to_str (CONF_DIR, type);
	state_enum_to_str (CONF_JOB_DIR, type);

	return NULL;
}

/**
 * conf_source_type_str_to_enum:
 *
 * @type: string ConfSourceType value.
 *
 * Convert @expect back into an enum value.
 *
 * Returns: ConfSourceType representing @type, or -1 if not known.
 **/
ConfSourceType
conf_source_type_str_to_enum (const char *type)
{
	nih_assert (type);

	state_str_to_enum (CONF_FILE, type);
	state_str_to_enum (CONF_DIR, type);
	state_str_to_enum (CONF_JOB_DIR, type);

	return -1;
}

/**
 * conf_file_serialise:
 * @file: ConfFile to serialise.
 *
 * Convert @file into a JSON representation for serialisation.
 * Caller must free returned value using json_object_put().
 *
 * Returns: JSON-serialised ConfFile object, or NULL on error.
 **/
json_object *
conf_file_serialise (const ConfFile *file)
{
	json_object  *json;
	json_object  *json_job_class;
	JobClass     *registered;
	int           session_index;
	ssize_t       conf_source_index;

	nih_assert (file);

	json = json_object_new_object ();
	if (! json)
		return NULL;

	if (! state_set_json_string_var_from_obj (json, file, path))
		goto error;

	conf_source_index = conf_source_get_index (file->source);
	if (conf_source_index < 0)
		goto error;

	if (! state_set_json_int_var (json, "conf_source", conf_source_index))
		goto error;

	if (! state_set_json_int_var_from_obj (json, file, flag))
		goto error;

	if (! file->job) {
		/* File exists on disk but contains invalid
		 * (unparseable) syntax, and hence no associated JobClass.
		 * Thus, simply encode the ConfFile without a class.
		 *
		 * Deserialisation is handled automatically since
		 * JobClasses are deserialised by directly iterating
		 * through all JobClass'es found in the JSON. Here,
		 * there simply won't be a JobClass to deserialise.
		 */
		goto out;
	}

	/*
	 * Ignore the "best" JobClass associated with this ConfFile
	 * (file->job) since it won't be serialised.
	 *
	 * Instead look up the currently registered JobClass and
	 * reference that. This ensures that best == registered for the
	 * re-exec. This may change though immediately after re-exec
	 * when conf_reload() gets called.
	 *
	 * See job_class_serialise_all() for further details.
	 */
	registered = job_class_get_registered (file->job->name,
			file->job->session);

	if (! registered)
		goto error;

	/* Create a reference to the registered job class in the JSON by
	 * encoding the name and session index. We do this rather than
	 * simply encoding an index number for the JobClass since
	 * job_classes is a hash and it is safer should a re-exec
	 * result from an upgrade to NIH, say, where its hashing
	 * algorithm changed meaning the index may be unreliable once
	 * the job_classes hash was created post-re-exec.
	 */
	json_job_class = json_object_new_object ();
	if (! json_job_class)
		goto error;

	if (! state_set_json_string_var (json_job_class,
				"name",
				registered->name))
		goto error;

	session_index = session_get_index (registered->session);
	if (session_index < 0)
		goto error;

	if (! state_set_json_int_var (json_job_class,
				"session",
				session_index))
		goto error;

	json_object_object_add (json, "job_class", json_job_class);

out:
	return json;

error:
	json_object_put (json);
	return NULL;
}

/**
 * conf_file_deserialise:
 * @source: ConfSource,
 * @json: JSON-serialised ConfFile object to deserialise.
 *
 * Create ConfFile from provided JSON and add to the
 * conf sources list.
 *
 * Returns: ConfFile object, or NULL on error.
 **/
ConfFile *
conf_file_deserialise (ConfSource *source, json_object *json)
{
	ConfFile        *file = NULL;
	nih_local char  *path = NULL;

	nih_assert (json);

	if (! state_check_json_type (json, object))
		goto error;

	if (! state_get_json_string_var_strict (json, "path", NULL, path))
		goto error;

	file = conf_file_new (source, path);
	if (! file)
		goto error;

	/* Note that the associated JobClass is not handled at this
	 * stage: it can't be since the JobClasses haven't been deserialised
	 * yet. As such, the ConfFile->JobClass link is dealt with in
	 * job_class_deserialise_all().
	 */
	file->job = NULL;

	if (! state_get_json_int_var_to_obj (json, file, flag))
		goto error;

	return file;

error:
	if (file)
		nih_free (file);

	return NULL;
}

/**
 * conf_file_deserialise_all:
 *
 * @source: ConfSource,
 * @json: root of JSON-serialised state.
 *
 * Convert JSON representation of ConfFiles back into ConfFile objects.
 *
 * Returns: 0 on success, -1 on error.
 **/
int
conf_file_deserialise_all (ConfSource *source, json_object *json)
{
	json_object  *json_conf_files;
	ConfFile     *file = NULL;

	nih_assert (source);
	nih_assert (json);

	conf_init ();

	if (! json_object_object_get_ex (json, "conf_files", &json_conf_files))
		goto error;

	if (! state_check_json_type (json_conf_files, array))
		goto error;

	for (int i = 0; i < json_object_array_length (json_conf_files); i++) {
		json_object  *json_file;

		json_file = json_object_array_get_idx (json_conf_files, i);
		if (! json_file)
			goto error;

		if (! state_check_json_type (json_file, object))
			goto error;

		file = conf_file_deserialise (source, json_file);

		if (! file)
			goto error;
	}

	return 0;

error:
	if (file)
		nih_free (file);

	return -1;
}

/**
 * conf_source_get_index:
 *
 * @source: ConfSource to search for.
 *
 * Returns: index of @source in the conf sources list,
 * or -1 if not found.
 **/
ssize_t
conf_source_get_index (const ConfSource *source)
{
	ssize_t i = 0;

	nih_assert (source);

	conf_init ();

	NIH_LIST_FOREACH (conf_sources, iter) {
		ConfSource *s = (ConfSource *)iter;

		if (! strcmp (source->path, s->path)
				&& source->session == s->session)
			return i;
		i++;
	}

	return -1;
}

/**
 * conf_file_find:
 *
 * @name: name of ConfFile (without dirname and extension),
 * @session: session ConfFile belongs to.
 *
 * Find the ConfFile with name @name in session @session.
 *
 * Returns: ConfFile or NULL if not found.
 **/
ConfFile *
conf_file_find (const char *name, const Session *session)
{
	nih_local char  *basename = NULL;

	nih_assert (name);

	conf_init ();

	/* There can only be one ConfFile per session with the same
	 * basename.
	 */
	basename = NIH_MUST (nih_sprintf (NULL, "/%s%s",
				name, CONF_EXT_STD));

	NIH_LIST_FOREACH (conf_sources, iter) {
		ConfSource *source = (ConfSource *)iter;

		if (source->session != session)
			continue;

		NIH_HASH_FOREACH (source->files, file_iter) {
			ConfFile *file = (ConfFile *)file_iter;
			char     *match;
			char     *slash;

			match = strstr (file->path, basename);
			slash = strrchr (file->path, '/');

			if (match && match == slash)
				return file;
		}
	}

	return NULL;
}

#ifdef DEBUG

void
debug_show_event_operator (EventOperator *oper)
{
	nih_local char *env = NULL;

	nih_assert (oper);

	if (oper->env) env = state_collapse_env ((const char **)oper->env);

	nih_debug ("EventOperator %p: type='%s', value=%d, name='%s', event='%s', env='%s'",
			oper,
			oper->type == EVENT_MATCH ? "EVENT_MATCH"
			: oper->type == EVENT_AND ? "EVENT_AND"
			: "EVENT_OR",
			oper->value,
			oper->name,
			oper->event ? oper->event->name : "",
			env ? env : "");
}

void
debug_show_event_operators (EventOperator *root)
{
	nih_assert (root);

	NIH_TREE_FOREACH_POST (&root->node, iter) {
		EventOperator *oper = (EventOperator *)iter;

		debug_show_event_operator (oper);
	}
}

size_t
debug_count_list_entries (const NihList *list)
{
	size_t i = 0;
	NIH_LIST_FOREACH (list, iter) {
		i++;
	}
	return i;
}

size_t
debug_count_hash_entries (const NihHash *hash)
{
	size_t i = 0;
	NIH_HASH_FOREACH_SAFE (hash, iter) {
		i++;
	}
	return i;
}

void
debug_show_job_class (const JobClass *class)
{
	nih_local char *start_on = NULL;
	nih_local char *stop_on = NULL;

	nih_assert (class);

	nih_debug ("JobClass %p: name='%s', path='%s', task=%d, "
			"respawn=%d, console=%x, deleted=%d, debug=%d",
			class, class->name, class->path, class->task,
			class->respawn, class->console, class->deleted, class->debug);

	if (class->start_on) start_on = event_operator_collapse (class->start_on);
	if (class->stop_on)  stop_on = event_operator_collapse (class->stop_on);

	nih_debug ("\tstart_on=%p (%s), stop_on=%p (%s), emits=%p, process=%p",
			class->start_on, start_on ? start_on : "",
			class->stop_on, stop_on ? stop_on : "",
			class->emits, class->process);

	for (int i = 0; i < PROCESS_LAST; i++) {
		if (class->process[i]) {
			nih_debug ("Process[%d]=%p: script=%d, cmd='%s'",
					i, class->process[i],
					class->process[i]->script,
					class->process[i]->command);
		} else {
			nih_debug ("Process[%d]=%p",
					i, class->process[i]);
		}


	}

	nih_debug ("\tauthor='%s', description='%s'",
			class->author, class->description);

	if (class->env && *class->env) {
		nih_local char *env = state_collapse_env ((const char **)class->env);
		nih_debug ("\tenv:%s", env);
	} else {
		nih_debug ("\tenv: none.");
	}

	if (class->export && *class->export) {
		nih_local char *export = state_collapse_env ((const char **)class->export);
		nih_debug ("\texport:%s", export);
	} else {
		nih_debug ("\texport: none");
	}

	debug_show_jobs (class->instances);
}

void
debug_show_job_classes (void)
{
	nih_debug ("job_classes:");

	NIH_HASH_FOREACH_SAFE (job_classes, iter) {
		JobClass *job = (JobClass *)iter;
		debug_show_job_class (job);
	}
}

void
debug_show_job (const Job *job)
{
	nih_local char *env = NULL;
	nih_local char *start_env = NULL;
	nih_local char *stop_env = NULL;
	nih_local char *stop_on = NULL;

	nih_assert (job);

	if (job->env)
		env = state_collapse_env ((const char **)job->env);

	if (job->start_env)
		start_env = state_collapse_env ((const char **)job->start_env);

	if (job->stop_env)
		stop_env = state_collapse_env ((const char **)job->stop_env);

	if (job->stop_on)
		stop_on = event_operator_collapse (job->stop_on);

	nih_debug ("Job %p: name=%s, class=%p (%s), path=%s, env='%s'"
			"start_env='%s', stop_env='%s', stop_on='%s', "
			"goal=%d, state=%d, failed=%d, exit_status=%d",
			job,
			job->name ? job->name : "",
			job->class, job->class->name,
			job->path,
			env ? env : "",
			start_env ? start_env : "",
			stop_env ? stop_env : "",
			stop_on ? stop_on : "",
			job->goal,
			job->state,
			job->failed,
			job->exit_status);
}

void
debug_show_jobs (const NihHash *instances)
{
	if (! instances)
		return;

	nih_debug ("jobs:");

	NIH_HASH_FOREACH (instances, iter) {
		Job *job = (Job *)iter;
		debug_show_job (job);
	}
}

void
debug_show_event (const Event *event)
{
	nih_assert (event);

	nih_debug ("Event %p: name='%s', progress=%x, failed=%d, "
			"blockers=%d, blocking=%p",
			event, event->name, event->progress, event->failed,
			event->blockers, (void *)&event->blocking);
}

void
debug_show_events (void)
{
	nih_assert (events);

	NIH_LIST_FOREACH (events, iter) {
		Event *event = (Event *)iter;

		debug_show_event (event);
	}
}

void
debug_show_conf_file (const ConfFile *file)
{
	nih_assert (file);

	nih_debug ("ConfFile %p: path='%s', source=%p, flag=%x, job=%p",
			file, file->path, file->source, file->flag, file->job);

	/* Some ConfFile objects won't have any JobClass details, for example,
	 * the ConfFile object associated with "/etc/init.conf".
	 */
	if (! file->job) {
		nih_debug ("ConfFile %p: job: no JobClass object.", file);
		return;
	}

	nih_debug ("ConfFile %p: job:", file);
	debug_show_job_class (file->job);
}

void
debug_show_conf_source (const ConfSource *source)
{
	nih_assert (source);

	nih_debug ("ConfSource %p: path='%s', type=%x, flag=%x",
			source, source->path, source->type, source->flag);

	nih_debug ("ConfSource %p files (%d):", source,
			(int)debug_count_hash_entries (source->files));

	NIH_HASH_FOREACH (source->files, file_iter) {
		ConfFile *file = (ConfFile *)file_iter;
		debug_show_conf_file (file);
	}
}

void
debug_show_conf_sources (void)
{
	nih_assert (conf_sources);

	nih_debug ("conf_sources:");

	NIH_LIST_FOREACH (conf_sources, iter) {
		ConfSource *source = (ConfSource *)iter;
		debug_show_conf_source (source);
	}
}

#endif /* DEBUG */
