#include <stdio.h>
#include "core/core.h"
// #include "util/util.h"

int main(void) {
    core_initialize();
    // core_log(stdout);
    double val;
    unsigned long steps;
    unsigned long *path;
    core_find_path(1, 2, 0, &val, &steps, &path);
    printf("val: %lf\nsteps: %lu\n", val, steps);
    core_log_path(steps, path, stdout);
    core_free_path(path);
    core_finalize();
    // struct Heap heap;
    // heap_initialize(&heap);
    // for (unsigned long i = 100; i > 0; --i) {
    //     heap_push_back(&heap, i, i);
    // }
    // for (; heap.size; heap_pop(&heap)) {
    //     printf("%lu %lf %lu\n", heap.size, heap.root->key, heap.root->idx);
    // }
    // struct List list;
    // list_initialize(&list, "shit", 0, 0);
    // for (unsigned long i = 0; i < 10; ++i) {
    //     list_push_back(&list, i, i, i);
    // }
    // list_log(&list, stdout);
    // list_finalize(&list);
    return 0;
}
