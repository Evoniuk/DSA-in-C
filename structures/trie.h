#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

#define AB_SIZE 26

typedef struct TrieNode {
    struct TrieNode* chars[AB_SIZE];
    char character;
    bool is_end;
} TrieNode;

TrieNode* init_trie();
void free_trie(TrieNode* trie);
void print_trie(TrieNode* trie);
bool exists(TrieNode* trie, char* string);
bool delete(TrieNode* trie, char* string);
void add(TrieNode* trie, char* string);

#endif
