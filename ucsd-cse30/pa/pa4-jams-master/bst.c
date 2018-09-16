#include "bst.h"
#include <stdio.h>
#include <string.h>

// You might find implementing functions with these signatures useful.  (For
// the ones with two options listed per function, you should only implement one
// -- that is, don't implement both versions of bst_addHelper).
/************************/
/*      Helper Funcs    */
/************************/

/* Helper function to find the minimum value in a tree or subtree,
 * depending on what node is supplied. We use it to find inorder
 * successor for the bst_removeNode function.
 */
struct BSTNode* minNode(struct BSTNode* node)
{
  struct BSTNode* searchNode = node;
  // loops to the smallest node starting at a specified node
  // which does not have to be the root of the BST
  while(searchNode->left != NULL)
    searchNode = searchNode->left;
  return searchNode;
}

/* Helper function to recursively remove a particular node from a tree */
struct BSTNode* bst_removeHelper(struct BSTNode* node, char* key)
{
  // Check base case (the root itself at first)
  if(node == NULL)
    return node;

  /* First find the node */
  // If the key to be deleted is less than the node(starting at root)
  // then the node to be deleted is in the left subtree
  if(strcmp(key, node->key) < 0) {
    node->left = bst_removeHelper(node->left, key);
  
  // If the key to be deleted is greater than the node(starting at root)
  // then the node to be deleted is in the right subtree
  } else if(strcmp(key, node->key) > 0) {
    node->right = bst_removeHelper(node->right, key);

  // if the key of the current node is the same as the 
  //one we are looking for, then we found it here
  } else {
    // node has only one child or the node is leaf
    if( node->left == NULL ){
      struct BSTNode* temp = node->right;
      free(node->key);
      free(node);
      node = NULL;
      return temp;
    } else if(node->right == NULL) {
      struct BSTNode* temp = node->left;
      free(node->key);
      free(node);
      node = NULL;
      return temp;
    }
    // node has 2 children
    // get the inorder successor of the right subtree and return it as the next
    struct BSTNode* temp = minNode(node->right);
    node->key = temp->key;
    node->right = bst_removeHelper(node->right, temp->key);
  }
  return node;
}

/* Helper function to recursively search a tree for a node*/
struct BSTNode* bst_containsHelper(struct BSTNode* node, char* key)
{
  // recursion needs a base case
  if((node == NULL) || (strcmp(node->key, key) == 0))
    return node;
  // searching key > node key
  if(strcmp(node->key, key) < 0 ) {
    if(node->right == NULL)
      return node;
    return bst_containsHelper(node->right, key);
  // searching key < node key
  } else {
    if(node->left == NULL)
      return node;
    return bst_containsHelper(node->left, key);
  }
}

/* Helper function for bst_deleteTree */
/* Post order traversal required so as to not access free'd memory*/
void bst_deleteTreeHelper(struct BSTNode* node)
{
  if(node == NULL)
    return;
  bst_deleteTreeHelper(node->left);
  bst_deleteTreeHelper(node->right);
  free(node->key);
  free(node);
}

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

/**
 *  bst_makeNode - makes a node using supplied values.
 *
 *  Parameters:
 *    char* key  - key of the new node we are making.
 *    struct BSTNode* left - pointer to the left node(child) of the new node
 *    struct BSTNode* right - pointer to the right node(child) of the new node
 *
 *  Return value: pointer to the new node
 */
struct BSTNode* bst_makeNode(char* key, struct BSTNode* left, struct BSTNode* right){
  struct BSTNode* node = (struct BSTNode*)malloc(sizeof(struct BSTNode));
  node->key = strdup(key);
  node->left = left;
  node->right = right;
  return node;
}

/**
 *  bst_add - adds a BSTNode* with the specified key to bst. Does nothing if
 *            the key already exists in the tree
 *
 *  Parameters:
 *    struct BST* bst - pointer to the BST we are adding to
 *    char* key  - key of the new node we are adding to bst
 */
void bst_add(struct BST* bst, char* key) {
  struct BSTNode* node;
  if(bst == NULL) // If bst is null, return from function
    return;
  if(bst->root == NULL)
    bst->root = bst_makeNode(key, NULL, NULL);
  node = bst->root;

  while(node != NULL) {
    if(strcmp(node->key,key) > 0) {   // key to insert < compared key
      if(node->left == NULL) {
        node->left = bst_makeNode(key, NULL, NULL);
      }
      node = node->left;
    } else if(strcmp(node->key, key) < 0) {  // key to insert > compared key
      if(node->right == NULL) {
        node->right = bst_makeNode(key, NULL, NULL);
      }
      node = node->right;
    } else { //if(node->key == key)
      return;
    }
  }
}

/*
 *  bst_remove - removes a BSTNode* with the specified key from bst. 
 *               Does nothing if the key doesn't exist in the tree
 *
 *  Parameters:
 *    struct BST* bst - pointer to the BST we are removing from
 *    char* key  - key of the new node we are removing from bst
 */ 
void bst_remove(struct BST* bst, char* key) {
  bst_removeHelper(bst->root, key);
  return;
}

/**
 *  bst_contains
 *
 *  Parameters:
 *    struct BST* bst - the tree to search
 *    char* key  - key of the node we are searching for
 *
 *  Return value: 1 if found, 0 if not found
 */
int bst_contains(struct BST* bst, char* key)
{
  struct BSTNode* new = bst_containsHelper(bst->root, key);
  if(strcmp(new->key, key) == 0)
    return 1;
  else
    return 0;
}

/**
 *  bst_min - finds the key of the smallest (leftmost) node in this bst.
 *
 *  Parameters:
 *    struct BST* bst - tree whose smallest node we're looking for.
 *
 *  Return value: largest key in the tree, or
 *    empty string if tree is empty.
 */
char* bst_min(struct BST* bst) {
  struct BSTNode* node = bst->root;
  if (node) {
    while (node->left) {
      node = node->left;
    }
    return node->key;
  } else {
    return NULL;
  }
}

/**
 *  bst_count - counts the number of nodes in tree.
 *
 *  Parameters:
 *    struct BST* bst - tree whose nodes we are counting.
 *
 *  Return value: number of nodes in the tree.
 */
int bst_count(struct BST* bst)
{
  return count(bst->root); //call the assembly function "count", return count
}

/**
 *  bst_totalLength - sums the keys of each node in the tree.
 *
 *  Parameters:
 *    struct BST* bst - tree whose nodes we are summing.
 *
 *  Return value: the sum of the values of each node's key.
 */
int bst_totalLength(struct BST* bst)
{
  return totalLength(bst->root); //call the assembly function "totalLength", return count
}

/**
 *  bst_deleteTree - deletes the whole bst tree.
 *
 *  Parameters:
 *    struct BST* bst - tree ehich we are deleting.
 *
 *  Return value: void
 */
void bst_deleteTree(struct BST* bst)
{
  bst_deleteTreeHelper(bst->root);
  free(bst);
  bst->root = NULL;
}
