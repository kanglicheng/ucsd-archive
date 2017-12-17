#include <stdio.h>
#include <string.h>

struct Student {
  char pid[10]; 
  char* name;
};

void set_name(struct Student* s, char* name) {
  s->name = name;
}

void add_1(int* n) {
  n += 1;
}

int main() {
  struct Student s = { "A123456789", NULL };
  int i = 0;

  set_name(&s, strdup("Joe Politz"));

  add_1(&i);

  printf("%d %p\n", i, &i);

  printf("%s\n", s.name);

  return 0;
}

