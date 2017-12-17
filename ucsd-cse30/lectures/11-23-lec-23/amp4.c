#include <stdio.h>
#include <string.h>

int main() {
  int cs[4];
  int* cs2 = cs;

  printf("%p %p\n", cs, cs2);

}
