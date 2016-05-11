#include <math.h>
#include <x86intrin.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <inttypes.h>

typedef struct _Stats {
    double mean;
    double max;
    double min;
    double stdev;
} Statistics;

Statistics compute_stats(double* x, int N) {
    Statistics s;
    s.min = x[0];
    s.max = x[0];
    s.mean = 0.0;
    s.stdev = 0.0;

    for (int i = 0; i < N; ++i) {
        s.mean += x[i];
        if (x[i] < s.min) {
            s.min = x[i];
        }
        if (x[i] > s.max) {
            s.max = x[i];
        }
    }
    s.mean /= N;
    for (int i = 0; i < N; ++i) {
        s.stdev += pow(x[i] - s.mean, 2);
    }
    s.stdev /= (N-1);
    s.stdev = sqrt(s.stdev);

    return s;
}

void print_stats(Statistics stat, char* name) {
    printf( "%s: %e [%e, %e] ~%e\n"
            , name
            , stat.mean
            , stat.min
            , stat.max
            , stat.stdev
          );
}

uint64_t time_write_int(int* dst, int N) {
    uint64_t start, end;
    int tmp = rand() % 0xffff;
    start = _rdtsc();
    for (int i = 0; i < N; i++) {
        dst[i] = tmp;
    }
    end = _rdtsc();
    return end - start;
}

uint64_t time_write_char(char* dst, int N) {
    uint64_t start, end;
    int tmp = rand() % 0xff;
    start = _rdtsc();
    for (int i = 0; i < N; i++) {
        dst[i] = tmp;
    }
    end = _rdtsc();
    return end - start;
}

uint64_t time_read_int(int* src, int N) {
    int tmp;
    uint64_t start, end;
    start = _rdtsc();
    for (int i = 0; i < N; i++) {
        tmp = src[i];
    }
    end = _rdtsc();
    return end - start;
}

uint64_t time_read_char(char* src, int N) {
    char tmp;
    uint64_t start, end;
    start = _rdtsc();
    for (int i = 0; i < N; i++) {
        tmp = src[i];
    }
    end = _rdtsc();
    return end - start;
}

uint64_t time_write(int bytes, int stride) {
    char* dst = malloc(bytes);
    uint64_t dt = 0;
    if (stride == 4)
        dt = time_write_int((int*)dst, bytes/4);
    else if (stride == 1)
        dt = time_write_char(dst, bytes);
    else {
        printf("Manual read/write stride is either 1 (char) or 4 (int)\n");
        exit(1);
    }
    free(dst);
    return dt;
}

uint64_t time_read(int bytes, int stride) {
    char* src = malloc(bytes);
    uint64_t dt = 0;
    if (stride == 4)
        dt = time_read_int((int*)src, bytes/4);
    else if (stride == 1)
        dt = time_read_char(src, bytes);
    else {
        printf("Manual read/write stride is either 1 (char) or 4 (int)\n");
        exit(1);
    }
    free(src);
    return dt;
}

uint64_t time_copy(int bytes, int block_size) {
    if (block_size > bytes) {
        block_size = bytes;
    }
    int N = bytes / block_size;

    char* src = malloc(bytes);
    char* dst = malloc(bytes);
    memcpy(dst, src, block_size);
    memset(dst, 0, bytes);
    memset(src, N, bytes);

    int64_t start, end;

    char* d = dst;
    char* s = src;

    start = _rdtsc();
    for (int i = 0; i < N; ++i) {
        memcpy(d, s, block_size);
        d += block_size;
        s += block_size;
    }
    end = _rdtsc();
    free(src);
    free(dst);
    return end - start;
}

typedef uint64_t(*measure_func)(int bytes, int stride);

int main(int argc, char** argv) {
    if (argc != 5) {
        printf("%s <copy/read/write> <bytes> <block size> <trials>\n", argv[0]);
        exit(1);
    }

    measure_func f;
    if (strcmp(argv[1], "copy") == 0)
        f = time_copy;
    else if (strcmp(argv[1], "read") == 0)
        f = time_read;
    else if (strcmp(argv[1], "write") == 0)
        f = time_write;
    else {
        printf("Invalid comparison type: %s\n", argv[1]);
        exit(1);
    }

    int bytes  = atoi(argv[2]);
    int stride = atoi(argv[3]);
    int trials = atoi(argv[4]);

    double* dts = malloc(sizeof(double)*trials);

    for (int t = 0; t < trials; ++t) {
        dts[t] = (double)bytes/f(bytes, stride);
    }

    Statistics stats = compute_stats(dts, trials);
    print_stats(stats, argv[1]);

    return 0;
}

