#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

typedef struct RBNode RBNode;
typedef struct RedBlackTree RBOrderedSet;

RBOrderedSet *rb_create(void);
void rb_destroy(RBOrderedSet *tree);
void rb_insert(RBOrderedSet *tree, int key);
void rb_delete(RBOrderedSet *tree, int key);
RBNode *rb_search(RBOrderedSet *tree, int key);
int rb_get(RBNode *node);
void rb_print(RBOrderedSet *tree);

#endif
