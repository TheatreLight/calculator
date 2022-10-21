#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(s21::Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  controller_ = controller;
  ui->setupUi(this);
  ui->lineEdit_2->setValidator(
      new QRegularExpressionValidator(QRegularExpression("[-,0-9]*")));
  ui->lineEdit_4->setValidator(
      new QRegularExpressionValidator(QRegularExpression("[-,0-9]*")));
  ui->lineEdit_5->setValidator(
      new QRegularExpressionValidator(QRegularExpression("[-,0-9]*")));
  ui->lineEdit_6->setValidator(
      new QRegularExpressionValidator(QRegularExpression("[-,0-9]*")));
  ui->lineEdit_7->setValidator(
      new QRegularExpressionValidator(QRegularExpression("[-,0-9]*")));
  set_start_zero();
}

MainWindow::~MainWindow() {
  controller_ = nullptr;
  delete ui;
}

void MainWindow::on_pushButton_10_clicked() {
  if (is_variable_) return;
  insert_number("0");
}

void MainWindow::on_pushButton_11_clicked() {
  if (is_variable_) return;
  if (!ui->lineEdit->isModified() && !is_dot_set_) {
    ui->lineEdit->clear();
    ui->lineEdit->insert("0.");
    is_dot_set_ = true;
    is_unary_ = false;
    is_number_ = true;
  } else if ((is_sign_set_ || is_unary_) && !is_dot_set_) {
    ui->lineEdit->insert("0.");
    is_dot_set_ = true;
    is_unary_ = false;
    is_number_ = true;
  } else if (!is_dot_set_) {
    ui->lineEdit->insert(".");
    is_dot_set_ = true;
  }
}

void MainWindow::on_pushButton_clicked() {
  if (is_variable_) return;
  insert_number("1");
}

void MainWindow::on_pushButton_6_clicked() {
  if (is_variable_) return;
  insert_number("2");
}

void MainWindow::on_pushButton_9_clicked() {
  if (is_variable_) return;
  insert_number("3");
}

void MainWindow::on_pushButton_2_clicked() {
  if (is_variable_) return;
  insert_number("4");
}

void MainWindow::on_pushButton_5_clicked() {
  if (is_variable_) return;
  insert_number("5");
}

void MainWindow::on_pushButton_8_clicked() {
  if (is_variable_) return;
  insert_number("6");
}

void MainWindow::on_pushButton_3_clicked() {
  if (is_variable_) return;
  insert_number("7");
}

void MainWindow::on_pushButton_4_clicked() {
  if (is_variable_) return;
  insert_number("8");
}

void MainWindow::on_pushButton_7_clicked() {
  if (is_variable_) return;
  insert_number("9");
}

void MainWindow::on_pushButton_28_clicked() { set_start_zero(); }

void MainWindow::on_pushButton_12_clicked() { insert_func("sin ( "); }

void MainWindow::on_pushButton_15_clicked() { insert_func("cos ( "); }

void MainWindow::on_pushButton_18_clicked() { insert_func("tan ( "); }

void MainWindow::on_pushButton_13_clicked() { insert_func("asin ( "); }

void MainWindow::on_pushButton_16_clicked() { insert_func("acos ( "); }

void MainWindow::on_pushButton_19_clicked() { insert_func("atan ( "); }

void MainWindow::on_pushButton_14_clicked() { insert_func("sqrt ( "); }

void MainWindow::on_pushButton_17_clicked() { insert_func("log ( "); }

void MainWindow::on_pushButton_20_clicked() { insert_func("ln ( "); }

void MainWindow::on_pushButton_21_clicked() {
  if (!is_sign_set_ && !is_unary_) {
    ui->lineEdit->insert(" mod ");
    is_sign_set_ = true;
    is_dot_set_ = false;
    is_unary_ = false;
    is_variable_ = false;
  }
}

void MainWindow::on_pushButton_29_clicked() { insert_func(" ( "); }

void MainWindow::on_pushButton_30_clicked() {
  if (is_bracket_open_ && !is_unary_ && !is_sign_set_) {
    ui->lineEdit->insert(" ) ");
    bracket_count_--;
    if (bracket_count_ <= 0) is_bracket_open_ = false;
    is_number_ = true;
    is_variable_ = true;
  }
}

void MainWindow::on_pushButton_23_clicked() {
  if (is_bracket_open_ && !is_number_) return;
  insert_sign(" + ");
}

void MainWindow::on_pushButton_24_clicked() {
  if (is_bracket_open_ && !is_number_) return;
  insert_sign(" - ");
}

void MainWindow::on_pushButton_25_clicked() {
  if (is_bracket_open_ && !is_number_) return;
  insert_sign(" * ");
}

void MainWindow::on_pushButton_26_clicked() {
  if (is_bracket_open_ && !is_number_) return;
  insert_sign(" / ");
}

void MainWindow::on_pushButton_22_clicked() {
  if (is_bracket_open_ && !is_number_) return;
  insert_sign(" ^ ");
}

void MainWindow::on_pushButton_27_clicked() {  // = pressed
  if (ui->lineEdit->isModified()) {
    set_input_string();
    x_ = ui->lineEdit_2->text().toStdString();
    controller_->Start(input_, x_);
    ui->lineEdit->clear();
    ui->lineEdit->setText(QString::number(controller_->get_answer(), 'g', 7));
    is_sign_set_ = false;
    is_dot_set_ = false;
    is_unary_ = false;
    is_number_ = false;
    is_variable_ = false;
    is_bracket_open_ = false;
    bracket_count_ = 0;
  }
}

void MainWindow::on_pushButton_32_clicked() {
  if (!ui->lineEdit->isModified()) ui->lineEdit->clear();
  if (!is_unary_ && !is_number_ && !is_variable_) {
    ui->lineEdit->insert("x");
    is_sign_set_ = false;
    is_number_ = true;
    is_variable_ = true;
  }
}

void MainWindow::on_pushButton_31_clicked() {
  if (!is_unary_ && !is_number_) {
    if (!ui->lineEdit->isModified()) ui->lineEdit->clear();
    ui->lineEdit->insert(" -");
    is_unary_ = true;
  }
}

void MainWindow::on_pushButton_33_clicked() {
  ui->widget->clearGraphs();

  double x_first, x_last, step = 0.1, x, range_x, range_y;

  x_first = ui->lineEdit_4->text().toDouble();
  x_last = ui->lineEdit_6->text().toDouble();
  range_x = ui->lineEdit_5->text().toDouble();
  range_y = ui->lineEdit_7->text().toDouble();

  ui->widget->xAxis->setRange(-1 * range_x, range_x);
  ui->widget->yAxis->setRange(-1 * range_y, range_y);

  QVector<double> scope_x, scope_y;

  for (x = x_first; x <= x_last;) {
    scope_x.push_back(x);
    controller_->Start(ui->lineEdit_3->text().toStdString(), std::to_string(x));
    scope_y.push_back(controller_->get_answer());
    x += step;
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(scope_x, scope_y);
  ui->widget->replot();
}

void MainWindow::on_pushButton_34_clicked() {
  ui->lineEdit_3->setText("0");
  ui->lineEdit_4->setText("0");
  ui->lineEdit_5->setText("0");
  ui->lineEdit_6->setText("0");
  ui->lineEdit_7->setText("0");
  ui->widget->clearGraphs();
  ui->widget->replot();
}

void MainWindow::on_pushButton_35_clicked() {
  ui->lineEdit_3->setText(ui->lineEdit->text());
}

void MainWindow::set_input_string() {
  input_ = ui->lineEdit->text().toStdString();
}

void MainWindow::set_start_zero() {
  controller_->ClearResult();
  ui->lineEdit->clear();
  ui->lineEdit->setText(QString::number(controller_->get_answer(), 'g', 7));
  is_sign_set_ = false;
  is_dot_set_ = false;
  is_unary_ = false;
  is_number_ = false;
  is_variable_ = false;
  is_bracket_open_ = false;
  bracket_count_ = 0;
  x_.clear();
  ui->lineEdit_2->clear();
  ui->lineEdit_2->setText("0");
}

void MainWindow::insert_number(QString input) {
  if (!ui->lineEdit->isModified()) ui->lineEdit->clear();
  ui->lineEdit->insert(input);
  is_sign_set_ = false;
  is_unary_ = false;
  is_number_ = true;
}

void MainWindow::insert_func(QString input) {
  if (!ui->lineEdit->isModified()) ui->lineEdit->clear();
  if (!is_unary_ && !is_number_) {
    ui->lineEdit->insert(input);
    is_bracket_open_ = true;
    bracket_count_++;
  }
}

void MainWindow::insert_sign(QString input) {
  if (!is_sign_set_ && !is_unary_) {
    ui->lineEdit->insert(input);
    is_sign_set_ = true;
    is_dot_set_ = false;
    is_number_ = false;
    is_variable_ = false;
  }
}
