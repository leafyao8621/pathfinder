#include <stdio.h>
#include "controller/controller.h"
// #include "core/core.h"
// #include "util/util.h"

int main(void) {
    controller_initialize();
    for (; controller_handle(););
    controller_finalize();
    return 0;
}
