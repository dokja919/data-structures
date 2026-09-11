#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <stddef.h>

typedef struct BItem BItem;
typedef struct BinaryHeap BPriorityQueue;

BPriorityQueue *b_create(void);
void b_destroy(BPriorityQueue *heap);
void b_insert(BPriorityQueue *heap, int priority);
int b_extract(BPriorityQueue *heap);
size_t b_size(BPriorityQueue *heap);

void b_heapify(BItem *items, size_t size, size_t parent);

#endif