#ifndef ADJ_MATRIX_H
#define ADJ_MATRIX_H

#include <stdbool.h>

typedef struct AdjacencyMatrix {
    int** matrix;
    int*  data;
    int   length;
    int   capacity;
} AdjacencyMatrix; 

AdjacencyMatrix* init_adj_matrix();
void free_adj_matrix(AdjacencyMatrix* adj_matrix);
int  add(AdjacencyMatrix* adj_matrix, int data);
void connect(AdjacencyMatrix* adj_matrix, int from, int to, int weight);
bool is_connected(AdjacencyMatrix* adj_matrix, int from, int to);

#endif
