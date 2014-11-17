#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <error.h>

void error_and_die(const char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

int main() {
  int r;

  const char *memname = "sample";
  const size_t region_size = sysconf(_SC_PAGE_SIZE);

  int fd = shm_open(memname, O_CREAT | O_TRUNC | O_RDWR, 0666);
  if (fd == -1)
    error_and_die("shm_open");

  r = ftruncate(fd, 4096*12);
  if (r != 0)
    error_and_die("ftruncate");

  void *ptr = mmap(0, 4096*12, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (ptr == MAP_FAILED)
  error_and_die("mmap");
  close(fd);
  pid_t pid = fork();

  if (pid == 0) {
    strcpy(ptr,"string");
    exit(0);
  }
  else {
    int status;
    waitpid(pid, &status, 0);
    printf("child wrote %s\n", (char *) ptr);
  }

  r = munmap(ptr, region_size);
  if (r != 0)
    error_and_die("munmap");

  r = shm_unlink(memname);
  if (r != 0)
    error_and_die("shm_unlink");

  return 0;
}
