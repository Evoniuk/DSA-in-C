#include <stdio.h>
#include <stdlib.h>

#include "minheap.h"

int parent_of(int index)
{
    return (index - 1) / 2;
}

int left_child(int index)
{
    return 2 * index + 1;
}

int right_child(int index)
{
    return 2 * index + 2;
}

void heapify_up(MinHeap* heap, int index)
{
    if (index == 0) return;
    
    int* arr = heap->arr;
    int parent = parent_of(index);

    if (arr[index] > arr[parent]) return;

    int temp = arr[index];
    arr[index] = arr[parent];
    arr[parent] = temp;

    heapify_up(heap, parent);
}

void heapify_down(MinHeap* heap, int index)
{
    if (index >= heap->length) return;

    int l_index = left_child(index);
    int r_index = right_child(index);

    if (l_index >= heap->length) return;

    int* arr = heap->arr;

    int l_value = arr[l_index];
    int r_value = arr[r_index];
    int value   = arr[index];

    if (l_value < r_value && value < r_value)
    {
        arr[index]   = r_value;
        arr[r_index] = value;
        heapify_down(heap, r_index);
    }

    else if (r_value > l_value && value < l_value)
    {
        arr[index]   = l_value;
        arr[l_index] = value;
        heapify_down(heap, l_index);
    }
}

// PUBLIC FUNCTIONS:

MinHeap* init_heap()
{
    MinHeap* heap = malloc(sizeof(MinHeap));
    int* arr      = malloc(8 * sizeof(int));

    heap->arr      = arr;
    heap->length   = 0;
    heap->capacity = 8;

    return heap;
} 

void free_heap(MinHeap* heap)
{
    free(heap->arr);
    free(heap);
}

void insert(MinHeap* heap, int val)
{
    if (heap->length == heap->capacity)
    {
        heap->capacity *= 2;
        heap->arr = realloc(heap->arr, heap->capacity);
    }

    heap->arr[heap->length++] = val;
    heapify_up(heap, heap->length - 1);
}

int delete(MinHeap* heap)
{
    if (heap->length == 0) return -1;

    if (heap->length == 1) 
        return heap->arr[--heap->length];

    int result = heap->arr[0];

    heap->length--;
    heap->arr[0] = heap->arr[heap->length];
    heapify_down(heap, 0);

    return result;
}
