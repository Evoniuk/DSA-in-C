#include <stdio.h>

void merge(int* arr, int* helper, int lo, int middle, int hi)
{
    // copy arr into helper
    for (int i = lo; i <= hi; i++)
        helper[i] = arr[i];

    // look through both halves of helper and merge them into arr
    int arr_index  = lo;
    int help_left  = lo;
    int help_right = middle + 1;

    while (help_left <= middle && help_right <= hi)
        arr[arr_index++] = helper[help_left] <= helper[help_right] ?
            helper[help_left++] :
            helper[help_right++];

    // when left half has greatest elements, we need to continue
    // copying them over; when right half has greatest elements
    // those elements will already be in place, so we don't need
    // to do anything
    while (help_left <= middle)
        arr[arr_index++] = helper[help_left++];
}

void ms(int* arr, int* helper, int lo, int hi)
{
    if (lo >= hi) return;

    int middle = lo + (hi - lo) / 2;

    ms(arr, helper, lo, middle);        // sort left half
    ms(arr, helper, middle + 1, hi);    // sort right half

    merge(arr, helper, lo, middle, hi); // merge sorted halfs
}

int* mergesort(int* arr, int length)
{
    int helper[length];

    ms(arr, helper, 0, length - 1);

    return arr;
}
