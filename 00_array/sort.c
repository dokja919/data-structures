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

        for (size_t j = i + 1; j < n; j++)
            if (list[j] < list[min_index]) {
                min_index = j;
            }
        swap(&list[i], &list[min_index]);
    }
}
void merge(int *list, size_t left, size_t mid, size_t right)
{
    int *temp = malloc(sizeof(int) * (right - left + 1));

    size_t i = left;
    size_t j = mid + 1;
    size_t k = 0;

    while (i <= mid && j <= right) {
        if (list[i] <= list[j]) {
            temp[k++] = list[i++];
        } else {
            temp[k++] = list[j++];
        }
    }

    for (; i <= mid; i++) {
        temp[k++] = list[i];
    }
    for (; j <= right; j++) {
        temp[k++] = list[j];
    }

    for (k = 0; k <= right - left; k++) {
        list[left + k] = temp[k];
    }
    free(temp);
}
void merge_sort_recur(int *list, size_t left, size_t right)
{
    if (left >= right) {
        return;
    }
    size_t mid = (left + right) / 2;

    merge_sort_recur(list, left, mid);
    merge_sort_recur(list, mid + 1, right);
    merge(list, left, mid, right);
}
void merge_sort(int *list, size_t n)
{
    if (n < 2) {
        return;
    }
    merge_sort_recur(list, 0, n - 1);
}
void merge_sort_iter(int *list, size_t n)
{
    for (size_t width = 1; width < n; width *= 2) {
        for (size_t left = 0; left < n; left += 2 * width) {
            size_t mid = left + width - 1;
            size_t right = left + 2 * width - 1;

            if (mid >= n - 1) {
                break;
            }

            if (right >= n) {
                right = n - 1;
            }
            merge(list, left, mid, right);
        }
    }
}
void merge_sort_iter1(int *list, size_t n)
{
    size_t width, left, right, mid, i;
    for (width = 2; width <= n; width = width * 2) {
        for (i = 0; i + width - 1 < n; i = i + width) {
            left = i;
            right = i + width - 1;
            mid = (left + right) / 2;
            merge(list, left, mid, right);
        }
        if (n - i > width / 2) {
            left = i;
            right = i + width - 1;
            mid = (left + right) / 2;
            merge(list, left, mid, n - 1);
        }
    }
    if (width / 2 < n) {
        merge(list, 0, width / 2 - 1, n - 1);
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
        bubble_sort(list, n);
        break;
    case 1:
        insertion_sort(list, n);
        break;
    case 2:
        selection_sort(list, n);
        break;
    case 3:
        merge_sort(list, n);
        break;
    case 4:
        merge_sort_iter(list, n);
    }
    print(list, n);

    return 0;
}