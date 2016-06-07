#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <x86intrin.h>
#include <inttypes.h>

#include "common.h"

int main(int argc, char** argv) {
  if (argc != 5) {
    fprintf(stderr, "Usage: %s <filename> <block size> <nblocks> <trials>\n", argv[0]);
    exit(1);
  }
  uint64_t blocksize = atoi(argv[2]);
  uint64_t nblocks   = atoi(argv[3]);
  int trials    = atoi(argv[4]);

  int fd = open(argv[1], O_RDONLY);
  if (fd < 0) {
    fprintf(stderr, "Cannot open file %s\n", argv[1]);
    exit(1);
  }

  uint64_t filesize = lseek(fd, 0, SEEK_END);
  fprintf(stderr, "Reading from file size %ld\n", filesize);

  if (filesize < nblocks*blocksize) {
    fprintf(stderr, "Cannot read %ld x %ld bytes from a %ld byte file\n",
            nblocks, blocksize, filesize);
    close(fd);
    exit(1);
  }

  printf("Processor cycles to read %ld x %ld bytes\n",
         nblocks, blocksize);
  uint64_t dt;
  int tenpercent = trials/10;
  fprintf(stderr, "Starting trails: ");
  for (int i = 0; i < trials; ++i) {
    dt = measure_read(fd, blocksize, nblocks);
    printf("%ld\n", dt);
    if (i % tenpercent == 0) {
      fprintf(stderr, "*");
      fflush(stderr);
    }
  }
  fprintf(stderr, "\n");

  close(fd);

  return 0;
}
