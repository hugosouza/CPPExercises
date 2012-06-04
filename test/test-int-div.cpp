#include <iostream>
#include <cstdio>
#include <cstdint>

int main() {
  int a = 2;
  printf("%u div: %u rest: %u float: %.04f\n", a, (uint16_t)a/3, a % 3, (float)a/3);
}
