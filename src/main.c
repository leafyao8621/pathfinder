#include <stdio.h>
#include "controller/controller.h"
// #include "core/core.h"
// #include "util/util.h"

int main(void) {
    controller_initialize();
    for (; controller_handle(););
    controller_finalize();
    // unsigned long size;
    // core_initialize(&size);
    // core_log(stdout);
    // double val;
    // unsigned long steps;
    // unsigned long *path;
    // int ret = core_find_path(1, 2, 0, &val, &steps, &path);
    // if (!ret) {
    //     printf("val: %lf\nsteps: %lu\n", val, steps);
    //     core_log_path(steps, path, stdout);
    //     core_free_path(path);
    // } else {
    //     if (ret < 0) {
    //         const char *from, *to;
    //         core_idx_to_str(4, &from);
    //         core_idx_to_str(2, &to);
    //         printf("no path from %s to %s\n", from, to);
    //     } else {
    //         puts("error");
    //     }
    // }
    // ret = core_find_path(4, 2, 0, &val, &steps, &path);
    // if (!ret) {
    //     printf("val: %lf\nsteps: %lu\n", val, steps);
    //     core_log_path(steps, path, stdout);
    //     core_free_path(path);
    // } else {
    //     if (ret < 0) {
    //         const char *from, *to;
    //         core_idx_to_str(4, &from);
    //         core_idx_to_str(2, &to);
    //         printf("no path from %s to %s\n", from, to);
    //     } else {
    //         puts("error");
    //     }
    // }
    // core_finalize();
    return 0;
}
