#include "cutest/CuTest.h"
#include "ll.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Helper function for dynamically allocate a struct LL and initialize the 
 * member correctly
 */
struct LL* configure() {

  // Dynamically allocate on the heap
  struct LL* ll = (struct LL*)malloc(sizeof(struct LL));

  // Initialize the member start as NULL because malloc doesn't initialize 
  // members for you, which might cause seg fault
  ll->start = 0;

  return ll;
}

/**
 * Test make_node by make a single node and check its value
 */
void TestMakeNode_SingleNode(CuTest *tc){
  int expected = 1;
  struct Node * n = make_node(expected, NULL);

  //Check if n is null and if not, check the members
  CuAssertPtrNotNull(tc,n);
  CuAssertIntEquals(tc,expected,n->value);
  CuAssertPtrEquals(tc,NULL,n->next);

  // Free the node dynamically allocated
  free(n);
  
}

/**
 * Test make_node by adding multiple nodes manually
 */
void TestMakeNode_MultipleNodes(CuTest *tc){

  int expected1 = 1;
  int expected2 = 3;
  int expected3 = 100;

  // Link three nodes manually. n3->n2->n1
  struct Node * n1 = make_node(expected1, NULL);
  struct Node * n2 = make_node(expected2, n1);
  struct Node * n3 = make_node(expected3, n2);

  //Check if n3 is null and if not, check the members
  CuAssertPtrNotNull(tc,n3);
  CuAssertIntEquals(tc,expected3,n3->value);
  CuAssertPtrEquals(tc,n2,n3->next);
  
  //Check if n2 is null and if not, check the members
  CuAssertPtrNotNull(tc,n2);
  CuAssertIntEquals(tc,expected2,n2->value);
  CuAssertPtrEquals(tc,n1,n2->next);
  
  //Check if n1 is null and if not, check the members
  CuAssertPtrNotNull(tc,n1);
  CuAssertIntEquals(tc,expected1,n1->value);
  CuAssertPtrEquals(tc,NULL,n1->next);

  // Free the node dynamically allocated
  free(n1);
  free(n2);
  free(n3);
}

/**
 * Test add front by adding a node to an empty linked list
 */
void TestAddFront_AddToEmpty(CuTest *tc){

  struct LL* ll = configure();

  int value = 0;
  add_front(ll,value);

  //Check if the node is correctly added as the first node
  CuAssertPtrNotNull(tc, ll->start);
  CuAssertIntEquals(tc, value, ll->start->value);
  CuAssertPtrEquals(tc, NULL, ll->start->next);

  // Free all nodes and the ll itself
  delete_LL(ll);

  
}

/**
 * Test add front by adding multiple nodes to an empty linked list
 */
void TestAddFront_AddMultiple(CuTest *tc){

  struct LL* ll = configure();

  int value1 = 1;
  int value2 = 2;
  int value3 = 3;

  // Should be 3->2->1 after add
  add_front(ll,value1);
  add_front(ll,value2);
  add_front(ll,value3);

  // A pointer to hold a node temporarily
  struct Node* temp = ll->start;

  // Check if the first node holds value3
  CuAssertPtrNotNull(tc, ll->start);
  CuAssertIntEquals(tc, value3, temp->value);
  
  // Go to next node
  temp = temp->next;

  // Check if the next node holds value2
  CuAssertPtrNotNull(tc, temp);
  CuAssertIntEquals(tc, value2, temp->value);
  
  // Go to next node
  temp = temp->next;

  // Check if the next node holds value1
  CuAssertPtrNotNull(tc, temp);
  CuAssertIntEquals(tc, value1, temp->value);
  
  // Go to the next node and it should be NULL
  temp = temp->next;
  CuAssertPtrEquals(tc, NULL, temp);

  // Free all nodes and the ll itself
  delete_LL(ll);
}

/**
 * Test add front by adding duplicates. It should behave add them normally.
 */
void TestAddFront_AddDuplicate(CuTest *tc){

  struct LL* ll = configure();

  int value1 = 2;
  int value2 = 2;
  int value3 = 3;

  add_front(ll,value1);
  add_front(ll,value2);
  add_front(ll,value3);

  //A pointer to hold a node temporarily
  struct Node* temp = ll->start;

  //Check if the first node holds value3
  CuAssertPtrNotNull(tc, ll->start);
  CuAssertIntEquals(tc, value3, temp->value);
  
  //Go to next node
  temp = temp->next;

  //Check if the next node holds value2
  CuAssertPtrNotNull(tc, temp);
  CuAssertIntEquals(tc, value2, temp->value);
  
  //Go to next node
  temp = temp->next;

  //Check if the next node holds value1
  CuAssertPtrNotNull(tc, temp);
  CuAssertIntEquals(tc, value1, temp->value);
  
  // Go to the next node and it should be NULL
  temp = temp->next;
  CuAssertPtrEquals(tc, NULL, temp);

  // Free all nodes and the ll itself
  delete_LL(ll);
}


/**
 * Test add_front with adding to a NULL linked list. Nothing should happen.
 */
void TestAddFront_NullLinkedList(CuTest *tc) {

  struct LL* ll = NULL;
  add_front(ll, 0);
  
  // The linked list should still be NULL	
  CuAssertPtrEquals(tc, NULL, ll);
}
 
/**
 * Test remove_front with Null linked list. Nothing should happen.
 */
void TestRemoveFront_NullLinkedList(CuTest *tc) {

  struct LL* ll = NULL;

  int none = remove_front(ll);
	
  // Remove should return -1
  CuAssertIntEquals(tc, -1, none);
}

/**
 * Test remove_front
 */
void TestRemoveFront(CuTest *tc) {

  struct LL* ll = configure();

  // Add a node with 1
  add_front(ll, 1);

  // Node w/ 2 is at front now.
  add_front(ll, 2);	

  remove_front(ll);	

  // Node with 1 should be at front now		
  CuAssertIntEquals(tc, 1, ll->start->value);

  // Free all nodes and ll itself
  delete_LL(ll);
}

/**
 * Add all tests to the test suite
 */
CuSuite* StrUtilGetSuite() {
  CuSuite* suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, TestMakeNode_SingleNode);
  SUITE_ADD_TEST(suite, TestMakeNode_MultipleNodes);
  SUITE_ADD_TEST(suite, TestAddFront_AddToEmpty);
  SUITE_ADD_TEST(suite, TestAddFront_AddMultiple);
  SUITE_ADD_TEST(suite, TestAddFront_AddDuplicate);
  SUITE_ADD_TEST(suite, TestAddFront_NullLinkedList);
  SUITE_ADD_TEST(suite, TestRemoveFront_NullLinkedList);
  SUITE_ADD_TEST(suite, TestRemoveFront);
  return suite;
}
