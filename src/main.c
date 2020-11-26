#include <stdio.h>
// #include "core/core.h"
#include "util/util.h"

int main(void) {
    // core_initialize();
    // core_log(stdout);
    // core_finalize();
    struct Heap heap;
    heap_initialize(&heap);
    for (unsigned long i = 100; i > 0; --i) {
        heap_push_back(&heap, i, i);
    }
    for (; heap.size; heap_pop(&heap)) {
        printf("%lu %lf %lu\n", heap.size, heap.root->key, heap.root->idx);
    }
    return 0;
}
