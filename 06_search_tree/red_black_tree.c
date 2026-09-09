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
static void rb_subtree_destroy(RBOrderedSet *st, RBNode *node);
static void rb_rotate_left(RBOrderedSet *st, RBNode *x);
static void rb_rotate_right(RBOrderedSet *st, RBNode *y);
static void rb_insert_fixup(RBOrderedSet *st, RBNode *new_node);
static void rb_transplant(RBOrderedSet *st, RBNode *old_subtree, RBNode *new_subtree);
static void rb_delete_fixup(RBOrderedSet *st, RBNode *current);
static void rb_node_print(RBOrderedSet *st, RBNode *node, int depth, int black_count);
static RBNode *rb_node_search(RBOrderedSet *st, RBNode *node, RBItem key);
static RBNode *rb_get_min(RBOrderedSet *st, RBNode *node);

RBOrderedSet *rb_create(void)
{
    RBOrderedSet *st = malloc(sizeof(RBOrderedSet));
    if (st == NULL) {
        return NULL;
    }

    st->nil = rb_node_create(0);
    if (st->nil == NULL) {
        free(st);
        return NULL;
    }
    st->nil->color = BLACK;
    st->nil->parent = st->nil;
    st->nil->left = st->nil;
    st->nil->right = st->nil;

    st->root = st->nil;

    return st;
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
void rb_destroy(RBOrderedSet *st)
{
    if (st == NULL) {
        return;
    }
    rb_subtree_destroy(st, st->root);
    rb_node_destroy(st->nil);
    free(st);
}
static void rb_node_destroy(RBNode *node)
{
    free(node);
}
static void rb_subtree_destroy(RBOrderedSet *st, RBNode *node)
{
    if (node == st->nil) {
        return;
    }
    rb_subtree_destroy(st, node->left);
    rb_subtree_destroy(st, node->right);
    rb_node_destroy(node);
}
static void rb_rotate_left(RBOrderedSet *st, RBNode *x)
{
    RBNode *y = x->right;

    x->right = y->left;
    if (y->left != st->nil) {
        y->left->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == st->nil) {
        st->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}
static void rb_rotate_right(RBOrderedSet *st, RBNode *y)
{
    RBNode *x = y->left;

    y->left = x->right;
    if (x->right != st->nil) {
        x->right->parent = y;
    }

    x->parent = y->parent;
    if (y->parent == st->nil) {
        st->root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
}
void rb_insert(RBOrderedSet *st, RBItem key)
{
    if (st == NULL) {
        return;
    }
    RBNode *new_node = rb_node_create(key);
    if (new_node == NULL) {
        return;
    }
    new_node->left = st->nil;
    new_node->right = st->nil;

    RBNode *parent = st->nil;
    RBNode *target = st->root;

    while (target != st->nil) {
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

    if (parent == st->nil) {
        st->root = new_node;
    } else if (new_node->key < parent->key) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
    rb_insert_fixup(st, new_node);
}
static void rb_insert_fixup(RBOrderedSet *st, RBNode *new_node)
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
                    rb_rotate_left(st, new_node);
                    parent = new_node->parent;
                }
                parent->color = BLACK;
                parent->parent->color = RED;
                rb_rotate_right(st, parent->parent);
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
                    rb_rotate_right(st, new_node);
                    parent = new_node->parent;
                }
                parent->color = BLACK;
                parent->parent->color = RED;
                rb_rotate_left(st, parent->parent);
            }
        }
    }
    st->root->color = BLACK;
}
static void rb_transplant(RBOrderedSet *st, RBNode *old_subtree, RBNode *new_subtree)
{
    if (old_subtree->parent == st->nil) {
        st->root = new_subtree;
    } else if (old_subtree == old_subtree->parent->left) {
        old_subtree->parent->left = new_subtree;
    } else {
        old_subtree->parent->right = new_subtree;
    }
    new_subtree->parent = old_subtree->parent;
}
void rb_delete(RBOrderedSet *st, RBItem key)
{
    if (st == NULL) {
        return;
    }
    RBNode *target = rb_search(st, key);
    if (target == NULL) {
        return;
    }
    RBNode *replacement = target;
    Color original_color = replacement->color;
    RBNode *child = NULL;

    if (target->left == st->nil) {
        child = replacement->right;
        rb_transplant(st, replacement, child);
    } else if (target->right == st->nil) {
        child = replacement->left;
        rb_transplant(st, replacement, child);
    } else {
        replacement = rb_get_min(st, target->right);
        original_color = replacement->color;
        child = replacement->right;

        if (replacement != target->right) {
            // Remove replacement from its original position.
            rb_transplant(st, replacement, child);

            // target's right subtree becomes replacement's right subtree.
            replacement->right = target->right;
            replacement->right->parent = replacement;
        } else {
            // replacement is already target's right child.
            child->parent = replacement;
        }
        // Move replacement into target's position.
        rb_transplant(st, target, replacement);

        replacement->left = target->left;
        replacement->left->parent = replacement;

        replacement->color = target->color;
    }
    rb_node_destroy(target);

    if (original_color == BLACK) {
        rb_delete_fixup(st, child);
    }
}
static void rb_delete_fixup(RBOrderedSet *st, RBNode *current)
{
    while (current != st->root && current->color == BLACK) {
        if (current == current->parent->left) {
            RBNode *sibling = current->parent->right;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                current->parent->color = RED;
                rb_rotate_left(st, current->parent);
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
                    rb_rotate_right(st, sibling);
                    sibling = current->parent->right;
                }

                sibling->color = current->parent->color;
                current->parent->color = BLACK;
                sibling->right->color = BLACK;
                rb_rotate_left(st, current->parent);
                current = st->root;
            }
        } else {
            RBNode *sibling = current->parent->left;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                current->parent->color = RED;
                rb_rotate_right(st, current->parent);
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
                    rb_rotate_left(st, sibling);
                    sibling = current->parent->left;
                }

                sibling->color = current->parent->color;
                current->parent->color = BLACK;
                sibling->left->color = BLACK;
                rb_rotate_right(st, current->parent);
                current = st->root;
            }
        }
    }
    current->color = BLACK;
}
static RBNode *rb_get_min(RBOrderedSet *st, RBNode *node)
{
    while (node->left != st->nil) {
        node = node->left;
    }
    return node;
}
RBNode *rb_search(RBOrderedSet *st, RBItem key)
{
    if (st == NULL) {
        return NULL;
    }
    return rb_node_search(st, st->root, key);
}
static RBNode *rb_node_search(RBOrderedSet *st, RBNode *node, RBItem key)
{
    if (node == st->nil || node->key == key) {
        return node == st->nil ? NULL : node;
    }
    if (key < node->key) {
        return rb_node_search(st, node->left, key);
    }
    return rb_node_search(st, node->right, key);
}
void rb_print(RBOrderedSet *st)
{
    if (st == NULL) {
        return;
    }

    rb_node_print(st, st->root, 0, 0);
}
static void rb_node_print(RBOrderedSet *st, RBNode *node, int depth, int black_count)
{
    rb_node_print(st, node->left, depth + 1, black_count);

    int parent_key = -1;
    char position = 'X';

    if (node == st->nil) {
        return;
    }

    if (node->color == BLACK) {
        black_count++;
    }

    if (node->parent != st->nil) {
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

    if (node->left == st->nil && node->right == st->nil) {
        printf(" --------- %d", black_count);
    }

    printf("\n");

    rb_node_print(st, node->right, depth + 1, black_count);
}