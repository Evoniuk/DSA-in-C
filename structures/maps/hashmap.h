#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdbool.h>

typedef struct Entry {
    char* key;
    int   value;
    struct Entry* next;
} Entry;

typedef struct Map {
    Entry** entries;
    unsigned int count;
    unsigned int capacity;
} Map;

Map* init_map();
void free_map(Map* map);
void add(Map* map, const char* key, int value);
bool delete(Map* map, const char* key);
int  get_value(Map* map, const char* key);
void print_map(Map* map);

#endif
