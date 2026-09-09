#include "binary_search_tree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} BSItem;

struct BSNode {
    BSItem data;
    struct BSNode *left;
    struct BSNode *right;
};

struct BinarySearchTree {
    BSNode *root;
};

static BSNode *bs_node_create(int key);
static void bs_node_destroy(BSNode *node);
static void bs_subtree_destroy(BSNode *subtree);
static BSNode *bs_node_insert(BSNode *node, int key);
static void bs_transplant(BSOrderedSet *st, BSNode *parent,
                          BSNode *old_subtree, BSNode *new_subtree);
static BSNode *bs_get_min(BSNode *node);
static void bs_inorder(BSNode *node);

BSOrderedSet *bs_create(void)
{
    BSOrderedSet *st = malloc(sizeof(BSOrderedSet));
    if (st == NULL) {
        return NULL;
    }

    st->root = NULL;

    return st;
}
void bs_destroy(BSOrderedSet *st)
{
    if (st == NULL) {
        return;
    }

    bs_subtree_destroy(st->root);
    free(st);
}
static BSNode *bs_node_create(int key)
{
    BSNode *new_node = malloc(sizeof(BSNode));
    if (new_node == NULL) {
        return NULL;
    }

    new_node->data.key = key;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}
static void bs_node_destroy(BSNode *node)
{
    free(node);
}
static void bs_subtree_destroy(BSNode *subtree)
{
    if (subtree == NULL) {
        return;
    }
    bs_subtree_destroy(subtree->left);
    bs_subtree_destroy(subtree->right);
    bs_node_destroy(subtree);
}
void bs_insert(BSOrderedSet *st, int key)
{
    if (st == NULL) {
        return;
    }
    st->root = bs_node_insert(st->root, key);
}
static BSNode *bs_node_insert(BSNode *node, int key)
{
    if (node == NULL) {
        return bs_node_create(key);
    }
    if (key < node->data.key) {
        node->left = bs_node_insert(node->left, key);
    } else if (key > node->data.key) {
        node->right = bs_node_insert(node->right, key);
    }
    return node;
}
static void bs_transplant(BSOrderedSet *st, BSNode *parent,
                          BSNode *old_subtree, BSNode *new_subtree)
{
    if (parent == NULL) {
        st->root = new_subtree;
    } else if (old_subtree == parent->left) {
        parent->left = new_subtree;
    } else {
        parent->right = new_subtree;
    }
}
void bs_delete(BSOrderedSet *st, int key)
{
    if (st == NULL) {
        return;
    }
    ///////////
    BSNode *target_parent = NULL;
    BSNode *target = st->root;
    while (target && target->data.key != key) {
        target_parent = target;
        if (key < target->data.key) {
            target = target->left;
        } else {
            target = target->right;
        }
    }
    if (target == NULL) {
        return;
    }
    //////////////
    if (target->left == NULL || target->right == NULL) {
        BSNode *child = target->left ? target->left : target->right;

        bs_transplant(st, target_parent, target, child);
        bs_node_destroy(target);
        return;
    }
    ///////////
    BSNode *succ_parent = target;
    BSNode *succ = target->right;
    while (succ->left != NULL) {
        succ_parent = succ;
        succ = succ->left;
    }
    ///////////
    if (succ != target->right) {
        bs_transplant(st, succ_parent, succ, succ->right);
        succ->right = target->right;
    }
    bs_transplant(st, target_parent, target, succ);
    succ->left = target->left;
    bs_node_destroy(target);
}
static BSNode *bs_get_min(BSNode *node)
{
    if (node == NULL) {
        return NULL;
    }
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}
BSNode *bs_search(BSOrderedSet *st, int key)
{
    if (st == NULL) {
        return NULL;
    }
    BSNode *target = st->root;
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
int bs_get(BSNode *node)
{
    if (node == NULL) {
        return 0;
    }
    return node->data.key;
}
void bs_print(BSOrderedSet *st)
{
    if (st == NULL || st->root == NULL) {
        return;
    }
    bs_inorder(st->root);
    printf("\n");
}
static void bs_inorder(BSNode *node)
{
    if (node == NULL) {
        return;
    }
    bs_inorder(node->left);
    printf("%d ", node->data.key);
    bs_inorder(node->right);
}