#include "bst.h"
#include <stdio.h>
#include <string.h>

// You might find implementing functions with these signatures useful.  (For
// the ones with two options listed per function, you should only implement one
// -- that is, don't implement both versions of bst_addHelper).

// void bst_addHelper(struct BSTNode* node, char* key);
// struct BSTNode* bst_addHelper(struct BSTNode* node, char* key);

// struct BSTNode* bst_removeHelper(struct BSTNode* node, char* key);
// void bst_removeHelper(struct BSTNode* node, char* key);

// void bst_deleteTreeHelper(struct BSTNode* node);

/**
 *  bst_max - finds the key of the largest (rightmost) node in this bst.
 *
 *  Parameters:
 *    struct BST* bst - tree whose largest node we're looking for.
 *
 *  Return value: largest key in the tree, or
 *    empty string if tree is empty.
 */
char* bst_max(struct BST* bst) {
  struct BSTNode* node = bst->root;
  if (node) {
    while (node->right) {
      node = node->right;
    }
    return node->key;
  } else {
    return NULL;
  }
}
