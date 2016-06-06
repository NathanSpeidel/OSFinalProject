#define _GNU_SOURCE 

#include <stdlib.h>
#include <stdio.h>

#include <semaphore.h>
#include <unistd.h>
#include <string.h>

#include <fcntl.h>

#include <x86intrin.h>
#include <inttypes.h>

uint64_t measure_read(int fd, int blocksize, int nblocks) {
  uint64_t start, end;

  // Go to the beginning of the file
  lseek(fd, 0, SEEK_SET);

  char* buffer = malloc(blocksize);

  start = _rdtsc();
  for (int i = 0; i < nblocks; ++i)
    read(fd, buffer, blocksize);
  end = _rdtsc();

  free(buffer);

  return end - start;
}

sem_t* setup_barrier() {
  sem_t* barrier = sem_open("contention_barrier", O_CREAT|O_EXCL, 0600);
  if (barrier == SEM_FAILED) {
    perror("sem_open");
    exit(1);
  }
  return barrier;
}

void cleanup_barrier(sem_t* barrier) {
  if (sem_close(barrier) == -1) {
    perror("sem_close");
    exit(1);
  }

  if (sem_unlink("contention_barrier") == -1) {
    perror("sem_unlink");
    exit(1);
  }
}

void wait_for_children(int n) {
  int childret;
  for (int i = 1; i < n; ++i) {
    wait(&childret);
  }
}

void barrier_wait(int pid, sem_t* barrier) {
  if (pid)
    sem_post(barrier);
  else {
    sem_wait(barrier);
    sem_post(barrier);
  }
}

int main(int argc, char** argv) {
  if (argc != 5) {
    fprintf(stderr, "Usage: %s <nprocs> <file prefix> <blocksize> <nblocks>\n", argv[0]);
    exit(1);
  }
  int nprocs = atoi(argv[1]);
  char* fileprefix = argv[2];
  char* filename = malloc(strlen(fileprefix) + 10);

  int blocksize = atoi(argv[3]);
  int nblocks   = atoi(argv[4]);

  sem_t* barrier = setup_barrier();
  
  int cid = 0;
  int parent;
  for (int i = 1; i < nprocs; ++i) {
    cid = i;
    parent = fork();
    if (!parent)
      break;
  }
  if (parent)
    cid = 0;

  barrier_wait(parent, barrier);
  
  sprintf(filename, "%s%03d.raw", fileprefix, cid);
  //int fd = open(filename, O_RDONLY, O_DIRECT | O_SYNC);
  int fd = open(filename, O_RDONLY, O_SYNC);
  if (fd < 0) {
    fprintf(stderr, "cannot open file %s\n", argv[2]);
    exit(1);
  }
  uint64_t read_time = measure_read(fd, blocksize, nblocks);
  free(filename);

  printf("%lld ", read_time);
  if (!parent) {
    return 0;
  }

  wait_for_children(nprocs);
  printf("\n");

  cleanup_barrier(barrier);
  return 0;
}
