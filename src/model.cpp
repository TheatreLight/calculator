#include "model.h"

s21::Model::Model() {}

void s21::Model::Parser::ParseInputString(std::string input) {
  setlocale(LC_ALL, "C");
  std::string temp;
  bool isNum = false;
  bool isNextUnary = true;
  for (auto elem : input) {
    if (IsSign(elem) || IsBrackets(elem)) {
      if ((elem == '+' || elem == '-') && isNextUnary) {
        PushFunction(&temp, isNum);
        temp.clear();
        temp.push_back(elem);
        isNextUnary = false;
        isNum = true;
      } else if (elem == 'm') {
        PushNumber(&temp, isNum);
        isNum = false;
        temp.push_back(elem);
      } else {
        PushNumber(&temp, isNum);
        PushFunction(&temp, isNum);
        std::string kind(1, elem);
        modified_string_.emplace_back(0, kind);
        isNum = false;
      }
      if (IsSign(elem) || elem == '(') isNextUnary = true;
    } else if (IsNumber(elem)) {
      PushFunction(&temp, isNum);
      if (elem == 'x') {
        temp.append(x_);
      } else {
        temp.push_back(elem);
      }
      isNum = true;
      isNextUnary = false;
    } else if (IsFunc(elem)) {
      isNextUnary = false;
      temp.push_back(elem);
      if (elem == 'd') isNextUnary = true;
    } else if (elem == ',') {
      temp.push_back('.');
    } else {
      continue;
    }
  }
  PushNumber(&temp, isNum);
  PushFunction(&temp, isNum);
}

bool s21::Model::Parser::IsSign(char ch) {
  if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' ||
      ch == 'm') {
    return true;
  }
  return false;
}

bool s21::Model::Parser::IsNumber(char ch) {
  if ((ch >= 48 && ch <= 57) || ch == '.' || ch == 'x') return true;
  return false;
}

bool s21::Model::Parser::IsBrackets(char ch) {
  if (ch == '(' || ch == ')') return true;
  return false;
}

bool s21::Model::Parser::IsFunc(char ch) {
  if (ch >= 'a' && ch <= 'z') return true;
  return false;
}

void s21::Model::Parser::PushNumber(std::string *temp, bool isNum) {
  if (temp->length() > 0 && isNum) {
    double d = std::stod(*temp);
    modified_string_.emplace_back(d, "num");
    temp->clear();
  }
}

void s21::Model::Parser::PushFunction(std::string *temp, bool isNum) {
  if (temp->length() > 0 && !isNum) {
    modified_string_.emplace_back(0, *temp);
    temp->clear();
  }
}

void s21::Model::GetRpn() {
  rpn_.clear();
  for (auto elem : tokenized_string_) {
    if (IsTokenNumber(elem)) {
      rpn_.push_back(elem);
    } else if (IsTokenFunction(elem)) {
      stack_.push(elem);
    } else if (IsTokenOpenBracket(elem)) {
      stack_.push(elem);
    } else if (IsTokenClosedBracket(elem)) {
      while (!IsTokenOpenBracket(stack_.top())) {
        rpn_.push_back(stack_.top());
        stack_.pop();
      }
      stack_.pop();
    } else if (IsTokenOperator(elem)) {
      while (!stack_.empty() && (IsTokenFunction(stack_.top()) ||
                                 IsTokenPriority(elem, stack_.top()))) {
        rpn_.push_back(stack_.top());
        stack_.pop();
      }
      stack_.push(elem);
    }
  }

  while (!stack_.empty()) {
    rpn_.push_back(stack_.top());
    stack_.pop();
  }
}

void s21::Model::CalculateRpn() {
  if (!stack_.empty()) {
    return;
  }

  for (auto elem : rpn_) {
    if (IsTokenNumber(elem)) {
      stack_.push(elem);
    } else {
      double tmp = stack_.top().get_num();
      if (elem.get_str().compare("+") == 0) {
        stack_.pop();
        tmp += stack_.top().get_num();
      } else if (elem.get_str().compare("-") == 0) {
        stack_.pop();
        tmp = stack_.top().get_num() - tmp;
      } else if (elem.get_str().compare("*") == 0) {
        stack_.pop();
        tmp *= stack_.top().get_num();
      } else if (elem.get_str().compare("/") == 0) {
        stack_.pop();
        tmp = stack_.top().get_num() / tmp;
      } else if (elem.get_str().compare("mod") == 0) {
        stack_.pop();
        int x = (int)stack_.top().get_num();
        int y = (int)tmp;
        tmp = (double)(x % y);
      } else if (elem.get_str().compare("^") == 0) {
        stack_.pop();
        tmp = pow(stack_.top().get_num(), tmp);
      } else if (elem.get_str().compare("sin") == 0) {
        tmp = sin(tmp);
      } else if (elem.get_str().compare("cos") == 0) {
        tmp = cos(tmp);
      } else if (elem.get_str().compare("tan") == 0) {
        tmp = tan(tmp);
      } else if (elem.get_str().compare("asin") == 0) {
        tmp = asin(tmp);
      } else if (elem.get_str().compare("acos") == 0) {
        tmp = acos(tmp);
      } else if (elem.get_str().compare("atan") == 0) {
        tmp = atan(tmp);
      } else if (elem.get_str().compare("sqrt") == 0) {
        tmp = sqrt(tmp);
      } else if (elem.get_str().compare("log") == 0) {
        tmp = log10(tmp);
      } else if (elem.get_str().compare("ln") == 0) {
        tmp = log(tmp);
      }
      stack_.top().set_num(tmp);
    }
  }
  result_ = stack_.top().get_num();
  stack_.pop();
}

void s21::Model::set_tokenized_string(std::string input, std::string x) {
  Parser parser(x);
  parser.ParseInputString(input);
  tokenized_string_ = parser.get_modified_str();
}

bool s21::Model::IsTokenNumber(Token token) {
  if (token.get_str().compare("num") == 0) return true;
  return false;
}

bool s21::Model::IsTokenOperator(Token token) {
  if (token.get_str().compare("+") == 0 || token.get_str().compare("-") == 0 ||
      token.get_str().compare("*") == 0 || token.get_str().compare("/") == 0 ||
      token.get_str().compare("^") == 0 || token.get_str().compare("mod") == 0)
    return true;
  return false;
}

bool s21::Model::IsTokenFunction(Token token) {
  if (token.get_str().compare("sin") == 0 ||
      token.get_str().compare("cos") == 0 ||
      token.get_str().compare("tan") == 0 ||
      token.get_str().compare("asin") == 0 ||
      token.get_str().compare("acos") == 0 ||
      token.get_str().compare("atan") == 0 ||
      token.get_str().compare("ln") == 0 ||
      token.get_str().compare("log") == 0 ||
      token.get_str().compare("sqrt") == 0)
    return true;
  return false;
}

bool s21::Model::IsTokenOpenBracket(Token token) {
  if (token.get_str().compare("(") == 0) return true;
  return false;
}

bool s21::Model::IsTokenClosedBracket(Token token) {
  if (token.get_str().compare(")") == 0) return true;
  return false;
}

bool s21::Model::IsTokenPriority(Token input_token, Token pushed_token) {
  auto isPriority{[](Token input_token, Token pushed_token,
                     std::string one_push, std::string another_push,
                     std::string one_input, std::string another_input) {
    return (pushed_token.get_str().compare(one_push) == 0 ||
            pushed_token.get_str().compare(another_push) == 0) &&
           (input_token.get_str().compare(one_input) == 0 ||
            input_token.get_str().compare(another_input) == 0);
  }};
  if (input_token.get_str().compare("^") != 0 &&
      pushed_token.get_str().compare("^") == 0)
    return true;
  if (isPriority(input_token, pushed_token, "*", "/", "+", "-")) return true;
  if (isPriority(input_token, pushed_token, "*", "/", "*", "/")) return true;
  if (isPriority(input_token, pushed_token, "+", "-", "+", "-")) return true;
  if (isPriority(input_token, pushed_token, "mod", "", "+", "-")) return true;
  if (isPriority(input_token, pushed_token, "mod", "", "*", "/")) return true;
  if (isPriority(input_token, pushed_token, "mod", "", "mod", "")) return true;

  return false;
}
