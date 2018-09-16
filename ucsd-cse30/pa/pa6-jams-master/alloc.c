#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

size_t HEAP_SIZE = 1028; // in bytes (e.g. 1kb of memory)
int WORD_SIZE = sizeof(int);

void* heap_ptr = NULL;
void* current_free_list = NULL;

/* Helper Function Definition */
int align(size_t size);
int words_in_free_block(int metadata);
void dump(int n);

void setup_heap() {
	// The mmap system call asks the operating system to please put HEAP_SIZE
	// memory into this process's address space. The resulting addresses
	// start at the very beginning of heap space (more or less). This is the
	// lowest-level interface to access memory without writing an operating
	// system yourself. It returns memory in fairly large chunks (usually
	// at least 1kb gets mapped at a time).
	heap_ptr = mmap(NULL, HEAP_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);

	// Set the first word on the heap to hold the total size available. See above for
	// a description of *(int*)ptr
	*(int*)heap_ptr = HEAP_SIZE - WORD_SIZE;
	*(void**)(heap_ptr+WORD_SIZE) = NULL;
	current_free_list = heap_ptr;
}

void teardown_heap(){
  munmap(heap_ptr, HEAP_SIZE);
  heap_ptr = NULL;
  current_free_list = NULL;
}

void *my_malloc(size_t size){
  // Resolves Boundary Case: Allocating Negative or Zero Bytes
  if(size <= 0 || size > HEAP_SIZE) { return NULL; }
  int metadata_size = align(size);

  if(current_free_list == 0)
    return NULL;
    

  /* Search free_list(linked list) for large enough free entry */
  int* flp = (int*)current_free_list;
  int* prev = flp;
  while(*flp <= metadata_size && *(flp+1) != 0) {
    prev = flp;
    flp = (int*)*(flp+1);
  }
  // if there isn't any free entry big enough for size, return empty
  if(*(flp+1) == 0 && *flp <= metadata_size) {
    return NULL;
  }

  
  if(size + 8 <= *flp){  
    // ===set free entry data===
    // The incoming link to the free entry should be updated to refer 
    // to its new location
    int new_occupied_words = words_in_free_block(metadata_size);
    int new_free_words = words_in_free_block(*flp) - new_occupied_words;

    // The size of the free entry should be updated to reflect the 
    // appropriate amount of space,    
    *(flp + new_occupied_words) = (new_free_words-1) * WORD_SIZE;

    // And the outgoing link from the free entry should be maintained.
    *(flp + new_occupied_words + 1) = *(flp+1);

    // == set occupied entry data==
    *flp = metadata_size;

    // change current_free_list to point to most recently freed entry on heap
    if(prev == flp) {
      current_free_list = (flp + new_occupied_words);
    } else {
      *(prev+1) = *(prev+1) + WORD_SIZE*new_occupied_words;
    }
    
  } else {
    // reuse whole entry
    *flp = *flp | 0x1;
    if(prev == flp) {
      current_free_list = (int*)*(flp + 1);
    } else {
      *(prev+1) = *(flp+1);
    }
  }
  return (void*)(flp+1);
}

int my_free(void *ptr){

  int *p = (int*)ptr;
  
 if (                          //errors and boundary trapping
    // Invalid Address Free: If my_free is called with an address that isn't 
    // a multiple of 4, it can't possibly have been allocated by my_malloc. 
    ( (int)p % WORD_SIZE != 0) ||
    // Similarly, if my_free is called with an address that isn't 
    // in the range of the provided heap, it can't have been 
    // allocated with my_malloc. In both of these invalid cases, 
    // my_free should change nothing and return 0.
    (p < (int*)heap_ptr) ||
    (p >= (int*)heap_ptr + HEAP_SIZE / WORD_SIZE - 1) ||
    // Double Free: If the program calls my_free with a pointer 
    // to memory that contains a free entry, my_free should change 
    // nothing and return 0.
    (*(p-1) % 2 != 1)
  ) return 0;

  // Change the metadata of the entry referred to by the 
  // given pointer so it indicates a free entry (this just 
  // means changing the least-significant bit from 1 to 0)
  int free_size = *(int*)(ptr-WORD_SIZE) - 1; // changes LSB to 0
  *(int*)(ptr-WORD_SIZE) = free_size;
  // Make the free entry's next pointer refer 
  // to the current start of the free list
  *(int*)ptr = (int)current_free_list;
  // Make the current start of the free list refer to 
  // this newly-created free entry
  current_free_list = (int*)(ptr-WORD_SIZE);
  
  return 1;
}


void consolidate(){
  int* heap_end=(int*)(heap_ptr+HEAP_SIZE);//heap end
  int* ptr = (int*)heap_ptr;          //implicit traversal pointer
  int* start;                         //start of free blocks
  int* previous;                      //previous free group
  int allocated = *ptr & 0x00000001;  //allocated bit
  int bytes = *ptr & 0xfffffffe;      //block size in bytes
  int sum = 0;                        //bytes available for new block
  int first = 1;                      //bool flag for incoming link

  //traverse heap (ignoring current_free_list and free list pointers)
  while(ptr < heap_end){                         
    //find, delineate, and consolidate a group of contiguous free blocks
    //1. find
    while(allocated){
      ptr += (1 + bytes / WORD_SIZE);
      allocated = *ptr & 0x00000001;
      bytes = *ptr & 0xfffffffc;
    } //ptr to first free block
    //set incoming link
    if (first) {current_free_list = ptr; first = 0;}
    else {*(previous+1) = (int)ptr;}
                      
    //2. delineate size
    start = ptr; //start of free blocks
    sum = 0;
    do {
      sum += (bytes + WORD_SIZE);
      ptr += (1 + bytes / WORD_SIZE);
      allocated = *ptr & 0x00000001;
      bytes = *ptr & 0xfffffffc;
    } while (!allocated && (ptr < heap_end));
    //This code exits with 'ptr' pointing to the word directly past
    //end of the last free block of a group of one or more contiguous
    //free blocks. 'sum' is the number of bytes available for the new
    //consolidated block including its header.
   
    //3. consolidate
    *start = sum - WORD_SIZE;  //size of consolidated block
    *(start+1) = 0;            //next block in case it's to be null
    previous = start;          //ready for next loop
  } // next loop
}

void print_heap(){
  int i;
  for(i = 0; i < 40; i += 4) { // replace i < X with i < HEAP_SIZE
    // In the format below,
    // - %p means "format as a pointer"
    // - %d means "format as integer"
    // - %#010x means "format as 10 hex digits with a leading 0x"
    printf("%10p:\t%d\t%#010x\n", (int*)(heap_ptr + i), *(int*)(heap_ptr + i), *(int*)(heap_ptr + i));
  }
  printf("heap_ptr: %10p\n", heap_ptr);
  printf("current_free_list: %10p\n", current_free_list);
}


int free_space(){
  if(current_free_list == 0)
    return 0;
  int* ptr = current_free_list;
  int sum = 0;
  while (1) {
    sum = sum + *ptr;          //sum the free bytes
    if (*(ptr+1) != 0) {       //if next pointer not null
      ptr = (int*)*(ptr + 1); //go to next pointer
    } else {
      return sum;             //null hit so return total
    }
  }
}

int live_data(){
  int* ptr = (int*)heap_ptr;
  int live = 0;
  int bytes = 0;
  while (1) {
    bytes = *ptr & 0xffffffe;  //retrieve bytes in block
    if (*ptr % 4) {live += bytes;} //if live add to total
    ptr += 1+ bytes / WORD_SIZE;
    if (ptr >= (int*)(heap_ptr + HEAP_SIZE)) return live; //
  }
  return 0;
}

/////////////////////
// helper functions//
/////////////////////
/*
 * Helper function
 * Resolves Boundary Case: Odd Sizes
 */
int align(size_t size)
{
  int sz = size % 4;
  if(sz != 0) {
    sz = 4 - sz;
  }
  return (sz + size + 1);
}

int words_in_free_block(int metadata)
{
  int i = (metadata / WORD_SIZE) + 1;
  return i;
}

void dump(int n) // print the heap
{
  int i;
  for (i = 0; i<n; i+=4) {
    if (!(i % 16)) {
      printf("\n");
      printf("0x%8x:  %08x ",(int)(heap_ptr+i), *(int*)(heap_ptr+i));
    }
    else {
      printf("%08x ", *(int*)(heap_ptr+i));
    };
  }
  printf("\n");
  printf("current_free_list: %p\n\n", current_free_list);
}
