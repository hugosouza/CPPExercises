#include <iostream>
#include <cstring>

void t() {
  int* a;
  a = new int[10000];
  for (int i = 0; i < 10000; i++) {
    a[i] = i;
  }
  int* b;
  b = new int[20000];
  // for (int i = 0; i < 10000; i++) {
  //   b[i] = a[i];
  //   printf("%9d %9d\r", a[i], b[i]);
  // }
  memcpy(b, a, sizeof(int)*10000);
  for (int i = 0; i < 10000; i++) {
    printf("%9d\r", i);
  }
  delete[] a;

  // for(int i = 0; i < 10; i++) {
  //   printf("%d ", a[i]);
  // }

  delete[] b;
}

int main(int argc, char** argv) {
  for(int i = 0; i < 1000000; i++) {
    t();
    //printf("%8d/%8d\r", i, 1000000);
  }
  printf("\n");
}
