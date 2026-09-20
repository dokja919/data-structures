
// 하나의 bucket
typedef struct {
    Node *head;
} Bucket;

// bucket에 원소 추가
void pushBucket(Bucket *bucket, int value)
{

    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = value;
    newNode->next = bucket->head;

    bucket->head = newNode;
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

            // 삽입할 위치 찾기
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

    // 모든 값이 같으면 이미 정렬된 상태
    if (min == max)
        return;

    // 2) n개의 bucket 생성
    Bucket *buckets =
        (Bucket *)malloc(n * sizeof(Bucket));

    for (int i = 0; i < n; i++) {
        buckets[i].head = NULL;
    }

    // 3) 각 원소를 적절한 bucket에 삽입
    for (int i = 0; i < n; i++) {

        int bi =
            (long long)(arr[i] - min) * (n - 1) / (max - min);

        pushBucket(&buckets[bi], arr[i]);
    }

    // 4) 각 bucket을 삽입 정렬
    for (int i = 0; i < n; i++) {

        buckets[i].head =
            insertionSort(buckets[i].head);
    }

    // 5) 모든 bucket을 다시 arr에 합치기
    int index = 0;

    for (int i = 0; i < n; i++) {

        Node *current = buckets[i].head;

        while (current != NULL) {

            arr[index++] = current->data;

            current = current->next;
        }
    }

    // 6) 동적 메모리 해제
    for (int i = 0; i < n; i++) {

        Node *current = buckets[i].head;

        while (current != NULL) {

            Node *temp = current;

            current = current->next;

            free(temp);
        }
    }

    free(buckets);
}
//////////////

typedef struct {
    int *data;
    int size;
    int capacity;
} Bucket;

// 버킷에 값 추가
void insertBucket(Bucket *bucket, int value)
{
    if (bucket->size == bucket->capacity) {
        bucket->capacity *= 2;
        bucket->data = (int *)realloc(
            bucket->data,
            bucket->capacity * sizeof(int));
    }

    bucket->data[bucket->size++] = value;
}

// 각 버킷을 정렬하는 함수
// pseudocode의 nextSort()
void nextSort(int arr[], int n)
{
    // insertion sort 사용
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

// Bucket Sort
void bucketSort(int array[], int n, int k)
{

    // buckets ← new array of k empty lists
    Bucket *buckets = (Bucket *)malloc(k * sizeof(Bucket));

    for (int i = 0; i < k; i++) {
        buckets[i].size = 0;
        buckets[i].capacity = 2;
        buckets[i].data =
            (int *)malloc(2 * sizeof(int));
    }

    // M ← 1 + maximum value
    int max = array[0];

    for (int i = 1; i < n; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    int M = max + 1;

    // 각 값을 버킷에 삽입
    for (int i = 0; i < n; i++) {

        int bucketIndex =
            (k * array[i]) / M;

        insertBucket(
            &buckets[bucketIndex],
            array[i]);
    }

    // 각 버킷 정렬
    for (int i = 0; i < k; i++) {
        nextSort(
            buckets[i].data,
            buckets[i].size);
    }

    // 버킷들을 다시 array에 연결
    int index = 0;

    for (int i = 0; i < k; i++) {

        for (int j = 0; j < buckets[i].size; j++) {

            array[index++] =
                buckets[i].data[j];
        }
    }

    // 메모리 해제
    for (int i = 0; i < k; i++) {
        free(buckets[i].data);
    }

    free(buckets);
}
/////////////////////

// 연결 리스트 맨 뒤에 삽입
void insert(Node **head, int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node *p = *head;

    while (p->next != NULL) {
        p = p->next;
    }

    p->next = newNode;
}

// 정렬된 연결 리스트에 노드 삽입
void sortedInsert(Node **head, Node *node)
{
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

// 연결 리스트 삽입 정렬
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
void bucketSort(int arr[], int n)
{

    // 최솟값, 최댓값 구하기
    int min = arr[0];
    int max = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] < min)
            min = arr[i];

        if (arr[i] > max)
            max = arr[i];
    }

    // 1) n개의 빈 버킷 생성
    Node **buckets =
        (Node **)malloc(n * sizeof(Node *));

    for (int i = 0; i < n; i++) {
        buckets[i] = NULL;
    }

    // 2) 각 정수를 적절한 버킷에 삽입
    for (int i = 0; i < n; i++) {

        int bucketIndex =
            (long long)n * (arr[i] - min) / ((long long)max - min + 1);

        insert(&buckets[bucketIndex], arr[i]);
    }

    // 3) 각 버킷을 insertion sort
    for (int i = 0; i < n; i++) {
        insertionSort(&buckets[i]);
    }

    // 4) 모든 버킷을 다시 arr에 합치기
    int index = 0;

    for (int i = 0; i < n; i++) {

        Node *p = buckets[i];

        while (p != NULL) {
            arr[index++] = p->data;
            p = p->next;
        }
    }

    // 메모리 해제
    for (int i = 0; i < n; i++) {

        Node *p = buckets[i];

        while (p != NULL) {
            Node *temp = p;
            p = p->next;
            free(temp);
        }
    }

    free(buckets);
}

// static int a_linear_search_transpose(a_list *list, a_item key)
//{
//     if (list == NULL) {
//         return -1;
//     }
//     int index = 0;
//
//     while (index < list->size && list->items[index] != key) {
//         index++;
//     }
//     if (index == list->size) {
//         return -1;
//     }
//     if (index > 0) {
//         a_item temp = list->items[index - 1];
//         list->items[index - 1] = list->items[index];
//         list->items[index] = temp;
//         index--;
//     }
//     return index;
// }
// static int a_linear_search_move2front(a_list *list, a_item key)
//{
//     if (list == NULL) {
//         return -1;
//     }
//     int index = 0;
//
//     while (index < list->size && list->items[index] != key) {
//         index++;
//     }
//     if (index == list->size) {
//         return -1;
//     }
//     while (index > 0) {
//         list->items[index] = list->items[index - 1];
//         index--;
//     }
//     list->items[0] = key;
//
//     return index;
// }
//