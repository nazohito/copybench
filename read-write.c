#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/fadvise.h>

#define BUF_SIZE 8192

int main(int argc, char **argv)
{
  int r;
  char buf[BUF_SIZE];

  if (argc < 3) {
    fprintf(stderr, "usage: %s src out\n", argv[0]);
    exit(EXIT_SUCCESS);
  }

  char *src  = argv[1];
  char *dest = argv[2];
  assert(strcmp(src, dest) != 0);

  int srcfd = open(src, O_RDONLY, 0644);
  assert(srcfd >= 0);

#if USE_FADVISE
  r = posix_fadvise(srcfd, 0, 0, POSIX_FADV_SEQUENTIAL);
  assert(r == 0);
  r = posix_fadvise(srcfd, 0, 0, POSIX_FADV_NOREUSE);
  assert(r == 0);
#endif

  /* get permission */
  struct stat st_buf;
  r = fstat(srcfd, &st_buf);
  assert(r >= 0);

  int destfd = open(dest, O_WRONLY | O_CREAT, st_buf.st_mode);
  assert(destfd >= 0);

  /* copy */
  int n = 0;
  while ((n = read(srcfd, buf, sizeof(buf))) > 0) {
    char *p = &buf[0];
    const char * const endp = buf + n;
    while (p < endp) {
      ssize_t num_bytes = write(destfd, p, endp - p);
      assert(num_bytes > 0);
      p += num_bytes;
    }
  }
  assert(n == 0);

  fsync(destfd);

  /* check size */
  struct stat st_buf2;
  r = fstat(destfd, &st_buf2);
  assert(r >= 0);
  assert(st_buf.st_size == st_buf2.st_size);

  /* finalize */
  close(destfd);
  close(srcfd);

  exit(EXIT_SUCCESS);
}
