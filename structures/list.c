#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

// PRIVATE
void grow_capacity(List* list)
{
    list->capacity *= 2;
    list->values = realloc(list->values, list->capacity * sizeof(int));
}

// PUBLIC
List* init_list()
{
    List* list = malloc(sizeof(List));

    list->values   = malloc(8 * sizeof(int));
    list->length   = 0;
    list->capacity = 8;

    return list;
}

void free_list(List* list)
{
    free(list->values);
    free(list);
}

void print_list(List* list)
{
    if (!list->length) return;

    printf("[");
    for (int i = 0; i < list->length - 1; i++)
        printf("%d, ", list->values[i]);

    printf("%d]\n", list->values[list->length - 1]);
}

void push(List* list, int value)
{
    if (list->length >= list->capacity)
        grow_capacity(list);

    list->values[list->length++] = value;
}

int pop(List* list)
{
    if (!list->length) return 0;
    return list->values[--list->length];
}

int peek(List* list)
{
    return list->values[list->length - 1];
}

void insert_at(List* list, int value, int index)
{
    if (list->length >= list->capacity)
        grow_capacity(list);

    while (index >= list->capacity)
        grow_capacity(list);

    memmove(
        &list->values[index + 1],
        &list->values[index],
        (list->length - index) * sizeof(int)
    );

    list->values[index] = value;

    if (index >= list->length)
        list->length = index + 1;
    else list->length++;
}

int delete_at(List* list, int index)
{
    int value = list->values[index];

    memmove(
        &list->values[index],
        &list->values[index + 1],
        (list->length - index) * sizeof(int)
    );

    list->length--;

    return value;
}

void enqueue(List* list, int value)
{
    insert_at(list, value, 0);
}

int dequeue(List* list)
{
    return delete_at(list, 0);
}
