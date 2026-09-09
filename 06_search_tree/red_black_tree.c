#include "red_black_tree.h"
#include <stdio.h>
#include <stdlib.h>

struct RBNode {
    RBItem key;
    Color color;
    struct RBNode *parent;
    struct RBNode *left;
    struct RBNode *right;
};
struct RedBlackTree {
    RBNode *root;
    RBNode *nil;
};

static RBNode *rb_node_create(RBItem key);
static void rb_node_destroy(RBNode *node);
static void rb_subtree_destroy(RBOrderedSet *tree, RBNode *node);
static void rb_rotate_left(RBOrderedSet *tree, RBNode *x);
static void rb_rotate_right(RBOrderedSet *tree, RBNode *y);
static void rb_insert_fixup(RBOrderedSet *tree, RBNode *new_node);
static void rb_transplant(RBOrderedSet *tree, RBNode *old_subtree, RBNode *new_subtree);
static void rb_delete_fixup(RBOrderedSet *tree, RBNode *current);
static void rb_node_print(RBOrderedSet *tree, RBNode *node, int depth, int black_count);
static RBNode *rb_node_search(RBOrderedSet *tree, RBNode *node, RBItem key);
static RBNode *rb_get_min(RBOrderedSet *tree, RBNode *node);

RBOrderedSet *rb_create(void)
{
    RBOrderedSet *tree = malloc(sizeof(RBOrderedSet));
    if (tree == NULL) {
        return NULL;
    }

    tree->nil = rb_node_create(0);
    if (tree->nil == NULL) {
        free(tree);
        return NULL;
    }
    tree->nil->color = BLACK;
    tree->nil->parent = tree->nil;
    tree->nil->left = tree->nil;
    tree->nil->right = tree->nil;

    tree->root = tree->nil;

    return tree;
}
static RBNode *rb_node_create(RBItem key)
{
    RBNode *node = malloc(sizeof(RBNode));
    if (node == NULL) {
        return NULL;
    }

    node->key = key;
    node->color = RED;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;

    return node;
}
void rb_destroy(RBOrderedSet *tree)
{
    if (tree == NULL) {
        return;
    }
    rb_subtree_destroy(tree, tree->root);
    rb_node_destroy(tree->nil);
    free(tree);
}
static void rb_node_destroy(RBNode *node)
{
    free(node);
}
static void rb_subtree_destroy(RBOrderedSet *tree, RBNode *node)
{
    if (node == tree->nil) {
        return;
    }
    rb_subtree_destroy(tree, node->left);
    rb_subtree_destroy(tree, node->right);
    rb_node_destroy(node);
}
static void rb_rotate_left(RBOrderedSet *tree, RBNode *x)
{
    RBNode *y = x->right;

    x->right = y->left;
    if (y->left != tree->nil) {
        y->left->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == tree->nil) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}
static void rb_rotate_right(RBOrderedSet *tree, RBNode *y)
{
    RBNode *x = y->left;

    y->left = x->right;
    if (x->right != tree->nil) {
        x->right->parent = y;
    }

    x->parent = y->parent;
    if (y->parent == tree->nil) {
        tree->root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
}
void rb_insert(RBOrderedSet *tree, RBItem key)
{
    if (tree == NULL) {
        return;
    }
    RBNode *new_node = rb_node_create(key);
    if (new_node == NULL) {
        return;
    }
    new_node->left = tree->nil;
    new_node->right = tree->nil;

    RBNode *parent = tree->nil;
    RBNode *target = tree->root;

    while (target != tree->nil) {
        parent = target;
        if (new_node->key < target->key) {
            target = target->left;
        } else if (new_node->key > target->key) {
            target = target->right;
        } else {
            free(new_node);
            return;
        }
    }
    new_node->parent = parent;

    if (parent == tree->nil) {
        tree->root = new_node;
    } else if (new_node->key < parent->key) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
    rb_insert_fixup(tree, new_node);
}
static void rb_insert_fixup(RBOrderedSet *tree, RBNode *new_node)
{
    while (new_node->parent->color == RED) {
        RBNode *parent = new_node->parent;

        if (parent == parent->parent->left) {
            RBNode *uncle = parent->parent->right;

            if (uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                parent->parent->color = RED;
                new_node = parent->parent;
            } else {
                if (new_node == parent->right) {
                    new_node = parent;
                    rb_rotate_left(tree, new_node);
                    parent = new_node->parent;
                }
                parent->color = BLACK;
                parent->parent->color = RED;
                rb_rotate_right(tree, parent->parent);
            }
        } else {
            RBNode *uncle = parent->parent->left;

            if (uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                parent->parent->color = RED;
                new_node = parent->parent;
            } else {
                if (new_node == parent->left) {
                    new_node = parent;
                    rb_rotate_right(tree, new_node);
                    parent = new_node->parent;
                }
                parent->color = BLACK;
                parent->parent->color = RED;
                rb_rotate_left(tree, parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}
static void rb_transplant(RBOrderedSet *tree, RBNode *old_subtree, RBNode *new_subtree)
{
    if (old_subtree->parent == tree->nil) {
        tree->root = new_subtree;
    } else if (old_subtree == old_subtree->parent->left) {
        old_subtree->parent->left = new_subtree;
    } else {
        old_subtree->parent->right = new_subtree;
    }
    new_subtree->parent = old_subtree->parent;
}
void rb_delete(RBOrderedSet *tree, RBItem key)
{
    if (tree == NULL) {
        return;
    }
    RBNode *target = rb_search(tree, key);
    if (target == NULL) {
        return;
    }
    RBNode *replacement = target;
    Color original_color = replacement->color;
    RBNode *child = NULL;

    if (target->left == tree->nil) {
        child = replacement->right;
        rb_transplant(tree, replacement, child);
    } else if (target->right == tree->nil) {
        child = replacement->left;
        rb_transplant(tree, replacement, child);
    } else {
        replacement = rb_get_min(tree, target->right);
        original_color = replacement->color;
        child = replacement->right;

        if (replacement != target->right) {
            // Remove replacement from its original position.
            rb_transplant(tree, replacement, child);

            // target's right subtree becomes replacement's right subtree.
            replacement->right = target->right;
            replacement->right->parent = replacement;
        } else {
            // replacement is already target's right child.
            child->parent = replacement;
        }
        // Move replacement into target's position.
        rb_transplant(tree, target, replacement);

        replacement->left = target->left;
        replacement->left->parent = replacement;

        replacement->color = target->color;
    }
    rb_node_destroy(target);

    if (original_color == BLACK) {
        rb_delete_fixup(tree, child);
    }
}
static void rb_delete_fixup(RBOrderedSet *tree, RBNode *current)
{
    while (current != tree->root && current->color == BLACK) {
        if (current == current->parent->left) {
            RBNode *sibling = current->parent->right;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                current->parent->color = RED;
                rb_rotate_left(tree, current->parent);
                sibling = current->parent->right;
            }

            if (sibling->left->color == BLACK &&
                sibling->right->color == BLACK) {
                sibling->color = RED;
                current = current->parent;
            } else {
                if (sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rb_rotate_right(tree, sibling);
                    sibling = current->parent->right;
                }

                sibling->color = current->parent->color;
                current->parent->color = BLACK;
                sibling->right->color = BLACK;
                rb_rotate_left(tree, current->parent);
                current = tree->root;
            }
        } else {
            RBNode *sibling = current->parent->left;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                current->parent->color = RED;
                rb_rotate_right(tree, current->parent);
                sibling = current->parent->left;
            }

            if (sibling->right->color == BLACK &&
                sibling->left->color == BLACK) {
                sibling->color = RED;
                current = current->parent;
            } else {
                if (sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    rb_rotate_left(tree, sibling);
                    sibling = current->parent->left;
                }

                sibling->color = current->parent->color;
                current->parent->color = BLACK;
                sibling->left->color = BLACK;
                rb_rotate_right(tree, current->parent);
                current = tree->root;
            }
        }
    }
    current->color = BLACK;
}
static RBNode *rb_get_min(RBOrderedSet *tree, RBNode *node)
{
    while (node->left != tree->nil) {
        node = node->left;
    }
    return node;
}
RBNode *rb_search(RBOrderedSet *tree, RBItem key)
{
    if (tree == NULL) {
        return NULL;
    }
    return rb_node_search(tree, tree->root, key);
}
static RBNode *rb_node_search(RBOrderedSet *tree, RBNode *node, RBItem key)
{
    if (node == tree->nil || node->key == key) {
        return node == tree->nil ? NULL : node;
    }
    if (key < node->key) {
        return rb_node_search(tree, node->left, key);
    }
    return rb_node_search(tree, node->right, key);
}
void rb_print(RBOrderedSet *tree)
{
    if (tree == NULL) {
        return;
    }

    rb_node_print(tree, tree->root, 0, 0);
}
static void rb_node_print(RBOrderedSet *tree, RBNode *node, int depth, int black_count)
{
    rb_node_print(tree, node->left, depth + 1, black_count);

    int parent_key = -1;
    char position = 'X';

    if (node == tree->nil) {
        return;
    }

    if (node->color == BLACK) {
        black_count++;
    }

    if (node->parent != tree->nil) {
        parent_key = node->parent->key;

        if (node == node->parent->left) {
            position = 'L';
        } else {
            position = 'R';
        }
    }

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    printf("%d %s [%c,%d]", node->key, node->color == RED ? "RED" : "BLACK", position, parent_key);

    if (node->left == tree->nil && node->right == tree->nil) {
        printf(" --------- %d", black_count);
    }

    printf("\n");

    rb_node_print(tree, node->right, depth + 1, black_count);
}