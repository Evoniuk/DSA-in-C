#ifndef ADJ_LIST_H
#define ADJ_LIST_H

#include <stdbool.h>

typedef struct Adjacency {
    int to;
    int weight;
} Adjacency;

typedef struct Node {
    int data;
    Adjacency* adjacencies;
    int length;
    int capacity;
} Node;

typedef struct AdjacencyList {
    Node** nodes;
    int    length;
    int    capacity;
} AdjacencyList; 

AdjacencyList* init_adj_list();
void free_adj_list(AdjacencyList* adj_list);
int  add(AdjacencyList* adj_list, int data);
void connect(AdjacencyList* adj_list, int from, int to, int weight);
bool is_connected(AdjacencyList* adj_list, int from, int to);

#endif
