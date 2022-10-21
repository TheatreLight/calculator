#ifndef TOKEN_H
#define TOKEN_H

#include <string>
namespace s21 {
class Token {
 public:
  Token(double number, const std::string& kind);
  Token(const Token& other) = default;
  Token& operator=(const Token& other) = default;
  Token(Token&& other) = delete;
  Token& operator=(Token&& other) = delete;
  ~Token() = default;

  std::string get_str() { return kind_; }
  double get_num() { return number_; }
  void set_num(double number) { number_ = number; }
  bool IsNumber() {
    if (kind_.compare("num") == 0) {
      return true;
    }
    return false;
  }

  Token get_token() { return *this; }

 private:
  double number_;
  std::string kind_;
};
}  // namespace s21

#endif  // TOKEN_H
