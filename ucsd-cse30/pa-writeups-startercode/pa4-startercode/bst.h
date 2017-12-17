#ifndef BST_CLASS
#define BST_CLASS
#include "bst.h"
#include <stdlib.h>
#include <string.h>

struct BSTNode {
  char* key;
  struct BSTNode* left;
  struct BSTNode* right;
};

struct BST {
  struct BSTNode* root;
};

// In C
struct BSTNode* bst_makeNode(char* key, struct BSTNode* left, struct BSTNode* right);
void bst_add(struct BST* bst, char* key);
void bst_remove(struct BST* bst, char* key);
int bst_contains(struct BST* bst, char* key);
char* bst_max(struct BST* bst);
char* bst_min(struct BST* bst);
void bst_deleteTree(struct BST* bst);

// In assembly (helper functions for bst_count and bst_totalLength)
int count(struct BSTNode* node);
int totalLength(struct BSTNode* node);

// Two C functions, implemented with Assembly helpers
int bst_count(struct BST* bst);
int bst_totalLength(struct BST* bst);

#endif // BST_CLASS
