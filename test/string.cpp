#include <iostream>
#include <string>
#include <utility>
#include <algorithm>

int main() {
  std::string s("test 123");
  for_each(s.begin(),
           s.end(),
           //[] (std::string::iterator xx) { std::cout << *xx << "\n"; printf("[%c]\n", *xx); });
           [] (char xx) { printf("[%c]\n", xx); });
}
