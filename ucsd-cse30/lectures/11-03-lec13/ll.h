#ifndef LL_CLASS
#define LL_CLASS

#include <stdlib.h>
#include <stdio.h>

struct LL {
  struct Node* start;
};

struct Node {
  int value;
  struct Node* next;
};

// Implemented at the bottom; just prints
void print_ll(struct LL* ll);

// A constructor
struct Node* make_node(int value, struct Node* next);

void add_front(struct LL* ll, int value);

// Assume that start is not NULL
// Return the value of the start node, and remove
// the start node from the list
int remove_front(struct LL* ll);

void delete_LL(struct LL* ll);

#endif // LL_CLASS
