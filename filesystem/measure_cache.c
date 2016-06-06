#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <x86intrin.h>
#include <inttypes.h>

uint64_t measure_seek(int fd, char* buffer, int blocksize, int nblocks) {
  uint64_t start, end;

  // Go to the beginning of the file
  lseek(fd, 0, SEEK_SET);

  start = _rdtsc();
  for (int i = 0; i < nblocks; ++i)
    read(fd, buffer, blocksize);
  end = _rdtsc();

  return end - start;
}

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
  char* buffer = malloc(blocksize);

  printf("Processor cycles to read %ld x %ld bytes\n",
         nblocks, blocksize);
  uint64_t dt;
  int tenpercent = trials/10;
  fprintf(stderr, "Starting trails: ");
  for (int i = 0; i < trials; ++i) {
    dt = measure_seek(fd, buffer, blocksize, nblocks);
    printf("%ld\n", dt);
    if (i % tenpercent == 0) {
      fprintf(stderr, "*");
      fflush(stderr);
    }
  }
  fprintf(stderr, "\n");

  free(buffer);
  close(fd);

  return 0;
}
