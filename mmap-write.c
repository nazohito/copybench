#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
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
  int to = open(argv[2], O_CREAT | O_WRONLY, 0666);
  assert(to >= 0);

  /* copy */
  char *p = from_mmap;
  const char * const endp = (char*)from_mmap + size;
  while (p < endp) {
    ssize_t num_bytes = write(to, p, endp - p);
    assert(num_bytes > 0);
    p += num_bytes;
  }
  assert(p == endp);

  fsync(to);

  /* check size */
  struct stat st_buf2;
  r = fstat(to, &st_buf2);
  assert(r >= 0);
  off_t size2 = st_buf2.st_size;
  assert(size == size2);

  /* finalize */
  close(to);
  close(from);

  return 0;
}
