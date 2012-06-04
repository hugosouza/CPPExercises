#include <iostream>
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>

void t(std::vector<int> x) {
  for_each(x.begin(),
           x.end(),
           [] (int i) { printf("[%u]\n", i); }
  );
}

int main() {
  std::string s("10");
  printf("[%s] [%u]\n", s.c_str(), boost::lexical_cast<int>(s));
  t({10, 20, 30});
}
