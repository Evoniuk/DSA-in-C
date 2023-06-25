#include <stdlib.h>
#include <stdio.h>

#include "adjacency-list.h"

#define INIT_SIZE 8

Node* init_node(int data)
{
    Node* node = malloc(sizeof(Node));

    node->data        = data;
    node->adjacencies = malloc(INIT_SIZE * sizeof(Adjacency));
    node->length      = 0;
    node->capacity    = INIT_SIZE;

    return node;
}

// PUBLIC FUNCTIONS:

AdjacencyList* init_adj_list()
{
    AdjacencyList* adj_list = malloc(sizeof(AdjacencyList));

    adj_list->nodes    = malloc(INIT_SIZE * sizeof(Node*));
    adj_list->length   = 0;
    adj_list->capacity = INIT_SIZE;

    return adj_list;
}

void free_adj_list(AdjacencyList* adj_list)
{
    for (int i = 0; i < adj_list->length; i++)
    {
        free(adj_list->nodes[i]->adjacencies);
        free(adj_list->nodes[i]);
    }

    free(adj_list->nodes);
    free(adj_list);
}

int add(AdjacencyList* adj_list, int data)
{
    if (adj_list->length == adj_list->capacity)
    {
        adj_list->capacity *= 2;
        adj_list->nodes = realloc(adj_list->nodes, adj_list->capacity * sizeof(Node*));
    }

    adj_list->nodes[adj_list->length++] = init_node(data);

    return adj_list->length - 1;
}

void connect(AdjacencyList* adj_list, int from, int to, int weight)
{
    Node* node = adj_list->nodes[from];
    
    if (node->length == node->capacity)
    {
        node->capacity *= 2;
        node->adjacencies = realloc(node->adjacencies, node->capacity * sizeof(Adjacency));
    }

    Adjacency* adj = &node->adjacencies[node->length++];
    adj->to     = to;
    adj->weight = weight;
}

bool is_connected(AdjacencyList* adj_list, int from, int to)
{
    Node* node = adj_list->nodes[from];

    for (int i = 0; i < node->length; i++)
        if (node->adjacencies[i].to == to)
            return true;

    return false;
}
