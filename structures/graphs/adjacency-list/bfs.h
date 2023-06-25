#ifndef BFS_H
#define BFS_H

#include "../../list.h"
#include "adjacency-list.h"

List* bfs(AdjacencyList* adj_list, int from, int to);

#endif
