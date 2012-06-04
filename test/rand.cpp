#include <iostream>

#include <cstdlib>
#include <ctime>

int main() {
  std::srand(time(0));
  printf("%d\n", rand()%10);
}
