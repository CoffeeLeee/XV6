#include "user/user.h"

void primes(int *fd);

int main(int agrc, int *argv[]) {
  int fd[2];
  pipe(fd);
  if (fork() == 0) {
    primes(fd);
  } else {
    close(fd[0]);
    for (int i = 2; i <= 35; ++i) {
      write(fd[1], (void *)&i, sizeof(i));
    }
    close(fd[1]);
    wait(0);
  }
  exit(0);
}


void primes(int *fd) {
  close(fd[1]);
  int num, prime;
  if (read(fd[0], (void *)&prime, sizeof(prime))) {
    printf("prime %d\n", prime);
  }
  if (read(fd[0], (void *)&num, sizeof(num))) {
    int fd1[2];
    pipe(fd1);
    if (fork() == 0) {
      primes(fd1);
    } else {
      close(fd1[0]);
      do {
        if (num % prime != 0) {
          write(fd1[1], (void *)&num, sizeof(int));
        }
      } while (read(fd[0], &num, sizeof(int)));
      close(fd1[1]);
      close(fd[0]);
      wait(0);
    }
  }
  exit(0);
}
