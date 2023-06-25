#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "adjacency-matrix.h"
#include "../../list.h"

List* dijkstra(AdjacencyMatrix* graph, int start, int end);

#endif
