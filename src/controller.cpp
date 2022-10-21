#include "controller.h"

s21::Controller::Controller(Model *model) { model_ = model; }

void s21::Controller::Start(std::string input, std::string x) {
  model_->set_tokenized_string(input, x);
  model_->GetRpn();
  model_->CalculateRpn();
  output_ = std::to_string(model_->get_result());
}
