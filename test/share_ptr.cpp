#include <iostream>

#include <boost/shared_ptr.hpp>

class T {
private:
  int i;
public:
  T() {}
  ~T() { printf("destroying T(): i = %d\n", i); }
  void set(int x) { i = x; }
  int get() { return i; }
};

typedef boost::shared_ptr<T> TPtr;

TPtr test(int x) {
  TPtr a(new T);
  a->set(x);
  printf("test(): a->get(): %d\n", a->get());
  return a;
}

int main(int argc, char **argv) {
  TPtr x;
  x = test(10);
  printf("x->get(): %d\n", x->get());
}

