#include <iostream>
#include <string>
#include <vector>

#include <cctype>

class MathExpr {
  std::string _e;
  std::string _curr_token;
  uint16_t  _curr_pos;
  bool readToken();
  bool isOperator(const char c);

  enum token_read_state {
    undefined,
    reading_number
  };

  enum token_type {
    digit,
    oper
  };

public:
  MathExpr(std::string expr) : _e(expr), _curr_pos(0) {}
  ~MathExpr() {}

  double eval();
};

bool MathExpr::isOperator(const char c) {
  switch (c) {
    case '+': case '-': case '/': case '*':
      return true;
    default:
      return false;
  }
}

bool MathExpr::readToken() {
  if (_curr_pos == _e.size()) return false;
  token_read_state state = undefined;
  std::string tempToken;
  bool found = false;
  bool done = false;

  while (!done) {
    char c = _e[_curr_pos];
    printf("current char [%c]\n", c);
    switch(state) {
      case undefined:
        if (isdigit(c)) {
          printf("found start of number, state = number now\n");
          state = reading_number;
        } else if (c == ' ') {
          printf("found space, ignoring and advancing c to %d\n", _curr_pos+1);
          _curr_pos++;
        } else if (isOperator(c)) {
          printf("Found operator (%c), search done\n", c);
          _curr_pos++;
          tempToken = c;
          done = found = true;
        } else {
          printf("Error, invalid character found [%c]\n", c);
          done = true;
          found = false;
        }
        break;
      case reading_number:
        if (isdigit(c)) {
          printf("Adding digit [%c]\n", c);
          tempToken += c;
          _curr_pos++;
        } else {
          printf("Ended number [%s]\n", tempToken.c_str());
          state = undefined;
          done = found = true;
        }
        break;
    };
  }

  if (found) _curr_token = tempToken;

  return found;
}

double MathExpr::eval() {
  std::vector<std::string> tokens;
  while (readToken()) {
    tokens.push_back(_curr_token);
  }

  int i = 0;
  printf("original: %s\n", _e.c_str());
  for(auto t: tokens) {
    printf("token [%d]: [%s]\n", i++, t.c_str());
  }
  return 0.0;
}

int main(int argc, char **argv) {
  MathExpr me("10 + 20+30/29**1  ++ + +    a2");
  me.eval();
}
