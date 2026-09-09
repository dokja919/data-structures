#include "a_v_l_tree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} AVLItem;

struct AVLNode {
    AVLItem data;
    size_t height;
    struct AVLNode *left;
    struct AVLNode *right;
};
struct AVLTree {
    AVLNode *root;
};
static AVLNode *avl_node_create(int key);
static void avl_node_destroy(AVLNode *node);
static void avl_subtree_destroy(AVLNode *subtree);
static AVLNode *avl_node_insert(AVLNode *node, int key);
static AVLNode *avl_node_delete(AVLNode *node, int key);
static size_t avl_get_height(AVLNode *node);
static size_t avl_get_bigger(size_t a, size_t b);
static void avl_update_height(AVLNode *node);
static AVLNode *avl_rotate_left(AVLNode *x);
static AVLNode *avl_rotate_right(AVLNode *y);
static int avl_balancefactor(AVLNode *node);
static AVLNode *avl_rebalance(AVLNode *node);
static AVLNode *avl_get_min(AVLNode *node);
static void avl_inorder(AVLNode *node);

AVLOrderedSet *avl_create(void)
{
    AVLOrderedSet *tree = malloc(sizeof(AVLOrderedSet));
    if (tree == NULL) {
        return NULL;
    }
    tree->root = NULL;

    return tree;
}
void avl_destroy(AVLOrderedSet *tree)
{
    if (tree == NULL) {
        return;
    }
    avl_subtree_destroy(tree->root);
    free(tree);
}
static AVLNode *avl_node_create(int key)
{
    AVLNode *new_node = malloc(sizeof(AVLNode));
    if (new_node == NULL) {
        return NULL;
    }

    new_node->data.key = key;
    new_node->height = 1;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}
static void avl_node_destroy(AVLNode *node)
{
    free(node);
}
static void avl_subtree_destroy(AVLNode *subtree)
{
    if (subtree == NULL) {
        return;
    }
    avl_subtree_destroy(subtree->left);
    avl_subtree_destroy(subtree->right);
    avl_node_destroy(subtree);
}
static size_t avl_get_height(AVLNode *node)
{
    return node ? node->height : 0;
}
static size_t avl_get_bigger(size_t a, size_t b)
{
    return a > b ? a : b;
}
static void avl_update_height(AVLNode *node)
{
    if (node == NULL) {
        return;
    }
    size_t left_height = avl_get_height(node->left);
    size_t right_height = avl_get_height(node->right);
    node->height = 1 + avl_get_bigger(left_height, right_height);
}
static AVLNode *avl_rotate_left(AVLNode *x)
{
    if (x == NULL) {
        return NULL;
    }
    AVLNode *y = x->right;
    x->right = y->left;
    y->left = x;
    avl_update_height(x);
    avl_update_height(y);
    return y;
}
static AVLNode *avl_rotate_right(AVLNode *y)
{
    if (y == NULL) {
        return NULL;
    }
    AVLNode *x = y->left;
    y->left = x->right;
    x->right = y;
    avl_update_height(y);
    avl_update_height(x);
    return x;
}
static int avl_balancefactor(AVLNode *node)
{
    return (int)avl_get_height(node->left) - (int)avl_get_height(node->right);
}
static AVLNode *avl_rebalance(AVLNode *node)
{
    if (node == NULL) {
        return NULL;
    }
    avl_update_height(node);
    int balance = avl_balancefactor(node);

    if (balance > 1) {
        if (avl_balancefactor(node->left) < 0) {
            node->left = avl_rotate_left(node->left);
        }

        return avl_rotate_right(node);
    }
    if (balance < -1) {

        if (avl_balancefactor(node->right) > 0) {
            node->right = avl_rotate_right(node->right);
        }
        return avl_rotate_left(node);
    }
    return node;
}
void avl_insert(AVLOrderedSet *tree, int key)
{
    if (tree == NULL) {
        return;
    }
    tree->root = avl_node_insert(tree->root, key);
}
static AVLNode *avl_node_insert(AVLNode *node, int key)
{
    if (node == NULL) {
        return avl_node_create(key);
    }
    if (key < node->data.key) {
        node->left = avl_node_insert(node->left, key);
    } else if (key > node->data.key) {
        node->right = avl_node_insert(node->right, key);
    } else {
        return node;
    }
    return avl_rebalance(node);
}
void avl_delete(AVLOrderedSet *tree, int key)
{
    if (tree == NULL) {
        return;
    }
    tree->root = avl_node_delete(tree->root, key);
}
static AVLNode *avl_node_delete(AVLNode *node, int key)
{
    if (node == NULL) {
        return NULL;
    }

    if (key < node->data.key) {
        node->left = avl_node_delete(node->left, key);
    } else if (key > node->data.key) {
        node->right = avl_node_delete(node->right, key);
    } else {
        if (node->left == NULL || node->right == NULL) {
            AVLNode *child = NULL;
            if (node->left) {
                child = node->left;
            } else {
                child = node->right;
            }
            avl_node_destroy(node);
            return child;
        }
        AVLNode *successor = avl_get_min(node->right);
        node->data.key = successor->data.key;
        node->right = avl_node_delete(node->right, successor->data.key);
    }

    return avl_rebalance(node);
}
static AVLNode *avl_get_min(AVLNode *node)
{
    if (node == NULL) {
        return NULL;
    }
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}
AVLNode *avl_search(AVLOrderedSet *tree, int key)
{
    if (tree == NULL) {
        return NULL;
    }
    AVLNode *target = tree->root;
    while (target != NULL) {
        if (key == target->data.key) {
            return target;
        } else if (key < target->data.key) {
            target = target->left;
        } else {
            target = target->right;
        }
    }
    return NULL;
}
int avl_get(AVLNode *node)
{
    if (node == NULL) {
        return 0;
    }
    return node->data.key;
}
void avl_print(AVLOrderedSet *tree)
{
    if (tree == NULL || tree->root == NULL) {
        return;
    }
    avl_inorder(tree->root);
    printf("\n");
}
static void avl_inorder(AVLNode *node)
{
    if (node == NULL) {
        return;
    }
    avl_inorder(node->left);
    printf("%d ", node->data.key);
    avl_inorder(node->right);
}