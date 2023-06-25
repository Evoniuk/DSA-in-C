#ifndef MINHEAP_H
#define MINHEAP_H

typedef struct MinHeap {
    int* arr;
    int  length;
    int  capacity;
} MinHeap;

MinHeap* init_heap();
void free_heap(MinHeap* heap);

void insert(MinHeap* heap, int val);
int  delete(MinHeap* heap);

#endif
