#ifndef CIRCULAR_DOUBLY_LINKED_LIST_H
#define CIRCULAR_DOUBLY_LINKED_LIST_H

#include <stddef.h>

typedef int CDLItem;
typedef struct CircularDoublyLinkedList CDLList;

void cdl_insert(CDLList *list, size_t index, int value);
CDLItem cdl_delete(CDLList *list, size_t index);
CDLItem cdl_get(CDLList *list, size_t index);
size_t cdl_size(CDLList *list);
void cdl_print(CDLList *list);

CDLList *cdl_create(void);
void cdl_destroy(CDLList *list);

#endif
