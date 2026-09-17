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
    if (array == NULL || n < 2) {
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
    if (array == NULL || n < 2) {
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
    if (array == NULL || n < 2) {
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
void merge(int array[], size_t begin, size_t mid, size_t end)
{
    int *temp = malloc(sizeof(int) * (end - begin));
    if (temp == NULL) {
        return;
    }

    size_t i = begin;
    size_t j = mid;
    size_t k = 0;

    while (i < mid && j < end) {
        if (array[i] <= array[j]) {
            temp[k++] = array[i++];
        } else {
            temp[k++] = array[j++];
        }
    }

    while (i < mid) {
        temp[k++] = array[i++];
    }
    while (j < end) {
        temp[k++] = array[j++];
    }

    for (size_t i = 0; i < k; i++) {
        array[begin + i] = temp[i];
    }
    free(temp);
}
void merge_sort(int array[], size_t begin, size_t end)
{
    if (array == NULL || end - begin < 2) {
        return;
    }
    size_t mid = (begin + end) / 2;

    merge_sort(array, begin, mid);
    merge_sort(array, mid, end);
    merge(array, begin, mid, end);
}
size_t partition(int array[], size_t begin, size_t end)
{
    int pivot = array[begin];

    size_t i = begin + 1;
    size_t j = end - 1;

    while (i <= j) {
        while (i < end - 1 && array[i] <= pivot) {
            i++;
        }

        while (j >= i && array[j] >= pivot) {
            j--;
        }

        if (i >= j) {
            break;
        }

        swap(&array[i], &array[j]);
    }

    if (j != begin) {
        swap(&array[begin], &array[j]);
    }

    return j;
}
void quick_sort(int array[], size_t begin, size_t end)
{
    if (array == NULL || end - begin < 2) {
        return;
    }
    size_t pivot = partition(array, begin, end);
    quick_sort(array, begin, pivot);
    quick_sort(array, pivot + 1, end);
}

void heapify(int array[], size_t n, size_t i)
{
    size_t left = 2 * i + 1;
    if (left >= n) {
        return;
    }
    size_t right = left + 1;
    size_t child = left;

    if (right < n && array[right] > array[left]) {
        child = right;
    }

    if (array[i] >= array[child]) {
        return;
    }
    swap(&array[i], &array[child]);
    heapify(array, n, child);
}
void heap_sort(int array[], size_t n)
{
    if (array == NULL || n < 2) {
        return;
    }
    for (size_t i = n / 2; i > 0; i--) {
        heapify(array, n, i - 1);
    }
    for (size_t i = n; i > 1; i--) {
        swap(&array[0], &array[i - 1]);
        heapify(array, i - 1, 0);
    }
}
void counting_sort(int array[], size_t n)
{
    if (array == NULL || n < 2) {
        return;
    }

    int max = array[0];
    if (max < 0) {
        return;
    }

    for (size_t i = 1; i < n; i++) {
        if (array[i] < 0) {
            return;
        }
        if (array[i] > max) {
            max = array[i];
        }
    }

    size_t *count = calloc((size_t)max + 2, sizeof(*count));
    if (count == NULL) {
        return;
    }

    int *output = malloc(n * sizeof(*output));
    if (output == NULL) {
        free(count);
        return;
    }

    for (size_t i = 0; i < n; i++) {
        count[array[i] + 1]++;
    }

    for (size_t v = 0; v <= max; v++) {
        count[v + 1] += count[v];
    }

    for (size_t i = 0; i < n; i++) {
        int value = array[i];

        output[count[value]] = value;
        count[value]++;
    }

    for (size_t i = 0; i < n; i++) {
        array[i] = output[i];
    }

    free(count);
    free(output);
}
void counting_sort1(int array[], size_t n)
{
    if (array == NULL || n < 2) {
        return;
    }

    int max = array[0];
    if (max < 0) {
        return;
    }

    for (size_t i = 1; i < n; i++) {
        if (array[i] < 0) {
            return;
        }
        if (array[i] > max) {
            max = array[i];
        }
    }
    size_t *count = calloc((size_t)max + 1, sizeof(*count));
    if (count == NULL) {
        return;
    }
    int *output = malloc(n * sizeof(*output));
    if (output == NULL) {
        free(count);
        return;
    }

    for (size_t i = 0; i < n; i++) {
        count[array[i]]++;
    }

    for (size_t v = 1; v <= max; v++) {
        count[v] += count[v - 1];
    }

    for (size_t i = n; i > 0; i--) {
        int value = array[i - 1];
        output[count[value] - 1] = value;
        count[value]--;
    }
    for (size_t i = 0; i < n; i++) {
        array[i] = output[i];
    }

    free(count);
    free(output);
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
    int keys[] = {11, 13, 7, 12, 16, 9, 24, 5, 10, 3};
    // int array[] = {1, 3};
    size_t n = sizeof(keys) / sizeof(*keys);

    size_t sort_number = 6;

    switch (sort_number) {
    case 0:
        bubble_sort(keys, n);
        break;
    case 1:
        selection_sort(keys, n);
        break;
    case 2:
        insertion_sort(keys, n);
        break;
    case 3:
        merge_sort(keys, 0, n);
        break;
    case 4:
        quick_sort(keys, 0, n);
        break;
    case 5:
        heap_sort(keys, n);
        break;
    case 6:
        counting_sort(keys, n);
    }
    print(keys, n);

    return 0;
}
