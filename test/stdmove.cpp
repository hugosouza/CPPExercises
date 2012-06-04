#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>

std::string t(const char* p) {
  std::string a(p);
  printf(">>[%s]: 0x%lx\n", a.c_str(), (long unsigned int)&a);
  //return std::move(a);
  return a;
}

int main() {
  std::string a;
  std::vector<std::string> list;
  for(int i = 0; i < 1; i++) {
    std::ostringstream oss;
    oss << "test " << i;

    a = t(oss.str().c_str());
    printf("%8d [%s]: 0x%lx\n", i, a.c_str(), (long unsigned int)&a);
    list.push_back(a);
  }

  for(auto s: list) { printf("== [%s]\n", s.c_str());}

  printf("0x%0lx\n", (long unsigned int)nullptr);
}
