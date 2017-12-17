#include <stdio.h>
#include <stdlib.h>

int main() {
  int* x = malloc(sizeof(int));
  *x = 555;
  int** ptr_to_stack = &x;
  **ptr_to_stack = 333;
  printf("%d\n", *x);
}
