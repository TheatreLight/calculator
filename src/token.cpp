#include "token.h"

s21::Token::Token(double number, const std::string &kind) : kind_(kind) {
  number_ = number;
}
