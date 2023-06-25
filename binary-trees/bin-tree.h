#ifndef BIN_TREE_H
#define BIN_TREE_H

#include <stdbool.h>

typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* init_node(int val);
void free_tree(TreeNode* tree);
void pre_order(TreeNode* tree);
void in_order(TreeNode* tree);
void post_order(TreeNode* tree);
bool compare_trees(TreeNode* a, TreeNode* b);

#endif
