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
void rb_destroy(RBOrderedSet *tree);
void rb_insert(RBOrderedSet *tree, RBItem key);
RBNode *rb_search(RBOrderedSet *tree, RBItem key);
void rb_delete(RBOrderedSet *tree, RBItem key);
void rb_print(RBOrderedSet *tree);

#endif
