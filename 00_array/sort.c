#include <stdbool.h>
// #include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
void sort_bubble(int *A, size_t n)
{
    bool flag = false;

    for (size_t i = 0; i < n - 1; i++) {
        flag = false;

        for (size_t j = 0; j < n - 1 - i; j++) {
            if (A[j] > A[j + 1]) {
                swap(&A[j], &A[j + 1]);
                flag = true;
            }
        }
        if (flag == true) {
            break;
        }
    }
}
void sort_insertion(int *A, size_t n)
{
    for (size_t i = 1; i < n; i++) {
        int key = A[i];
        size_t j = i;

        while (j > 0 && key < A[j - 1]) {
            A[j] = A[j - 1];
            j--;
        }

        A[j] = key;
    }
}
void print(int *A)
{
    for (size_t i = 0; i < 10; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}
int main()
{
    int A[] = {11, 13, 7, 12, 16, 9, 24, 5, 10, 3};

    size_t n = 10;

    size_t sort_number = 1;

    switch (sort_number) {
    case 0:
        sort_bubble(A, n);
        break;
    case 1:
        sort_insertion(A, n);
        break;
    }
    print(A);

    return 0;
}