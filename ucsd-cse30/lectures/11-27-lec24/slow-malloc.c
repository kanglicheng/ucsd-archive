#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

/*

  This is an implementation of the SLOW version of malloc from class on Nov 27.

  It's provided as an example of how to use some casting and arithmetic
  operations on pointers, which you'll need for your PA.

*/

void* heap_ptr = NULL;
void* heap_max = NULL;
size_t HEAP_SIZE = 1024; // in bytes (e.g. 1kb of memory)

int WORD_SIZE = sizeof(int);

void* slow_malloc(size_t size) {

  if(size == 0) { return NULL; }

  // Make sure size is aligned on a WORD_SIZE boundary
  if(size % WORD_SIZE != 0) {
    size = size + (WORD_SIZE - (size % WORD_SIZE));
  }

  void* cur = heap_ptr;
  while(cur < heap_ptr + HEAP_SIZE) {

    // There are two parts to this expression.
    // - The (int*)cur is a _cast_, that says "treat the void* pointer cur as
    //   an int* pointer"
    // - The * in front then gets the contents of one int at that location.

    // The end result is that cur_size holds the first 4 bytes (interpreted as
    // an int) of where cur is pointing
    int cur_word = *(int*)cur;

    // cur_size & 0x1 is checking if the least-significant bit is 1 (e.g. this
    // is occupied space)
    int is_occupied = cur_word & 0x1;

    // cur_size & ~0x1 gets the rest of the value without the least significant
    // bit, and represents the actual size
    int cur_size = cur_word & ~0x1;

    // Read these conditions as "if the block is occupied OR it is too
    // small to hold the requested size"
    if(is_occupied || cur_size < size) {

      // If these conditions are true, then skip the current block by adding to
      // cur. Note that when we add to a void* pointer, it adds by bytes. So
      // this adds cur_size _bytes_ to the address stored in cur
      cur += cur_size + WORD_SIZE;
      continue;
    }

    // If the space is unoccupied AND the size is large enough to fit, then we
    // split the space if necessary, and mark it as occupied
    else {

      // If the size we're asking for within 4 of the size of the block, then
      // there's no use in splitting it up
      if(cur_size <= size+ WORD_SIZE) {

        // Set the contents of the cur word to have a 1 in the least
        // significant bit (marking it as occupied). Leave the size alone
        *(int*)cur |= 0x1;

        // Return the word immediately after the metadata word
      }

      // We know that size must be at least 5 larger than cur_size, and since
      // we round to 4, it must be at least 8!
      else {

        // Set the contents of the cur word to have a 1 in the least
        // significant bit (marking it as occupied), and the requested size
        *(int*)cur = size | 0x1;

        // Set the contents of the address _after_ the allocated data to the
        // difference in sizes. Note that the least-significant bit must be 0
        // because these are all 4-byte-aligned values
        void* address_of_free_space = cur + size + WORD_SIZE;
        *(int*)address_of_free_space = (cur_size - size - WORD_SIZE);
      }

      // Finally, we return the word _after_ the current word
      return cur + sizeof(int);
    }
  }
  return NULL;
}

void slow_free(void* ptr) {
  *(int*)(ptr - WORD_SIZE) &= ~0x1;
}

void print_mem(int* addr, int howmany) {
  int i;
  for(i = 0; i < howmany; i += 1) {
    // In the format below,
    // - %p means "format as pointer"
    // - %d means "format as integer"
    // - %#010x means "format as 10 hex digits with a leading 0x"
    printf("%10p:\t%d\t%#010x\n", addr + i, *(addr + i), *(addr + i));
  }
}

void setup_heap() {
  // The mmap system call asks the operating system to please put HEAP_SIZE
  // memory into this process's address space. The resulting addresses
  // start at the very beginning of heap space (more or less). This is the
  // lowest-level interface to access memory without writing an operating
  // system yourself. It returns memory in fairly large chunks (usually
  // at least 1kb gets mapped at a time).
  heap_ptr = mmap(NULL, HEAP_SIZE, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0);

  // Set the first word on the heap to hold the total size available. See above for
  // a description of *(int*)ptr
  *(int*)heap_ptr = HEAP_SIZE - WORD_SIZE;
}

void example1() {

  setup_heap();

  printf("This example shows incrementally re-using existing freed space, which is filled with two smaller allocations\n");

  printf("\n\nInitial empty heap:\n\n");
  print_mem(heap_ptr, 20);

  int* addr = slow_malloc(sizeof(int) * 3);
  int* addr2 = slow_malloc(sizeof(int) * 5);
  int* addr3 = slow_malloc(sizeof(int) * 4);

  printf("\n\nWith the first three allocations:\n\n");
  print_mem(heap_ptr, 20);

  slow_free(addr2);

  printf("\n\nAfter freeing the second block:\n\n");
  print_mem(heap_ptr, 20);

  int* addr4 = slow_malloc(sizeof(int) * 2);

  printf("\n\nAfter allocating 8 bytes into the freed block:\n\n");
  print_mem(heap_ptr, 20);

  printf("\n\nAfter allocating 8 bytes into the (now smaller) freed block:\n\n");
  int* addr5 = slow_malloc(sizeof(int) * 2);
  print_mem(heap_ptr, 20);

}

void example2() {

  setup_heap();

  printf("\n\nThis example shows that small free spaces must be skipped by larger allocations\n\n");

  printf("\n\nInitial empty heap:\n\n");
  print_mem(heap_ptr, 24);

  int* addr1 = slow_malloc(sizeof(int) * 3);
  int* addr2 = slow_malloc(sizeof(int) * 3);
  int* addr3 = slow_malloc(sizeof(int) * 3);
  int* addr4 = slow_malloc(sizeof(int) * 3);

  printf("\n\nWith 4 allocations of size 12:\n\n");
  print_mem(heap_ptr, 24);

  slow_free(addr1);
  slow_free(addr3);

  printf("\n\nAfter freeing the first and third:\n\n");
  print_mem(heap_ptr, 24);


  slow_malloc(sizeof(int) * 4);

  printf("\n\nAn allocation of size 16 must go at the end:\n\n");
  print_mem(heap_ptr, 24);

  slow_malloc(sizeof(int) * 3);

  printf("\n\nBut an allocation of size 12 can re-use space:\n\n");
  print_mem(heap_ptr, 24);


}

int main() {

  example1();
  example2();

}

