#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>

struct ListNode {
    unsigned long idx;
    double dist;
    double cost;
    struct ListNode *prev, *next;
};

struct List {
    char *name, visited;
    double longitude, latitude, cur;
    struct ListNode *head, *tail;
};

struct HeapNode {
    double key;
    unsigned long idx;
    struct HeapNode *parent, *left, *right;
};

struct Heap {
    unsigned long size;
    struct HeapNode *root;
};

double calc_dist(double lon1, double lat1, double lon2, double lat2);
int list_initialize(struct List *list,
                    const char *name,
                    double longitude,
                    double latitude);
int list_push_back(struct List *list,
                   unsigned long idx,
                   double dist,
                   double cost);
int list_finalize(struct List *list);
int list_log(struct List *list,
             FILE *fout);
int heap_initialize(struct Heap *heap);
int heap_push_back(struct Heap *heap,
                   double key,
                   unsigned long idx);
int heap_pop(struct Heap *heap);

#endif
