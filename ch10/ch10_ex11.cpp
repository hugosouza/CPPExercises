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
    operator_plus,
    operator_minus,
    operator_multiply,
    operator_division
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
  bool isOperatorPlusOrMinus(operator_types);
  bool isOperatorMulOrDiv(operator_types);
public:
  MathExpr(std::string expr);
  ~MathExpr() {}

  double eval();
  void printError();

  static std::map<unsigned char, operator_types> _char_to_operator;
  static std::map<operator_types, unsigned char> _operator_to_char;
};

std::map<unsigned char, MathExpr::operator_types> MathExpr::_char_to_operator = {
  {'+', operator_plus},
  {'-', operator_minus},
  {'*', operator_multiply},
  {'/', operator_division}
};

std::map<MathExpr::operator_types, unsigned char> MathExpr::_operator_to_char = {
  {operator_plus,     '+'},
  {operator_minus,    '-'},
  {operator_multiply, '*'},
  {operator_division, '/'},
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

bool MathExpr::isOperatorPlusOrMinus(operator_types o) {
  return o == operator_plus || o == operator_minus;
}

bool MathExpr::isOperatorMulOrDiv(operator_types o) {
  return o == operator_multiply || o == operator_division;
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
          _error_pos = _curr_pos+1;
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
        _error_pos = _curr_pos;
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
        _error_pos = _curr_pos;
        _is_valid = false;
        printError();
        return;
      }
      _operators.push_back(_char_to_operator[_curr_token[0]]);
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
    printf("%c\n", _operator_to_char[i]);
  }

  std::vector<operator_types> t_operators;
  std::vector<double> t_operands;

  size_t operator_idx = 0;
  size_t operand_idx = 0;
  int ii = 1;

  while (operator_idx < _operands.size()-1) {
    printf("iter[%d]\n", ii++);
    if (isOperatorPlusOrMinus(_operators[operator_idx])) {
      printf("storing %.06f and %c\n", _operands[operand_idx],
             _operator_to_char[_operators[operator_idx]]);
      t_operands.push_back(_operands[operand_idx++]);
      t_operators.push_back(_operators[operator_idx++]);
    } else if (isOperatorMulOrDiv(_operators[operator_idx])) {
      double s = _operands[operand_idx++];
      printf("evaluating * or /\n");
      do {
        if (operand_idx >= _operands.size()) {
          printf("Missing operand after [%.06f %c]\n",
                 _operands[operand_idx-1],
                 _operator_to_char[_operators[operator_idx]]);
          return 0.0;
        }
        if (_operators[operator_idx] == operator_multiply) {
          printf("calculating %.06f * %.06f\n", s, _operands[operand_idx]);
          s *= _operands[operand_idx++];
        } else if (_operators[operator_idx] == operator_division) {
          if (_operands[operand_idx]) {
            printf("calculating %.06f / %.06f\n", s, _operands[operand_idx]);
            s /= _operands[operand_idx++];
          } else {
            printf("Division by zero after [%.06f %c]\n",
                 _operands[operand_idx-1],
                 _operators[operator_idx]);
            return 0.0;
          }
        }
        operator_idx++;
      } while (isOperatorMulOrDiv(_operators[operator_idx]));
      printf("storing %.06f\n", s);
      t_operands.push_back(s);
      t_operators.push_back(_operators[operator_idx++]);
    }
  }
  printf("storing %.06f\n", _operands[operand_idx]);
  t_operands.push_back(_operands[operand_idx]);

  printf("done with * or /\n");

  for (auto i: t_operands) {
    printf("operand: %.06f\n", i);
  }

  for (auto i: t_operators) {
    printf("operator: %c\n", _operator_to_char[i]);
  }

  double s = t_operands[0];
  for (size_t i = 0; i < t_operands.size(); i++) {
    if (t_operators[i] == operator_plus) {
      printf("doing %.06f + %.06f\n", s, t_operands[i+1]);
      s += t_operands[i+1];
    } else {
      printf("doing %.06f - %.06f\n", s, t_operands[i+1]);
      s -= t_operands[i+1];
    }
  }

  printf("[%s] = %.06f\n", _e.c_str(), s);

  return 0.0;
}

void MathExpr::printError() {
  printf("%s\n", _e.c_str());
  for (int i = 0; i < _error_pos-1; i++) {
    printf(" ");
  }
  printf("^\n");
}

int main(int argc, char **argv) {
  // printf("=====\n");
  // MathExpr me("10 + +20+30/29**1  ++ + +    a2");
  // printf("=====\n");
  MathExpr me2("10 + 20+30/29*1  +    999 * 20/3 * 100");
  printf("=====\n");
  me2.eval();
}
