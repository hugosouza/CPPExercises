#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

#include <ctime>

#include <boost/lexical_cast.hpp>

#define MAX_TABLE_SIZE 100000

class Table {
  struct _keyvalue {
    std::string key;
    std::string value;
    _keyvalue* next;
  };
  typedef _keyvalue* keyvalue_structP;
  keyvalue_structP _table[MAX_TABLE_SIZE];

  int16_t hash(std::string);

public:
  Table();
  ~Table();

  keyvalue_structP addNode(std::string, std::string);
  keyvalue_structP getNode(std::string);

  std::vector<std::string> keys();
};

Table::Table() {
  for(int i = 0; i < MAX_TABLE_SIZE; i++) {
    _table[i] = nullptr;
  }
}

Table::~Table() {}

int16_t Table::hash(std::string s) {
  uint16_t index = 0;
  for_each(s.begin(),
           s.end(),
           [&index](char c) {index += c;});
  index %= MAX_TABLE_SIZE;
  return index;
}

Table::keyvalue_structP Table::addNode(std::string k, std::string v) {
  uint16_t index = hash(k);
  Table::keyvalue_structP t;
  t = _table[index];
  if (t == nullptr) {
    t = new _keyvalue;
    *t = {k, v, nullptr};
    _table[index] = t;
    return t;
  }

  Table::keyvalue_structP last;
  for(Table::keyvalue_structP i = t; i != nullptr; i = i->next) {
    last = i;
    //printf(" --> k[%s] [0x%0lx] next [0x%0lx]\n", i->key.c_str(), (long unsigned int)i, (long unsigned int)i->next);
    if (i->key == k) {
      i->value = v;
      return i;
    }
  }
  t = new _keyvalue;
  *t = {k, v, nullptr};
  return last->next = t;
}

Table::keyvalue_structP Table::getNode(std::string k) {
  uint16_t index = hash(k);
  for(Table::keyvalue_structP i = _table[index]; i != nullptr; i = i->next) {
    if (i->key == k) return i;
  }
  return nullptr;
}

std::vector<std::string> Table::keys() {
  std::vector<std::string> list;
  for(int i = 0; i < MAX_TABLE_SIZE; i++) {
    for(Table::keyvalue_structP t = _table[i]; t != nullptr; t = t->next) {
      list.push_back(t->key);
    }
  }
  return std::move(list);
}

std::string charList("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890");
uint8_t charListSize = charList.size();
uint8_t randChar() {
  return charList[rand() % charListSize];
}

std::string genRandStr() {
  std::string s("");
  for(int i = 0; i < 10; i++) {
    s += randChar();
  }
  return std::move(s);
}


int main(int argc, char** argv) {
  srand(time(NULL));
  Table test;
  test.addNode("key 1", "value 1");
  test.addNode("key 2", "value 2");
  test.addNode("key 3", "value 3");
  test.addNode("key 3", "value 3");
  test.addNode("key 3", "value 3");
  test.addNode("key 3", "value 3");
  test.addNode("key 3", "value 3");
  test.addNode("key 3", "value 9999");
  test.addNode(genRandStr(), genRandStr());

  std::cout << "test.get(\"key 1\"): " << test.getNode("key 1")->value << "\n";
  std::cout << "test.get(\"key 2\"): " << test.getNode("key 2")->value << "\n";
  std::cout << "test.get(\"key 3\"): " << test.getNode("key 3")->value << "\n";

  int count = 10;

  if (argc >= 2) {
    count = boost::lexical_cast<int>(argv[1]);
  }

  printf("count = %d\n", count);

  std::vector<std::pair<std::string, std::string>> testlist;
  for (int i = 0; i < count; i++) {
    printf("%10d/%10d\r", i++, count);
    // std::string a1 = genRandStr();
    // std::string a2 = genRandStr();
    // testlist.push_back(std::make_pair(a1, a2));
    test.addNode(genRandStr(), genRandStr());
  }

  printf("\n\nPRINT\n\n");

  for(auto ss: test.keys()) {
     printf("->[%s]: %s\n", ss.c_str(), test.getNode(ss)->value.c_str());
  }

  // int ii = 0;
  // // for (auto ss: testlist) {
  //   //printf("%10d/%10d\r", ii++, count);
  //   if (ss.second != test.getNode(ss.first)->value) {
  //     printf("Error with key [%s]: expected [%s] got [%s]\n", ss.first.c_str(), ss.second.c_str(), test.getNode(ss.first)->value.c_str());
  //   }
  //   //printf("ss.first[%s], ss.second[%s], getNode()[%s]\n", ss.first.c_str(), ss.second.c_str(), test.getNode(ss.first)->value.c_str());
  // }
  printf("\n");

  return 0;
}
