// int partition(int *list, size_t left, size_t right)
//{
//     int pivot = list[left];
//     size_t i = left;
//     size_t j = right;
//
//     do {
//         do {
//             i++;
//         } while (list[i] <= pivot);
//         do {
//             j--;
//         } while (list[j] > pivot);
//
//         if (i < j)
//             swap(&list[i], &list[j]);
//     } while (i < j);
//
//     swap(&list[left], &list[j]);
//     return j;
// }
// int Partition(int arr[], int left, int right)
//{
//     int pivot = arr[left]; // 피벗의 위치는 가장 왼쪽!
//     int low = left + 1;
//     int high = right;
//
//     printf("피벗: %d \n", pivot);
//
//     while (low <= high) // 교차되지 않을 때까지 반복
//     {
//         /*
//         while(pivot > arr[low])
//                 low++;
//
//         while(pivot < arr[high])
//                 high--;
//         */
//
//         while (pivot >= arr[low] && low <= right)
//             low++;
//
//         while (pivot <= arr[high] && high >= (left + 1))
//             high--;
//
//         if (low <= high)          // 교차되지 않은 상태라면 Swap 실행
//             Swap(arr, low, high); // low와 high가 가리키는 대상 교환
//     }
//
//     Swap(arr, left, high); // 피벗과 high가 가리키는 대상 교환
//     return high;           // 옮겨진 피벗의 위치 정보 반환
// }
// int Partition(int arr[], int left, int right)
//{
//     int pivot = arr[left]; // 피벗의 위치는 가장 왼쪽!
//     int low = left + 1;
//     int high = right;
//
//     while (low <= high) // 교차되지 않을 때까지 반복
//     {
//         while (pivot > arr[low])
//             low++;
//
//         while (pivot < arr[high])
//             high--;
//
//         /*
//         while(pivot >= arr[low] && low <= right)
//                 low++;
//
//         while(pivot <= arr[high] && high >= (left+1))
//                 high--;
//         */
//
//         if (low <= high)          // 교차되지 않은 상태라면 Swap 실행
//             Swap(arr, low, high); // low와 high가 가리키는 대상 교환
//     }
//
//     Swap(arr, left, high); // 피벗과 high가 가리키는 대상 교환
//     return high;           // 옮겨진 피벗의 위치 정보 반환
// }
// int Partition(int DataSet[], int Left, int Right)
//{
//     int First = Left;
//     int Pivot = DataSet[First];
//
//     ++Left;
//
//     while (Left <= Right) {
//         while (DataSet[Left] <= Pivot && Left < Right)
//             ++Left;
//
//         while (DataSet[Right] >= Pivot && Left <= Right)
//             --Right;
//
//         if (Left < Right)
//             Swap(&DataSet[Left], &DataSet[Right]);
//         else
//             break;
//     }
//
//     Swap(&DataSet[First], &DataSet[Right]);
//
//     return Right;
// }
//
// int partition(int list[], int left, int right)
//{
//     int pivot, temp;
//     int low, high;
//
//     low = left;
//     high = right + 1;
//     pivot = list[left];
//     do {
//         do
//             low++;
//         while (list[low] < pivot);
//         do
//             high--;
//         while (list[high] > pivot);
//         if (low < high)
//             SWAP(list[low], list[high], temp);
//     } while (low < high);
//
//     SWAP(list[left], list[high], temp);
//     return high;
// }
// int partition(int A[], int p, int r)
//{
//     int x = A[r]; /* pivot */
//     int i = p - 1;
//
//     for (int j = p; j < r; j++) {
//         if (A[j] <= x) {
//             i++;
//             swap(&A[i], &A[j]);
//         }
//     }
//
//     swap(&A[i + 1], &A[r]);
//     return i + 1;
// }
// size_t partition(int arr[], size_t left, size_t right)
//{
//     int pivot = arr[right];
//     size_t i = left;
//
//     for (size_t j = left; j < right; j++) {
//         if (arr[j] <= pivot) {
//             swap(&arr[i], &arr[j]);
//             i++;
//         }
//     }
//
//     swap(&arr[i], &arr[right]);
//
//     return i;
// }
//
// void quick_sort(int arr[], size_t left, size_t right)
//{
//     if (left >= right)
//         return;
//
//     size_t pivot = partition(arr, left, right);
//
//     if (pivot > left)
//         quick_sort(arr, left, pivot - 1);
//
//     if (pivot < right)
//         quick_sort(arr, pivot + 1, right);
// }
//
///*
// * Quicksort using Lomuto partition.
// */
// void quicksort(int A[], int p, int r)
//{
//    if (p < r) {
//        int q = partition(A, p, r);
//
//        quicksort(A, p, q - 1); /* low side */
//        quicksort(A, q + 1, r); /* high side */
//    }
//}
// void quick_sort(int list[], int left, int right)
//{
//    if (left < right) {
//        int q = partition(list, left, right);
//        quick_sort(list, left, q - 1);
//        quick_sort(list, q + 1, right);
//    }
//}
// void QuickSort(int DataSet[], int Left, int Right)
//{
//    if (Left < Right) {
//        int Index = Partition(DataSet, Left, Right);
//
//        QuickSort(DataSet, Left, Index - 1);
//        QuickSort(DataSet, Index + 1, Right);
//    }
//}
//
// void QuickSort(int arr[], int left, int right)
//{
//    if (left <= right) {
//        int pivot = Partition(arr, left, right); // 둘로 나눠서
//        QuickSort(arr, left, pivot - 1);         // 왼쪽 영역을 정렬
//        QuickSort(arr, pivot + 1, right);        // 오른쪽 영역을 정렬
//    }
//}
//
// void QuickSort(int arr[], int left, int right)
//{
//    if (left < right) {
//        int pivot = Partition(arr, left, right); // 둘로 나눠서
//        QuickSort(arr, left, pivot - 1);         // 왼쪽 영역을 정렬
//        QuickSort(arr, pivot + 1, right);        // 오른쪽 영역을 정렬
//    }
//}
// void QuickSort(int A[], int l, int h)
//{
//    int j;
//
//    if (l < h) {
//        j = partition(A, l, h);
//        QuickSort(A, l, j);
//        QuickSort(A, j + 1, h);
//    }
//}
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