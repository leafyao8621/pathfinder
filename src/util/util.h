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
    char *name;
    double longitude, latitude;
    struct ListNode *head, *tail;
};

struct HeapNode {
    double key;
    unsigned long idx;
    struct HeapNode *parent, *left, *right;
};

struct Heap {
    unsigned long size;
    struct HeapNode *head;
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
int list_remove(struct List *list,
                unsigned long idx);
int list_finalize(struct List *list);
int list_log(struct List *list,
             FILE *fout);

#endif
