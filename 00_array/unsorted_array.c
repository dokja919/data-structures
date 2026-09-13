
// void heapify(int *list, size_t n, size_t root)
//{
//    while (true) {
//        size_t largest = root;
//        size_t left = root * 2 + 1;
//        size_t right = root * 2 + 2;
//
//        if (left < n && list[left] > list[largest]) {
//            largest = left;
//        }
//        if (right < n && list[right] > list[largest]) {
//            largest = right;
//        }
//
//        if (largest == root) {
//            break;
//        }
//
//        swap(&list[root], &list[largest]);
//        root = largest;
//    }
//}
//
// void sort_heap(int *list, size_t n)
//{
//    if (n < 2) {
//        return;
//    }
//
//    for (size_t i = n / 2; i > 0; i--) {
//        heapify(list, n, i - 1);
//    }
//
//    for (size_t i = n; i > 1; i--) {
//        swap(&list[0], &list[i - 1]);
//        heapify(list, i - 1, 0);
//    }
//}
// void Insert(int A[], int n)
//{
//     int i = n, temp;
//     temp = A[i];
//     while (i > 1 && temp > A[i / 2]) {
//         A[i] = A[i / 2];
//         i = i / 2;
//     }
//     A[i] = temp;
// }
// void HInsert(Heap *ph, HData data)
//{
//    int idx = ph->numOfData + 1;
//
//    while (idx != 1) {
//        //	if(pr < (ph->heapArr[GetParentIDX(idx)].pr))
//        if (ph->comp(data, ph->heapArr[GetParentIDX(idx)]) > 0) {
//            ph->heapArr[idx] = ph->heapArr[GetParentIDX(idx)];
//            idx = GetParentIDX(idx);
//        } else {
//            break;
//        }
//    }
//
//    ph->heapArr[idx] = data;
//    ph->numOfData += 1;
//}
//
// int Delete(int A[], int n)
//{
//     int i, j, x, temp, val;
//     val = A[1];
//     x = A[n];
//     A[1] = A[n];
//     A[n] = val;
//     i = 1;
//     j = i * 2;
//     while (j <= n - 1) {
//         if (j < n - 1 && A[j + 1] > A[j])
//             j = j + 1;
//         if (A[i] < A[j]) {
//             temp = A[i];
//             A[i] = A[j];
//             A[j] = temp;
//             i = j;
//             j = 2 * j;
//         } else
//             break;
//     }
//     return val;
// }
// int main()
//{
//     int H[] = {0, 14, 15, 5, 20, 30, 8, 40};
//     int i;
//     for (i = 2; i <= 7; i++)
//         Insert(H, i);
//
//     for (i = 7; i > 1; i--) {
//         Delete(H, i);
//     }
//     for (i = 1; i <= 7; i++)
//         printf("%d ", H[i]);
//     printf("\n");
//
//     return 0;
// }
// HData HDelete(Heap *ph)
//{
//    HData retData = ph->heapArr[1];
//    HData lastElem = ph->heapArr[ph->numOfData];
//
//    int parentIdx = 1;
//    int childIdx;
//
//    while (childIdx = GetHiPriChildIDX(ph, parentIdx)) {
//        //	if(lastElem.pr <= ph->heapArr[childIdx].pr)
//        if (ph->comp(lastElem, ph->heapArr[childIdx]) >= 0)
//            break;
//
//        ph->heapArr[parentIdx] = ph->heapArr[childIdx];
//        parentIdx = childIdx;
//    }
//
//    ph->heapArr[parentIdx] = lastElem;
//    ph->numOfData -= 1;
//    return retData;
//}
// void HeapSort(int arr[], int n, PriorityComp pc)
//{
//    Heap heap;
//    int i;
//
//    HeapInit(&heap, pc);
//
//    // 정렬 대상을 가지고 힙을 구성한다.
//    for (i = 0; i < n; i++)
//        HInsert(&heap, arr[i]);
//
//    // 순서대로 하나씩 꺼내서 정렬을 완성한다.
//    for (i = 0; i < n; i++)
//        arr[i] = HDelete(&heap);
//}
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