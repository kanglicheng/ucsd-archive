#include "cutest/CuTest.h"
#include "alloc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
    

void TestMyMalloc0(CuTest *tc) {
  setup_heap();
  void *p1 = my_malloc(0);
  CuAssertPtrEquals(tc, NULL, p1);
  teardown_heap();
}


void TestMyFreeOnFreeEntry(CuTest * tc){
  setup_heap();
  int result = my_free(current_free_list);
  CuAssertIntEquals(tc, 0,result);
  teardown_heap();
}

/*
 * Note that as you add new testing functions, you need to add them to the list
 * below using SUITE_ADD_TEST. Otherwise they will not run.
 */
CuSuite* StrUtilGetSuite() {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, TestMyMalloc0);
  SUITE_ADD_TEST(suite, TestMyFreeOnFreeEntry);
  return suite;
}
