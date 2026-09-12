#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
void bubble_sort(int *list, size_t n)
{
    if (n < 2) {
        return;
    }
    for (size_t pass = 0; pass < n - 1; pass++) {
        bool flag = false;

        for (size_t j = 0; j < n - 1 - pass; j++) {
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
void insertion_sort(int *list, size_t n)
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
void selection_sort(int *list, size_t n)
{
    if (n < 2) {
        return;
    }
    for (size_t i = 0; i < n - 1; i++) {
        size_t min_index = i;

        for (size_t j = i + 1; j < n; j++) {
            if (list[j] < list[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(&list[i], &list[min_index]);
        }
    }
}
void merge(int *list, size_t left, size_t mid, size_t right)
{
    int *temp = malloc(sizeof(int) * (right - left));
    if (temp == NULL) {
        return;
    }

    size_t i = left;
    size_t j = mid;
    size_t k = 0;

    while (i < mid && j < right) {
        if (list[i] <= list[j]) {
            temp[k++] = list[i++];
        } else {
            temp[k++] = list[j++];
        }
    }

    while (i < mid) {
        temp[k++] = list[i++];
    }
    while (j < right) {
        temp[k++] = list[j++];
    }

    for (size_t i = 0; i < k; i++) {
        list[left + i] = temp[i];
    }
    free(temp);
}
void merge_sort(int *list, size_t left, size_t right)
{
    if (right - left <= 1) {
        return;
    }
    size_t mid = left + (right - left) / 2;

    merge_sort(list, left, mid);
    merge_sort(list, mid, right);
    merge(list, left, mid, right);
}
// void merge_sort_iter(int *list, size_t n)
//{
//     for (size_t width = 1; width < n; width *= 2) {
//
//         for (size_t left = 0; left < n; left += 2 * width) {
//
//             size_t mid = left + width;
//             if (mid >= n) {
//                 break;
//             }
//
//             size_t right = left + 2 * width;
//             if (right > n) {
//                 right = n;
//             }
//
//             merge(list, left, mid, right);
//         }
//     }
// }
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
        bubble_sort(list, n);
        break;
    case 1:
        insertion_sort(list, n);
        break;
    case 2:
        selection_sort(list, n);
        break;
    case 3:
        merge_sort(list, 0, n);
        break;
    case 4:
        merge_sort_iter(list, n);
    }
    print(list, n);

    return 0;
}