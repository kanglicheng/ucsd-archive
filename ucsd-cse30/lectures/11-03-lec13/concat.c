#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* my_strappend(char* s1, char* s2) {
  int l1 = strlen(s1), l2 = strlen(s2);
  char* newstr = malloc(l1 + l2 + 1);
  int i = 0;
  for(i = 0; i < l1; i += 1) { newstr[i] = s1[i]; }
  for(i = 0; i < l2; i += 1) { newstr[i + l1] = s2[i]; }
  newstr[l1 + l2] = '\0';
  return newstr;
}



int main() {
  int* nums = malloc(sizeof(int) * 10);
  nums[4] = 100;
  printf("%d\n", *(4 + nums));
  char* added = my_strappend("hello, ", "cse30");
  printf("%s (%d characters long)\n", (added), strlen(added));
}
