#include <stdlib.h>

int main() {
  int* some_numbers = malloc(8);

  *some_numbers = 10;
  *(some_numbers + 1) = 11;

  int* some_numbers2 = malloc(32);

  return 0;
}



