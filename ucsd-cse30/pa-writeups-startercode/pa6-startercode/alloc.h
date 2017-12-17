#include <sys/types.h>
#include <stddef.h>

extern size_t HEAP_SIZE;
extern int WORD_SIZE;

extern void* heap_ptr;
extern void* current_free_list;

void *my_malloc(size_t size);
int my_free(void *ptr);

void consolidate();
void print_heap();
int free_space();
int live_data();

void setup_heap();
void teardown_heap();
