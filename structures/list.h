#ifndef LIST_H
#define LIST_H

typedef struct List {
    int* values;
    int  length;
    int  capacity;
} List;

List* init_list();
void  free_list(List* list);

void print_list(List* list);

void push(List* list, int value);
int  pop(List* list);
int  peek(List* list);

void enqueue(List* list, int value);
int  dequeue(List* list);

void insert_at(List* list, int value, int index);
int  delete_at(List* list, int index);

#endif
