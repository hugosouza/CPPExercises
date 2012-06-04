#include <iostream>
#include <tuple>

#include <cstdio>

int main(int argc, char **argv) {
  auto t = std::make_tuple<std::string, int, int>("test 1", 10, 20);
  printf("[%s] [%d] [%d]\n", std::get<0>(t).c_str(), std::get<1>(t), std::get<2>(t));
}

