
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