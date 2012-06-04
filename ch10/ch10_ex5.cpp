// Histogram
#include <iostream>
#include <vector>
#include <algorithm>

class Interval {
  int64_t _min;
  int64_t _max;
  int64_t _c;
  int64_t _sum;

public:
  Interval(int64_t min = 0, int64_t max = 0) :
    _min(min), _max(max), _c(0), _sum(0) {}
  ~Interval() {}
  bool add(int64_t);
  int64_t getMin();
  int64_t getMax();
  int64_t getCount();
  int64_t getSum();
};

bool Interval::add(int64_t i) {
  if (i >= _min && i < _max) {
    _c++;
    _sum = _sum + i;
    return true;
  }
  return false;
}

int64_t Interval::getMin() { return _min; }
int64_t Interval::getMax() { return _max; }
int64_t Interval::getCount() { return _c; }
int64_t Interval::getSum() { return _sum; }

class Histogram {
  std::vector<Interval*> _list;
public:
  Histogram() {}
  ~Histogram() {}
  void addInterval(int64_t, int64_t);
  void addCount(int64_t);
  void list();
};

void Histogram::addInterval(int64_t min, int64_t max) {
  _list.push_back(new Interval(min, max));
}

void Histogram::addCount(int64_t i) {
  for (auto interval: _list) {
    if (interval->add(i)) break;
  }
}

void Histogram::list() {
  int64_t total = 0;
  for(auto i: _list) {
    printf("[%9lld-%-9lld]: %9lld (c:%lld)\n", i->getMin(), i->getMax(),
           i->getCount(), i->getSum());
    total += i->getCount();
  }
  printf("Total occurrences: %lld\n", total);
}

int main(int argc, char **argv) {
  Histogram hist;

  srand(time(0));

  hist.addInterval(0, 10);
  hist.addInterval(10, 100);
  hist.addInterval(100, 1000);

  int ii = 0;

  for(int64_t i = 0; i < 10000; i++) {
    int64_t xx = rand()%1100;
    hist.addCount(xx);
    if (xx >= 1000) ii++;
  }

  hist.list();
  printf("over 1000: %d\n", ii);

}
