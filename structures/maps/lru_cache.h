#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <stdbool.h>

typedef struct Entry {
    char* key;
    int   value;
    struct Entry* ll_next;
    struct Entry* ll_prev;
    struct Entry* next;
} Entry;

typedef struct Map {
    Entry** entries;
    unsigned int count;
    unsigned int capacity;
} Map;

typedef struct LRU {
    Map*   map;
    Entry* head;
    Entry* tail;
} LRU;

LRU* init_lru();
void free_lru(LRU* lru);
void update(LRU* lru, char* key, int value);
bool delete(LRU* lru, char* key);
int  get_value(LRU* lru, char* key);

#endif
