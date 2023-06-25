#include <stdio.h>

void swap(int* arr, int i1, int i2)
{
    int temp = arr[i1];
    arr[i1] = arr[i2];
    arr[i2] = temp;
}

int partition(int* arr, int lo, int hi)
{
    int pivot = arr[hi];
    int index = lo;

    for (int i = lo; i <= hi; i++)
        if (arr[i] <= pivot)
            swap(arr, index++, i);

    return index - 1;
}

void qs(int* arr, int lo, int hi)
{
    if (lo >= hi) return;

    int pivot_index = partition(arr, lo, hi);

    qs(arr, lo, pivot_index - 1);
    qs(arr, pivot_index + 1, hi);
}

int* quicksort(int* arr, int length)
{
    qs(arr, 0, length - 1);

    return arr;
}
