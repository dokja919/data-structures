#define _CRT_SECURE_NO_WARNINGS
#ifndef LINKED_DEQUE_H
#define LINKED_DEQUE_H

#include <stdbool.h>
#include <stddef.h>

typedef int LItem;
typedef struct LinkedDeque LDeque;

void l_push_front(LDeque *deque, int value);
void l_push_back(LDeque *deque, int value);
LItem l_pop_front(LDeque *deque);
LItem l_pop_back(LDeque *deque);
LItem l_front(LDeque *deque);
LItem l_back(LDeque *deque);
size_t l_size(LDeque *deque);
bool l_is_empty(LDeque *deque);

LDeque *l_create(void);
void l_destroy(LDeque *deque);

#endif