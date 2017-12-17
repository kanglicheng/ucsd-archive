#include <stdlib.h>
#include <stdio.h>

int my_strlen(char* s) {
  int index = 0;
  char current = *s;
  while(current != '\0') {
    index += 1;
    current = *(s + index);
  }
  return index;
}

// Return a _new_ string that's the concatenation of s1, s2
char* my_strcat(char* s1, char* s2) {

  int len1 = my_strlen(s1);
  int len2 = my_strlen(s2);

  // Which malloc makes the most sense to start with?

  // A:
  char* new_str = malloc(len1 + len2);

  // B:
  char* new_str = malloc(len1 + len2 + 1);

  // C:
  char* new_str = malloc(len1 + len2 - 1);
  
  // D:
  char* new_str = malloc(len1 + 1);

  // E:
  char* new_str = malloc(len2 + 1);












}

int main() {
  char* h = "hello ";
  char* c = "cse30";
  char* empty = "";
  printf("%d %d %d\n", my_strlen(h), my_strlen(c), my_strlen(empty));
}
