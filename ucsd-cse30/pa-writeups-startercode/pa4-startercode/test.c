#include "cutest/CuTest.h"
#include "bst.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
    
/*
 * Your tests won't look like this; they will use helpers like makeNode and
 * call the actual bst_ functions. This is here to give you an example of
 * creating space for a BSTNode with malloc and using a testing function to
 * check the string.
 *
 */
void TestManualMallocAndFree(CuTest *tc) {
  // This is a lot of manually allocating! Once you write bst_makeNode, this
  // can get simpler
  struct BSTNode* node = (struct BSTNode*)malloc(sizeof(struct BSTNode));
  node->key = strdup("apple");
  node->left = NULL;
  node->right = NULL;
  CuAssertStrEquals(tc, "apple", node->key);

  struct BSTNode* forRight = (struct BSTNode*)malloc(sizeof(struct BSTNode));
  forRight->key = strdup("cranberry");
  forRight->left = NULL;
  forRight->right = NULL;

  struct BST* bst = (struct BST*)malloc(sizeof(struct BST*));
  bst->root = node;
  bst->root->right = forRight;

  CuAssertStrEquals(tc, "cranberry", bst_max(bst));

  // This is a lot of freeing! Once you write the delete functions this won't
  // be necessary anymore; the next five lines should really just be
  // bst_deleteTree

  free(forRight->key);
  free(forRight);

  free(node->key);
  free(node);

  free(bst);
}



/*
 * Note that as you add new testing functions, you need to add them to the list
 * below using SUITE_ADD_TEST. Otherwise they will not run.
 */
CuSuite* StrUtilGetSuite() {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, TestManualMallocAndFree);
  return suite;
}
