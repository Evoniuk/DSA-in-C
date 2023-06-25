#include <stdlib.h>
#include <limits.h>

#include "dijkstra.h"

bool has_unvisited(bool* seen, int* dists, int length)
{
    for (int i = 0; i < length; i++)
        if (!seen[i] && dists[i] < INT_MAX)
            return true;

    return false;
}

int lowest_unvisited(bool* seen, int* dists, int length)
{
    int index       = -1;
    int lowest_dist = INT_MAX;

    for (int i = 0; i < length; i++)
    {
        if (seen[i]) continue;
        if (lowest_dist > dists[i])
        {
            index       = i;
            lowest_dist = dists[i];
        }
    }

    return index;
}

List* dijkstra(AdjacencyMatrix* graph, int start, int end)
{
    int length = graph->length;

    bool* seen  = calloc(length, sizeof(bool));
    int*  prev  = calloc(length, sizeof(int));
    int*  dists = calloc(length, sizeof(int));

    for (int i = 0; i < length; i++)
    {
        seen[i]  = false;
        prev[i]  = -1;
        dists[i] = INT_MAX;
    }

    dists[start] = 0;
    
    while (has_unvisited(seen, dists, length))
    {
        int current = lowest_unvisited(seen, dists, length);
        seen[current] = true;

        int* adjacencies = graph->matrix[current];
        for (int i = 0; i < length; i++)
        {
            int edge = adjacencies[i];
            if (seen[i] || edge == 0) continue;

            int distance = dists[current] + edge;
            if (distance < dists[i])
            {
                dists[i] = distance;
                prev[i]  = current;
            }
        }
    }

    List* path = init_list();

    for (int current = end; prev[current] != -1; current = prev[current])
        enqueue(path, current);

    if (path->length)
        enqueue(path, start);

    free(prev);
    free(seen);
    free(dists);

    return path;
}
