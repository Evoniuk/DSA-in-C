#ifndef SORTED_BIN_TREE_H
#define SORTED_BIN_TREE_H

#include <stdbool.h>

#include "bin-tree.h"

bool bin_search(TreeNode* node, int val);
void insert(TreeNode* node, int val);
void delete(TreeNode* head, int val);

#endif
