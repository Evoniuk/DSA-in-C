#include <stdlib.h>

#include "bfs.h"

List* bfs(AdjacencyList* adj_list, int from, int to)
{
    bool* seen = calloc(adj_list->length, sizeof(bool));
    List* prev = init_list();

    for(int i = 0; i < adj_list->length; i++)
        push(prev, -1);

    seen[from] = true;

    List* queue = init_list();
    enqueue(queue, from);

    while (queue->length)
    {
        int current = dequeue(queue);
        if (current == to) break;

        Node* node = adj_list->nodes[current];
        for (int i = 0; i < node->length; i++)
        {
            Adjacency adj = node->adjacencies[i];
            if (seen[adj.to]) continue;

            seen[adj.to] = true;
            prev->values[adj.to] = current;
            push(queue, adj.to);
        }

        seen[current] = true;
    }

    int current = to;
    List* path = init_list();

    while(prev->values[current] != -1)
    {
        enqueue(path, current);
        current = prev->values[current];
    }
     
    if (path->length)
        enqueue(path, from);

    free(seen);
    free_list(prev);

    return path;
}
