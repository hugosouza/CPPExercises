#include <iostream>
#include <string>

#include <cstdlib>
#include <ctime>
#include <cstdint>
#include <cstring>

#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

#define LIST_SIZE_FACTOR  10

class IntSet {
  int64_t* _list;
  uint32_t _pos;
  uint32_t _size;

  void move(uint32_t);
  void resize(uint8_t);
  uint32_t findClose(int64_t);
public:
  IntSet();
  ~IntSet();

  typedef boost::shared_ptr<IntSet> IntSetPtr;

  void add(int64_t);
  int64_t get(uint32_t);
  void list();
  inline uint32_t getSize() { return _pos; }
  bool contains(int64_t);
  static IntSetPtr join(IntSetPtr&, IntSetPtr&);
  static IntSetPtr intersect(IntSetPtr&, IntSetPtr&);
  static IntSetPtr diff(IntSetPtr&, IntSetPtr&);

  class Ex {
  public:
    std::string _err;
    Ex(std::string e) : _err(e) {};
  };
};

IntSet::IntSet() : _pos(0), _size(LIST_SIZE_FACTOR) {
  _list = new int64_t[_size];
}

IntSet::~IntSet() {
  delete[] _list;
}

void IntSet::add(int64_t i) {
  if (_pos == 0) {
    _list[_pos++] = i;
    return;
  }

  if (_pos == _size) {
    resize(2);
  }

  uint32_t p = findClose(i);
  if (i == _list[p]) return;
  move(p);
  if (i > _list[p]) {
    _list[p+1] = i;
  } else {
    _list[p] = i;
  }
  _pos++;
}

void IntSet::resize(uint8_t factor) {
  printf("resizing from %d to %d\n", _size, _size*factor);
  int64_t* temp = new int64_t[_size*factor];
  memcpy(temp, _list, sizeof(int64_t)*_size);
  delete[] _list;
  _list = temp;
  _size *= factor;
}

void IntSet::move(uint32_t p) {
  uint32_t i = _pos;
  do {
    _list[i] = _list[i-1];
    i--;
  } while(i>p);
}

void IntSet::list() {
  for (uint32_t i = 0; i < _pos; i++) {
    printf("%7lli ", _list[i]);
    if (!((i+1)%10)) printf("\n");
  }
  printf("\n");
}

int64_t IntSet::get(uint32_t pos) {
  if (pos >= _size) {
    throw new IntSet::Ex("IntSet::get(pos): pos out of bounds");
  }
  return _list[pos];
}

uint32_t IntSet::findClose(int64_t n) {
  uint32_t pivot, begin, end;
  begin = 0;
  end = _pos-1;

  if (_pos == 0) return 0;

  while (1) {
    if (end-begin == 0) {
      return begin;
    }
    pivot = begin+((end-begin)/2);
    if (n ==_list[pivot]) {
      return pivot;
    } else if (n > _list[pivot]) {
      begin = pivot+1;
    } else {
      end = pivot;
    }
  }
}

bool IntSet::contains(int64_t n) {
  uint32_t i = findClose(n);
  return _list[i] == n ? true : false;
}

IntSet::IntSetPtr IntSet::join(IntSetPtr& set1, IntSetPtr& set2) {
  IntSetPtr t(new IntSet);
  for (uint32_t i = 0; i < set1->getSize(); i++) {
    t->add(set1->get(i));
  }
  for (uint32_t i = 0; i < set2->getSize(); i++) {
    t->add(set2->get(i));
  }
  return t;
}

IntSet::IntSetPtr IntSet::intersect(IntSetPtr& set1, IntSetPtr& set2) {
  IntSetPtr t(new IntSet);

  for (uint32_t i = 0; i < set1->getSize(); i++) {
    if (set2->contains(set1->get(i))) {
      t->add(set1->get(i));
    }
  }
  return t;
}

IntSet::IntSetPtr IntSet::diff(IntSetPtr& set1, IntSetPtr& set2) {
  IntSetPtr t(new IntSet);

  for (uint32_t i = 0; i < set1->getSize(); i++) {
    if (!set2->contains(set1->get(i))) {
      t->add(set1->get(i));
    }
  }
  return t;
}

int main(int argc, char** argv) {
  IntSet::IntSetPtr l(new IntSet), l2(new IntSet);
  IntSet::IntSetPtr l3, l4, l5;
  uint32_t iter = 100;
  uint32_t maxNumber = 100;

  if (argc > 1) {
    iter = boost::lexical_cast<uint32_t>(argv[1]);
  }
  if (argc > 2) {
    maxNumber = boost::lexical_cast<uint32_t>(argv[2]);
  }

  std::srand(time(0));
  printf("%d rand(0-%d) numbers\n", iter, maxNumber);
  for (uint32_t i = 0; i < iter; i++) {
    l->add(rand()%maxNumber);
    l2->add(rand()%maxNumber);
  }
  printf("=== l.list() ===\n");
  l->list();
  printf("=== l2.list() ===\n");
  l2->list();

  printf("calling join\n");
  l3 = IntSet::join(l, l2);
  printf("=== l3.list() ===\n");
  l3->list();
  printf("calling intersect\n");
  l4 = IntSet::intersect(l, l2);
  printf("=== l4.list() ===\n");
  l4->list();
  printf("calling diff\n");
  l5 = IntSet::diff(l, l2);
  printf("=== l5.list() ===\n");
  l5->list();
}
