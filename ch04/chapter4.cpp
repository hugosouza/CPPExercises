/**
 * Exercises from The C++ Programming Language Special Edition
 * Tested on Microsoft Visual Studio 11
 * <hsouza@gmail.com> Apr/2012
 */


#include <iostream>
#include <limits>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <utility>
#include <string>

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
	char p[1000];
	while (std::cin >> p) value((std::string)p)++;
	for (std::vector<Pair>::const_iterator i = pairs.begin(); i != pairs.end(); i++) {
		printf("[%s] = [%.0f]\n", i->n.c_str(), i->v);
	}
}

void ex5_1() {
	char* a;
	int b[10];
	int (&c)[10] = b;
	string d1 = "test";
	string dd[10];
	string (*d)[10] = &dd;
	char **e = &a;
	const int f = 10;
	const int* g = &f;
}

void ex5_3() {
	typedef unsigned char uchar;
	typedef const unsigned char cuchar;
	typedef int* p2int;
	typedef char** p2p2char;
	typedef char (*p2arrayofchar)[];
	typedef int (*p2arrayofint)[7];
	typedef int* (*p2arrayofp2int)[7];
	typedef int* (arrayof8[8])[7];

	arrayof8 a;
	a[0][0] = new int(10);

	printf("-->[%d]\n", *a[0][0]);
}

map<string, int> histogram;

void record(const string s) {
	histogram[s]++;
}

class print_word_c {
public:
	print_word_c() { }
	void operator()(pair<string,int> p) { printf("[%s]: [%d]\n", p.first.c_str(), p.second); }
};

void print_word(pair<string,int> p) {
	printf("[%s] = [%d]\n", p.first.c_str(), p.second);
}

void ex5_11() {
	istream_iterator<string> ii(cin);
	istream_iterator<string> eos;
	for_each(ii, eos, record);
	for_each(histogram.begin(), histogram.end(), print_word_c() );
}

void ex5_12() {
	//
}

void test01() {
	/*char *a = "1234567890";
	char *b = "abcedfg";
	char *c = b;*/
	//*a++ = *a++;
	//*a++ = *a;
	/*printf("[0x%x] [0x%x] [0x%x]\n", a, b);
	printf("[%c] [%c]\n", *a, *b);*/
	// a[0] = 'z';
	int zz;
	int *yy = &zz;
	*yy = 10;
	char b[] = "123456";
	char *ww = b;
	*ww = 'a';
	cout << ww << "\n";
}

void test02(int a) {
	int *q = new int[20];
	q[19] = 10;
	cout << a << "\n";
	delete[] q;
}

typedef void (*x)(int);

void test03(x f) {
	int *uuu = static_cast<int*>(malloc(sizeof(int)));
	*uuu = 20;
	cout << "*uuu = " << *uuu << "\n";
	delete(uuu);
	(*f)(30);
}