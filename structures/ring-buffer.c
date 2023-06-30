/*
    RING BUFFER

    Ring buffers, also known as circular buffers or circular queues, are an
    amazing data structure that has constant-time lookup (so not a linked list),
    constant time enqueueing / dequeing (so not an array), and constant time
    pushing / popping.

    How it accomplishes this is suggested by its name: it organizes its data
    as an array underneath, but one that "wraps around". The wrapping is
    done by storing the index of the head and the index of the tail (which may
    be less that the head!). As long as the difference between the tail and
    head is less than the size of the array, the sequence of data can begin
    anywhere in the array and wrap around back to the beginning of the array
    when it hits the end.

    EXAMPLE:
        If we have the sequence [1, 2, 3, 4, 5, 6] in a ring buffer using an
        array of size 8, it might be stored as

            [5, 6, x, x, 1, 2, 3, 4]
                ^ tail   ^ head

        where `x` is junk data. In this example, `head` would be 4 (the index
        of the start), and `tail` would be 9 (head + how many more values there
        are). If we wished to access the value at the tail, we would look at
        the value at tail % (length of array).

    Taking the index mod the array length is how we convert between the
    "virtual indices" and the actual location in the array. To allow for a fast
    modulo operation, we use arrays with a size equal to a power of two, as

        n % 2^m == n & (2^m - 1)

    and subtraction and bitwise and are much faster opertations than modulo.

    When the number of values exceeds the size of the array we're using, we
    reallocate to the an array twice the size.

    With this setup, pushing, popping, enqueueing, and dequeueing are done
    by adjusting the head or tail forward or back.
*/
#include <stdio.h>
#include <stdlib.h>

#include "ring-buffer.h"

#define INIT_SIZE 8

int real_index(int virtual_index, int capacity)
{
    while (virtual_index < 0) virtual_index += capacity; // 'cause the modulo operator is stupid for negatives
    return virtual_index & (capacity - 1); // assumes capacity is power of 2
}

void grow_buffer(RingBuffer* rb)
{
    rb->capacity *= 2;
    int* new_buffer = malloc(rb->capacity * sizeof(int));

    int j = 0;
    for (int i = rb->head; i < rb->tail; i++, j++)
        new_buffer[j] = rb->buffer[real_index(i, rb->capacity / 2)];

    free(rb->buffer);
    rb->buffer = new_buffer;

    rb->head = 0;
    rb->tail = j;
}

// PUBLIC FUNCTIONS:

RingBuffer* init_rb()
{
    RingBuffer* rb = malloc(sizeof(RingBuffer));

    rb->head     = 0;
    rb->tail     = 0;
    rb->buffer   = malloc(INIT_SIZE * sizeof(int));
    rb->capacity = INIT_SIZE;

    return rb;
}

void free_rb(RingBuffer* rb)
{
    free(rb->buffer);
    free(rb);
}

void push(RingBuffer* rb, int value)
{
    if (rb->tail - rb->head >= rb->capacity)
        grow_buffer(rb);

    rb->buffer[real_index(rb->tail++, rb->capacity)] = value;
}

int pop(RingBuffer* rb)
{
    if (rb->head == rb->tail) return 0;

    return rb->buffer[real_index(--rb->tail, rb->capacity)];
}

int peek(RingBuffer* rb)
{
    return rb->buffer[real_index(rb->tail - 1, rb->capacity)];
}

void enqueue(RingBuffer* rb, int value)
{
    if (rb->tail - rb->head >= rb->capacity)
        grow_buffer(rb);

    rb->buffer[real_index(--rb->head, rb->capacity)] = value;
}

int dequeue(RingBuffer* rb)
{
    if (rb->head == rb->tail) return 0;

    return rb->buffer[real_index(rb->head++, rb->capacity)];
}

int look(RingBuffer* rb)
{
    return rb->buffer[real_index(rb->head, rb->capacity)];
}

int at_index(RingBuffer* rb, int index)
{
    if (rb->head + index > rb->tail) return 0;

    return rb->buffer[real_index(rb->head + index, rb->capacity)];
}

void print_rb(RingBuffer* rb)
{
    for (int i = rb->head; i < rb->tail; i++)
        printf("%d\n", rb->buffer[real_index(i, rb->capacity)]);
}
