#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <cstdio>
#include <cctype>
#include <cstdint>

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

  enum operator_types {
    operator_unknown,
    operator_plus     = '+',
    operator_minus    = '-',
    operator_multiply = '*',
    operator_division = '/'
  };

  std::string _e;
  std::string _curr_token;
  token_type  _curr_token_type;
  uint16_t _curr_pos;
  uint16_t _error_pos;
  bool _is_valid;
  std::vector<double> _operands;
  std::vector<operator_types> _operators;

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
  _error_pos(0),
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
    switch(state) {
      case undefined:
        if (isdigit(c)) {
          state = reading_number;
          _curr_token_type = operand_token;
        } else if (c == ' ') {
          _curr_pos++;
        } else if (isOperator(c)) {
          _curr_pos++;
          _curr_token_type = operator_token;
          tempToken = c;
          done = found = true;
        } else {
          printf("Error, invalid character found [%c]\n", c);
          _error_pos = _curr_pos+1;
          _is_valid = false;
          done = true;
          found = false;
        }
        break;
      case reading_number:
        if (isdigit(c)) {
          tempToken += c;
          _curr_pos++;
        } else {
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
      if (previous_token == operand_token) {
        printf("Invalid token found: 2 consecutive operands\n");
        _is_valid = false;
        _error_pos = _curr_pos;
        printError();
        return;
      }
      _operands.push_back(boost::lexical_cast<double>(_curr_token));
      previous_token = operand_token;
    } else {
      if (previous_token == operator_token) {
        printf("Invalid token found: 2 consecutive operators\n");
        _error_pos = _curr_pos;
        _is_valid = false;
        printError();
        return;
      }
      _operators.push_back(operator_types(_curr_token[0]));
      previous_token = operator_token;
    }
  }
}

double MathExpr::eval() {
  if (!_is_valid) {
    printf("Warning: invalid expression\n");
    printError();
    return 0.0;
  }

  std::vector<operator_types> t_operators;
  std::vector<double> t_operands;
  size_t operator_idx = 0;
  size_t operand_idx = 0;

 while (operator_idx < _operators.size()) {
    switch (_operators[operator_idx]) {
      case operator_unknown:
        printf("Unknown operator found\n");
        return 0.0;
      case operator_plus:
      case operator_minus:
        t_operands.push_back(_operands[operand_idx++]);
        if (operator_idx < _operators.size()) {
          t_operators.push_back(_operators[operator_idx++]);
        }
        break;
      case operator_multiply:
      case operator_division:
        double s = _operands[operand_idx++];
        do {
          if (operand_idx >= _operands.size()) {
            printf("Missing operand after operator %c\n",
                   _operators[operator_idx]);
            return 0.0;
          }
          if (_operators[operator_idx] == operator_multiply) {
            s *= _operands[operand_idx++];
          } else if (_operators[operator_idx] == operator_division) {
            if (_operands[operand_idx]) {
              s /= _operands[operand_idx++];
            } else {
              printf("Division by zero detected, leaving\n");
              return 0.0;
            }
          }
          operator_idx++;
        } while (_operators[operator_idx] == operator_multiply ||
                 _operators[operator_idx] == operator_division);
        t_operands.push_back(s);
        if (operator_idx < _operators.size()) {
          t_operators.push_back(_operators[operator_idx++]);
        }
        break;
    }
  }
  if (operand_idx < _operands.size()) {
    t_operands.push_back(_operands[operand_idx]);
  }

  double s = t_operands[0];
  for (size_t i = 0; i < t_operators.size(); i++) {
    switch (t_operators[i]) {
      case operator_plus:
        s += t_operands[i+1];
        break;
      case operator_minus:
        s -= t_operands[i+1];
        break;
      default:
        printf("Invalid or missing operator %c\n", t_operators[i]);
        break;
    }
  }
  printf("\n");

  return s;
}

void MathExpr::printError() {
  printf("%s\n", _e.c_str());
  for (int i = 0; i < _error_pos-1; i++) {
    printf(" ");
  }
  printf("^\n");
}

int main(int argc, char **argv) {
  if (argc !=2 ) {
    printf("syntax: %s \"expr\"\n", argv[0]);
    exit(1);
  }
  MathExpr me(argv[1]);
  double r = me.eval();
  printf("[%s] = %.06f\n", argv[1], r);
}
