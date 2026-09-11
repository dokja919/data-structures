#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
void sort_bubble(int *list, size_t n)
{
    if (n < 2) {
        return;
    }
    bool flag = false;

    for (size_t i = 0; i < n - 1; i++) {
        flag = false;

        for (size_t j = 0; j < n - 1 - i; j++) {
            if (list[j] > list[j + 1]) {
                swap(&list[j], &list[j + 1]);
                flag = true;
            }
        }
        if (flag == false) {
            break;
        }
    }
}
void sort_insertion(int *list, size_t n)
{
    if (n < 2) {
        return;
    }
    for (size_t i = 1; i < n; i++) {
        int key = list[i];
        size_t j = i;

        while (j > 0 && key < list[j - 1]) {
            list[j] = list[j - 1];
            j--;
        }

        list[j] = key;
    }
}
void sort_selection(int *list, size_t n)
{
    if (n < 2) {
        return;
    }
    for (size_t i = 0; i < n - 1; i++) {
        size_t min_index = i;

        for (size_t j = i + 1; j < n; j++)
            if (list[j] < list[min_index]) {
                min_index = j;
            }
        swap(&list[i], &list[min_index]);
    }
}
void print(int *list, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}
int main()
{
    int list[] = {11, 13, 7, 12, 16, 9, 24, 5, 10, 3};

    size_t n = 10;

    size_t sort_number = 2;

    switch (sort_number) {
    case 0:
        sort_bubble(list, n);
        break;
    case 1:
        sort_insertion(list, n);
        break;
    case 2:
        sort_selection(list, n);
        break;
    }
    print(list, n);

    return 0;
}