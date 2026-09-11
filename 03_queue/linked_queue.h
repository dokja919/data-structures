#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include <stdbool.h>
#include <stddef.h>

typedef int LItem;
typedef struct LinkedQueue LQueue;

void l_enqueue(LQueue *queue, int value);
LItem l_dequeue(LQueue *queue);
LItem l_peek(LQueue *queue);
bool l_is_empty(LQueue *queue);
size_t l_size(LQueue *queue);

LQueue *l_create(void);
void l_destroy(LQueue *queue);

#endif