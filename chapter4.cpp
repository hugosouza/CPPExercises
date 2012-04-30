/**
 * Exercises from The C++ Programming Language Special Edition
 * Tested on Microsoft Visual Studio 11
 * <hsouza@gmail.com> Apr/2012
 */


#include <iostream>
#include <limits>
#include <vector>

#include <stdio.h>

using namespace std;

void ex4_3() {
	enum T { A, B, C, D, E, F };
	printf("%d\n", sizeof(T));
}

void ex4_5() {
	printf("max float: %f, min float: %f\n",
		   std::numeric_limits<float>::max(),
		   std::numeric_limits<float>::min()
	);
	printf("max double: %f, min double: %f\n",
		   std::numeric_limits<double>::max(),
		   std::numeric_limits<double>::min()
	);
}

struct Pair {
	std::string n;
	double v;
};

std::vector<Pair> pairs;

double& value(const string& s) {
	for (unsigned int i = 0; i < pairs.size(); i++) {
		if (!pairs[i].n.compare(s)) return pairs[i].v;
	}
	Pair p = {s, 0};
	pairs.push_back(p); 
	return pairs[pairs.size()-1].v;
}

void ch_55() {
	char p[10];
	while (std::cin >> p) value((std::string)p)++;
	for (std::vector<Pair>::const_iterator i = pairs.begin(); i != pairs.end(); i++) {
		printf("[%s] = [%.0f]\n", i->n.c_str(), i->v);
	}
}


int main(int argc, char* argv[]) {
	char a[] = "abc"
		"def";
	printf("Hello [%s]\n", a);
	ex4_5();
	ch_55();
	_sleep(100000);
}
