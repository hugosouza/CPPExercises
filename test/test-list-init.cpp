#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <algorithm>
#include <cstdio>

void a1(std::string s) {
    printf("-->[%s]\n", s.c_str());
}

int main(int argc, char **argv) {
    std::map<const std::string, int> test_vector {
        { "test 1", 10 },
        { "test 2", 30 } 
    };

    for_each(test_vector.begin(),
             test_vector.end(),
             [](std::pair<const std::string, int> a) { printf("[%s]: %d\n", a.first.c_str(), a.second); });

    int a = 10;
    int b;
    std::string c("abc");
    std::string d;

    b = std::move(a);
    d = std::move(c);

    printf("a: %d, b: %d\n", a, b);
    printf("c: %s, d: %s\n", c.c_str(), d.c_str());
    a1(std::move(c));
    a1(std::move(d));
    printf("c: %s, d: %s\n", c.c_str(), d.c_str());


    return 1;
}
