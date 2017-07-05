/*
 * This software copyright 1997 Joshua M. Yelon.
 * Debian Maintainer and new Features:
 *   copyright 1999 Bernd Eckenfels, Germany, ecki@debian.org 
 *   (see debian/changelog)
 *
 * Distribution subject to the terms of the GPL.
 *
 */

#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <dirent.h>
#include <stdio.h>

int wide = 0;
int needinode = 0;

typedef int (*qcmp)(const void *, const void *);

typedef struct mapping *mapping;

struct mapping
{
  unsigned int fs, inode, offs, pid, lo, hi;
  char *path; int valid;
};

mapping maptab_data;
size_t  maptab_fill;
size_t  maptab_size;

static void maptab_expand(void)
{
  size_t bytes;
  maptab_size = maptab_size*2 + 100;
  bytes = maptab_size * sizeof(struct mapping);
  maptab_data = (mapping)realloc(maptab_data, bytes);
  if (maptab_data == NULL) {
  	fprintf(stderr, "Error: realloc returned null, possibly out of memory? Exiting.\n");
  	exit(2);
  }
}

static dev_t convert_to_dev_t(char *str)
{
  unsigned int result = 0;
  while (*str) {
    if      ((*str>='0')&&(*str<='9')) result=result*16+(*str)-'0';
    else if ((*str>='a')&&(*str<='f')) result=result*16+(*str)-'a'+10;
    else if ((*str>='A')&&(*str<='F')) result=result*16+(*str)-'A'+10;
    str++;
  }
  return result;
}

static void read_proc(void)
{
  unsigned int nread, pid, lo, hi, offs; unsigned long inode; char *p;
  char dev[80], buff[PATH_MAX + 300], path[PATH_MAX + 300];
  DIR *d; struct dirent *ent; FILE *f;
  mapping m;
  d = opendir("/proc");
  if (d==0) { perror("/proc"); exit(1); }
  while (1) {
    ent = readdir(d);
    if (ent==0) break;
    pid = strtol(ent->d_name, NULL, 10);
    if (pid==0) continue;
    sprintf(buff,"/proc/%d/maps",pid);
    f = fopen(buff, "r");
    if (f==0) continue;
    while (fgets(buff,sizeof(buff),f)) {
      p = strchr(buff,'-');
      if (p) *p=' ';
      path[0] = '\0';
      if ((strlen(buff) == 10) && (strcmp(buff, " (deleted)") == 0))
        continue;
      nread = sscanf(buff,"%x %x %*s %x %s %lu %s",&lo,&hi,&offs,dev,&inode,path);
      if (nread<5) { 
	fprintf(stderr,"I don't recognize format of /proc/%d/maps. (nread=%d)\n", pid, nread);
	exit(1);
      }
      if (maptab_fill == maptab_size) maptab_expand();
      m = maptab_data + maptab_fill;
      m->fs    = convert_to_dev_t(dev);
      m->inode = inode;
      m->offs  = offs;
      m->pid   = pid;
      m->lo    = lo;
      m->hi    = hi;
      m->valid = 1;
      if (path && path[0]) {
	m->path = strdup(path);
      } else {
      	sprintf(buff,"[%04x]:%lu",m->fs,inode);
      	m->path  = strdup(buff);
      	needinode = 1;
      }
      maptab_fill++;
    }
    fclose(f);
  }
  closedir(d);
}

static int sort_by_pid(mapping m1, mapping m2)
{
  int delta;
  delta = m1->pid - m2->pid;
  if (delta) return delta;
  delta = m1->lo - m2->lo;
  if (delta) return delta;
  delta = m1->hi - m2->hi;
  if (delta) return delta;
  delta = m1->fs - m2->fs;
  if (delta) return delta;
  delta = m1->inode - m2->inode;
  return delta;
}

static int sort_by_inode(mapping m1, mapping m2)
{
  int delta;
  delta = m1->fs - m2->fs;
  if (delta) return delta;
  delta = m1->inode - m2->inode;
  if (delta) return delta;
  delta = m1->pid - m2->pid;
  return delta;
}

static void register_path(unsigned int fs, unsigned int inode, char *path, int valid)
{
  size_t i;
  mapping m; char *copy=0;
  for (i=0; i<maptab_fill; i++) {
    m = maptab_data + i;
    if ((m->path)&&(m->path[0]=='[')&&(m->fs == fs)&&(m->inode == inode)) {
      if (copy==0) copy=strdup(path);
      m->path = copy;
      m->valid = valid;
    }
  }
}

static void scan_directory(char *dir)
{
  DIR *d; struct dirent *ent;
  struct stat info; int ok;
  char full[8192];
  d = opendir(dir);
  if (d==0) return;
  while ((ent=readdir(d))!=0) {
    sprintf(full,"%s/%s", dir, ent->d_name);
    ok = stat(full, &info);
    if (ok<0) continue;
    register_path(info.st_dev, info.st_ino, full, S_ISREG(info.st_mode));
  }
  closedir(d);
}

static void scan_fpath(const char *fn)
{
  char *p;
  FILE *f = fopen(fn, "r");
  char buff[1024];
  if (f==0) {
    fprintf(stderr,"Cannot open /etc/memstat.conf\n");
    exit(1);
  }
  while (fgets(buff, 1023, f)) {
    if (buff[0]=='#') continue;
    p = strchr(buff, '\n');
    if (p) *p=0;
    scan_directory(buff);
  }
  fclose(f);
}

static void printline(char *str)
{
  int len;
  if (wide) goto done;
  len = strlen(str);
  if (len<=79) goto done;
  str[76]='.';
  str[77]='.';
  str[78]='.';
  str[79]=0;
done:
  printf("%s\n", str);
}

static void summarize_usage(void)
{
  char buffer[8192];
  unsigned int grand, i, offs, fs, inode, pid, lo, hi, scan, tail, total;
  mapping m; char *exe;
  grand = 0;
  qsort(maptab_data, maptab_fill, sizeof(struct mapping), (qcmp)sort_by_pid);
  for (offs=0; offs<maptab_fill; offs=scan) {
    pid = maptab_data[offs].pid;
    total = 0; exe = 0;
    for (scan=offs; scan<maptab_fill; scan++) {
      m = maptab_data + scan;
      if (m->pid != pid) break;
      if (m->fs || m->inode) {
	if (exe==0) exe=m->path;
      } else { total += (m->hi - m->lo); }
    }
    sprintf(buffer, "%7dk: PID %5d (%s)", total/1024, pid, exe);
    printline(buffer);
    grand += total;
  }
  qsort(maptab_data, maptab_fill, sizeof(struct mapping), (qcmp)sort_by_inode);
  for (offs=0; offs<maptab_fill; offs=scan) {
    m = maptab_data + offs;
    if (m->valid==0) { scan=offs+1; continue; }
    fs=m->fs; inode=m->inode; exe=m->path;
    if ((fs==0)&&(inode==0)) { scan=offs+1; continue; }
    lo = 0xFFFFFFFF; hi = 0;
    for (scan=offs; scan<maptab_fill; scan++) {
      m = maptab_data + scan;
      if ((m->fs!=fs)||(m->inode!=inode)) break;
      if (m->offs < lo) lo = m->offs;
      tail = m->offs + m->hi - m->lo;
      if (tail > hi) hi=tail;
    }
    sprintf(buffer,"%7dk: %s", (hi-lo)/1024, exe);
    pid=0;
    for (i=offs; i<scan; i++) {
      m = maptab_data + i;
      if (m->pid != pid) {
	pid = m->pid;
	sprintf(buffer+strlen(buffer), " %d", pid);
      }
    }
    printline(buffer);
    grand += (hi - lo);
  }
  printf("--------\n");
  printf("%7dk\n", grand/1024);
}

static void usage(char *prog)
{
  fprintf(stderr,"usage: %s [-w]\n", prog);
  exit(1);
}

int main(int argc, char **argv) {
  char *prog = argv[0];
  argc--; argv++;
  while (*argv) {
    if (strcmp(*argv,"-w")==0) { wide=1; argv++; }
    else usage(prog);
  }
  read_proc();
  if (needinode)
    scan_fpath("/etc/memstat.conf");
  summarize_usage();
  return(0);
}
