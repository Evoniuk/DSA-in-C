#include "adjacency-matrix.h"
#include "stdlib.h"

AdjacencyMatrix* init_adj_matrix()
{
    AdjacencyMatrix* adj_matrix = malloc(sizeof(AdjacencyMatrix));

    adj_matrix->matrix = malloc(8 * sizeof(int*));
    for (int i = 0; i < 8; i++)
        adj_matrix->matrix[i] = calloc(8, sizeof(int));

    adj_matrix->data     = malloc(8 * sizeof(int));
    adj_matrix->capacity = 8;
    adj_matrix->length   = 0;

    return adj_matrix;
}

void free_adj_matrix(AdjacencyMatrix* adj_matrix)
{
    for (int i = 0; i < adj_matrix->length; i++)
        free(adj_matrix->matrix[i]);
    free(adj_matrix->matrix);
    free(adj_matrix->data);
    free(adj_matrix);
}

int add(AdjacencyMatrix* adj_matrix, int data)
{
    if (adj_matrix->length == adj_matrix->capacity)
    {
        adj_matrix->capacity *= 2;
        adj_matrix->matrix = realloc(adj_matrix->matrix, adj_matrix->capacity * sizeof(int*));

        for (int i = 0; i < adj_matrix->length; i++)
            adj_matrix->matrix[i] = realloc(adj_matrix->matrix[i], adj_matrix->capacity * sizeof(int));
        for (int i = adj_matrix->length; i < adj_matrix->capacity; i++)
            adj_matrix->matrix[i] = malloc(adj_matrix->capacity * sizeof(int));
    }

    adj_matrix->data[adj_matrix->length++] = data;

    return adj_matrix->length - 1;
}

void connect(AdjacencyMatrix* adj_matrix, int from, int to, int weight)
{
    adj_matrix->matrix[from][to] = weight;
}

bool is_connected(AdjacencyMatrix* adj_matrix, int from, int to)
{
    return adj_matrix->matrix[from][to];
}
