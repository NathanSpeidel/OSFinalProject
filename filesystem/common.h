#ifndef COMMON_H
#define COMMON_H

uint64_t measure_read(int fd, int blocksize, int nblocks);
uint64_t measure_seek(int fd, int blocksize, int* blockindices, int nblocks);

#endif
