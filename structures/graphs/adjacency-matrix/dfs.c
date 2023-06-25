#include <stdlib.h>

#include "dfs.h"

bool path_to(AdjacencyMatrix* matrix, int from, int to, List* path, bool* seen)
{
    if (seen[from]) return false;
    seen[from] = true;

    push(path, from);
    if (from == to) return true;

    for (int i = 0; i < matrix->length; i++)
        if (is_connected(matrix, from, i) && path_to(matrix, i, to, path, seen))
            return true;

    pop(path);

    return false;
}

List* dfs(AdjacencyMatrix* matrix, int from, int to)
{
    bool* seen = calloc(matrix->length, sizeof(bool));
    List* path = init_list();

    bool found = path_to(matrix, from, to, path, seen);

    free(seen);

    if (found) return path;

    free(path);
    return NULL;
}
