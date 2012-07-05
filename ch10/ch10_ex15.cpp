#include <iostream>

#include <cstdio>

class Test {
public:
  Test () { printf("construct\n"); }
  ~Test() { printf("destruction\n"); }
};

Test a;

int main(int argc, char** argv) {
  printf("hello world\n");
}
