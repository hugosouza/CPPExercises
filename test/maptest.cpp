#include <string>
#include <map>

#include <cstdio>

int main(int argc, char** argv) {
  std::map<std::string, int> xx;
  xx["test1"] = 0;
  xx["test2"] = 2;
  printf("test1: [0x%X]\n", xx.count("test1"));
  printf("test2: [0x%X]\n", xx.count("test2"));
  printf("test2: [0x%X]\n", xx.count("null"));
}
