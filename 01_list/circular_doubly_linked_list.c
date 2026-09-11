#include "circular_doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _cdl_node {
    CDLItem data;
    struct _cdl_node *next;
    struct _cdl_node *prev;
} cdl_node;

struct CircularDoublyLinkedList {
    cdl_node *sentinel;
    size_t size;
};

static cdl_node *cdl_node_create(int value);
static void cdl_node_destroy(cdl_node *node);
static cdl_node *cdl_node_get(CDLList *list, size_t index);

CDLList *cdl_create(void)
{
    CDLList *list = malloc(sizeof(CDLList));
    if (list == NULL) {
        return NULL;
    }

    list->sentinel = cdl_node_create(0);
    if (list->sentinel == NULL) {
        free(list);
        return NULL;
    }
    list->sentinel->next = list->sentinel;
    list->sentinel->prev = list->sentinel;

    list->size = 0;

    return list;
}
void cdl_destroy(CDLList *list)
{
    if (list == NULL) {
        return;
    }
    while (list->size > 0) {
        cdl_delete(list, 0);
    }
    cdl_node_destroy(list->sentinel);
    free(list);
}
static cdl_node *cdl_node_get(CDLList *list, size_t index)
{
    if (list == NULL || index > list->size) {
        return NULL;
    }
    if (index == list->size) {
        return list->sentinel; // 센티널 반환
    }

    cdl_node *target = NULL;

    if (index < list->size / 2) {
        target = list->sentinel->next;

        for (size_t i = 0; i < index; i++) {
            target = target->next;
        }
    } else {
        target = list->sentinel->prev;

        for (size_t i = list->size - 1; i > index; i--) {
            target = target->prev;
        }
    }
    return target;
}
void cdl_insert(CDLList *list, size_t index, int value)
{
    if (list == NULL || index > list->size) {
        return;
    }

    cdl_node *new_node = cdl_node_create(value);
    if (new_node == NULL) {
        return;
    }

    cdl_node *next = cdl_node_get(list, index);
    if (next == NULL) {
        return;
    }
    cdl_node *prev = next->prev;
    prev->next = new_node;
    new_node->prev = prev;

    new_node->next = next;
    next->prev = new_node;

    list->size++;
}
static cdl_node *cdl_node_create(int value)
{
    cdl_node *new_node = malloc(sizeof(cdl_node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = value;
    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;
}
CDLItem cdl_delete(CDLList *list, size_t index)
{
    if (list == NULL || index >= list->size) {
        return 0;
    }
    cdl_node *target = cdl_node_get(list, index);
    if (target == NULL) {
        return 0;
    }
    cdl_node *prev = target->prev;
    cdl_node *next = target->next;

    prev->next = next;
    next->prev = prev;
    CDLItem data = target->data;
    cdl_node_destroy(target);

    list->size--;
    return data;
}
static void cdl_node_destroy(cdl_node *node)
{
    free(node);
}
CDLItem cdl_get(CDLList *list, size_t index)
{
    if (list == NULL || index >= list->size) {
        return 0;
    }
    return cdl_node_get(list, index)->data;
}
void cdl_print(CDLList *list)
{
    if (list == NULL || list->sentinel == NULL) {
        return;
    }
    cdl_node *current = list->sentinel->next;

    while (current != list->sentinel) {
        printf("<- %d ->", current->data);
        current = current->next;
    }

    printf("<- head\n");
}
size_t cdl_size(CDLList *list)
{
    return list ? list->size : 0;
}