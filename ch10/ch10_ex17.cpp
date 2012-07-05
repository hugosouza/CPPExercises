#include <iostream>

#include <cstdio>

class T2;

class T1 {
public:
  T1 () {}
  static void staticT1() { printf("staticT1();\n"); }
  void callT2();
};

class T2 {
public:
  T2 () {}
  static void staticT2() { printf("staticT2();\n"); }
  void callT1();
};

void T1::callT2 () { T2::staticT2(); }
void T2::callT1 () { T1::staticT1(); }

int main(int argc, char** argv) {
  T1 t1;
  T2 t2;
  t1.callT2();
  t2.callT1();
}
