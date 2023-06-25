#include <stdlib.h>

#include "bin-tree.h"

typedef struct QueueNode {
    TreeNode* node;
    struct QueueNode* next;
    struct QueueNode* prev;
} QueueNode;

typedef struct Queue {
    QueueNode* head;
    QueueNode* tail;
} Queue;

void enqueue(Queue* queue, TreeNode* node)
{
    QueueNode* queue_node = malloc(sizeof(QueueNode));

    queue_node->node = node;
    queue_node->next = NULL;
    queue_node->prev = queue->tail;

    if (!queue->head)
        queue->head = queue_node;
    else
        queue->tail->next = queue_node;
    
    queue->tail = queue_node;
}

TreeNode* dequeue(Queue* queue)
{
    if (!queue->head) return NULL;

    TreeNode* node = queue->head->node;
    
    QueueNode* new_head = queue->head->next;
    free(queue->head);
    queue->head = new_head;

    return node;
}

void visit(TreeNode* node)
{
    printf("%d\n", node->val);
}

void breadth_first(TreeNode* head)
{
    Queue queue;
    queue.head = NULL;
    queue.tail = NULL;

    enqueue(&queue, head);

    TreeNode* current;
    while ((current = dequeue(&queue)))
    {
        if (current->left)  enqueue(&queue, current->left);
        if (current->right) enqueue(&queue, current->right);

        visit(current);
    }
}
