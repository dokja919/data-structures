#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}
void bubble_sort(int array[], size_t n)
{
    if (array == NULL || n < 2) {
        return;
    }
    for (size_t pass = 0; pass < n - 1; pass++) {
        bool swapped = false;

        for (size_t i = 0; i < n - 1 - pass; i++) {
            if (array[i] > array[i + 1]) {
                swap(&array[i], &array[i + 1]);
                swapped = true;
            }
        }
        if (swapped == false) {
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
        size_t position = i;

        while (position > 0 && key < array[position - 1]) {
            array[position] = array[position - 1];
            position--;
        }

        array[position] = key;
    }
}
void merge(int array[], size_t begin, size_t middle, size_t end)
{
    size_t n = end - begin;
    int *buffer = malloc(n * sizeof(*buffer));
    if (buffer == NULL) {
        return;
    }

    size_t left = begin;
    size_t right = middle;

    size_t buffer_index = 0;
    while (left < middle && right < end) {
        if (array[left] <= array[right]) {
            buffer[buffer_index++] = array[left++];
        } else {
            buffer[buffer_index++] = array[right++];
        }
    }
    while (left < middle) {
        buffer[buffer_index++] = array[left++];
    }
    while (right < end) {
        buffer[buffer_index++] = array[right++];
    }

    for (size_t i = 0; i < n; i++) {
        array[begin + i] = buffer[i];
    }
    free(buffer);
}
void merge_sort(int array[], size_t begin, size_t end)
{
    if (array == NULL || end - begin < 2) {
        return;
    }
    size_t middle = (begin + end) / 2;

    merge_sort(array, begin, middle);
    merge_sort(array, middle, end);
    merge(array, begin, middle, end);
}
size_t partition(int array[], size_t begin, size_t end)
{
    int pivot_value = array[begin];

    size_t left = begin;
    size_t right = end;
    do {
        do {
            left++;
        } while (left < end - 1 && array[left] < pivot_value);

        do {
            right--;
        } while (right >= left && array[right] > pivot_value);

        if (left >= right) {
            break;
        }
        swap(&array[left], &array[right]);

    } while (left < right);

    swap(&array[begin], &array[right]);

    return right;
}
void quick_sort(int array[], size_t begin, size_t end)
{
    if (array == NULL || end - begin < 2) {
        return;
    }
    size_t pivot_index = partition(array, begin, end);

    quick_sort(array, begin, pivot_index);
    quick_sort(array, pivot_index + 1, end);
}
void heapify(int array[], size_t n, size_t root)
{
    size_t left_child = 2 * root + 1;
    if (left_child >= n) {
        return;
    }

    size_t right_child = left_child + 1;
    size_t larger_child = left_child;

    if (right_child < n && array[right_child] > array[left_child]) {
        larger_child = right_child;
    }

    if (array[root] >= array[larger_child]) {
        return;
    }
    swap(&array[root], &array[larger_child]);
    heapify(array, n, larger_child);
}
void heap_sort(int array[], size_t n)
{
    if (array == NULL || n < 2) {
        return;
    }
    for (size_t i = n / 2; i > 0; i--) {
        heapify(array, n, i - 1);
    }
    for (size_t end = n - 1; end > 0; end--) {
        swap(&array[0], &array[end]);
        heapify(array, end, 0);
    }
}
bool get_nonnegative_max(int array[], size_t n, size_t *max_value)
{
    if (array == NULL || n == 0 || max_value == NULL) {
        return false;
    }

    int temp = 0;

    for (size_t i = 0; i < n; i++) {
        if (array[i] < 0) {
            return false;
        }
        int value = array[i];

        if (value > temp) {
            temp = value;
        }
    }

    *max_value = (size_t)temp;
    return true;
}
void counting_sort(int array[], size_t n)
{
    if (array == NULL || n < 2) {
        return;
    }

    size_t max_value;
    if (!get_nonnegative_max(array, n, &max_value)) {
        return;
    }

    size_t *counts = calloc(max_value + 1, sizeof(*counts));
    if (counts == NULL) {
        return;
    }

    int *output = malloc(n * sizeof(*output));
    if (output == NULL) {
        free(counts);
        return;
    }

    for (size_t i = 0; i < n; i++) {
        size_t value = (size_t)array[i];
        counts[value]++;
    }

    for (size_t value = 1; value <= max_value; value++) {
        counts[value] += counts[value - 1];
    }

    for (size_t i = n; i > 0; i--) {
        int value = array[i - 1];
        size_t counts_index = (size_t)value;

        size_t index = --counts[counts_index];
        output[index] = value;
    }
    for (size_t i = 0; i < n; i++) {
        array[i] = output[i];
    }

    free(counts);
    free(output);
}
void counting_pass(int array[], size_t n, size_t place_value)
{
    size_t counts[10] = {0};

    int *output = malloc(n * sizeof(*output));
    if (output == NULL) {
        return;
    }

    for (size_t i = 0; i < n; i++) {
        size_t digit = ((size_t)array[i] / place_value) % 10;
        counts[digit]++;
    }

    for (size_t digit = 1; digit <= 9; digit++) {
        counts[digit] += counts[digit - 1];
    }

    for (size_t i = n; i > 0; i--) {
        int value = array[i - 1];
        size_t digit = ((size_t)value / place_value) % 10;

        size_t index = --counts[digit];
        output[index] = value;
    }
    for (size_t i = 0; i < n; i++) {
        array[i] = output[i];
    }

    free(output);
}
void radix_sort(int array[], size_t n)
{
    if (array == NULL || n < 2) {
        return;
    }
    size_t max_value;
    if (!get_nonnegative_max(array, n, &max_value)) {
        return;
    }

    for (size_t place_value = 1; max_value / place_value > 0; place_value *= 10) {
        counting_pass(array, n, place_value);
    }
}

typedef struct Node {
    int data;
    struct Node *next;
} Node;

/* 연결 리스트 맨 뒤에 값 추가 */
void append(Node **head, int value)
{
    Node *newNode = malloc(sizeof(Node));

    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node *temp = *head;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
}

/* 연결 리스트 삽입 정렬 */
Node *insertion_sort(Node *head)
{
    Node *sorted = NULL;

    while (head != NULL) {

        Node *current = head;
        head = head->next;

        /* sorted가 비었거나 맨 앞에 삽입해야 하는 경우 */
        if (sorted == NULL || current->data < sorted->data) {

            current->next = sorted;
            sorted = current;
        }

        else {

            Node *temp = sorted;

            while (temp->next != NULL &&
                   temp->next->data <= current->data) {

                temp = temp->next;
            }

            current->next = temp->next;
            temp->next = current;
        }
    }

    return sorted;
}

/* Bucket Sort */
void bucket_sort(int A[], int n)
{
    if (n <= 1)
        return;

    /* 최댓값 찾기 */
    int max = A[0];

    for (int i = 1; i < n; i++) {
        if (A[i] > max)
            max = A[i];
    }

    /* n개의 버킷 생성 */
    Node **B = calloc(n, sizeof(Node *));

    /* 각 정수를 버킷에 분배 */
    for (int i = 0; i < n; i++) {

        int index =
            (int)(((long long)A[i] * n) / (max + 1));

        append(&B[index], A[i]);
    }

    /* 각 버킷 정렬 */
    for (int i = 0; i < n; i++) {
        B[i] = insertion_sort(B[i]);
    }

    /* 버킷들을 다시 배열 A에 저장 */
    int k = 0;

    for (int i = 0; i < n; i++) {

        Node *current = B[i];

        while (current != NULL) {

            A[k++] = current->data;

            Node *temp = current;
            current = current->next;

            free(temp);
        }
    }

    free(B);
}
// 버킷에 값 삽입
void insertBucket(Node **bucket, int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = value;
    newNode->next = *bucket;

    *bucket = newNode;
}

// 연결 리스트 삽입 정렬
Node *insertionSort(Node *head)
{
    Node *sorted = NULL;

    while (head != NULL) {
        Node *current = head;
        head = head->next;

        if (sorted == NULL || current->data < sorted->data) {
            current->next = sorted;
            sorted = current;
        } else {
            Node *temp = sorted;

            while (temp->next != NULL &&
                   temp->next->data <= current->data) {
                temp = temp->next;
            }

            current->next = temp->next;
            temp->next = current;
        }
    }

    return sorted;
}

// 버킷 정렬
void bucketSort(int A[], int n)
{
    if (n <= 1)
        return;

    // 최솟값, 최댓값 찾기
    int min = A[0];
    int max = A[0];

    for (int i = 1; i < n; i++) {
        if (A[i] < min)
            min = A[i];

        if (A[i] > max)
            max = A[i];
    }

    // 모든 값이 같은 경우
    if (min == max)
        return;

    // B[0 ... n-1]
    Node **B = (Node **)calloc(n, sizeof(Node *));

    // 각 데이터를 적절한 버킷에 삽입
    for (int i = 0; i < n; i++) {
        int index =
            (int)(((long long)(A[i] - min) * (n - 1)) / (max - min));

        insertBucket(&B[index], A[i]);
    }

    // 각 버킷을 삽입 정렬
    for (int i = 0; i < n; i++) {
        B[i] = insertionSort(B[i]);
    }

    // 버킷을 순서대로 합치기
    int k = 0;

    for (int i = 0; i < n; i++) {
        Node *current = B[i];

        while (current != NULL) {
            A[k++] = current->data;

            Node *temp = current;
            current = current->next;

            free(temp);
        }
    }

    free(B);
}
// 버킷의 맨 뒤에 값 삽입
void insert(Node **head, int value)
{

    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = value;
    newNode->next = NULL;

    // 비어 있는 버킷
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    // 마지막 노드까지 이동
    Node *p = *head;

    while (p->next != NULL) {
        p = p->next;
    }

    p->next = newNode;
}

// 정렬된 연결 리스트에 노드 삽입
void sortedInsert(Node **head, Node *node)
{

    // 맨 앞에 들어가는 경우
    if (*head == NULL || (*head)->data >= node->data) {

        node->next = *head;
        *head = node;

        return;
    }

    Node *p = *head;

    while (p->next != NULL &&
           p->next->data < node->data) {

        p = p->next;
    }

    node->next = p->next;
    p->next = node;
}

// 연결 리스트 insertion sort
void insertionSort(Node **head)
{

    Node *sorted = NULL;
    Node *current = *head;

    while (current != NULL) {

        Node *next = current->next;

        sortedInsert(&sorted, current);

        current = next;
    }

    *head = sorted;
}

// Bucket Sort
void bucketSort(int array[], int n, int k)
{

    // 1. 최대값 찾기
    int max = array[0];

    for (int i = 1; i < n; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    int M = max + 1;

    // 2. k개의 빈 연결 리스트 생성
    Node **buckets =
        (Node **)malloc(k * sizeof(Node *));

    for (int i = 0; i < k; i++) {
        buckets[i] = NULL;
    }

    // 3. 원소들을 각 버킷에 삽입
    for (int i = 0; i < n; i++) {

        int bucketIndex =
            (k * array[i]) / M;

        insert(
            &buckets[bucketIndex],
            array[i]);
    }

    // 4. 각각의 버킷 정렬
    for (int i = 0; i < k; i++) {

        insertionSort(
            &buckets[i]);
    }

    // 5. 버킷들을 순서대로 다시 배열에 저장
    int index = 0;

    for (int i = 0; i < k; i++) {

        Node *p = buckets[i];

        while (p != NULL) {

            array[index++] = p->data;

            p = p->next;
        }
    }

    // 6. 연결 리스트 메모리 해제
    for (int i = 0; i < k; i++) {

        Node *p = buckets[i];

        while (p != NULL) {

            Node *temp = p;

            p = p->next;

            free(temp);
        }
    }

    free(buckets);
}
// 연결 리스트에 원소 추가
void pushNode(Node **head, int value)
{

    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = value;
    newNode->next = *head;

    *head = newNode;
}

// 연결 리스트 삽입 정렬
Node *insertionSort(Node *head)
{

    Node *sorted = NULL;

    while (head != NULL) {

        Node *current = head;
        head = head->next;

        // 맨 앞에 삽입
        if (sorted == NULL || current->data < sorted->data) {

            current->next = sorted;
            sorted = current;
        }

        else {

            Node *temp = sorted;

            while (temp->next != NULL &&
                   temp->next->data <= current->data) {

                temp = temp->next;
            }

            current->next = temp->next;
            temp->next = current;
        }
    }

    return sorted;
}

// Bucket Sort
void bucketSort(int arr[], int n)
{

    if (n <= 1)
        return;

    // 1) 최솟값, 최댓값 찾기
    int min = arr[0];
    int max = arr[0];

    for (int i = 1; i < n; i++) {

        if (arr[i] < min)
            min = arr[i];

        if (arr[i] > max)
            max = arr[i];
    }

    if (min == max)
        return;

    // 2) 버킷의 head를 저장하는 배열 생성
    Node **buckets =
        (Node **)malloc(n * sizeof(Node *));

    for (int i = 0; i < n; i++) {
        buckets[i] = NULL;
    }

    // 3) 각 원소를 적절한 버킷에 삽입
    for (int i = 0; i < n; i++) {

        int bi =
            (long long)(arr[i] - min) * (n - 1) / (max - min);

        pushNode(&buckets[bi], arr[i]);
    }

    // 4) 각 버킷 정렬
    for (int i = 0; i < n; i++) {

        buckets[i] =
            insertionSort(buckets[i]);
    }

    // 5) 다시 배열에 합치기
    int index = 0;

    for (int i = 0; i < n; i++) {

        Node *current = buckets[i];

        while (current != NULL) {

            arr[index++] = current->data;

            current = current->next;
        }
    }

    // 6) 연결 리스트 메모리 해제
    for (int i = 0; i < n; i++) {

        Node *current = buckets[i];

        while (current != NULL) {

            Node *temp = current;

            current = current->next;

            free(temp);
        }
    }

    free(buckets);
}

void print_array(int *array, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
int main()
{
    // int values[] = {11, 13, 7, 12, 16, 9, 24, 5, 10, 3};
    int values[] = {3, 3};
    size_t n = sizeof(values) / sizeof(*values);

    size_t sort_number = 4;

    switch (sort_number) {
    case 0:
        bubble_sort(values, n);
        break;
    case 1:
        selection_sort(values, n);
        break;
    case 2:
        insertion_sort(values, n);
        break;
    case 3:
        merge_sort(values, 0, n);
        break;
    case 4:
        quick_sort(values, 0, n);
        break;
    case 5:
        heap_sort(values, n);
        break;
    case 6:
        counting_sort(values, n);
        break;
    case 7:
        radix_sort(values, n);
        break;
    default:
        printf("Invalid sort choice.\n");
        return 1;
    }
    print_array(values, n);

    return 0;
}
