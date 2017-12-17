#include <stdlib.h>
struct Node {
  int value;
  struct Node* next;
};

int main() {
  struct Node* node = malloc(sizeof(struct Node));
  node->value = 12;
  node->next = NULL;
  return 0;
}


