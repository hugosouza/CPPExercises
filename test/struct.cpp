#include <iostream>

int main() {
  typedef struct a {
    int x;
  } b;

  b test1 = {10};
  b* test2;
  test2 = &test1;

  printf("[%d]\n", test2->x);
}
