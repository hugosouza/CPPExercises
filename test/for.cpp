#include <iostream>
#include <vector>
#include <map>
#include <utility>

int main(int argc, char** argv) {
  std::vector<int> x = {10, 20, 30, 40};
  struct test {
    std::string s;
    int b;
  };
  std::vector<test> yy = {
    {"test 1", 10},
    {"test 2", 20},
    {"test 3", 30}
  };
  std::map<std::string, test> zz;
  zz["t1"] = { "test 1", 11 };
  zz["t2"] = { "test 2", 22 };
  zz["t3"] = { "test 3", 33 };

  for(auto i: x) {
    printf("[%i]\n", i);
  }

  for(auto i: yy) {
    printf("[%s] - [%d]\n", i.s.c_str(), i.b);
  }

  for (std::pair<std::string, test> a: zz) {
    printf("[%s] - [%s]:[%d]\n", a.first.c_str(), a.second.s.c_str(), a.second.b);
  }
}
