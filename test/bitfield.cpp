#include <iostream>
#include <map>
#include <functional>

#include <cmath>

enum test_type {
  type1,
  type2,
  type3,
  type4
};

struct t {
  bool b1 : 1;
  bool b2 : 1;
  test_type b3 : 2;
  bool b4 : 1;
};

struct charBitField {
  bool b0 : 1;
  bool b1 : 1;
  bool b2 : 1;
  bool b3 : 1;
  bool b4 : 1;
  bool b5 : 1;
  bool b6 : 1;
  bool b7 : 1;
};

std::map<test_type, std::string> type2str = {
  {type1, "Type 1"},
  {type2, "Type 2"},
  {type3, "Type 3"},
  {type4, "Type 4"},
};

int main(int argc, char **argv) {
  char xx = 'c';
  charBitField *xx_bf = (charBitField*)&xx;

  struct t a;
  a.b1 = true;
  a.b2 = false;
  a.b3 = type3;

  printf("a.b1[0x%08x], a.b2[0x%08x], a.b3[%s]\n", a.b1, a.b2, type2str[a.b3].c_str());
  printf("sizeof a: %lu\n", sizeof(a));

  printf("xx = %c (%d)\n", xx, xx);
  printf("xx_bf->b0 = [%d] = %.f\n", xx_bf->b0, xx_bf->b0 ? pow(2,0) : 0);
  printf("xx_bf->b1 = [%d] = %.f\n", xx_bf->b1, xx_bf->b1 ? pow(2,1) : 0);
  printf("xx_bf->b2 = [%d] = %.f\n", xx_bf->b2, xx_bf->b2 ? pow(2,2) : 0);
  printf("xx_bf->b3 = [%d] = %.f\n", xx_bf->b3, xx_bf->b3 ? pow(2,3) : 0);
  printf("xx_bf->b4 = [%d] = %.f\n", xx_bf->b4, xx_bf->b4 ? pow(2,4) : 0);
  printf("xx_bf->b5 = [%d] = %.f\n", xx_bf->b5, xx_bf->b5 ? pow(2,5) : 0);
  printf("xx_bf->b6 = [%d] = %.f\n", xx_bf->b6, xx_bf->b6 ? pow(2,6) : 0);
  printf("xx_bf->b7 = [%d] = %.f\n", xx_bf->b7, xx_bf->b7 ? pow(2,7) : 0);

  std::function<void(uint16_t, uint16_t)> print_func;
  print_func = [] (uint16_t i, uint16_t exp) {printf("[%d]: [%d] = %.f\n", exp, i, i ? pow(2, exp) : 0);};

  print_func(xx_bf->b0, 0);
  print_func(xx_bf->b1, 1);
  print_func(xx_bf->b2, 2);
  print_func(xx_bf->b3, 3);
  print_func(xx_bf->b4, 4);
  print_func(xx_bf->b5, 5);
  print_func(xx_bf->b6, 6);
  print_func(xx_bf->b7, 7);
}
