#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

typedef struct Node {
    int key;
    struct Node *next;
} Node;

typedef struct HashTable {
    Node *buckets[TABLE_SIZE];
} HashTable;

/* 해시 함수 */
int hashFunction(int key)
{
    return key % TABLE_SIZE;
}

/* 해시 테이블 초기화 */
void initHashTable(HashTable *table)
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
}

/* 데이터 삽입 */
void insert(HashTable *table, int key)
{
    int index = hashFunction(key);

    Node *current = table->buckets[index];

    /* 이미 존재하는 key인지 확인 */
    while (current != NULL) {

        if (current->key == key) {
            return;
        }

        current = current->next;
    }

    /* 새로운 노드 생성 */
    Node *newNode = malloc(sizeof(Node));

    newNode->key = key;

    /* 연결 리스트의 앞에 삽입 */
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
}

/* 데이터 검색 */
Node *search(HashTable *table, int key)
{
    int index = hashFunction(key);

    Node *current = table->buckets[index];

    while (current != NULL) {

        if (current->key == key) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

/* 데이터 삭제 */
void deleteKey(HashTable *table, int key)
{
    int index = hashFunction(key);

    Node *current = table->buckets[index];
    Node *previous = NULL;

    while (current != NULL) {

        if (current->key == key) {

            if (previous == NULL) {
                /* 첫 번째 노드 삭제 */
                table->buckets[index] = current->next;
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

/* 해시 테이블 출력 */
void printHashTable(HashTable *table)
{
    for (int i = 0; i < TABLE_SIZE; i++) {

        printf("[%d] ", i);

        Node *current = table->buckets[i];

        while (current != NULL) {

            printf("-> %d ", current->key);

            current = current->next;
        }

        printf("\n");
    }
}

/* 메모리 해제 */
void freeHashTable(HashTable *table)
{
    for (int i = 0; i < TABLE_SIZE; i++) {

        Node *current = table->buckets[i];

        while (current != NULL) {

            Node *temp = current;
            current = current->next;

            free(temp);
        }

        table->buckets[i] = NULL;
    }
}

int main(void)
{
    HashTable table;

    initHashTable(&table);

    insert(&table, 10);
    insert(&table, 20);
    insert(&table, 15);
    insert(&table, 25);
    insert(&table, 35);

    printf("=== Hash Table ===\n");
    printHashTable(&table);

    printf("\n=== Search ===\n");

    Node *result = search(&table, 25);

    if (result != NULL) {
        printf("25 found\n");
    } else {
        printf("25 not found\n");
    }

    printf("\n=== Delete 25 ===\n");

    deleteKey(&table, 25);

    printHashTable(&table);

    freeHashTable(&table);

    return 0;
}