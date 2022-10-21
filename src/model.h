#ifndef MODEL_H
#define MODEL_H

#include <clocale>
#include <cmath>
#include <stack>
#include <vector>

#include "token.h"

namespace s21 {
class Model {
 public:
  class Parser {
   public:
    explicit Parser(const std::string& x) : x_(x) {}
    Parser(const Parser& other) = delete;
    Parser& operator=(const Parser& other) = delete;
    Parser(Parser&& other) = delete;
    Parser& operator=(Parser&& other) = delete;

    void ParseInputString(std::string input);
    std::vector<Token> get_modified_str() { return modified_string_; }

   private:
    std::vector<Token> modified_string_;
    std::string x_;

    bool IsSign(char ch);
    bool IsNumber(char ch);
    bool IsBrackets(char ch);
    bool IsFunc(char ch);
    void PushNumber(std::string* temp, bool isNum);
    void PushFunction(std::string* temp, bool isNum);
  };

  Model();
  Model(const Model& other) = delete;
  Model& operator=(const Model& other) = delete;
  Model(Model&& other) = delete;
  Model& operator=(Model&& other) = delete;

  void set_tokenized_string(std::string input, std::string x);
  void GetRpn();
  void CalculateRpn();
  double get_result() { return result_; }
  void ClearResult() { result_ = 0; }

 private:
  std::vector<Token> tokenized_string_;
  std::vector<Token> rpn_;
  std::stack<Token> stack_;
  double result_ = 0;

  bool IsTokenNumber(Token token);
  bool IsTokenOperator(Token token);
  bool IsTokenFunction(Token token);
  bool IsTokenOpenBracket(Token token);
  bool IsTokenClosedBracket(Token token);
  bool IsTokenPriority(Token input_token, Token pushed_token);
};
}  // namespace s21

#endif  // MODEL_H
