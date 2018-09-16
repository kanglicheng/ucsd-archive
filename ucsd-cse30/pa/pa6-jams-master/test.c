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

void TestMallocOutOfBounds(CuTest * tc) {
  setup_heap();
  CuAssertPtrEquals(tc, NULL, my_malloc(1028));
  teardown_heap();
}

void TestFreeOutOfBounds(CuTest * tc) {
  setup_heap();
  void* p1 = my_malloc(9);
  CuAssertIntEquals(tc, 0, my_free(heap_ptr-1));
  CuAssertIntEquals(tc, 0, my_free(heap_ptr+1028));
  my_free(p1);
  teardown_heap();
}

void TestFreeSpaceSetupTeardown(CuTest * tc) {
  setup_heap();
  CuAssertIntEquals(tc, 1024, free_space());
  teardown_heap();
}

void TestFreeSpaceSetupMallocTeardown(CuTest * tc) {
  setup_heap();
  void *p1 = my_malloc(9);
  CuAssertIntEquals(tc, 1008, free_space());
  void *p2 = my_malloc(25);
  CuAssertIntEquals(tc, 976, free_space());
  my_free(p1);
  my_free(p2);
  teardown_heap();
}

void TestFreeSpaceSetupMallocFreeTeardown(CuTest * tc) {
  setup_heap();
  void* p1 = my_malloc(9);
  CuAssertIntEquals(tc, 1008, free_space());
  void *p2 = my_malloc(25);
  CuAssertIntEquals(tc, 976, free_space());
  my_free(p2);
  CuAssertIntEquals(tc, 1004, free_space());
  my_free(p1);
  CuAssertIntEquals(tc, 1016, free_space());
  teardown_heap();
}

void TestLiveDataSetupTeardown(CuTest * tc) {
  setup_heap();
  CuAssertIntEquals(tc, 0, live_data());
  teardown_heap();
}
  
void TestLiveDataSetupMallocTeardown(CuTest * tc) {
  setup_heap();
  CuAssertIntEquals(tc, 0, live_data());
  void* p1 = my_malloc(9);
  CuAssertIntEquals(tc, 12, live_data());
  void* p2 = my_malloc(25);
  CuAssertIntEquals(tc, 40, live_data());
  my_free(p1);
  my_free(p2);
  teardown_heap();
}

void TestLiveDataSetupMallocFreeTeardown(CuTest * tc) {
  setup_heap();
  CuAssertIntEquals(tc, 0, live_data());
  void* p1 = my_malloc(9);
  CuAssertIntEquals(tc, 12, live_data());
  void* p2 = my_malloc(25);
  CuAssertIntEquals(tc, 40, live_data());
  my_free(p2);
  CuAssertIntEquals(tc, 12, live_data());
  my_free(p1); 
  CuAssertIntEquals(tc, 0, live_data());
  teardown_heap();
}

void TestAllocatingNegativeOrZeroBytes(CuTest * tc) {
  setup_heap();
  int i;
  CuAssertPtrEquals(tc, NULL, my_malloc(-100));
  CuAssertPtrEquals(tc, NULL, my_malloc(0));
  for(i = -100; i <= 0; i++)
  {
    CuAssertPtrEquals(tc, NULL, my_malloc(i));
  }
  
  teardown_heap();
}

void TestDoubleFree(CuTest * tc) {
  setup_heap();
  void* p1 = my_malloc(9);
  int f1 = my_free(p1);
  int f2 = my_free(p1);
  CuAssertIntEquals(tc, 1, f1);
  CuAssertIntEquals(tc, 0, f2);
  teardown_heap();
}

void TestInvalidAddressFree(CuTest * tc) {
  setup_heap();
  void* p1 = my_malloc(11);
  int i;
  for(i = 0; i < 100; i++) {
    if(i % 4 != 0) { 
      CuAssertIntEquals(tc, 0, my_free(p1+i));
    }
  }
  teardown_heap();
}

void TestREADMEQuestion1(CuTest *tc) {
  setup_heap();
  int i;
  int arraysize = 150;
  int* ptr_array[arraysize];
  int free_array[arraysize];

  for(i = 1; i < arraysize; i++) {
    int r = rand() % 17  +1;
    free_array[i] += 1;
    printf("next:     i: %i  0x-------- = my_malloc(%i)\n incoming CFL: %p\n", i, r, current_free_list);
    getchar();

    int *p = (int*)my_malloc(r);
    ptr_array[i] = p;

    dump(1028);
    printf("live data: %i  free space: %i \n", live_data(), free_space() );
    printf("previous: i: %i  %p = my_malloc(%i)\n", i, ptr_array[i], r);
  }

  for(i = 0; i < arraysize; i++) {
    free_array[i] = my_free(ptr_array[rand() % 100 + 1]);
  }
  dump(1028);
  printf("Free Space should be relatively large and my_malloc returns  null");
  printf("free_space = %d\n", free_space());
  teardown_heap();
}


void TestREADMEQuestion2(CuTest * tc) {
  setup_heap();
  void* p1 = my_malloc(500);
  void* p2 = my_malloc(250);
  void* p3 = my_malloc(125);
  void* p4 = my_malloc(40);
  my_free(p1);
  my_free(p2);
  my_free(p3);
  my_free(p4);
  teardown_heap();
}


void StressTest(CuTest *tc){
  setup_heap();
  int i = 0;
  int arraysize = 10;
  int* ptr_array[arraysize];
  int free_array[arraysize];
  int* p;

  for (i = 0; i < arraysize; i++) {
    free_array[i] = 1;
  }

  for (i = 0; i < 555555; i++) {
    int fate = rand() % 2;
    int ai = i % arraysize;
    printf("fate: %i   i: %i   i mod a: %i ", fate, i, ai);


    if (fate == 1 && free_array[ai] == 1) {
      int r = rand() % 250 +1;
      p = (int*)my_malloc(r);
      ptr_array[ai] = p;
      if(p != NULL) { 
        free_array[ai] = 0;
      }
      printf("  %p = my_malloc(%i)\n", p, r);
    } else {
      printf("\n");
    }

    if (fate == 0 && free_array[ai] == 0) {
      free_array[ai] = my_free(ptr_array[ai]);
      printf("   my_free(%p)\n", ptr_array[ai]);
    } else {
      printf("\n");
    }
    
    char c = getchar();
    if (c == 'c')  {consolidate(); printf("CONSOLIDATE!");}
    dump(1028);
    if (ai && ((rand() % 150 +1) == 1)) {
      consolidate(); 
      printf("CONSOLIDATE!");
    }
    int ld = live_data();
    int fs = free_space();
    printf("live data: %i  free space: %i  frag: %f\n\n", ld, fs, (float)(1028-ld-fs)/1028 );
  }
  teardown_heap();
}

/*
 * Note that as you add new testing functions, you need to add them to the list
 * below using SUITE_ADD_TEST. Otherwise they will not run.
 */
CuSuite* StrUtilGetSuite() {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, TestMyMalloc0);
  SUITE_ADD_TEST(suite, TestMallocOutOfBounds);
  SUITE_ADD_TEST(suite, TestFreeOutOfBounds);
  
  //SUITE_ADD_TEST(suite, TestPrintHeap);
  SUITE_ADD_TEST(suite, TestFreeSpaceSetupTeardown);
  SUITE_ADD_TEST(suite, TestFreeSpaceSetupMallocTeardown);
 
  SUITE_ADD_TEST(suite, TestFreeSpaceSetupMallocFreeTeardown);
  SUITE_ADD_TEST(suite, TestLiveDataSetupTeardown);
  SUITE_ADD_TEST(suite, TestLiveDataSetupMallocTeardown);
  SUITE_ADD_TEST(suite, TestLiveDataSetupMallocFreeTeardown);
 
  SUITE_ADD_TEST(suite, TestAllocatingNegativeOrZeroBytes);
    
  SUITE_ADD_TEST(suite, TestDoubleFree); 
  SUITE_ADD_TEST(suite, TestInvalidAddressFree); 
  
  //SUITE_ADD_TEST(suite, TestREADMEQuestion1);
  //SUITE_ADD_TEST(suite, TestREADMEQuestion2);
  //SUITE_ADD_TEST(suite, StressTest);
  
  return suite;
}
