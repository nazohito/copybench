#define _LARGEFILE64_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
  int r;
  if (argc != 3) {
    fprintf(stderr, "usage: %s from_file to_file", argv[0]);
    exit(0);
  }

  /* from */
  int from = open(argv[1], O_RDONLY, 0644);
  assert(from >= 0);

  struct stat st_buf;
  r = fstat(from, &st_buf);
  assert(r >= 0);
  off_t size = st_buf.st_size;

  void *from_mmap = mmap(NULL, size, PROT_READ, MAP_PRIVATE, from, 0);
  assert(from_mmap >= 0);

#if USE_MADVISE
  r = madvise(from_mmap, size, MADV_SEQUENTIAL);
  assert(r == 0);
#endif

  /* to */
  int to = open(argv[2], O_CREAT|O_RDWR, st_buf.st_mode);
  assert(to >= 0);

  int v = 0;
  r = lseek(to, size - sizeof(int), 0L);
  assert(r >= 0);
  ssize_t nwrites = write(to, (&v), sizeof(int));
  assert(nwrites == sizeof(int));

  void *to_mmap = mmap(NULL, size, PROT_WRITE, MAP_SHARED, to, 0);
  assert(to_mmap >= 0);

#if USE_MADVISE
  r = madvise(to_mmap, size, MADV_SEQUENTIAL);
  assert(r == 0);
#endif

  /* copy */
  memcpy(to_mmap, from_mmap, size);

  r = msync(to_mmap, size, MS_SYNC);
  assert(r == 0);

  r = ftruncate(to, size);
  assert(r == 0);

  /* check size */
  struct stat st_buf2;
  r = fstat(to, &st_buf2);
  assert(r >= 0);
  off_t size2 = st_buf2.st_size;
  assert(size == size2);

  /* finalize */
  close(from);
  close(to);

  return 0;
}
