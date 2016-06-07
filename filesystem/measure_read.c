#define _GNU_SOURCE 

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "common.h"

int* sequencial_indices(int N) {
  int* indices = malloc(sizeof(int)*N);
  for (int i = 0; i < N; ++i) {
    indices[i] = i;
  }
  return indices;
}

// Probably not the best way to do it, but should be good enough
void random_order(int *indices, int N) {
  int tmp;
  for (int i = 0; i < 2*N; ++i) {
    // Pick 2 indices and swap them
    int j = rand() % N;
    int k = rand() % N;
    tmp = indices[j];
    indices[j] = indices[k];
    indices[k] = tmp;
  }
}

int main(int argc, char** argv) {
  if (argc != 6) {
    fprintf(stderr, "Usage: %s <s/r> <filename> <block size> <nblocks> <trials>\n", argv[0]);
    exit(1);
  }
  uint64_t blocksize = atoi(argv[3]);
  uint64_t nblocks   = atoi(argv[4]);
  int trials    = atoi(argv[5]);

  int fd = open(argv[2], O_RDONLY, O_DIRECT | O_SYNC);
  if (fd < 0) {
    fprintf(stderr, "cannot open file %s\n", argv[2]);
    exit(1);
  }
  
  int* blockindices = NULL;

  fprintf(stderr, "Processor cycles to read %s ", argv[2]);
  if (argv[1][0] == 's')
    fprintf(stderr, "sequentially\n");
  else if (argv[1][0] == 'r') {
    fprintf(stderr, "randomly\n");
    blockindices = sequencial_indices(nblocks);
    random_order(blockindices, nblocks);
  } 
  else {
    fprintf(stderr, "read mode must either be 's' or 'r'\n");
    exit(1);
  }
      
  uint64_t dt;
  int tenpercent = trials/10;
  fprintf(stderr, "Starting trails: ");
  for (int i = 0; i < trials; ++i) {

    if (blockindices)
      dt = measure_seek(fd, blocksize, blockindices, nblocks);
    else
      dt = measure_read(fd, blocksize, nblocks);

    printf("%ld\n", dt);
    if (i % tenpercent == 0) {
      fprintf(stderr, "*");
      fflush(stderr);
    }
  }
  fprintf(stderr, "\n");

  close(fd);

  if (blockindices)
    free(blockindices);

  return 0;
}
