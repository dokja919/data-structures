#include "linked_stack.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _l_node {
    int data;
    struct _l_node *next;
} l_node;

struct LinkedStack {
    l_node *top;
};

static l_node *l_node_create(int data);
static void l_node_destroy(l_node *node);

static l_node *l_node_create(int data)
{
    l_node *new_node = malloc(sizeof(l_node));

    if (new_node == NULL) {
        return NULL;
    }

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}
static void l_node_destroy(l_node *node)
{
    free(node);
}
LStack *l_create(void)
{
    LStack *stack = malloc(sizeof(LStack));

    if (stack == NULL) {
        return NULL;
    }

    stack->top = NULL;

    return stack;
}
void l_destroy(LStack *stack)
{
    if (stack == NULL) {
        return;
    }

    while (!l_is_empty(stack)) {
        l_pop(stack);
    }

    free(stack);
}
void l_push(LStack *stack, int data)
{
    if (stack == NULL) {
        return;
    }

    l_node *new_top = l_node_create(data);

    if (new_top == NULL) {
        return;
    }

    new_top->next = stack->top;
    stack->top = new_top;
}

int l_pop(LStack *stack)
{
    if (l_is_empty(stack)) {
        return 0;
    }

    l_node *target = stack->top;
    stack->top = target->next;

    int data = target->data;
    l_node_destroy(target);
    return data;
}

int l_top(LStack *stack)
{
    if (l_is_empty(stack)) {
        return 0;
    }

    return stack->top->data;
}
size_t l_size(LStack *stack)
{
    if (stack == NULL) {
        return 0;
    }

    size_t size = 0;
    l_node *current = stack->top;

    while (current != NULL) {
        size++;
        current = current->next;
    }

    return size;
}
bool l_is_empty(LStack *stack)
{
    return stack == NULL || stack->top == NULL;
}
// #include "linked_stack.h"
// #include <stdio.h>
// #include <stdlib.h>
//
//     typedef struct _l_node {
//     int data;
//     struct _l_node *next;
// } l_node;
//
// struct LinkedStack {
//     l_node *top;
// };
//
// static l_node *l_node_create(int data);
// static void l_node_destroy(l_node *node);
//
// static l_node *l_node_create(int data)
//{
//     l_node *new_node = malloc(sizeof(l_node));
//
//     if (new_node == NULL) {
//         return NULL;
//     }
//
//     new_node->data = data;
//     new_node->next = NULL;
//
//     return new_node;
// }
//
// static void l_node_destroy(l_node *node)
//{
//     free(node);
// }
//
// LStack *l_create(void)
//{
//     LStack *stack = malloc(sizeof(LStack));
//
//     if (stack == NULL) {
//         return NULL;
//     }
//
//     stack->top = NULL;
//
//     return stack;
// }
//
// void l_destroy(LStack *stack)
//{
//     if (stack == NULL) {
//         return;
//     }
//
//     while (!l_is_empty(stack)) {
//         l_pop(stack);
//     }
//
//     free(stack);
// }
//
///* 핵심: l_node ** 사용 */
// static void l_push_node(l_node **top, int data)
//{
//     l_node *new_top = l_node_create(data);
//
//     if (new_top == NULL) {
//         return;
//     }
//
//     new_top->next = *top;
//     *top = new_top;
// }
//
// static int l_pop_node(l_node **top)
//{
//     if (top == NULL || *top == NULL) {
//         return 0;
//     }
//
//     l_node *target = *top;
//     *top = target->next;
//
//     int data = target->data;
//
//     l_node_destroy(target);
//
//     return data;
// }
//
// void l_push(LStack *stack, int data)
//{
//     if (stack == NULL) {
//         return;
//     }
//
//     l_push_node(&stack->top, data);
// }
//
// int l_pop(LStack *stack)
//{
//     if (l_is_empty(stack)) {
//         return 0;
//     }
//
//     return l_pop_node(&stack->top);
// }
//
// int l_top(LStack *stack)
//{
//     if (l_is_empty(stack)) {
//         return 0;
//     }
//
//     return stack->top->data;
// }
//
// size_t l_size(LStack *stack)
//{
//     if (stack == NULL) {
//         return 0;
//     }
//
//     size_t size = 0;
//     l_node *current = stack->top;
//
//     while (current != NULL) {
//         size++;
//         current = current->next;
//     }
//
//     return size;
// }
//
// bool l_is_empty(LStack *stack)
//{
//     return stack == NULL || stack->top == NULL;
// }
