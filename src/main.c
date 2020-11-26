#include <stdio.h>
#include "core/core.h"

int main(void) {
    core_initialize();
    core_log(stdout);
    core_finalize();
    return 0;
}
