#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

typedef enum {
    RED,
    BLACK
} Color;

typedef int RBItem;
typedef struct RBNode RBNode;
typedef struct RedBlackTree RBOrderedSet;

RBOrderedSet *rb_create(void);
void rb_destroy(RBOrderedSet *st);
void rb_insert(RBOrderedSet *st, RBItem key);
RBNode *rb_search(RBOrderedSet *st, RBItem key);
void rb_delete(RBOrderedSet *st, RBItem key);
void rb_print(RBOrderedSet *st);

#endif
