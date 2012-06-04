#include <iostream>
#include <string>

const char* t() {
  std::string s = "test string 1";
  return s.c_str();
}

const char* t2() {
  std::string s = "test string 2";
  return s.c_str();
}

const char* t3() {
  std::string s = "test string 3";
  return s.c_str();
}

int main() {
  for (int i = 0; i < 10000; i++) {
    printf("[%d] [%s]-[%s]-[%s]\n", i, t(), t2(), t3());
  }
}
