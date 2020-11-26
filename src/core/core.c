#include <stdlib.h>
#include "core.h"
#include "../db/connector.h"

static unsigned long size;
static struct List *adjacency_list;

int core_initialize(void) {
    connector_initialize();
    int ret = connector_read(&size, &adjacency_list);
    if (ret) {
        return 1;
    }
    return 0;
}

int core_finalize(void) {
    connector_finalize();
    struct List *iter = adjacency_list;
    for (unsigned long i = 0; i < size; ++i, list_finalize(iter++));
    free(adjacency_list);
}

int core_log(FILE *fout) {
    if (!fout) {
        return 1;
    }
    struct List *iter = adjacency_list;
    for (unsigned long i = 0; i < size; ++i, ++iter) {
        fprintf(fout, "city: %s\nlongitude: %lf\nlatitude: %lf\n",
                iter->name,
                iter->longitude,
                iter->latitude);
        for (struct ListNode *j = iter->head; j; j = j->next) {
            fprintf(fout, "to: %s\ndist: %lf\ncost: %lf\n",
                    adjacency_list[j->idx].name, j->dist, j->cost);
        }
    }
    return 0;
}

int core_idx_to_str(unsigned long idx, const char **out) {
    if (idx >= size) {
        return 1;
    }
    *out = adjacency_list[idx].name;
    return 0;
}
