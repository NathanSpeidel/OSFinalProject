#include <unistd.h>
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

uint64_t measure_seek(int fd, int blocksize, int* blockindices, int nblocks) {
  uint64_t start, end;

  // Go to the beginning of the file
  lseek(fd, 0, SEEK_SET);

  char* buffer = malloc(blocksize);

  start = _rdtsc();
  for (int i = 0; i < nblocks; ++i) {
    lseek(fd, blockindices[i]*blocksize, SEEK_SET);
    read(fd, buffer, blocksize);
  }
  end = _rdtsc();

  free(buffer);

  return end-start;
}
