#include <x86intrin.h>
#include <stdio.h>
#include <inttypes.h>

int main(int argc, char** argv) {

    if (argc < 4) {
        printf("%s <size> <stride> <max loads>\n", argv[0]);
        exit(1);
    }

    int size      = atoi(argv[1]);
    int stride    = atoi(argv[2]);
    int max_loads = atoi(argv[3]);

    // Create an array of pointers of length size
    int64_t* arr = malloc(sizeof(int64_t)*size);

    for (int i = 0; i < size; ++i) {
        arr[i] = (int64_t)(&arr[(i + stride) % size]);
    }

    int64_t* p = arr;
    int beg = 0;
    int end = 0;

    // start time
    beg = _rdtsc();
    for (int i = 0; i < max_loads; ++i) {
        p = (int64_t*)*p;
    }
    // end time
    end = _rdtsc();

    printf("%f\n", (float)(end - beg)/max_loads);

    return 0;
}
