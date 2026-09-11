#include "array_list.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 8

typedef int AItem;

struct ArrayList {
    AItem *items;
    size_t capacity;
    size_t size;
};

AList *a_create(void)
{
    AList *list = malloc(sizeof(AList));
    if (list == NULL) {
        return NULL;
    }

    size_t capacity = INITIAL_CAPACITY;
    list->items = malloc(sizeof(AItem) * capacity);
    if (list->items == NULL) {
        free(list);
        return NULL;
    }
    list->capacity = capacity;
    list->size = 0;

    return list;
}
void a_destroy(AList *list)
{
    if (list == NULL) {
        return;
    }
    free(list->items);
    free(list);
}

void a_insert(AList *list, size_t index, int value)
{
    if (list == NULL || index > list->size) {
        return;
    }
    if (list->size == list->capacity) {
        size_t new_capacity = list->capacity * 2;

        AItem *new_items = realloc(list->items, sizeof(AItem) * new_capacity);
        if (new_items == NULL) {
            return; // 메모리 부족
        }

        list->items = new_items;
        list->capacity = new_capacity;
    }

    for (size_t i = list->size; i > index; i--) {
        list->items[i] = list->items[i - 1];
    }
    list->items[index] = value;
    list->size++;
}
AItem a_delete(AList *list, size_t index)
{
    if (list == NULL || index >= list->size) {
        return 0;
    }
    AItem data = list->items[index];
    for (size_t i = index; i < list->size - 1; i++) {
        list->items[i] = list->items[i + 1];
    }
    list->size--;
    return data;
}
AItem a_get(AList *list, size_t index)
{
    if (list == NULL || index >= list->size) {
        return 0;
    }
    return list->items[index];
}
void a_print(AList *list)
{
    if (list == NULL) {
        return;
    }
    printf("| ");
    for (size_t index = 0; index < list->size; index++) {
        printf("%d | ", list->items[index]);
    }
}
size_t a_size(AList *list)
{
    return list ? list->size : 0;
}
// static int a_binary_search(AList *list, int key);
//
// static int a_binary_search(AList *list, int key)
//{
//     if (list == NULL) {
//         return -1;
//     }
//     int left = 0;
//     int mid = 0;
//     int right = (int)list->size - 1;
//
//     while (left <= right) {
//         mid = (left + right) / 2;
//
//         if (key == list->items[mid]) {
//             return mid;
//         }
//         if (key < list->items[mid]) {
//             right = mid - 1;
//         } else {
//             left = mid + 1;
//         }
//     }
//     return -1;
// }