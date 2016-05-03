#include <x86intrin.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <inttypes.h>

int main(int argc, char** argv) {
    if (argc != 4) {
        printf("%s <log2 buffer size> <N reads> <output file>\n", argv[0]);
        exit(1);
    }

    int N = atoi(argv[1]);;
    int M = atoi(argv[2]);;

    // Setup buffer
    int64_t stride = sysconf(_SC_PAGESIZE);
    int64_t bytes = stride * (1 << N);
    char* buffer  = malloc(bytes);
    // Touch every page once
    for (int64_t j = 0; j < (1 << N); ++j) {
        buffer[j*stride]  = (char)(rand() % 0xff);
    }

    // Measure memory access time
    uint64_t* ts = malloc(sizeof(uint64_t)*M);
    uint64_t start, end;
    for (int64_t i = 0; i < M; ++i) {
        start = _rdtsc();
        buffer[i*stride + (rand() % stride)]  = (char)(rand() % 0xff);
        end = _rdtsc();
        ts[i] = end - start;
    }

    // Record data in a binary file
    FILE* f = fopen(argv[3], "wb");
    fwrite(ts, sizeof(uint64_t)*M, 1, f);
    fclose(f);
    free(buffer);
    free(ts);
    return 0;
}
