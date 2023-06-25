#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"

void push(char* string, char character)
{
    while (*string++);
    *--string = character;
}

char pop(char* string)
{
    while (*++string);
    char character = *--string;
    *string = '\0';
    return character;
}

void print_trie_(TrieNode* trie, char* prefix)
{
    if (!trie) return;

    push(prefix, trie->character);

    for (int i = 0; i < AB_SIZE; i++)
       print_trie_(trie->chars[i], prefix);

    if (trie->is_end)
       printf("%s\n", prefix); 

    pop(prefix);
}

void delete_from(TrieNode* trie, char* string)
{
    if (!*string) return;

    TrieNode* next = trie->chars[*string - 'a'];
    trie->chars[*string - 'a'] = NULL;

    delete_from(next, string + 1);
    free(next);
}

bool is_terminal_or_branch(TrieNode* trie)
{
    if (trie->is_end) return true;
    
    int children = 0;
    for (int i = 0; i < AB_SIZE; i++)
        if (trie->chars[i])
            children++;

    return children > 1;
}

// PUBLIC FUNCTIONS:

TrieNode* init_trie()
{
    TrieNode* trie = malloc(sizeof(TrieNode));

    for (int i = 0; i < AB_SIZE; i++)
        trie->chars[i] = NULL;
    trie->character = '\0';
    trie->is_end    = false;

    return trie;
}

void free_trie(TrieNode* trie)
{
    if (!trie) return;

    for (int i = 0; i < AB_SIZE; i++)
        free_trie(trie->chars[i]);

    free(trie);
}

void print_trie(TrieNode* trie)
{
    char prefix[32] = {0}; // assume that words are at most 32 chars
    print_trie_(trie, prefix);
}

bool exists(TrieNode* trie, char* string)
{
    for (; *string; string++)
    {
        trie = trie->chars[*string - 'a'];
        if (!trie) return false;
    }

    return trie->is_end;
}

bool delete(TrieNode* trie, char* string)
{
    if (!exists(trie, string)) return false;

    // last_terminal_or_branch stores the location of the last place where the
    // end of a word or branch to a new word occurs. An end of a word would
    // occur, for example, when we're deleting the word "catskill", but also
    // have "cats" defined. A branch would occur, for example, when we want to
    // delete "catskill", but also have "catsup" defined. In both cases, we only
    // want to delete "kill", the characters after the last terminus/branch.
    TrieNode* last_terminal_or_branch = trie;
    int length = strlen(string);
    int index  = 0;
    
    for (int i = 0; i < length - 1; i++) // length - 1 because we don't include
    {                                    // the end of the word we're deleting
        trie = trie->chars[string[i] - 'a'];
        if (is_terminal_or_branch(trie))
        {
            last_terminal_or_branch = trie;
            index = i + 1; // + 1 because we want to delete *after* last_terminal_or_branch
        }
    }

    trie = trie->chars[string[length - 1] - 'a'];
    trie->is_end = false;

    // if the end has children, unmarking it as the end of a word is enough
    for (int i = 0; i < AB_SIZE; i++)
        if (trie->chars[i]) return true;

    delete_from(last_terminal_or_branch, string + index);

    return true;
}

void add(TrieNode* trie, char* string)
{
    for (; *string; string++)
    {
        char c = *string - 'a';
        if (trie->chars[c])
        {
            trie = trie->chars[c];
            continue;
        }
        trie->chars[c] = init_trie();
        trie = trie->chars[c];
        trie->character = *string;
    }

    trie->is_end = true;
}
