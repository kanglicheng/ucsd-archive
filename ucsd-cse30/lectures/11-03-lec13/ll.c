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
struct Node* make_node(int value, struct Node* next) {
  struct Node* n = malloc(sizeof(struct Node));
  n->value = value;
  n->next = next;
  return n;
}

void add_front(struct LL* ll, int value) {

  struct Node* start = ll->start;
  struct Node* new_node = make_node(value, start);
  ll->start = new_node;

}

// Assume that start is not NULL
// Return the value of the start node, and remove
// the start node from the list
int remove_front(struct LL* ll) {

  int value = ll->start->value;
  struct Node* n = ll->start;
  ll->start = ll->start->next;
  free(n);
  return value;

}

int main() {
  struct LL* ll = malloc(sizeof(struct LL));
  ll->start = NULL;
  add_front(ll, 3);
  add_front(ll, 4);
  print_ll(ll); // Should print "4, 3,"

  while(1) {
    for(int i = 0; i < 100; i += 1) {
      add_front(ll, i);
    }
    for(int i = 0; i < 100; i += 1) {
      remove_front(ll);
    }
  }

  print_ll(ll);

  return 0;
}



void print_ll(struct LL* ll) {
  struct Node* node = ll->start;
  while(node != NULL) {
    printf("%d, ", node->value);
    node = node->next;
  }
  printf("\n");
}

