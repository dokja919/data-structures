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
int partition(int list[], size_t left, size_t right)
{
    int pivot = list[left];
    size_t i = left;
    size_t j = right;

    do {
        do {
            i++;
        } while (list[i] <= pivot);

        do {
            j--;
        } while (list[j] > pivot);

        if (i < j)
            swap(&list[i], &list[j]);

    } while (i < j);

    swap(&list[left], &list[j]);
    return j;
}
int partition(int arr[], int lo, int hi)
{
    int pivot = arr[lo];
    int i = lo - 1;
    int j = hi + 1;

    while (1) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j)
            return j;

        swap(&arr[i], &arr[j]);
    }
}
int partition(int list[], int left, int right)
{
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = list[left];

    do {
        do
            low++;
        while (list[low] < pivot);

        do
            high--;
        while (list[high] > pivot);

        if (low < high)
            SWAP(list[low], list[high], temp);

    } while (low < high);

    SWAP(list[left], list[high], temp);

    return high;
}
void quick_sort(int array[], int left, int right)
{
    if (right - left < 1) {
        return;
    }
    size_t pivot = partition(array, left, right);
    quick_sort(array, left, pivot);
    quick_sort(array, pivot + 1, right);
}
void quick_sort_lomuto(int array[], size_t left, size_t right)
{
    if (right - left < 1) {
        return;
    }

    size_t pivot = partition(array, left, right);

    if (pivot > left) {
        quick_sort_lomuto(array, left, pivot - 1);
    }

    if (pivot < right) {
        quick_sort_lomuto(array, pivot + 1, right);
    }
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
