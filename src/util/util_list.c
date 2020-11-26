#include <stdlib.h>
#include <string.h>
#include "util.h"

int list_initialize(struct List *list,
                    const char *name,
                    double longitude,
                    double latitude) {
    if (!list || !name) {
        return 1;
    }
    size_t len = strlen(name);
    if (!(list->name = malloc(len + 1))) {
        return 2;
    }
    list->longitude = longitude;
    list->latitude = latitude;
    strcpy(list->name, name);
    list->head = 0;
    list->tail = 0;
    return 0;
}

int list_finalize(struct List *list) {
    if (!list) {
        return 1;
    }
    free(list->name);
    for (struct ListNode *i = list->head; i;) {
        struct ListNode *temp = i->next;
        free(i);
        i = temp;
    }
    return 0;
}

int list_push_back(struct List *list,
                   unsigned long idx,
                   double dist,
                   double cost) {
    if (!list) {
        return 1;
    }
    struct ListNode *temp = malloc(sizeof(struct ListNode));
    if (!temp) {
        return 2;
    }
    temp->idx = idx;
    temp->dist = dist;
    temp->cost = cost;
    temp->next = 0;
    if (!list->tail) {
        list->head = temp;
    } else {
        list->tail->next = temp;
    }
    temp->prev = list->tail;
    list->tail = temp;
    return 0;
}

int list_log(struct List *list,
             FILE *fout) {
    if (!list || !fout) {
        return 1;
    }
    fprintf(fout, "Name: %s\n", list->name);
    for (struct ListNode *i = list->head; i; i = i->next) {
        fprintf(fout, "idx: %lu\ndist: %lf\ncost: %lf\n",
                i->idx, i->dist, i->cost);
    }
    return 0;
}
