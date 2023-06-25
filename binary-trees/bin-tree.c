/*
TRAVERSALS

    For all orderings, imagine a button on each node, where pressing it
    visits the node. If you trace around the tree, starting from the head
    and going counter-clockwise, the order in which you press buttons
    depends on the position of the buttons:

        PRE-ORDER:  button is on the left
        IN-ORDER:   button is on the bottom
        POST-ORDER: button is on the right

    All these are depth-first.

    Each traversal has its own uses:

        PRE-ORDER: Visits parents before children, used to copy trees
        IN-ORDER:  For a sorted binary tree, will visit nodes in order
        POST-ORDER: Visits children before parents, used to free trees
*/
#include <stdlib.h>

#include "bin-tree.h"

void visit(TreeNode* tree)
{
    printf("%d\n", tree->val);
}

// PUBLIC FUNCTIONS:

TreeNode* init_node(int val)
{
    TreeNode* node = malloc(sizeof(TreeNode));

    node->val   = val;
    node->left  = NULL;
    node->right = NULL;

    return node;
}

void free_tree(TreeNode* tree)
{
    if (!tree) return;

    free_tree(tree->left);
    free_tree(tree->right);

    free(tree);
}

void pre_order(TreeNode* tree)
{
    if (!tree) return;

    visit(tree);
    pre_order(tree->left);
    pre_order(tree->right);
}

void in_order(TreeNode* tree)
{
    if (!tree) return;

    in_order(tree->left);
    visit(tree);
    in_order(tree->right);
}

void post_order(TreeNode* tree)
{
    if (!tree) return;

    post_order(tree->left);
    post_order(tree->right);
    visit(tree);
}

bool compare_trees(TreeNode* a, TreeNode* b)
{
    if (!a && !b)         return true;
    if (!a || !b)         return false;
    if (a->val != b->val) return false;

    return compare_trees(a->left, b->left) && 
           compare_trees(a->right, b->right);
}
