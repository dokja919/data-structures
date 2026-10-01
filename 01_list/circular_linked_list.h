#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

#include <stddef.h>

typedef int CLItem;
typedef struct CircularLinkedList CLList;

void cl_insert_at(CLList *list, size_t index, int value);
CLItem cl_delete_at(CLList *list, size_t index);
CLItem cl_get(CLList *list, size_t index);
size_t cl_size(CLList *list);
void cl_print(CLList *list);

CLList *cl_create(void);
void cl_destroy(CLList *list);

#endif
