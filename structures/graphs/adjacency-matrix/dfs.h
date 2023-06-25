#ifndef DFS_H
#define DFS_H

#include "../../list.h"
#include "adjacency-matrix.h"

List* dfs(AdjacencyMatrix* matrix, int from, int to);

#endif
