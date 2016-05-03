#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <inttypes.h>

int main() {
    int N = 21;
    int64_t stride = sysconf(_SC_PAGESIZE);
    int64_t bytes = stride * (1 << N);
    char* buffer  = malloc(bytes);
    char* dst = buffer;
    for (int64_t i = 0; i < stride; ++i) {
            printf("\r%6.2f%%", 100.0*i/stride);
            fflush(stdout);
        char val = (char)(rand() % 0xff);
        for (int64_t j = 0; j < (1 << N); ++j) {
            buffer[j*stride + i]  = val + j;
        }
    }
    int tmp;
    for (int64_t i = 0; i < (1 << 10); ++i) {
        tmp += buffer[(rand() % bytes)];
    }
    printf("%d\n", tmp);

    free(buffer);
    return 0;
}
