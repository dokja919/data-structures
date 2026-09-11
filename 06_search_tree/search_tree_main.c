#include "a_v_l_tree.h"
#include "binary_search_tree.h"
#include "red_black_tree.h"
#include <stdio.h>

void bs_test(void)
{
    BSOrderedSet *os = bs_create();
    int keys[] = {10, 20, 30, 40, 50, 25};

    for (int i = 0; i < 6; i++) {
        bs_insert(os, keys[i]);
    }

    bs_print(os);

    BSNode *node = bs_search(os, 40);

    if (node != NULL) {
        printf("result: %d\n", bs_get(node));
    }

    printf("after removing 30: ");
    bs_delete(os, 30);
    bs_print(os);

    bs_destroy(os);
}

void avl_test(void)
{
    AVLOrderedSet *os = avl_create();
    int datas[] = {10, 20, 30, 40, 50, 25};

    for (int i = 0; i < 6; i++) {
        avl_insert(os, datas[i]);
    }

    avl_print(os);

    printf("after removing 30\n");
    avl_delete(os, 30);
    avl_print(os);

    avl_destroy(os);
}

void rb_test(void)
{
    RBOrderedSet *os = rb_create();

    if (os == NULL)
        return;

    while (1) {
        int cmd;
        int param;
        char buffer[10];

        printf("Enter command number :\n");
        printf("(1) Create a node, (2) Remove a node, (3) Search a Node\n");
        printf("(4) Display Tree (5) quit\n");
        printf("command number:");

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &cmd);

        if (cmd < 1 || cmd > 5) {
            printf("Invalid command number.\n");
            continue;
        }

        if (cmd == 4) {
            rb_print(os);
            printf("\n");
            continue;
        }

        if (cmd == 5) {
            break;
        }

        printf("Enter parameter (1~200) :\n");

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &param);

        if (param < 1 || param > 200) {
            printf("Invalid parameter.%d\n", param);
            continue;
        }

        switch (cmd) {
        case 1:
            rb_insert(os, param);
            break;

        case 2:
            rb_delete(os, param);
            break;

        case 3:
            if (rb_search(os, param) == NULL) {
                printf("Not found node:%d\n", param);
            }
            break;
        }

        printf("\n");
    }

    rb_destroy(os);
}

int main(void)
{
    int os_number = 1;

    switch (os_number) {
    case 0:
        bs_test();
        break;

    case 1:
        avl_test();
        break;

    case 2:
        rb_test();
        break;
    }

    return 0;
}
