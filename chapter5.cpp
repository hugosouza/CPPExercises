/**
 * Exercises from The C++ Programming Language Special Edition
 * Tested on Microsoft Visual Studio 11
 * <hsouza@gmail.com> Apr/2012
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include <stdio.h>
#include <float.h>
#include <string.h>

using namespace std;

struct complex { float re, im; };
float real(complex* p) { return p->re; }

void ex01() {
	typedef char test_char;
	test_char ch;
	int count = 1;
	char* name = "Hugo";
	complex cvar;
	typedef complex point;
	point complex_point = { 10, -1 };
	typedef const double const_double;
	const_double pi = 3.14;
	struct user;
	struct user { int i, j; };
	enum beer;
	enum beer { Carlsberg, Tuborg, Thor };
}

void ex02() {
	char* p;
	int intarray[10];
	char** p_to_array;
	char* t[3] = { "test1", "test2", "test3" };
	char* i = new char('a');
	char** j = &i;
	p_to_array = t;
	cout << "t[0] = " << p_to_array[2] << "\n";
	cout << "i = " << *i << "\n";
	cout << "j = " << **j << "\n";
	const int a = 1;
	const int* aa = new int(20);
	int* const bb = new int(10);
	cout << "aa = " << *aa << ", b = " << *bb << "\n";
}

void ex03() {
	cout << "sizeof(int): " << sizeof(int) << "\n";
	cout << "sizeof(int*): " << sizeof(int*) << "\n";
	cout << "sizeof(char): " << sizeof(char) << "\n";
	cout << "sizeof(char*): " << sizeof(char*) << "\n";
	cout << "sizeof(long): " << sizeof(long) << "\n";
	cout << "sizeof(long*): " << sizeof(long*) << "\n";
	cout << "sizeof(long long int): " << sizeof(long long int) << "\n";
	cout << "sizeof(long long int*): " << sizeof(long long int*) << "\n";
	cout << "sizeof(double): " << sizeof(double) << "\n";
	cout << "sizeof(double*): " << sizeof(double*) << "\n";
	cout << "sizeof(float): " << sizeof(float) << "\n";
	cout << "sizeof(float*): " << sizeof(float*) << "\n";
	cout << "sizeof(short): " << sizeof(short) << "\n";
	cout << "sizeof(short*): " << sizeof(short*) << "\n";
	cout << "sizeof(char): " << sizeof(char) << "\n";
	cout << "sizeof(unsigned char): " << sizeof(unsigned char) << "\n";
	enum e1 { A1, A2, A3, A4, A5 };
	cout << "sizeof(e1) " << sizeof(e1) << "\n";
}

void ex04() {
	for (char i='a'; i <='z'; i++) {
		char t[200];
		_snprintf_s(t, 200, 200, "%x", i);
		cout << "i = " << i << ", int = " << (int)i << ", hexa = 0x" << t << "\n";
	}
	for (char i='0'; i <='9'; i++) {
		cout << "i = " << i << ", int = " << (int)i << "\n";
	}
}

void ex05() {
	union test {
		long int* a;
		char* b;
	} t1;

	t1.a = 0;
	cout << "t1.b = " << t1.b << "\n";
	cout << "t1.a = " << t1.a << "\n";
}

void ex05b() {
	cout << "sizeof(bool) " << sizeof(bool) << "\n";
	cout << "sizeof(void *) " << sizeof(void *) << "\n";
}

void ex05c() {
	union test {
		void* t;
		unsigned char bit[4];
	} tt;
	tt.t = (void *)0xFF880F05;
	string bitpattern;
	
	for (int i = sizeof(tt.bit)-1; i >= 0; i--) {
		for (int j = 7; j >= 0; j--) {
			bitpattern += (tt.bit[i] & (1 << j)) ? "1" : "0";
		}
		if (i > 0) bitpattern += "-";
	}
	printf("tt.t = [0x%04x]\n", tt.t);
	cout << "pattern = " << bitpattern.c_str() << "\n";
}

string bit_pattern(unsigned char c) {
	string buff;

	for (int i = 7; i >= 0; i--) {
		buff += (c & (1<<i)) ? "1" : "0";
	}

	printf("==>[%s]\n", buff.c_str());
	return buff;
}

string bit_pattern(unsigned short c) {
	string buff;

	for (int i = 15; i >= 0; i--) {
		buff += (c & (1<<i)) ? "1" : "0";
		if (!(i%4) && i > 0) buff += "-";
	}
	return buff;
}

template<typename T> string bit_pattern(T c) {
	string buff;
	union _t {
		T t1;
		unsigned char t2[sizeof(T)];
	} tt;
	tt.t1 = c;
	for (int j = 0; j < sizeof(tt.t2); j++) {
		for (int i = 7; i >= 0; i--) {
			buff += (tt.t2[j] & (1<<i)) ? "1" : "0";
			if (i == 4) buff += "-";
		}
		if (j != sizeof(tt.t2)-1) buff += "-";
	}
	return buff;
}

void ex06() {
	union tt {
		double dd;
		unsigned short pp[4];
	} a;
	a.dd = 10000.0;

	for (int i = 0; i < 4; i++ ) {
		printf("a.pp[%d] = [%04x] [%s]\n", i, a.pp[i], bit_pattern(a.pp[i]).c_str());
	}
	unsigned short exp = (a.pp[3] & 0x7FF0) >> 4;
	exp -= 1023;
	printf("a.dd = [%.06f]\n", a.dd);
	printf("exp = %d [0x%x] [%s]\n", exp, exp, bit_pattern(exp).c_str());
	printf("a.dd = [%e]\n", a.dd);

	double mant = 1;
	for (int i = 0; i < 52; i++) {
		if (i < 4) {
			mant += (a.pp[3] & (1 << (3-i)) ? 1 : 0)*pow(2,-i);
			printf("i = [%d]: a.pp[3] pow(2,-i) = [%.09f], bit = [%d] mant = [%.09f]\n",
				i,
				pow(2,-i),
				(a.pp[3] & (1 << (3-i))) ? 1 : 0,
				mant
			);
		} else {
			int index = 3-int((12+i)/16);
			int bitpos = 15-((12+i)%16);
			mant += (a.pp[index] & (1 << bitpos)) ? 1 : 0 * pow(2,-i);
			printf("i = [%d]: a.pp[%d] pow(2,-i) = [%.09f] , bit = [%d], bit pos = [%d], mant = [%.09f]\n",
				i,
				index,
				pow(2,-i),
				(a.pp[index] & (1 << bitpos)) ? 1 : 0,
				bitpos,
				mant
			);
		}
	}
    printf("t = [%.06f]\n", pow(2, exp));
	printf("mant = [%.010f]\n", mant);
	printf("original number = [%.06f]\n", pow(2, exp)*mant);
}

void ex07() {
	char char_max = 0x7F;
	char char_min = 0x80;
	unsigned uchar_max = 0xFF, uchar_min = 0;

	printf("char (%d)\n  max: %d (0x%X)\n  min: %d (0x%X)\n",
		sizeof(char),
		char_max,
		char_max,
		char_min,
		char_min
	);
	printf("unsigned char (%d)\n  max: %d (0x%X)\n  min: %d (0x%X)\n",
		sizeof(unsigned char),
		uchar_max,
		uchar_max,
		uchar_min,
		uchar_min
	);

	short short_min = 0x8000, short_max = 0x7FFF;
	unsigned ushort_min = 0, ushort_max = 0xFFFF;
	printf("short (%d)\n  max: %d (0x%X)\n  min: %d (0x%X)\n",
		sizeof(short),
		short_max,
		short_max,
		short_min,
		short_min
	);
	printf("unsigned short (%d)\n  max: %d (0x%X)\n  min: %d (0x%X)\n",
		sizeof(unsigned short),
		ushort_max,
		ushort_max,
		ushort_min,
		ushort_min
	);

	long long_min = 0x80000000, long_max = 0x7FFFFFFF;
	printf("long (%d)\n  max: %d (0x%X)\n  min: %d (0x%X)\n",
		sizeof(long),
		long_max,
		long_max,
		long_min,
		long_min
	);

	float float_min = -1 * (2-pow(2,-23))*(pow(2,127));
	float float_max = pow(2,127);
	printf("float (%d)\n  max: %f (0x%X)\n  min: %09f (0x%X)\n",
		sizeof(float),
		float_max,
		float_max,
		float_min,
		float_min
	);

	double double_min = DBL_MIN;
	double double_max = DBL_MAX;
	printf("double (%d)\n  max: %f (0x%X)\n  min: %09f (0x%X)\n",
		sizeof(double),
		double_max,
		double_max,
		double_min,
		double_min
	);
}

void ex59_1() {
	char* pointToChar;
	int arrayOf10Ints[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int (&refToArrayOfInts)[10] = arrayOf10Ints;
	char* pointerToArrayOfChars[3] = { "test1", "test2", "test3" };
	char* pointerToArrayOfChars2[3];
	pointerToArrayOfChars2[1] = "abc";
	pointerToArrayOfChars[1] = "1123123";
	pointerToArrayOfChars[1] = "zzzzz";
	cout << "pointerToArrayOfChars[1] : " << pointerToArrayOfChars[1] << "\n";
	cout << "pointerToArrayOfChars2[1] : " << pointerToArrayOfChars2[1] << "\n";

	char** p2p2char;
	const int const_int = 0xFF;
	int const *p2constint = &const_int;
	const int *constp2int = &const_int;

	cout << "p2constint = " << *p2constint << "\n";
	cout << "constp2int = " << *constp2int << "\n";

	int* p2int = (int *)0x1;

	int* arrayofp2int[7];
	int arrayof7ints[7] = { 10, 20, 30, 40, 50, 60, 70 };
	int (*p2arrayof7int)[7] = &arrayof7ints;

	cout << "p2arrayof7int[1] = " << p2arrayof7int[1] << "\n";
}

void ex59_3() {
	typedef unsigned char uchar;
	typedef const unsigned char constuchar;
	typedef int * p2int;
	typedef char ** p2p2char;
	typedef char (*p2arrayofchars)[10];
	typedef int *(*p2arrayofp2int)[7];
	typedef int *(p2arrayof8p2int[8])[7];

	char p2char[10] = "abc";
	p2arrayofchars pp = &p2char;
	p2arrayof8p2int z;

	z[0][0] = new int(1000);

	p2arrayofp2int a;
	a = (p2arrayofp2int) malloc(sizeof(p2arrayofp2int));
	printf("a[1] = [0x%x]\n", a[1]);
	(*a)[1] = new int(99);
	printf("a[1] = [%d][0x%x]\n", *(*a)[1], *((*a)[1]));

	cout << "z[0][0] = " << *(z[0][0]) << "\n";

	//cout << "p2arrayOfpOfInt[1] = " << p2arrayOfpOfInt[1] << "\n";
}

void ex59_4(int* a, int* b) {
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

void ex59_4(int& a, int& b) {
	int i = a;
	a = b;
	b = i;
}

void ex59_4_test() {
	int i = 10, j = 20;
	printf("i = %d, j = %d\n", i, j);
	ex59_4(i, j);
	printf("i = %d, j = %d\n", i, j);
}

void ex59_5() {
	char str[] = "a short string";
	char *p = str;
	printf("str[] = [%s] [%d]\n", str, sizeof(str));
	printf("p = [%s]\n", p);
}

void f(char a) { printf("f() [%d]\n", a); }
void g(char& a) { printf("g() [%d]\n", a); }
void h(const char& a) { printf("h() [%d]\n", a); }

void ex59_6() {
	char c = 'b';
	unsigned char uc = 'c';
	signed char sc = 'd';

	//f('a'); g('a'); h('a');
	//f(49); g(49); h(49);
	//f(3300); g(3300); h(3300);
	//f(c); g(c); h(c);
	//f(uc); g(uc); h(uc);
	//f(sc); g(sc); h(sc);
}

void ex59_7() {
	const char* months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	for (int i = 0; i < 12; i++) {
		printf("[%s] - [%d]\n", months[i], days[i]);
	}

	typedef struct mon_days {
		char* mon;
		int days;
	};

	mon_days l[] = {
		{ "Jan", 31 },
		{ "Feb", 28 },
		{ "Mar", 31 },
		{ "Apr", 30 },
		{ "May", 31 }
	};

	printf("---\nsizeof(l) = %d rec size = %d\n", sizeof(l), sizeof(mon_days));

	mon_days* ll = l;

	for (int i = 0; i < sizeof(l)/sizeof(mon_days); i++, ll++) {
		printf("[%s] - [%d]\n", ll->mon, ll->days);
	}
}

void printArrayOfStr(string a[], int size) {
	for(int i = 0; i < size; i++) {
		printf("-->[%s]\n", a[i].c_str());
	}
}

void ex59_10() {
	string arrayOfStr[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun" };

	printf("sizeof(arrayOfStr) = [%d]\n", sizeof(arrayOfStr));

	for(int i = 0; i < sizeof(arrayOfStr)/sizeof(string); i++) {
		printf("[%s]\n", arrayOfStr[i].c_str());
	}

	printArrayOfStr(arrayOfStr, sizeof(arrayOfStr)/sizeof(string));
}

void ex59_11() {
	vector<string> t;
	map<string, int> printed;

	while (1) {
		char a[255];
		cin.getline(a, 255, '\n');
		if (strcmp(a, "quit") == 0) break;
		t.push_back((string)a);
	}

	for(vector<string>::size_type i = 0; i < t.size(); i++) {
		if (printed[t[i]]) {
			continue;
		}
		printf("[%5d]: [%s]\n", i, t[i].c_str());
		printed[t[i]] = 1;
	}
	int i = getchar();
	
	sort(t.begin(), t.end());

	for(vector<string>::iterator i = t.begin(); i != t.end(); i++) {
		printf("==[%s]==\n", i->c_str());
	}
}

int countStr(string s, string t) {
	string::size_type i = 0;
	int count = 0;
	while (1) {
		string::size_type j = s.find(t, i);
		if (j == string::npos) {
			break;
		}
		count++;
		i = j+1;
	}
	printf("countStr(): found [%s] in [%s] [%d] times\n", t.c_str(), s.c_str(), count);
	return 0;
}

int countStrFromChar(const char *s, const char *t) {
	int i = 0, count = 0;
	char *origS = (char *)s;
	while (1) {
		char *tt = strstr(origS, t);
		if (!tt) {
			break;
		}
		origS = tt+1;
		count++;
	}
	printf("countStrFromChar(): found [%s] in [%s] [%d] times\n", t, s, count);
	return count;
}

void ex59_12() {
	string a = "ab def abc 123 abcc 123 123 123 uquiowquio", b = "123";
	const char *x = "ajklaskljasjklajk a ajklasjklasjklas asjkl asjklas";
	const char *y = "aj";
	countStr(a, b);
	countStrFromChar(x, y);
}

int main(int argc, char* argv[]) {
	int i;
	ex59_12();
	i = getchar();

	double a = 100.0;
	printf("-->[0x%x -- %s]\n", 0xDEADBEEF, bit_pattern(0xDEADBEEF).c_str());
	printf("-->[%s]\n", bit_pattern(a).c_str());
	_sleep(20000);
}