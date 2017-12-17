#include <stdlib.h>
#include <stdio.h>

char* f(){
  char* m = malloc(sizeof(char)* 10);
  char* n = malloc(sizeof(char)* 6);
  m = n;
  return m;
}

int main() {
  char* o = f(0);
  free(o);
}
