#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <utility>
#include <algorithm>

#include <boost/regex.hpp>

#include <ctime>
#include <cstdint>

class Date {
  uint16_t _d, _m, _y;
  static Date default_date;
  bool isLeapYear(int);
  uint16_t string2int(std::string);
  bool _valid;

public:
  static std::vector<int> daysPerMonth;

  Date(uint16_t, uint16_t, uint16_t);
  Date(std::string);
  ~Date();

  void addYear(uint16_t n);
  void addMonth(uint16_t n);
  void addDay(uint16_t n);

  inline bool isValidDate() { return _valid; };
  bool validate();

  std::string getDateStr();

  static void setDefault(uint16_t, uint16_t, uint16_t);

  class Ex {
  public:
    const char *m;
    Ex(const char *p) : m(p) {}
  };
};

Date::Date(uint16_t d = 0, uint16_t m = 0, uint16_t y = 0) {
  if (!default_date._d && !default_date._m && !default_date._y &&
      !d && !m && !y) {
    std::time_t now = std::time(NULL);
    std::tm* t = std::localtime(&now);
    _valid = true;
    _d = default_date._d = t->tm_mday;
    _m = default_date._m = t->tm_mon+1;
    _y = default_date._y = t->tm_year+1900;
    return;
  }

  _d = d ? d : default_date._d;
  _m = m ? m : default_date._m;
  _y = y ? y : default_date._y;
  validate();
}

Date::Date(std::string d) {
  boost::regex dateRE(R"(^\s*(\d{1,2})\s*/\s*(\d{1,2})\s*/\s*(\d{1,4})\s*$)");
  boost::cmatch results;

  if (!boost::regex_match(d.c_str(), results, dateRE)) {
    throw new Date::Ex("invalid date string format");
  }

  _d = string2int(results[1].str());
  _m = string2int(results[2].str());
  _y = string2int(results[3].str());
  std::cout << "Date::Date(string) _d=" << _d
            << " _m=" << _m
            << " _y=" << _y << "\n";
  validate();
}

Date::~Date() {
  std::cout << "implement Date::~Date()\n";
}

uint16_t Date::string2int(std::string d) {
  std::istringstream iss(d);
  uint16_t t;
  iss >> t;
  return t;
}

bool Date::validate() {
  std::string errmsg;
  _valid = true;
  if (_y == 0) {
    _valid = false;
    throw new Date::Ex("invalid year");
  }

  if (_m < 1 || _m > 12){
    _valid = false;
    throw new Date::Ex("invalid month");
  }

  int monthDays = Date::daysPerMonth[_m-1];
  if (_d <= 0 || _d > monthDays) {
    if (_d != 29 || _m != 2 || !isLeapYear(_y)) {
      _valid = false;
      throw new Date::Ex("invalid day");
    }
  }

  if (!_valid) throw new Date::Ex(errmsg.c_str());
  return _valid;
}

inline void Date::addYear(uint16_t n) {
  _y += n;
  validate();
}

inline void Date::addMonth(uint16_t n) {
  uint16_t years, months;
  years = (uint16_t)n/12;
  months = (uint16_t)n%12;
  _m += months;
  if (_m > 12) {
    _m -= 12;
    years++;
  }
  std::cout << "addMonth getDateStr(): " << getDateStr() << "\n";
  if (years) addYear(years);
  validate();
}

inline void Date::addDay(uint16_t n) {
  _d += n;
}

void Date::setDefault(uint16_t d, uint16_t m, uint16_t y) {
  Date::default_date = Date(d, m, y);
}

std::string Date::getDateStr() {
  std::stringstream ss;
  ss << _d << "/" << _m << "/" << _y;
  return (ss.str());
}

bool Date::isLeapYear(int y) {
    if (!(y % 4)) return true;
    if (!(y % 400)) return false;
    if (!(y % 100)) return true;
    return false;
}

std::vector<int> Date::daysPerMonth {
  31, 28, 31, 30,
  31, 30, 31, 31,
  30, 31, 30, 31
};

Date Date::default_date(0, 0, 0);

int main(int argc, char** argv) {
  for_each(Date::daysPerMonth.begin(),
           Date::daysPerMonth.end(),
           [] (int a) { printf("days = %d\n", a);});

  Date t,t1,t2,t3;
  std::cout << "Instanciating t3\n";
  try {
    std::cout << "t3(\" 20/ 12/ 2012\")\n";
    t3 = Date(" 20/ 12/ 2012");
  } catch (Date::Ex *de) {
    printf("t: error during date definition: %s\n", de->m);
  }
  std::cout << "Instanciating t\n";
  try {
    std::cout << "t3(-1, 1, 0)\n";
    t = Date(-1, 1, 0);
  } catch (Date::Ex *de) {
    printf("t: error during date definition: %s\n", de->m);
  }
  std::cout << "Instanciating t1\n";
  try {
    std::cout << "t1(29, 2, 2012)\n";
    t1 = Date(29, 2, 2012);
  } catch (Date::Ex *de) {
    printf("t: error during date definition: %s\n", de->m);
  }
  std::cout << "Instanciating t2\n";
  try {
    std::cout << "t2(32, 3, 2012)\n";
    t2 = Date(32, 3, 2012);
  } catch (Date::Ex *de) {
    printf("t1: error during date definition: %s\n", de->m);
  }

  std::cout << "t.getDateStr(): " << t.getDateStr() << "\n";
  std::cout << "t1.getDateStr(): " << t1.getDateStr() << "\n";
  std::cout << "t2.getDateStr(): " << t2.getDateStr() << "\n";
  std::cout << "t3.getDateStr(): " << t3.getDateStr() << "\n";

  std::cout << "\n======== TEST Date(string) ==========\n\n";
  std::vector<std::string> testDateList{
    "10/20/2012",
    "29/2/2011",
    " 1 / 1 / 1204 ",
    "error date",
    "a/ 1/2012"
  };
  for_each(testDateList.begin(),
           testDateList.end(),
           [] (std::string s) {
             printf("callind Date(%s)\n", s.c_str());
             try {
               Date temp(s);
             } catch (Date::Ex *de) {
               printf("error during date creation: %s\n", de->m);
             }
             std::cout << "\n";
           }
  ); // for_each

  std::cout << "\n======== TEST Date(int, int, int) ==========\n\n";
  struct testDate { uint16_t d, m, y; };
  std::vector<testDate> testDateListStruct {
    { 1, 2, 3 },
    { 29, 2, 4 },
    { 31, 12, 1900 },
    { 32, 7, 2012 },
  };
  for_each(testDateListStruct.begin(),
           testDateListStruct.end(),
           [] (testDate d) {
             printf("calling Date(%u, %u, %u)\n", d.d, d.m, d.y);
             try {
               Date temp(d.d, d.m, d.y);
             } catch (Date::Ex *de) {
               printf("error during date creation: %s\n", de->m);
              }
           }
  );

  std::cout << "\n==========================================\n\n";

  Date test(10, 2, 2012);
  std::cout << "test.getDateStr(): " << test.getDateStr().c_str() << "\n";
  test.addYear(10);
  std::cout << "addYear(10): test.getDateStr(): " << test.getDateStr().c_str() << "\n";
  test.addYear(-10);
  std::cout << "addYear(-10): test.getDateStr(): " << test.getDateStr().c_str() << "\n";
  test.addMonth(10);
  std::cout << "addMonth(10): test.getDateStr(): " << test.getDateStr().c_str() << "\n";
  test.addMonth(20);
  std::cout << "addMonth(20): test.getDateStr(): " << test.getDateStr().c_str() << "\n";

  std::cout << "\n\nEND\n";

  return 0;
}
