#ifndef RING_BUFFER_H
#define RING_BUFFER_H

typedef struct {
    int  head;
    int  tail;
    int* buffer;
    int  capacity;
} RingBuffer;

RingBuffer* init_rb();
void        free_rb(RingBuffer* rb);

void push(RingBuffer* rb, int value);
int  pop(RingBuffer* rb);
int  peek(RingBuffer* rb);

void enqueue(RingBuffer* rb, int value);
int  dequeue(RingBuffer* rb);
int  look(RingBuffer* rb);

int  at_index(RingBuffer* rb, int index);
void print_rb(RingBuffer* rb);

#endif
