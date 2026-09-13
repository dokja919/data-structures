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
void bubble_sort(int array[], size_t n)
{
    if (n < 2) {
        return;
    }
    for (size_t pass = 0; pass < n - 1; pass++) {
        bool flag = false;

        for (size_t j = 0; j < n - 1 - pass; j++) {
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
                flag = true;
            }
        }
        if (flag == false) {
            break;
        }
    }
}
void selection_sort(int array[], size_t n)
{
    if (n < 2) {
        return;
    }
    for (size_t i = 0; i < n - 1; i++) {
        size_t min_index = i;

        for (size_t j = i + 1; j < n; j++) {
            if (array[j] < array[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(&array[i], &array[min_index]);
        }
    }
}
void insertion_sort(int array[], size_t n)
{
    if (n < 2) {
        return;
    }
    for (size_t i = 1; i < n; i++) {
        int key = array[i];
        size_t j = i;

        while (j > 0 && key < array[j - 1]) {
            array[j] = array[j - 1];
            j--;
        }

        array[j] = key;
    }
}
void merge(int array[], size_t left, size_t mid, size_t right)
{
    int *temp = malloc(sizeof(int) * (right - left));
    if (temp == NULL) {
        return;
    }

    size_t i = left;
    size_t j = mid;
    size_t k = 0;

    while (i < mid && j < right) {
        if (array[i] <= array[j]) {
            temp[k++] = array[i++];
        } else {
            temp[k++] = array[j++];
        }
    }

    while (i < mid) {
        temp[k++] = array[i++];
    }
    while (j < right) {
        temp[k++] = array[j++];
    }

    for (size_t i = 0; i < k; i++) {
        array[left + i] = temp[i];
    }
    free(temp);
}
void merge_sort(int array[], size_t left, size_t right)
{
    if (right - left < 2) {
        return;
    }
    size_t mid = (left + right) / 2;

    merge_sort(array, left, mid);
    merge_sort(array, mid, right);
    merge(array, left, mid, right);
}
size_t partition(int array[], size_t left, size_t right)
{
    size_t pivot = array[left];
}
size_t partition0(int array[], size_t left, size_t right)
{
    size_t pivot = array[left];
    size_t i = left;
    size_t j = right;

    do {
        do {
            i++;
        } while (array[i] <= pivot);

        do {
            j--;
        } while (array[j] > pivot);

        if (i < j)
            swap(&array[i], &array[j]);

    } while (i < j);

    swap(&array[left], &array[j]);
    return j;
}
size_t partition1(int array[], size_t left, size_t right)
{
    size_t pivot = array[left];
    size_t i = left - 1;
    size_t j = right + 1;

    while (1) {
        do {
            i++;
        } while (array[i] < pivot);

        do {
            j--;
        } while (array[j] > pivot);

        if (i >= j) {
            return j;
        }

        swap(&array[i], &array[j]);
    }
}
size_t partition2(int array[], size_t left, size_t right)
{
    size_t pivot = array[left];
    size_t i = left;
    size_t j = right + 1;

    do {
        do {
            i++;
        } while (array[i] < pivot);

        do {
            j--;
        } while (array[j] > pivot);

        if (i < j) {
            swap(&array[i], &array[j]);
        }

    } while (i < j);

    swap(&array[left], &array[j]);

    return j;
}
void quick_sort(int array[], size_t left, size_t right)
{
    if (right - left < 1) {
        return;
    }
    size_t pivot = partition(array, left, right);
    quick_sort(array, left, pivot);
    quick_sort(array, pivot + 1, right);
}
void print(int *array, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
int main()
{
    int array[] = {11, 13, 7, 12, 16, 9, 24, 5, 10, 3};

    size_t n = 10;

    size_t sort_number = 2;

    switch (sort_number) {
    case 0:
        bubble_sort(array, n);
        break;
    case 1:
        insertion_sort(array, n);
        break;
    case 2:
        selection_sort(array, n);
        break;
    case 3:
        merge_sort(array, 0, n);
        break;
    }
    print(array, n);

    return 0;
}
