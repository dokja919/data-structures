#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

typedef struct Node {
    int key;
    struct Node *next;
} Node;

/* 해시 테이블 */
Node *hashTable[TABLE_SIZE];

/* 해시 함수 */
int hashFunction(int key)
{
    return key % TABLE_SIZE;
}

/* 해시 테이블 초기화 */
void initHashTable(void)
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

/* 데이터 삽입 */
void insert(int key)
{
    int index = hashFunction(key);

    Node *newNode = malloc(sizeof(Node));

    newNode->key = key;

    /* 연결 리스트 앞에 삽입 */
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

/* 데이터 검색 */
Node *search(int key)
{
    int index = hashFunction(key);

    Node *current = hashTable[index];

    while (current != NULL) {

        if (current->key == key) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

/* 해시 테이블 출력 */
void printHashTable(void)
{
    for (int i = 0; i < TABLE_SIZE; i++) {

        printf("[%d]", i);

        Node *current = hashTable[i];

        while (current != NULL) {
            printf(" -> %d", current->key);
            current = current->next;
        }

        printf("\n");
    }
}

/* 메모리 해제 */
void freeHashTable(void)
{
    for (int i = 0; i < TABLE_SIZE; i++) {

        Node *current = hashTable[i];

        while (current != NULL) {

            Node *temp = current;
            current = current->next;

            free(temp);
        }

        hashTable[i] = NULL;
    }
}

int main(void)
{
    initHashTable();

    insert(12);
    insert(22);
    insert(42);

    printHashTable();

    Node *result = search(22);

    if (result != NULL) {
        printf("\n22 found\n");
    } else {
        printf("\n22 not found\n");
    }

    freeHashTable();

    return 0;
}