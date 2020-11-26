#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int heap_initialize(struct Heap *heap) {
    if (!heap) {
        return 1;
    }
    heap->size = 0;
    heap->root = 0;
    return 0;
}

static void swap(struct HeapNode *a, struct HeapNode *b) {
    double key = a->key;
    unsigned long idx = a->idx;
    a->key = b->key;
    a->idx = b->idx;
    b->key = key;
    b->idx = idx;
}

int heap_push_back(struct Heap *heap,
                   double key,
                   unsigned long idx) {
    if (!heap) {
        return 1;
    }
    struct HeapNode *temp = malloc(sizeof(struct HeapNode));
    temp->key = key;
    temp->idx = idx;
    temp->left = 0;
    temp->right = 0;
    ++(heap->size);
    unsigned long msk = 0x8000000000000000lu;
    for (; !(heap->size & msk); msk >>= 1);
    msk >>= 1;
    struct HeapNode *cur = heap->root;
    for (; msk > 1; msk >>= 1) {
        cur = (heap->size & msk) ? cur->right : cur->left;
    }
    temp->parent = cur;
    if (cur) {
        if (heap->size & msk) {
            cur->right = temp;
        } else {
            cur->left = temp;
        }
    } else {
        heap->root = temp;
    }
    for (;
         temp->parent && (temp->key < temp->parent->key);
         swap(temp, temp->parent), temp = temp->parent);
    return 0;
}

int heap_pop(struct Heap *heap) {
    if (!heap) {
        return 1;
    }
    if (!(heap->size)) {
        return 2;
    }
    unsigned long msk = 0x8000000000000000lu;
    for (; !(heap->size & msk); msk >>= 1);
    msk >>= 1;
    struct HeapNode *cur = heap->root;
    for (; msk > 1; msk >>= 1) {
        cur = (heap->size & msk) ? cur->right : cur->left;
    }
    struct HeapNode *temp = 0;
    if (msk) {
        if (heap->size & msk) {
            temp = cur->right;
            cur->right = 0;
        } else {
            temp = cur->left;
            cur->left = 0;
        }
        swap(heap->root, temp);
        free(temp);
        cur = heap->root;
        for(; cur->left;) {
            double min = cur->left->key;
            char right = 0;
            if (cur->right && cur->right->key <= cur->left->key) {
                min = cur->right->key;
                right = 1;
            }
            if (cur->key < min) {
                break;
            }
            if (right) {
                swap(cur, cur->right);
                cur = cur->right;
            } else {
                swap(cur, cur->left);
                cur = cur->left;
            }
        }
    } else {
        free(heap->root);
        heap->root = 0;
    }
    --(heap->size);
    return 0;
}
