#include "circular_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _cl_node {
    CLItem data;
    struct _cl_node *next;
} cl_node;

struct CircularLinkedList {
    cl_node *tail;
    size_t size;
};

static cl_node *cl_node_create(int value);
static void cl_node_destroy(cl_node *node);

static cl_node *cl_node_create(int value)
{
    cl_node *new_node = malloc(sizeof(cl_node));
    if (new_node == NULL) {
        return NULL;
    }

    new_node->data = value;
    new_node->next = NULL;

    return new_node;
}
static void cl_node_destroy(cl_node *node)
{
    free(node);
}
CLList *cl_create(void)
{
    CLList *list = malloc(sizeof(CLList));
    if (list == NULL) {
        return NULL;
    }

    list->size = 0;
    list->tail = NULL;

    return list;
}
void cl_destroy(CLList *list)
{
    if (list == NULL) {
        return;
    }

    while (list->tail) {
        cl_delete(list, 0);
    }
    free(list);
}
void cl_insert(CLList *list, size_t index, int value)
{
    if (list == NULL || index > list->size) {
        return;
    }
    cl_node *new_node = cl_node_create(value);
    if (new_node == NULL) {
        return;
    }
    if (list->tail == NULL) {
        new_node->next = new_node;
        list->tail = new_node;
    } else {
        cl_node *prev = list->tail;

        for (size_t i = 0; i < index; i++) {
            prev = prev->next;
        }
        new_node->next = prev->next;
        prev->next = new_node;

        if (prev == list->tail) {
            list->tail = new_node;
        }
    }
    list->size++;
}
CLItem cl_delete(CLList *list, size_t index)
{
    if (list == NULL || index >= list->size) {
        return 0;
    }
    cl_node *prev = list->tail;

    for (size_t i = 0; i < index; i++) {
        prev = prev->next;
    }
    cl_node *target = prev->next;

    if (prev == target) {
        list->tail = NULL;
    } else {
        prev->next = target->next;

        if (list->tail == target) {
            list->tail = prev;
        }
    }
    CLItem data = target->data;
    cl_node_destroy(target);
    list->size--;
    return data;
}
CLItem cl_get(CLList *list, size_t index)
{
    if (list == NULL || index >= list->size) {
        return 0;
    }

    if (index == list->size - 1) {
        return list->tail->data;
    }

    cl_node *target = list->tail->next;
    for (size_t i = 0; i < index; i++) {
        target = target->next;
    }
    return target->data;
}
void cl_print(CLList *list)
{
    if (list == NULL || list->tail == NULL) {
        return;
    }
    cl_node *current = list->tail->next;

    do {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != list->tail->next);

    printf("head\n");
}
size_t cl_size(CLList *list)
{
    return list ? list->size : 0;
}