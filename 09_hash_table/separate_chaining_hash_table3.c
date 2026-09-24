#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *next;
} Node;

typedef struct Hash {
    int bucketCount;
    Node **table;
} Hash;

/* 해시 함수 */
int hashFunction(Hash *h, int key)
{
    return key % h->bucketCount;
}

/* 해시 테이블 초기화 */
void initHash(Hash *h, int bucketCount)
{
    h->bucketCount = bucketCount;

    h->table = malloc(sizeof(Node *) * bucketCount);

    for (int i = 0; i < bucketCount; i++) {
        h->table[i] = NULL;
    }
}

/* 삽입 */
void insertItem(Hash *h, int key)
{
    int index = hashFunction(h, key);

    Node *newNode = malloc(sizeof(Node));

    newNode->key = key;
    newNode->next = h->table[index];

    h->table[index] = newNode;
}

/* 삭제 */
void deleteItem(Hash *h, int key)
{
    int index = hashFunction(h, key);

    Node *current = h->table[index];
    Node *previous = NULL;

    while (current != NULL) {

        if (current->key == key) {

            if (previous == NULL) {
                h->table[index] = current->next;
            } else {
                previous->next = current->next;
            }

            free(current);
            return;
        }

        previous = current;
        current = current->next;
    }
}

/* 출력 */
void displayHash(Hash *h)
{
    for (int i = 0; i < h->bucketCount; i++) {

        printf("%d", i);

        Node *current = h->table[i];

        while (current != NULL) {
            printf(" --> %d", current->key);
            current = current->next;
        }

        printf("\n");
    }
}

/* 메모리 해제 */
void freeHash(Hash *h)
{
    for (int i = 0; i < h->bucketCount; i++) {

        Node *current = h->table[i];

        while (current != NULL) {

            Node *temp = current;
            current = current->next;

            free(temp);
        }
    }

    free(h->table);
}

int main(void)
{
    int a[] = {15, 11, 27, 8, 12};
    int n = sizeof(a) / sizeof(a[0]);

    Hash h;

    /* C++의 Hash h(7)에 해당 */
    initHash(&h, 7);

    for (int i = 0; i < n; i++) {
        insertItem(&h, a[i]);
    }

    /* 12 삭제 */
    deleteItem(&h, 12);

    /* 출력 */
    displayHash(&h);

    freeHash(&h);

    return 0;
}
