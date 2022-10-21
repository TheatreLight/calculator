#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"

namespace s21 {
class Controller {
 public:
  explicit Controller(Model* model);
  Controller(const Controller& other) = delete;
  Controller& operator=(const Controller& other) = delete;
  Controller(Controller&& other) = delete;
  Controller& operator=(Controller&& other) = delete;

  void Start(std::string input, std::string x);
  double get_answer() { return model_->get_result(); }
  void ClearResult() { model_->ClearResult(); }

 private:
  Model* model_;
  std::string output_;
};
}  // namespace s21

#endif  // CONTROLLER_H
