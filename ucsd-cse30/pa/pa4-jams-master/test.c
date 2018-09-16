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

  struct BST* bst = (struct BST*)malloc(sizeof(struct BST));
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

/* 2.1 bst_makeNode tests*/
/**
 * TestMakeNode_leafNode -  Test bst_makeNode by making a leafNode
 * 
 * Parameters: tc - CuTest instance
 * 
 * Return value: void
 */
void TestMakeNode_leafNode(CuTest *tc)
{
  char* key1 = "cse30";
  struct BSTNode* leftNode = NULL;
  struct BSTNode* rightNode = NULL;
  struct BSTNode* testNode = bst_makeNode(key1, leftNode, rightNode);
  CuAssertStrEquals(tc, "cse30", testNode->key);
  CuAssertPtrEquals(tc, NULL, testNode->left);
  CuAssertPtrEquals(tc, NULL, testNode->right);
  // free memory
  free(testNode->key);
  free(testNode);
}

/**
 * TestMakeNode_withChildren - Test bst_makeNode by making node with children.
 * 
 * Parameters: tc - CuTest instance
 * 
 * Return value: void
 */
void TestMakeNode_withChildren(CuTest *tc)
{
  struct BSTNode* testNode = bst_makeNode("cse30", bst_makeNode("James", NULL, NULL), bst_makeNode("John", NULL, NULL));
  int cond = 0;
  if((testNode->left->right == NULL) && (testNode->right->left == NULL))
    cond = 1;
  CuAssertStrEquals(tc, "cse30", testNode->key);
  CuAssertStrEquals(tc, "James", testNode->left->key);
  CuAssertStrEquals(tc, "John", testNode->right->key);
  CuAssertTrue(tc, cond);
  //free memory
  free(testNode->left->key);
  free(testNode->left);
  free(testNode->right->key);
  free(testNode->right);
  free(testNode->key);
  free(testNode);
}

/* Sample tree setups */
/**
 * A function to set up a sample bst
 */
struct BST* configureAlphabetTestTree()
{
  // Makes 
  //              m
  //          e       t
  //        b   f   r   x
  //      a      h       y
  struct BST* tree = (struct BST*)malloc(sizeof(struct BST));
  // Right subtree
  struct BSTNode* nodey = bst_makeNode("y", NULL, NULL);
  struct BSTNode* nodex = bst_makeNode("x", NULL, nodey);
  struct BSTNode* noder = bst_makeNode("r", NULL, NULL);
  struct BSTNode* nodet = bst_makeNode("t", noder, nodex);
  // Left subtree
  struct BSTNode* nodeh = bst_makeNode("h", NULL, NULL);
  struct BSTNode* nodef = bst_makeNode("f", NULL, nodeh);
  struct BSTNode* nodea = bst_makeNode("a", NULL, NULL);
  struct BSTNode* nodeb = bst_makeNode("b", nodea, NULL);
  struct BSTNode* nodee = bst_makeNode("e", nodeb, nodef);
  tree->root = bst_makeNode("m", nodee, nodet);
  return tree;
}

/* 2.2 bst_add tests */
/**
 * TestBSTAdd_alphabetBST - Test bst_add by adding to an populated tree.
 * 
 * Parameters: tc - CuTest instance
 * 
 * Return value: void
 */
void TestBSTAdd_alphabetBST(CuTest *tc)
{
  // Tests 
  //                  m
  //            e              t
  //        b     f          r      x
  //     a   +c    h          +s      y
  //             +g                    +z

  struct BST* tree = configureAlphabetTestTree();
  bst_add(tree, "c");
  bst_add(tree, "g");
  bst_add(tree, "s");
  bst_add(tree, "z");
  CuAssertStrEquals(tc, "c", tree->root->left->left->right->key);
  CuAssertStrEquals(tc, "g", tree->root->left->right->right->left->key);
  CuAssertStrEquals(tc, "s", tree->root->right->left->right->key);
  CuAssertStrEquals(tc, "z", tree->root->right->right->right->right->key);
 
  // free tree
  bst_deleteTree(tree);
}

/* 2.3 bst_remove tests  */
/**
 * TestBSTRemove_alphabetBST - test bst_remove on alphabet tree
 * 
 * Parameters: tc - CuTest instance
 * 
 * Return value: void
 */
void TestBSTRemove_alphabetBST(CuTest *tc)
{
  // Tests 
  //                    m
  //            e               t
  //        b     f          r      x
  //     a          h                 y
  struct BST* tree = configureAlphabetTestTree();
  // remove "r" - leaf node
  CuAssertStrEquals(tc, "r", tree->root->right->left->key);
  bst_remove(tree, "r");
  CuAssertPtrEquals(tc, NULL, tree->root->right->left);
  // remove "y" - leaf node
  CuAssertStrEquals(tc, "y", tree->root->right->right->right->key);
  bst_remove(tree, "y");
  CuAssertPtrEquals(tc, NULL, tree->root->right->right->right);
  // remove "t" - 2 children
  CuAssertStrEquals(tc, "t", tree->root->right->key);
  bst_remove(tree, "t");
  CuAssertStrEquals(tc, "x", tree->root->right->key);
  // remove "b" - 1 child
  CuAssertStrEquals(tc, "b", tree->root->left->left->key);
  bst_remove(tree, "b");
  CuAssertStrEquals(tc, "e", tree->root->left->key);
  CuAssertStrEquals(tc, "a", tree->root->left->left->key);
  // remove "m" - the root
  CuAssertStrEquals(tc, "m", tree->root->key);
  bst_remove(tree, "m");
  CuAssertStrEquals(tc, "e", tree->root->left->key);
 
  // free memory
  bst_deleteTree(tree);
}

/* 2.4 bst_contains tests  */
/**
 * TestBSTContains_alphabetBST - Test bst_contains on alphabet tree
 * 
 * Parameters: tc - CuTest instance
 * 
 * Return value: void
 */
void TestBSTContains_alphabetBST(CuTest *tc)
{
  // Tests 
  //                  m
  //            e              t
  //        b     f          r      x
  //     a         h                  y
  struct BST* tree = configureAlphabetTestTree();
  // test membership
  CuAssertTrue(tc, bst_contains(tree, "m"));
  CuAssertTrue(tc, bst_contains(tree, "e"));
  CuAssertTrue(tc, bst_contains(tree, "t"));
  CuAssertTrue(tc, bst_contains(tree, "b"));
  CuAssertTrue(tc, bst_contains(tree, "f"));
  CuAssertTrue(tc, bst_contains(tree, "r"));
  CuAssertTrue(tc, bst_contains(tree, "x"));
  CuAssertTrue(tc, bst_contains(tree, "a"));
  CuAssertTrue(tc, bst_contains(tree, "h"));
  CuAssertTrue(tc, bst_contains(tree, "y"));
  // test non-membership
  CuAssertTrue(tc, bst_contains(tree, "q") + 1 );
  CuAssertTrue(tc, bst_contains(tree, "s") - 1 );
  CuAssertTrue(tc, bst_contains(tree, "v") - 1 );
  CuAssertTrue(tc, bst_contains(tree, "n") - 1 );
  // free memory
  bst_deleteTree(tree);
}


/* 2.5 bst_max tests  */
/**
 * TestBSTMax_alphabetBST - Test bst_max on alphabet BST.
 * 
 * Parameters: tc - CuTest instance
 * 
 * Return value: void
 */
void TestBSTMax_alphabetBST(CuTest *tc) 
{
  struct BST* tree = configureAlphabetTestTree();
  CuAssertStrEquals(tc, "y", bst_max(tree));
  bst_add(tree, "z");
  CuAssertStrEquals(tc, "z", bst_max(tree));
  // free memory
  bst_deleteTree(tree);
}

/* 2.6 bst_min tests  */
/**
 * TestBSTMin_alphabetBST - Test bst_min on alphabet BST.
 * 
 * Parameters: tc - CuTest instance
 * 
 * Return value: void
 */
void TestBSTMin_alphabetBST(CuTest *tc)
{
  struct BST* tree = configureAlphabetTestTree();
  CuAssertStrEquals(tc, "a", bst_min(tree));
  // free memory
  bst_deleteTree(tree);
}

/* 2.7 bst_count tests  */
/**
 * TestBSTCount_alphabetBST - test count assembly function
 * 
 * Parameters: tc - CuTest instance
 * 
 * Return value: void
 */
void TestBSTCount_alphabetBST(CuTest *tc) 
{
  struct BST* tree = configureAlphabetTestTree();
  int cond = 0;
  if(bst_count(tree) == 10)
    cond = 1;
  CuAssertTrue(tc, cond);
  // free memory
  bst_deleteTree(tree);
}

/* 2.8 bst_totalLength tests  */
/**
 * TestBSTTotalLength - test bst_count on alphabet BST
 * 
 * Parameters: tc - CuTest instance
 * 
 * Return value: void
 */
void TestBSTTotalLength_smallBST(CuTest *tc)
{
  struct BST* tree = (struct BST*)malloc(sizeof(struct BST));
  bst_add(tree, "1");
  bst_add(tree, "2");
  bst_add(tree, "3");
  bst_add(tree, "9");
  bst_add(tree, "dogs");
  int sum = 8;
  int cond = 0;
  if(bst_totalLength(tree) == sum)
    cond = 1;
  CuAssertIntEquals(tc, sum, bst_totalLength(tree));
  CuAssertTrue(tc, cond);

  // free memory
  bst_deleteTree(tree);
}

/* 2.9 bst_deleteTree tests  */
/**
 * TestBSTTotalLength - test bst_count on alphabet BST
 * 
 * Parameters: tc - CuTest instance
 * 
 * Return value: void
 */
void TestBSTDeleteTree_alphabetBST(CuTest *tc)
{
/*
Anonymous 2 days ago

Thanks! Just to clarify, do we have to make a tester function for it in the test.c?
[Yimeng]
Yimeng 2 days ago

Not necessarily! You can just call deleteTree at the end of each tester function and see if there is memory leak in valgrind.
*/
}


/*
 * Note that as you add new testing functions, you need to add them to the list
 * below using SUITE_ADD_TEST. Otherwise they will not run.
 */
CuSuite* StrUtilGetSuite() {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, TestManualMallocAndFree);
  SUITE_ADD_TEST(suite, TestMakeNode_leafNode);
  SUITE_ADD_TEST(suite, TestMakeNode_withChildren);
  SUITE_ADD_TEST(suite, TestBSTAdd_alphabetBST);
  SUITE_ADD_TEST(suite, TestBSTRemove_alphabetBST);
  SUITE_ADD_TEST(suite, TestBSTContains_alphabetBST);
  SUITE_ADD_TEST(suite, TestBSTMax_alphabetBST);
  SUITE_ADD_TEST(suite, TestBSTMin_alphabetBST);
  SUITE_ADD_TEST(suite, TestBSTCount_alphabetBST);
  SUITE_ADD_TEST(suite, TestBSTTotalLength_smallBST);
  //SUITE_ADD_TEST(suite, TestBSTDeleteTree_alphabetBST);
  return suite;
}
