#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <cstdlib>
#include <ctime>

#include <boost/date_time/posix_time/posix_time.hpp>

std::string t(const char* p) {
  std::string a(p);
  return std::move(a);
}

std::string t2(const char* p) {
  std::string a(p);
  return a;
}

int main(int argc, char **argv) {
  std::string a;
  std::vector<std::string> list, list2;
  uint32_t count = 1;

  if (argc >= 2) {
    std::istringstream iss(argv[1]);
    iss >> count;
  }

  boost::posix_time::ptime starttime(boost::posix_time::microsec_clock::local_time());
  for(uint32_t i = 0; i < count; i++) {
    std::ostringstream oss;
    oss << "test " << i;

    a = t(oss.str().c_str());
    //printf("%8d [%s]: 0x%lx\n", i, a.c_str(), (long unsigned int)&a);
    list.push_back(std::move(a));
  }
  boost::posix_time::ptime endtime(boost::posix_time::microsec_clock::local_time());
  boost::posix_time::time_duration delay(endtime-starttime);

  boost::posix_time::ptime starttime2(boost::posix_time::microsec_clock::local_time());
  for(uint32_t i = 0; i < count; i++) {
    std::ostringstream oss;
    oss << "test " << i;

    a = t2(oss.str().c_str());
    //printf("%8d [%s]: 0x%lx\n", i, a.c_str(), (long unsigned int)&a);
    list2.push_back(a);
  }
  boost::posix_time::ptime endtime2(boost::posix_time::microsec_clock::local_time());
  boost::posix_time::time_duration delay2(endtime2-starttime2);

  printf("std::move: total_microseconds[%lld], avg: %.04f r/ms\n",
         delay.total_milliseconds(),
         (double)count/delay.total_milliseconds());
  printf("no std::move: total_microseconds[%lld], avg: %.04f r/ms\n",
         delay2.total_milliseconds(),
         (double)count/delay2.total_milliseconds());

  //for(auto s: list) { printf("== [%s]\n", s.c_str());}
}
