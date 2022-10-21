#ifndef SRC_MAINWINDOW_H_
#define SRC_MAINWINDOW_H_

#include <QMainWindow>

#include "controller.h"
#include "plot/qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(s21::Controller *controller, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_10_clicked();

  void on_pushButton_11_clicked();

  void on_pushButton_32_clicked();

  void on_pushButton_clicked();

  void on_pushButton_6_clicked();

  void on_pushButton_9_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_5_clicked();

  void on_pushButton_8_clicked();

  void on_pushButton_3_clicked();

  void on_pushButton_4_clicked();

  void on_pushButton_7_clicked();

  void on_pushButton_12_clicked();

  void on_pushButton_13_clicked();

  void on_pushButton_14_clicked();

  void on_pushButton_15_clicked();

  void on_pushButton_16_clicked();

  void on_pushButton_17_clicked();

  void on_pushButton_18_clicked();

  void on_pushButton_19_clicked();

  void on_pushButton_20_clicked();

  void on_pushButton_21_clicked();

  void on_pushButton_29_clicked();

  void on_pushButton_30_clicked();

  void on_pushButton_23_clicked();

  void on_pushButton_24_clicked();

  void on_pushButton_25_clicked();

  void on_pushButton_26_clicked();

  void on_pushButton_22_clicked();

  void on_pushButton_31_clicked();

  void on_pushButton_27_clicked();

  void on_pushButton_28_clicked();

  void on_pushButton_33_clicked();

  void on_pushButton_34_clicked();

  void on_pushButton_35_clicked();

 private:
  void set_input_string();

  void set_start_zero();

  void insert_number(QString input);

  void insert_func(QString input);

  void insert_sign(QString input);

 private:
  Ui::MainWindow *ui;
  s21::Controller *controller_;
  std::string input_;
  bool is_sign_set_ = false;
  bool is_dot_set_ = false;
  bool is_unary_ = false;
  bool is_number_ = false;
  bool is_variable_ = false;
  bool is_bracket_open_ = false;
  int bracket_count_ = 0;
  std::string x_;
};

#endif  // SRC_MAINWINDOW_H_
