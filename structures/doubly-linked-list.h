#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

typedef struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct LinkedList {
    Node* head;
    Node* tail;
    unsigned int count;
} LinkedList;

LinkedList* init_ll();
void free_ll(LinkedList* ll);

void push(LinkedList* ll, int value);
int  pop(LinkedList* ll);

void enqueue(LinkedList* ll, int value);
int  dequeue(LinkedList* ll);

void insert_at(LinkedList* ll, int value, unsigned int index);
int  remove_at(LinkedList* ll, unsigned int index);
int  value_at(LinkedList* ll, unsigned int index);

int  index_of(LinkedList* ll, int value);
void print_ll(LinkedList* ll);

#endif
