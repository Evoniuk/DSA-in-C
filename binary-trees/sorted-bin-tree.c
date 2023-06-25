/*
    A problem with the delete function is that there is the potential to free
    the head from underneath the caller. In such a case there isn't any way for
    the caller to know that the memory it references is now not allocated to
    the program. The most common workaround to this is for the delete function
    to take not a node pointer, but a pointer to a node pointer. Then, if the
    head needs to be deleted and the tree emptied, you can assign the value of
    the node pointer to NULL, so the caller gets a NULL pointer, and knows it's
    invalid.

    Other alternatives include having a return value to indicate whether the
    tree has been emptied, or a pointer to a sentinal value passed as an
    argument.

    We don't go through such pains here, but it's important to know about.
*/
#include <stdlib.h>

#include "sorted-bin-tree.h"

void delete_node(TreeNode* node, TreeNode* parent)
{
    // no children
    if (!node->left && !node->right)
    {
        if (parent)
        {
            if (parent->right == node) parent->right = NULL;
            if (parent->left  == node) parent->left  = NULL;
        }

        free(node); // if the above condition is false, we're deleting the head
        return;     // in an otherwise empty tree. this is dangerous, as it
    }               // frees memory without the caller being able to know

    // one child
    if (!node->left || !node->right)
    {
        if (!parent)        // if we're removing the head and only have one
        {                   // child, we make that child the new head by
            if (node->left) // copying its values to the current head and
            {               // freeing its original location
                node->val = node->left->val;
                node->left  = node->left->left;
                node->right = node->left->right;
                free(node->left);
            }

            else
            {
                node->val = node->right->val;
                node->left  = node->right->left;
                node->right = node->right->right;
                free(node->right);
            }
            return;
        }
        if (parent->right == node)
            parent->right = node->left ?
                node->left :
                node->right;
        else parent->left = node->left ?
                node->left :
                node->right;
        free(node);
        return;
    }

    // two children
    TreeNode* node_replacement = node->left; // in the case of two children
    parent = node;                           // we'll replace the node we're
                                             // deleting with the largest node
    while (node_replacement->right)          // on the left. The smallest node
    {                                        // on the right would also work
        parent           = node_replacement;
        node_replacement = node_replacement->right;
    }

    node->val = node_replacement->val;

    if (parent->left == node_replacement)
        parent->left = NULL;
    else parent->right = NULL;

    free(node_replacement);
}

// PUBLIC FUNCTIONS:

bool bin_search(TreeNode* node, int val)
{
    if (!node)            return false;
    if (node->val == val) return true;

    if (node->val < val)
        return bin_search(node->right, val);
    return bin_search(node->left, val);
}

void insert(TreeNode* node, int val)
{
    if (val <= node->val)
        if (node->left) insert(node->left, val);
        else node->left = init_node(val);

    else
        if (node->right) insert(node->right, val);
        else node->right = init_node(val);
}

void delete(TreeNode* head, int val)
{
    TreeNode* to_delete = head;
    TreeNode* parent    = NULL;

    while (to_delete && to_delete->val != val)
    {
        parent = to_delete;
        to_delete = to_delete->val < val ?
            to_delete->right:
            to_delete->left;
    }

    if (!to_delete) return;

    delete_node(to_delete, parent);
}
