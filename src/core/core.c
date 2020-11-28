#include <stdlib.h>
#include "core.h"
#include "../db/connector.h"

static unsigned long size;
static double inf;
static struct List *adjacency_list;

int core_initialize(void) {
    connector_initialize();
    int ret = connector_read(&size, &inf, &adjacency_list);
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

int core_find_path(unsigned long from,
                   unsigned long to,
                   char dist,
                   double *val,
                   unsigned long *steps,
                   unsigned long **path) {
    if (!path) {
        return 1;
    }
    struct Heap rem;
    int ret = heap_initialize(&rem);
    if (ret) {
        return 2;
    }
    struct List *iter = adjacency_list;
    for (unsigned long i = 0; i < size; ++i, ++iter) {
        iter->visited = 0;
        iter->prev = -1;
        iter->cur = i == from ? 0 : inf;
        if (heap_push_back(&rem, iter->cur, i)) {
            heap_finalize(&rem);
            return 3;
        }
    }
    for (; rem.size && (rem.root->idx != to);) {
        double cur = rem.root->key;
        unsigned long idx = rem.root->idx;
        heap_pop(&rem);
        if (adjacency_list[idx].visited) {
            continue;
        }
        adjacency_list[idx].visited = 1;
        for (struct ListNode *i = adjacency_list[idx].head;
             i; i = i->next) {
            double new_val = dist ? cur + i->dist : cur + i->cost;
            if (!adjacency_list[i->idx].visited &&
                new_val < adjacency_list[i->idx].cur) {
                adjacency_list[i->idx].cur = new_val;
                adjacency_list[i->idx].prev = idx;
                if (heap_push_back(&rem, new_val, i->idx)) {
                    heap_finalize(&rem);
                    return 4;
                }
            }
        }
    }
    heap_finalize(&rem);
    // printf("%lf\n", adjacency_list[to].cur);
    *val = adjacency_list[to].cur;
    if (*val == inf) {
        return -1;
    }
    unsigned long steps_buf = 1;
    adjacency_list[to].next = -1;
    unsigned long next_idx = to;
    for (unsigned long i = adjacency_list[to].prev;
         i != -1;
         adjacency_list[i].next = next_idx,
         next_idx = i,
         i = adjacency_list[i].prev, ++steps_buf);
    *steps = steps_buf;
    *path = malloc(sizeof(unsigned long) * steps_buf);
    if (!*path) {
        return 5;
    }
    for (unsigned long i = from, *iter = *path;
         i != -1;
         *(iter++) = i,
         i = adjacency_list[i].next);
    return 0;
}

int core_free_path(unsigned long *path) {
    free(path);
}

int core_log_path(unsigned long steps, unsigned long *path, FILE *fout) {
    const char *buf;
    for (unsigned long i = 0, *iter = path; i < steps; ++i) {
        core_idx_to_str(path[i], &buf);
        fprintf(fout, "%s", buf);
        if (i < steps - 1) {
            fprintf(fout, "%s", "->");
        }
        fputc(10, fout);
    }
}
