#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} LinkedList;

typedef struct {
    int m;             // hash table size
    LinkedList *table; // array of linked lists
} ChainedHashTable;

// Hash function
int hashFunction(int key, int m)
{
    return key % m;
}

// Initialize hash table
void initHashTable(ChainedHashTable *ht, int m)
{
    ht->m = m;

    ht->table = (LinkedList *)malloc(
        sizeof(LinkedList) * m);

    for (int i = 0; i < m; i++) {
        ht->table[i].head = NULL;
    }
}

// Insert at beginning of linked list
void insert(ChainedHashTable *ht, int data)
{

    int index = hashFunction(data, ht->m);

    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = ht->table[index].head;

    if (ht->table[index].head != NULL) {
        ht->table[index].head->prev = newNode;
    }

    ht->table[index].head = newNode;
}

// Search
Node *search(ChainedHashTable *ht, int key)
{

    int index = hashFunction(key, ht->m);

    Node *current = ht->table[index].head;

    while (current != NULL) {

        if (current->data == key) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

// Delete
void deleteNode(ChainedHashTable *ht, Node *node)
{

    if (node == NULL)
        return;

    int index = hashFunction(node->data, ht->m);

    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        // node is head
        ht->table[index].head = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    }

    free(node);
}

// Print hash table
void printHashTable(ChainedHashTable *ht)
{

    for (int i = 0; i < ht->m; i++) {

        printf("%d: ", i);

        Node *current = ht->table[i].head;

        while (current != NULL) {
            printf("%d", current->data);

            if (current->next != NULL)
                printf(" <-> ");

            current = current->next;
        }

        printf("\n");
    }
}

// Free memory
void freeHashTable(ChainedHashTable *ht)
{

    for (int i = 0; i < ht->m; i++) {

        Node *current = ht->table[i].head;

        while (current != NULL) {

            Node *temp = current;

            current = current->next;

            free(temp);
        }
    }

    free(ht->table);
}

int main(void)
{

    ChainedHashTable hashtable;

    // Equivalent to:
    // hashtable1 = ChainedHashTable(10)
    initHashTable(&hashtable, 10);

    // for i in range(10):
    //     hashtable1.insert(i)
    for (int i = 0; i < 10; i++) {
        insert(&hashtable, i);
    }

    printHashTable(&hashtable);

    // x = hashtable1.search(5)
    Node *x = search(&hashtable, 5);

    // hashtable1.delete(x)
    deleteNode(&hashtable, x);

    printf("\nAfter deleting 5:\n");

    printHashTable(&hashtable);

    // search(9)
    Node *result = search(&hashtable, 9);

    if (result != NULL)
        printf("\n9 found: %d\n", result->data);
    else
        printf("\n9 not found\n");

    // search(5)
    result = search(&hashtable, 5);

    if (result != NULL)
        printf("5 found: %d\n", result->data);
    else
        printf("5 not found\n");

    // hashtable1.insert(11)
    insert(&hashtable, 11);

    printf("\nAfter inserting 11:\n");

    printHashTable(&hashtable);

    freeHashTable(&hashtable);

    return 0;
}