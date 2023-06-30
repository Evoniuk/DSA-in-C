/*
    HASHMAPS

    Hashmaps are incredibly useful data structures. They're similar to arrays
    in that they allow for constant-time access to values, but unlike arrays
    they're not restricted to non-negative integral keys (what we call
    "indices"). Maps allow the use of arbitrary data as keys to retrieve
    corresponding data. The hashmap here uses strings to retrieve integer
    values.

    The way hashmaps achieve this is by *hashing* the keys. Hashing takes an
    input and gives a number as an output. This number is then used as an index
    to an array. Usually, though, the number is too big to use an index to an
    array, so it is modded modulo the length of the array. Because of this, we
    use an array whose length is equal to a power of 2. This allows for a
    faster modulo operation, as

        n % 2^m == n & (2^m - 1)

    and subtraction and bitwise and are much faster operations than modulo.

    There are many hashing algorithms; here we use the FNV-1a algorithm, as it's
    one of the simplest around.

    An important quality we want in hashing algorithms is that they be random
    and uniform. This allows our keys, regardless of what they are, to be
    evenly distributed throughout our array, which minimizes collisions (when
    two different inputs get the same index assigned by the hashing algorithm).

    Inevitably, though, there are collisions. There are two main ways to resolve
    them, chaining and probing:

    CHAINING

    Chaining, also called linear chaining, is the method adopted here. It
    resolves conflicts by creating a linked list of entries when there are more
    than one assigned to a bucket ("bucket" is often used to refer to a place
    in the array being used by a hashmap). This is why the Entry struct has an
    Entry* called `next` as one of its members.

    For example, if we're using an array of size 4 that looks like this:

    [
        {"string one": 1},
        NULL,
        NULL,
        {"string two": 2},
    ]

    and we add the key/value pair {"string three": 3}, which gets assigned to
    bucket 0, the result will be this:

    [
        {"string one": 1},
        NULL,
        NULL,
        {"string two": 2} -> {"string three": 3},
    ]

    This approach is good because it's conceptually simple, but it doesn't have
    good cache locality because it relies on pointers to jump around in memory,
    which usually makes it a bit slower than the next approach.

    PROBING 

    Probing, or linear probing, doesn't bother with linked lists, and instead,
    when there's a collision, the new element is just slotted in at the next
    open bucket in the array. This approach seems simpler, but consider this:

    Say we have an array that looks like this:

    [
        {"string one": 1},
        {"string two": 2},
        {"string three": 3},
        NULL,
    ]

    And let's say that "string three" *should* have been assigned to bucket 0,
    but got moved to bucket 2 because "string one" and "string two" were there
    first. So far so good.

    But then, "string two" gets deleted! So now, when we go to search for
    "string three", we find an empty bucket along the way, and assume that it
    just doesn't exist. After all, wouldn't it have gone in bucket 1, 'cause
    it's empty?

    Of course, this is a solved problem. The solution is to put a "tombstone"
    at deleted elements, so when searching through the array we know that
    things used to be there. This can involve having a nonsensical key/value
    pair, like {NULL, 1}.

    LOAD FACTOR

    One last thing to consider for hashmaps: they have a capacity. We don't want
    to use up the entirety of the array (though we can when using the chaining
    strategy, at the cost of performance), so we grow our array when it hits a
    certain threshhold, called the load factor. This hashmap uses .75 as a load
    factor.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hashmap.h"

#define INIT_MAP_SIZE   8
#define MAX_LOAD_FACTOR 0.75

unsigned int hash_string(const char* key)
{
    // FNV-1a hashing algorithm
    unsigned int hash = 0x811C9DC5;
    while (*key)
    {
        hash ^= *key++;
        hash *= 0x01000193;
    }

    return hash;
}

Entry* init_entry(const char* key, int value)
{
    Entry* entry = malloc(sizeof(Entry));

    entry->key   = calloc(strlen(key) + 1, sizeof(char));
    entry->value = value;
    entry->next  = NULL;

    strcpy(entry->key, key);

    return entry;
}

void free_entry(Entry* entry)
{
    free(entry->key);
    free(entry);
}

void _add(Map* map, const char* key, int value)
{
    unsigned int index = hash_string(key) & (map->capacity - 1);

    if (!map->entries[index])
        map->entries[index] = init_entry(key, value);

    else
    {
        Entry* entry = map->entries[index];
        while (entry->next) entry = entry->next;

        entry->next = init_entry(key, value);
    }

    map->count++;
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
        while (entry)
        {
            _add(map, entry->key, entry->value);

            Entry* next = entry->next;
            free_entry(entry);
            entry = next;
        }
    }

    free(old_entries);
}

Entry* lookup(Map* map, const char* key)
{
    unsigned int index = hash_string(key) & (map->capacity - 1);
    
    Entry* entry = map->entries[index];
    while (entry && strcmp(entry->key, key))
        entry = entry->next;

    return entry;
}

// PUBLIC FUNCTIONS:

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

        while (entry)
        {
            Entry* next = entry->next;
            free_entry(entry);
            entry = next;
        }
    }

    free(map);
}

void add(Map* map, const char* key, int value)
{
    if (map->count > map->capacity * MAX_LOAD_FACTOR)
        grow_map(map);

    Entry* entry = lookup(map, key);

    if (entry) entry->value = value;
    else _add(map, key, value);
}

bool delete(Map* map, const char* key)
{
    unsigned int index = hash_string(key) & (map->capacity - 1);

    Entry*  entry = map->entries[index];
    Entry** prev  = &map->entries[index];

    while (entry && strcmp(key, entry->key))
    {
        prev  = &entry->next;
        entry = entry->next;    
    }

    if (!entry) return false;

    *prev = entry->next;
    free_entry(entry);

    map->count--;

    return true;
}

int get_value(Map* map, const char* key)
{
    Entry* entry = lookup(map, key);

    return entry ? entry->value : 0;
}

void print_map(Map* map)
{
    for (unsigned int i = 0; i < map->capacity; i++)
    {
        Entry* entry = map->entries[i];
        while (entry)
        {
            printf("\"%s\": %d\n", entry->key, entry->value);
            entry = entry->next;
        }
    }
}
