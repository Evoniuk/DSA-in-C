/*
    LRU CACHE

    An LRU (least recently used) cache is a data structure very similar to a
    map: it stores key/value pairs and has constant time access to those
    values. The difference is that it also keeps track of how recently every
    element in the map has been used (which can mean updated, inserted, or
    accessed).

    Often times, there is a certain number of elements that is desired to keep,
    and every time this number is exceeded, the least recently used element is
    removed. We don't do this here, opting instead to just keep track of the
    order.

    The way the order is kept is through a doubly linked list. When an element
    is added, it is appended to the beginning of the list. When an existing
    element is updated or accessed, it is removed from its position in the
    linked list and put at the beginning. The head and tail of this list are
    kept track of so that we always know where to put the new stuff, and in the
    case that we want to delete the oldest thing, we have access to the tail.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lru_cache.h"

#define INIT_MAP_SIZE   8
#define MAX_LOAD_FACTOR 0.75

unsigned int hash_string(char* key)
{
    // FNV-1a algorithm
    unsigned int hash = 0x811C9DC5;
    while (*key)
    {
        hash ^= *key++;
        hash *= 0x01000193;
    }

    return hash;
}

Entry* init_entry(char* key, int value)
{
    Entry* entry = malloc(sizeof(Entry));

    entry->key     = calloc(strlen(key) + 1, sizeof(char));
    entry->value   = value;
    entry->next    = NULL;
    entry->ll_next = NULL;
    entry->ll_prev = NULL;

    strcpy(entry->key, key);

    return entry;
}

void free_entry(Entry* entry)
{
    free(entry->key);
    free(entry);
}

Entry* add(Map* map, char* key, int value)
{
    unsigned int index = hash_string(key) & (map->capacity - 1);

    Entry* new_entry = init_entry(key, value);
    if (!map->entries[index])
        map->entries[index] = new_entry;

    else
    {
        Entry* entry = map->entries[index];
        while (entry->next) entry = entry->next;

        entry->next = new_entry;
    }

    map->count++;

    return new_entry;
}

void grow_map(Map* map)
{
    unsigned int old_capacity = map->capacity;
    Entry** old_entries       = map->entries;

    map->capacity *= 2;
    map->entries = calloc(map->capacity, sizeof(Entry*));
    map->count   = 0;

    for (unsigned int i = 0; i < old_capacity; i++)
    {
        Entry* entry = old_entries[i];
        if (!entry) continue;

        while (entry)
        {
            add(map, entry->key, entry->value);

            Entry* next = entry->next;
            free_entry(entry);
            entry = next;
        }
    }

    free(old_entries);
}

Map* init_map()
{
    Map* map = malloc(sizeof(Map));

    map->entries  = calloc(INIT_MAP_SIZE, sizeof(Entry*));
    map->count    = 0;
    map->capacity = INIT_MAP_SIZE;

    return map;
}

void free_map(Map* map)
{
    for (int i = 0; i < map->capacity; i++)
    {
        Entry* entry = map->entries[i];
        if (!entry) continue;

        while (entry)
        {
            Entry* next = entry->next;
            free_entry(entry);
            entry = next;
        }
    }

    free(map);
}

Entry* lookup(Map* map, char* key)
{
    unsigned int index = hash_string(key) & (map->capacity - 1);
    
    Entry* entry = map->entries[index];
    while (entry && strcmp(entry->key, key))
        entry = entry->next;

    return entry;
}

void detatch(Entry* entry)
{
    if (entry->ll_prev) entry->ll_prev->ll_next = entry->ll_next;
    if (entry->ll_next) entry->ll_next->ll_prev = entry->ll_prev;

    entry->ll_prev = NULL;
    entry->ll_next = NULL;
}

void update_tail(LRU* lru, Entry* entry)
{
    if (!entry->ll_next && entry->ll_prev)
        lru->tail = entry->ll_prev;
}

void update_head(LRU* lru, Entry* entry)
{
    if (lru->head == entry) return;

    entry->ll_next = lru->head;
    entry->ll_prev = NULL;

    if (lru->head) lru->head->ll_prev = entry;
    lru->head = entry;
}

// PUBLIC FUNCTIONS:

LRU* init_lru()
{
    LRU* lru = malloc(sizeof(LRU));

    lru->map  = init_map();
    lru->head = NULL;
    lru->tail = NULL;

    return lru;
}

void free_lru(LRU* lru)
{
    free_map(lru->map);
    free(lru);
}

void update(LRU* lru, char* key, int value)
{
    if (lru->map->count > lru->map->capacity * MAX_LOAD_FACTOR)
        grow_map(lru->map);

    Entry* entry = lookup(lru->map, key); 

    if (entry)
    {
        entry->value = value;
        update_tail(lru, entry);
        detatch(entry);
    }

    else entry = add(lru->map, key, value);

    update_head(lru, entry);
}

bool delete(LRU* lru, char* key)
{
    Map* map = lru->map;
    unsigned int index = hash_string(key) & (map->capacity - 1);

    Entry*  entry = map->entries[index];
    Entry** prev  = &map->entries[index];

    while (entry && strcmp(key, entry->key))
    {
        prev  = &entry->next;
        entry = entry->next;    
    }

    if (!entry) return false;

    if (!entry->ll_next) lru->tail = entry->ll_prev;
    if (!entry->ll_prev) lru->head = entry->ll_next;

    detatch(entry);

    *prev = entry->next;
    free_entry(entry);

    map->count--;

    return true;
}

int get_value(LRU* lru, char* key)
{
    if (!strcmp(lru->head->key, key)) return lru->head->value;

    unsigned int index = hash_string(key) & (lru->map->capacity - 1);

    Entry* entry = lru->map->entries[index];
    while (entry && strcmp(entry->key, key))
        entry = entry->next;

    if (!entry) return 0;

    update_tail(lru, entry);
    detatch(entry);
    update_head(lru, entry);

    return entry->value; 
}

void print_ordered(LRU* lru)
{
    for (Entry* entry = lru->head; entry; entry = entry->ll_next)
        printf("'%s': %d\n", entry->key, entry->value);
}
