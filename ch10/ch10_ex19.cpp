#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#include <cstdio>


#define DIV_TOKENS " ,.;:!?"

typedef std::map<std::string, std::vector<uint16_t>> mapString2IntVector;

mapString2IntVector countWords(
    std::istream& is,
    std::vector<std::string> wordList) {
  std::string s;
  mapString2IntVector wordListCount;
  for (auto x: wordList) {
    wordListCount[x] = {};
  }
  uint16_t line = 1;
  while (std::getline(is,s)) {
    std::map<std::string, bool> currentLine;
    s.pop_back();
    size_t pos = 0;
    while (s.length() && pos <= s.length()) {
      std::string token = s.substr(pos, s.find_first_of(DIV_TOKENS, pos)-pos);
      pos += 1 + token.length();
      if (wordListCount.count(token) && !currentLine[token]) {
        wordListCount[token].push_back(line);
        currentLine[token] = true;
      }
    }
    line++;
  }
  return std::move(wordListCount);
}

int main(int argc, char **argv) {
  std::ifstream ifs;
  ifs.open("/home/user/pg1661.txt");
  std::vector<std::string> t = { "the", "only", "best", "source" };
  mapString2IntVector wordsLocations = countWords(ifs, t);
  for (auto word = wordsLocations.begin();
       word != wordsLocations.end();
       word++) {
    printf("%s\n  ->", word->first.c_str());
    for (auto lineNum: word->second) {
      printf("%d ", lineNum);
    }
    printf("\n");
  }
}
