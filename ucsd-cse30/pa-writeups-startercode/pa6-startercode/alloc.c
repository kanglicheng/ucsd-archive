#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

size_t HEAP_SIZE = 1028; // in bytes (e.g. 1kb of memory)
int WORD_SIZE = sizeof(int);

void* heap_ptr = NULL;
void* current_free_list = NULL;

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

	return NULL;
}

int my_free(void *ptr){
	return 0;
}

void consolidate(){
	
}

void print_heap(){

}

int free_space(){
	return 0;
}

int live_data(){
	return 0;
}
