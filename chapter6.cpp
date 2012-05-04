/**
 * Exercises from The C++ Programming Language Special Edition
 * Tested on Microsoft Visual Studio 11
 * <hsouza@gmail.com> May/2012
 */

#include <iostream>
#include <limits>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <utility>
#include <string>
#include <cstring>
#include <sstream>

#include <stdio.h>
#include <string.h>

using namespace std;

void ex6_01() {
	int i = 0;
	int max_length = 10;
	char input_line[] = "abcdef//ghi?jk?/*lmnop?qrstuv*/xwyz?";
	char *p = input_line;
	int len = sizeof(input_line);
	int quest_count = 0;

	while (*p) {
		if (*p++ == '?') quest_count++;
	}

	cout << "quest_count: " << quest_count << "\n";
}

struct each_word {
	double sum;
	int count;
};

typedef pair<string, each_word> pair_string_each_word;
typedef map<string, each_word> map_string_each_word;

each_word totals;

void print_each_word(pair_string_each_word p) {
	printf("[%s]: mean(%.02f/%i) = %.02f\n",
		p.first.c_str(),
		p.second.sum,
		p.second.count,
		p.second.sum/p.second.count
	);
	totals.count += p.second.count;
	totals.sum += p.second.sum;
}

void print_double(double d) {
	printf("-->[%.06f]\n", d);
}

void ex6_03() {
	char b = 0;
	string curr_key;
	map_string_each_word table;
	vector<double> val_list;
	int err = 0;

	while (1) {
		cin >> b;
		if (!b) break;
		if (isalpha(b)) {
			cin.putback(b);
			string key;
			cin>>key;
			if (curr_key.length() > 0) curr_key += " ";
			curr_key += key;
		} else if (isdigit(b)) {
			if (!curr_key.size()) {
				cerr << "Empty key\n";
				err = 1;
				break;
			}
			cin.putback(b);
			double value; 
			cin>>value;
			each_word& p = table[curr_key];
			if (p.count) {
				p.sum += value;
				p.count++;
			} else {
				p.sum = value;
				p.count = 1;
			}
			val_list.push_back(value);
			b = 0;
			curr_key = "";
		} else {
			cerr << "Invalid token\n";
			err = 1;
			break;
		}
	}

	totals.count = 0;
	totals.sum = 0;
	for_each(table.begin(), table.end(), print_each_word);
	printf("total: %.06f count: %d\n", totals.sum, totals.count);

	sort(val_list.begin(), val_list.end());
	for_each(val_list.begin(), val_list.end(), print_double);
	int medianIndex = static_cast<int>(val_list.size()/2);
	double median;
	if (medianIndex % 2) {
		median = val_list[medianIndex];
	} else {
		median = (val_list[medianIndex]+val_list[medianIndex-1])/2;
	}
	printf("have %d values, median = %.08f\n",
		val_list.size(),
		median
	);
}

void ex6_04() {
	printf("&:\n");
	printf("  0 & 0 = [0x%x]\n", 0 & 0);
	printf("  1 & 0 = [0x%x]\n", 1 & 0);
	printf("  0 & 1 = [0x%x]\n", 0 & 1);
	printf("  1 & 1 = [0x%x]\n", 1 & 1);
	printf("|:\n");
	printf("  0 | 0 = [0x%x]\n", 0 | 0);
	printf("  1 | 0 = [0x%x]\n", 1 | 0);
	printf("  0 | 1 = [0x%x]\n", 0 | 1);
	printf("  1 | 1 = [0x%x]\n", 1 | 1);
	printf("^:\n");
	printf("  0 ^ 0 = [0x%x]\n", 0 ^ 0);
	printf("  1 ^ 0 = [0x%x]\n", 1 ^ 0);
	printf("  0 ^ 1 = [0x%x]\n", 0 ^ 1);
	printf("  1 ^ 1 = [0x%x]\n", 1 ^ 1);
	printf("~:\n");
	printf("  ~0 = [0x%x]\n", ~0);
	printf("  ~0xFFFFFFFF = [0x%x]\n", ~0xFFFFFFFF);
	printf(">> <<:\n");
	printf("  1<<1 = [0x%08x]\n", 1<<1);
	printf("  1<<4 = [0x%08x]\n", 1<<4);
}

void ex6_09() {
	char a[] = "abcdefgh";
	char *p = a;

	printf("1) p = [0x%08x]\n", p);
	printf("2) *p++ = [%c] [0x%08x]\n", *(p++), p);
	printf("3) *p [%c] [0x%08x]\n", *p, p);
	/*p++;
	printf("*p [%c] [0x%08x]\n", *p, p);
	p++;
	printf("*p [%c] [0x%08x]\n", *p, p);*/
	printf("4) *--p = [%c] [0x%08x]\n", --(*p), p);
	printf("5) *p [%c] [0x%08x]\n", *p, p);

	int yy = 0;
	printf("--yy++ = [%d]\n", (++yy)--);
	printf("yy = [%d]\n", yy);

	struct xx {
		int *m;
	};
	xx pp;
	pp.m = new int();
	*pp.m = 10;
	cout << "*pp.m = " << *(pp.m) << "\n";
}

int ex6_10_strlen(const char *s) {
	int i = 0;
	while (*s++) i++;
	return i;
}

char* ex6_10_strcpy(char *d, const char *s) {
	while(*d++ = *s++) {}
	return d;
}

int ex6_10_strcmp(char *a, char *b) {
	int r = 0;

	if (!*a && *b) return -1;
	else if (*a && !*b) return 1;

	while (*a && *b) {
		if (*a == *b) {
			a++, b++;
			continue;
		}
		(*a > *b) ? r++ : r--;
		break;
	}
	return r;
}

void ex6_10() {
	string tt = "abcdef";
	char a[] = "aaaa1aa2aaa3aa";
	char b[sizeof(a)+1];
	cout << "ex6_10_strlen('test123'): " << ex6_10_strlen("test123") << "\n";
	printf("ex6_10_strlen(%s): %d\n", tt.c_str(), ex6_10_strlen(tt.c_str()));
	ex6_10_strcpy(b, a);
	printf("b = [%s]\n", b);
	printf("strcmp('abcdef', 'abcdef'): [%d]\n", ex6_10_strcmp("abcdef", "abcdef"));
	printf("strcmp('abcdeF', 'abcdef'): [%d]\n", ex6_10_strcmp("abcdeF", "abcdef"));
	printf("strcmp('abcdef', 'abcdeF'): [%d]\n", ex6_10_strcmp("abcdef", "abcdeF"));
	printf("strcmp('', 'abcdeF'): [%d]\n", ex6_10_strcmp("", "abcdeF"));
	printf("strcmp('abcdef', 'abcdef'): [%d]\n", strcmp("abcdef", "abcdef"));
	printf("strcmp('abcdeF', 'abcdef'): [%d]\n", strcmp("abcdeF", "abcdef"));
	printf("strcmp('abcdef', 'abcdeF'): [%d]\n", strcmp("abcdef", "abcdeF"));
	printf("strcmp('', 'abcdeF'): [%d]\n", strcmp("", "abcdeF"));
}

void ex6_11(int a, int b) {
	//if (a = 3) { }
	//if (a&077 = 0) { }
	//a := b+1;
}

void t1() {
	char b;
	cout << ":: ";
	cin >> b;
	cout << "[" << b << "]\n";
}

char* my_str_cat(const char *a, const char *b) {
	char *d = new char(sizeof(*a)+sizeof(*b)+1);
	char *e = d;

	while (*e++ = *a++) {}
	e--;
	while (*e++ = *b++) {}
	return d;
}

void ex6_13() {
	char t1[] = "abcdef";
	char t2[] = "123456";
	char *t3 = my_str_cat(t1, t2);

	cout << "*t3 = " << t3 << "\n";
}

char *rev(char *a) {
	char t;
	int i = 0, j = strlen(a)-1;

	printf("[%s] i[%d] j[%d]\n", a, i, j);

	if (j <= 0) return a;

	do {
		t = a[i];
		a[i] = a[j];
		a[j] = t;
		i++; j--;
	} while (abs(i-j) > 1);
	printf("[%s] i[%d] j[%d]\n", a, i, j);

	return a;
}

void ex6_14() {
	char a[] = "123456";
	printf("%s\n", rev(a));
}

double my_atoi(const char *a) {
	istream *iss = new istringstream(a);
	double i;
	*iss >> i;
	cout << "int = " << i << ", char = " << a << "\n";
	printf("[0x%x]\n", i + 1);
	return i;
}

int my_atoi_hex(const char *s) {
	unsigned int i = 0;
	int size = strlen(s)-1;
	for (int j = size; j > 1; j--) {
		unsigned char z;
		if (s[j] >= '0' && s[j] < '9')
			z = s[j] - 48;
		else if (s[j] >= 'a' && s[j] <= 'f')
			z = s[j] - 87;
		else if (s[j] >= 'A' && s[j] <= 'F')
			z = s[j] - 55;

		i |= (z << (size-j)*4);
	}

	printf("[%s] = [%x] = [%d]\n", s, i, i);
	return i;
}

void ex6_16() {
	//char a[] = "0x10";
	//cout << "a[] = " << a << " my_atoi(a) = " << my_atoi(a) << "\n";
	//printf("[888]: %d\n", my_atoi("0x888"));
	cout << my_atoi_hex("0xF0") << "\n";
	cout << my_atoi_hex("0xFFF0") << "\n";
	cout << my_atoi_hex("0xAFFF0") << "\n";
}

void ex6_22() {
	char buff[2000];
	int /* TE"t"ST */ in_str = 0, in_comment = 0;
	char a[] = "\"\'";

	while (!cin.eof() && cin.getline(buff, 2000, '\n')) {
		//cout << "[" << buff << "]\n";
		char *p = buff;
		char prev = 0;
		int blank = 1;
		while (*p) {
			//cout << "->" << *p << "<-\n";
			if (in_comment && *p == '*' && *(p+1) && *(p+1) == '/') {
				//cout << "end multi-line comment detected\n";
				in_comment = 0;
				p += 2;
				continue;
			}  else if (in_comment) {
				//cout << "in_comment, proceeding\n";
				prev = *p++;
				continue;
			} else if (*p == '"' || *p == '\'' ) {
				//cout << "found \" or \'\n";
				if (!in_comment && in_str && prev != '\\') in_str = 0;
				else if (!in_comment && !in_str && prev != '\\') in_str = 1;
			} else if (!in_str && *p == '/' && *(p+1) && *(p+1) == '*') {
				//cout << "start multi-line comment detected\n";
				in_comment = 1;
				prev = *p;
				p += 2;
				continue;
			} else if (!in_str && *p == '/' && *(p+1) && *(p+1) == '/') {
				//cout << "comment // found, ignoring rest of the line\n";
				break;
			}
			//cout << "[[" << *p << "]]\n";
			cout << *p;
			p++;
			blank = 0;
		}
		if (!blank) cout << "\n";
	}
}

int main() {
	ex6_22();
	_sleep(100000);
}