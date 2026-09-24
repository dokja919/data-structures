#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 8

typedef struct Entry {
    int key;
    struct Entry *next;
} Entry;

Entry *buckets[CAPACITY];

/* 해시 함수 */
unsigned int hash(int key)
{
    return key % CAPACITY;
}

/* 삽입 */
void insert(int key)
{
    unsigned int i = hash(key);

    /* 중복 key 확인 */
    for (Entry *e = buckets[i]; e != NULL; e = e->next) {
        if (e->key == key) {
            return;
        }
    }

    Entry *e = malloc(sizeof(Entry));

    e->key = key;

    /* 연결 리스트 앞에 삽입 */
    e->next = buckets[i];
    buckets[i] = e;
}

/* 검색 */
Entry *search(int key)
{
    unsigned int i = hash(key);

    for (Entry *e = buckets[i]; e != NULL; e = e->next) {

        if (e->key == key) {
            return e;
        }
    }

    return NULL;
}

/* 삭제 */
void removeKey(int key)
{
    unsigned int i = hash(key);

    Entry *current = buckets[i];
    Entry *previous = NULL;

    while (current != NULL) {

        if (current->key == key) {

            if (previous == NULL) {
                buckets[i] = current->next;
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
void printBuckets(void)
{
    for (int i = 0; i < CAPACITY; i++) {

        printf("bucket %d:", i);

        for (Entry *e = buckets[i]; e != NULL; e = e->next) {
            printf(" -> %d", e->key);
        }

        printf("\n");
    }
}

int main(void)
{
    insert(10);
    insert(18);
    insert(26);
    insert(7);
    insert(15);

    printBuckets();

    printf("\n");

    if (search(18) != NULL)
        printf("18 found\n");
    else
        printf("18 not found\n");

    removeKey(18);

    if (search(18) != NULL)
        printf("18 found\n");
    else
        printf("18 not found\n");

    return 0;
}