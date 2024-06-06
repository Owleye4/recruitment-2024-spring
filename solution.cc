#include <cstdio>
#include <cstddef>
#include <cstdlib>
#include <omp.h>
#include <tbb/parallel_sort.h>

void optimized_pre_phase1(size_t) {}

void optimized_post_phase1() {}

void optimized_pre_phase2(size_t) {}

void optimized_post_phase2() {}

void optimized_do_phase1(float* data, size_t size) {
    tbb::parallel_sort(data, data + size)
}

void optimized_do_phase2(size_t* result, float* data, float* query, size_t size) {
#   pragma omp parallel for num_threads(128)
    for (size_t i = 0; i < size; ++i) {
        size_t l = 0, r = size;
        while (l < r) {
            size_t m = l + (r - l) / 2;
            if (data[m] < query[i]) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        result[i] = l;
    }
}
