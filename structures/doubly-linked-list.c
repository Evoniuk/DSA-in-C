#include <stdio.h>
#include <stdlib.h>

#include "doubly-linked-list.h"

Node* init_node(int value)
{
    Node* node = malloc(sizeof(Node));

    node->value = value;
    node->next  = NULL;
    node->prev  = NULL;

    return node;
}

LinkedList* init_ll()
{
    LinkedList* ll = malloc(sizeof(LinkedList));

    ll->head  = NULL;
    ll->tail  = NULL;
    ll->count = 0;

    return ll;
}

void free_ll(LinkedList* ll)
{
    for (Node* node = ll->head; node; node = node->next)
        free(node);

    free(ll);
}

void push(LinkedList* ll, int value)
{
    Node* new_node = init_node(value);

    if (!ll->head) ll->head = new_node;

    if (ll->tail) ll->tail->next = new_node;
    new_node->prev = ll->tail;

    ll->tail = new_node;
    ll->count++;
}

int pop(LinkedList* ll)
{
    if (!ll->tail) return 0;

    Node* old_tail = ll->tail;

    ll->tail = ll->tail->prev;
    ll->tail->next = NULL;

    if (!ll->tail) ll->head = NULL;

    int value = old_tail->value;
    free(old_tail);

    ll->count--;

    return value;
}

void enqueue(LinkedList* ll, int value)
{
    Node* new_node = init_node(value);

    if (ll->head) ll->head->prev = new_node;
    new_node->next = ll->head;

    ll->head = new_node;
    if (!ll->tail) ll->tail = new_node;

    ll->count++;
}

int dequeue(LinkedList* ll)
{
    if (!ll->head) return 0;

    Node* old_head = ll->head;

    ll->head = ll->head->next;
    ll->head->prev = NULL;

    if (!ll->head) ll->tail = NULL;

    int value = old_head->value;
    free(old_head);

    ll->count--;

    return value;
}

void insert_at(LinkedList* ll, int value, unsigned int index)
{
    if (index > ll->count) return;

    if (index == 0)
    {
        enqueue(ll, value);
        return;
    }

    if (index == ll->count)
    {
        push(ll, value);
        return;
    }

    Node* node = ll->head;
    for (unsigned int i = 0; i < index; i++)
        node = node->next;

    Node* new_node   = init_node(value);

    new_node->next = node;
    new_node->prev = node->prev;

    node->prev->next = new_node;
    node->prev       = new_node;

    ll->count++;
}

int remove_at(LinkedList* ll, unsigned int index)
{
    if (index >= ll->count)     return 0;
    if (index == ll->count - 1) return pop(ll);
    if (index == 0)             return dequeue(ll);

    Node* node = ll->head;
    for (unsigned int i = 0; i < index; i++)
        node = node->next;

    node->next->prev = node->prev;
    node->prev->next = node->next;

    int value = node->value;
    free(node);

    ll->count--;

    return value;
}

int value_at(LinkedList* ll, unsigned int index)
{
    if (index > ll->count) return 0;

    Node* node = ll->head;
    for (unsigned int i = 0; i < index; i++)
        node = node->next;

    return node->value;
}

int index_of(LinkedList* ll, int value)
{
    int index = 0;

    for (Node* node = ll->head; node; node = node->next, index++)
        if (node->value == value) return index;

    return -1;
}

void print_ll(LinkedList* ll)
{
    printf("[");
    for (Node* node = ll->head; node; node = node->next)
        printf("%d, ", node->value);
    printf("\b\b]\n");
}
