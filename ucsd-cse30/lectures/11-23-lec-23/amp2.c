#include <stdio.h>

struct S {
  int* i;
  int* j;
};

int main() {
  int num1 = 0;
  int* num2 = malloc(sizeof(int));
  struct S s = { &num1, num2 };

  *(s.i) = 100;

  *(s.j) = 500;

  printf("%d\n", num1);
  printf("%d\n", *num2);

  return 0;
}

