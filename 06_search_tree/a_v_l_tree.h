#ifndef A_V_L_TREE_H
#define A_V_L_TREE_H

#include <stddef.h>

typedef struct AVLNode AVLNode;
typedef struct AVLTree AVLOrderedSet;

AVLOrderedSet *avl_create(void);
void avl_destroy(AVLOrderedSet *tree);
void avl_insert(AVLOrderedSet *tree, int key);
void avl_delete(AVLOrderedSet *tree, int key);
AVLNode *avl_search(AVLOrderedSet *tree, int key);
int avl_get(AVLNode *node);
void avl_print(AVLOrderedSet *tree);

#endif