
// typedef struct Node {
//    int data;
//    struct Node *next;
//} Node;
//
///* 연결 리스트 맨 뒤에 값 추가 */
// void append(Node **head, int value)
//{
//     Node *newNode = malloc(sizeof(Node));
//
//     newNode->data = value;
//     newNode->next = NULL;
//
//     if (*head == NULL) {
//         *head = newNode;
//         return;
//     }
//
//     Node *temp = *head;
//
//     while (temp->next != NULL) {
//         temp = temp->next;
//     }
//
//     temp->next = newNode;
// }
//
///* 연결 리스트 삽입 정렬 */
// Node *insertion_sort(Node *head)
//{
//     Node *sorted = NULL;
//
//     while (head != NULL) {
//
//         Node *current = head;
//         head = head->next;
//
//         /* sorted가 비었거나 맨 앞에 삽입해야 하는 경우 */
//         if (sorted == NULL || current->data < sorted->data) {
//
//             current->next = sorted;
//             sorted = current;
//         }
//
//         else {
//
//             Node *temp = sorted;
//
//             while (temp->next != NULL &&
//                    temp->next->data <= current->data) {
//
//                 temp = temp->next;
//             }
//
//             current->next = temp->next;
//             temp->next = current;
//         }
//     }
//
//     return sorted;
// }
//
///* Bucket Sort */
// void bucket_sort(int A[], int n)
//{
//     if (n <= 1)
//         return;
//
//     /* 최댓값 찾기 */
//     int max = A[0];
//
//     for (int i = 1; i < n; i++) {
//         if (A[i] > max)
//             max = A[i];
//     }
//
//     /* n개의 버킷 생성 */
//     Node **B = calloc(n, sizeof(Node *));
//
//     /* 각 정수를 버킷에 분배 */
//     for (int i = 0; i < n; i++) {
//
//         int index =
//             (int)(((long long)A[i] * n) / (max + 1));
//
//         append(&B[index], A[i]);
//     }
//
//     /* 각 버킷 정렬 */
//     for (int i = 0; i < n; i++) {
//         B[i] = insertion_sort(B[i]);
//     }
//
//     /* 버킷들을 다시 배열 A에 저장 */
//     int k = 0;
//
//     for (int i = 0; i < n; i++) {
//
//         Node *current = B[i];
//
//         while (current != NULL) {
//
//             A[k++] = current->data;
//
//             Node *temp = current;
//             current = current->next;
//
//             free(temp);
//         }
//     }
//
//     free(B);
// }
//// 버킷에 값 삽입
// void insertBucket(Node **bucket, int value)
//{
//     Node *newNode = (Node *)malloc(sizeof(Node));
//
//     newNode->data = value;
//     newNode->next = *bucket;
//
//     *bucket = newNode;
// }
//
//// 연결 리스트 삽입 정렬
// Node *insertionSort(Node *head)
//{
//     Node *sorted = NULL;
//
//     while (head != NULL) {
//         Node *current = head;
//         head = head->next;
//
//         if (sorted == NULL || current->data < sorted->data) {
//             current->next = sorted;
//             sorted = current;
//         } else {
//             Node *temp = sorted;
//
//             while (temp->next != NULL &&
//                    temp->next->data <= current->data) {
//                 temp = temp->next;
//             }
//
//             current->next = temp->next;
//             temp->next = current;
//         }
//     }
//
//     return sorted;
// }
//
//// 버킷 정렬
// void bucketSort(int A[], int n)
//{
//     if (n <= 1)
//         return;
//
//     // 최솟값, 최댓값 찾기
//     int min = A[0];
//     int max = A[0];
//
//     for (int i = 1; i < n; i++) {
//         if (A[i] < min)
//             min = A[i];
//
//         if (A[i] > max)
//             max = A[i];
//     }
//
//     // 모든 값이 같은 경우
//     if (min == max)
//         return;
//
//     // B[0 ... n-1]
//     Node **B = (Node **)calloc(n, sizeof(Node *));
//
//     // 각 데이터를 적절한 버킷에 삽입
//     for (int i = 0; i < n; i++) {
//         int index =
//             (int)(((long long)(A[i] - min) * (n - 1)) / (max - min));
//
//         insertBucket(&B[index], A[i]);
//     }
//
//     // 각 버킷을 삽입 정렬
//     for (int i = 0; i < n; i++) {
//         B[i] = insertionSort(B[i]);
//     }
//
//     // 버킷을 순서대로 합치기
//     int k = 0;
//
//     for (int i = 0; i < n; i++) {
//         Node *current = B[i];
//
//         while (current != NULL) {
//             A[k++] = current->data;
//
//             Node *temp = current;
//             current = current->next;
//
//             free(temp);
//         }
//     }
//
//     free(B);
// }
//// 버킷의 맨 뒤에 값 삽입
// void insert(Node **head, int value)
//{
//
//     Node *newNode = (Node *)malloc(sizeof(Node));
//
//     newNode->data = value;
//     newNode->next = NULL;
//
//     // 비어 있는 버킷
//     if (*head == NULL) {
//         *head = newNode;
//         return;
//     }
//
//     // 마지막 노드까지 이동
//     Node *p = *head;
//
//     while (p->next != NULL) {
//         p = p->next;
//     }
//
//     p->next = newNode;
// }
//
//// 정렬된 연결 리스트에 노드 삽입
// void sortedInsert(Node **head, Node *node)
//{
//
//     // 맨 앞에 들어가는 경우
//     if (*head == NULL || (*head)->data >= node->data) {
//
//         node->next = *head;
//         *head = node;
//
//         return;
//     }
//
//     Node *p = *head;
//
//     while (p->next != NULL &&
//            p->next->data < node->data) {
//
//         p = p->next;
//     }
//
//     node->next = p->next;
//     p->next = node;
// }
//
//// 연결 리스트 insertion sort
// void insertionSort(Node **head)
//{
//
//     Node *sorted = NULL;
//     Node *current = *head;
//
//     while (current != NULL) {
//
//         Node *next = current->next;
//
//         sortedInsert(&sorted, current);
//
//         current = next;
//     }
//
//     *head = sorted;
// }
//
//// Bucket Sort
// void bucketSort(int array[], int n, int k)
//{
//
//     // 1. 최대값 찾기
//     int max = array[0];
//
//     for (int i = 1; i < n; i++) {
//         if (array[i] > max) {
//             max = array[i];
//         }
//     }
//
//     int M = max + 1;
//
//     // 2. k개의 빈 연결 리스트 생성
//     Node **buckets =
//         (Node **)malloc(k * sizeof(Node *));
//
//     for (int i = 0; i < k; i++) {
//         buckets[i] = NULL;
//     }
//
//     // 3. 원소들을 각 버킷에 삽입
//     for (int i = 0; i < n; i++) {
//
//         int bucketIndex =
//             (k * array[i]) / M;
//
//         insert(
//             &buckets[bucketIndex],
//             array[i]);
//     }
//
//     // 4. 각각의 버킷 정렬
//     for (int i = 0; i < k; i++) {
//
//         insertionSort(
//             &buckets[i]);
//     }
//
//     // 5. 버킷들을 순서대로 다시 배열에 저장
//     int index = 0;
//
//     for (int i = 0; i < k; i++) {
//
//         Node *p = buckets[i];
//
//         while (p != NULL) {
//
//             array[index++] = p->data;
//
//             p = p->next;
//         }
//     }
//
//     // 6. 연결 리스트 메모리 해제
//     for (int i = 0; i < k; i++) {
//
//         Node *p = buckets[i];
//
//         while (p != NULL) {
//
//             Node *temp = p;
//
//             p = p->next;
//
//             free(temp);
//         }
//     }
//
//     free(buckets);
// }
//// 연결 리스트에 원소 추가
// void pushNode(Node **head, int value)
//{
//
//     Node *newNode = (Node *)malloc(sizeof(Node));
//
//     newNode->data = value;
//     newNode->next = *head;
//
//     *head = newNode;
// }
//
//// 연결 리스트 삽입 정렬
// Node *insertionSort(Node *head)
//{
//
//     Node *sorted = NULL;
//
//     while (head != NULL) {
//
//         Node *current = head;
//         head = head->next;
//
//         // 맨 앞에 삽입
//         if (sorted == NULL || current->data < sorted->data) {
//
//             current->next = sorted;
//             sorted = current;
//         }
//
//         else {
//
//             Node *temp = sorted;
//
//             while (temp->next != NULL &&
//                    temp->next->data <= current->data) {
//
//                 temp = temp->next;
//             }
//
//             current->next = temp->next;
//             temp->next = current;
//         }
//     }
//
//     return sorted;
// }
//
//// Bucket Sort
// void bucketSort(int arr[], int n)
//{
//
//     if (n <= 1)
//         return;
//
//     // 1) 최솟값, 최댓값 찾기
//     int min = arr[0];
//     int max = arr[0];
//
//     for (int i = 1; i < n; i++) {
//
//         if (arr[i] < min)
//             min = arr[i];
//
//         if (arr[i] > max)
//             max = arr[i];
//     }
//
//     if (min == max)
//         return;
//
//     // 2) 버킷의 head를 저장하는 배열 생성
//     Node **buckets =
//         (Node **)malloc(n * sizeof(Node *));
//
//     for (int i = 0; i < n; i++) {
//         buckets[i] = NULL;
//     }
//
//     // 3) 각 원소를 적절한 버킷에 삽입
//     for (int i = 0; i < n; i++) {
//
//         int bi =
//             (long long)(arr[i] - min) * (n - 1) / (max - min);
//
//         pushNode(&buckets[bi], arr[i]);
//     }
//
//     // 4) 각 버킷 정렬
//     for (int i = 0; i < n; i++) {
//
//         buckets[i] =
//             insertionSort(buckets[i]);
//     }
//
//     // 5) 다시 배열에 합치기
//     int index = 0;
//
//     for (int i = 0; i < n; i++) {
//
//         Node *current = buckets[i];
//
//         while (current != NULL) {
//
//             arr[index++] = current->data;
//
//             current = current->next;
//         }
//     }
//
//     // 6) 연결 리스트 메모리 해제
//     for (int i = 0; i < n; i++) {
//
//         Node *current = buckets[i];
//
//         while (current != NULL) {
//
//             Node *temp = current;
//
//             current = current->next;
//
//             free(temp);
//         }
//     }
//
//     free(buckets);
// }
//
//
//
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