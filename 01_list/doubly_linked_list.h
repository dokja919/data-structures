#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stddef.h>

typedef int DLItem;
typedef struct DoublyLinkedList DLList;

void dl_insert_at(DLList *list, size_t pos, int value);
DLItem dl_delete_at(DLList *list, size_t pos);
DLItem dl_get(DLList *list, size_t pos);
size_t dl_size(DLList *list);
void dl_print(DLList *list);

DLList *dl_create(void);
void dl_destroy(DLList *list);

#endif
