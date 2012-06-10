#include <iostream>
#include <string>
#include <vector>

#include <cctype>

#include <boost/lexical_cast.hpp>

class MathExpr {
  enum token_read_state {
    undefined,
    reading_number
  };

  enum token_type {
    unknown_token,
    operand_token,
    operator_token
  };

  std::string _e;
  std::string _curr_token;
  token_type  _curr_token_type;
  uint16_t  _curr_pos;
  bool _is_valid;
  std::vector<double> _operands;
  std::vector<unsigned char> _operators;

  bool readToken();
  bool isOperator(const char c);
  void parseExpr();
public:
  MathExpr(std::string expr);
  ~MathExpr() {}

  double eval();
  void printError();
};

MathExpr::MathExpr(std::string expr) :
  _e(expr),
  _curr_token_type(unknown_token),
  _curr_pos(0),
  _is_valid(true) {
  parseExpr();
}

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
    //printf("current char [%c]\n", c);
    switch(state) {
      case undefined:
        if (isdigit(c)) {
          //printf("found start of number, state = number now\n");
          state = reading_number;
          _curr_token_type = operand_token;
        } else if (c == ' ') {
          //printf("found space, ignoring and advancing c to %d\n", _curr_pos+1);
          _curr_pos++;
        } else if (isOperator(c)) {
          //printf("Found operator (%c), search done\n", c);
          _curr_pos++;
          _curr_token_type = operator_token;
          tempToken = c;
          done = found = true;
        } else {
          printf("Error, invalid character found [%c]\n", c);
          _curr_pos++;
          _is_valid = false;
          done = true;
          found = false;
        }
        break;
      case reading_number:
        if (isdigit(c)) {
          //printf("Adding digit [%c]\n", c);
          tempToken += c;
          _curr_pos++;
        } else {
          //printf("Ended number [%s]\n", tempToken.c_str());
          state = undefined;
          done = found = true;
        }
        break;
    };
  }

  if (found) _curr_token = tempToken;

  return found;
}

void MathExpr::parseExpr() {
  token_type previous_token = unknown_token;
  while (readToken()) {
    if (_curr_token_type == operand_token) {
      if (previous_token != operator_token &&
          previous_token != unknown_token) {
        printf("Invalid token found: 2 consecutive operands\n");
        _is_valid = false;
        printError();
        return;
      }
      _operands.push_back(boost::lexical_cast<double>(_curr_token));
      previous_token = operand_token;
    } else {
      printf("operator: %s\n", _curr_token.c_str());
      if (previous_token != operand_token &&
          previous_token != unknown_token) {
        printf("Invalid token found: 2 consecutive operators\n");
        _is_valid = false;
        printError();
        return;
      }
      _operators.push_back(_curr_token[0]);
      previous_token = operator_token;
    }
  }
}

double MathExpr::eval() {
  printf("[%s]\n", _e.c_str());
  if (!_is_valid) {
    printf("Warning: invalid expression\n");
    printError();
  }

  for (auto i: _operands) {
    printf("%.06f\n", i);
  }

  for (auto i: _operators) {
    printf("%c\n", i);
  }

  // for (size_t i; i < _token_list.size(); i++) {
  //
  // }
  /*
  while
    if operator - or +
      store operand and operator
    elseif operator * or /
      s = current operand
      do
        s operator= next operand
      while next operator * or /
      store s
      store next operator
  */
  return 0.0;
}

void MathExpr::printError() {
  printf("%s\n", _e.c_str());
  for (int i = 0; i < _curr_pos-1; i++) {
    printf(" ");
  }
  printf("^\n");
}

int main(int argc, char **argv) {
  printf("=====\n");
  MathExpr me("10 + +20+30/29**1  ++ + +    a2");
  printf("=====\n");
  MathExpr me2("10 + 20+30/29*1  +    999");
  printf("=====\n");
  me.eval();
  printf("=====\n");
  me2.eval();
}
