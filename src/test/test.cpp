#include <string>

#include "../controller.h"
#include "gtest/gtest.h"

double Calculate(std::string input) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.Start(input, "");
  return controller.get_answer();
}

TEST(suite, test1) { EXPECT_DOUBLE_EQ(Calculate("3 + 2"), 5); }

TEST(suite, test2) { EXPECT_DOUBLE_EQ(Calculate("(3+6)*9"), 81); }

TEST(suite, test3) {
  EXPECT_NEAR(Calculate("sin(1)"), 0.8414709848, 0.0000000001);
}

TEST(suite, test4) {
  EXPECT_NEAR(Calculate("cos(1)"), 0.54030230586, 0.0000000001);
}

TEST(suite, test5) {
  EXPECT_NEAR(Calculate("tan(1)"), 1.55740772465, 0.0000000001);
}

TEST(suite, test6) {
  EXPECT_NEAR(Calculate("asin(1)"), 1.5707963267949, 0.0000000001);
}

TEST(suite, test7) {
  EXPECT_NEAR(Calculate("acos(0.5)"), 1.0471975511966, 0.0000000001);
}

TEST(suite, test8) {
  EXPECT_NEAR(Calculate("atan(0.5)"), 0.463647609000806, 0.0000000001);
}

TEST(suite, test9) {
  EXPECT_NEAR(Calculate("sqrt(11)"), 3.31662479, 0.00000001);
}

TEST(suite, test10) {
  EXPECT_NEAR(Calculate("log(5)"), 0.69897000433, 0.00000001);
}

TEST(suite, test11) {
  EXPECT_NEAR(Calculate("ln(5)"), 1.60943791243, 0.00000001);
}

TEST(suite, test12) {
  EXPECT_NEAR(Calculate("log(7)+ln(5)"), 2.45453595245, 0.0000001);
}

TEST(suite, test13) {
  EXPECT_NEAR(Calculate("cos(6+3)"), -0.91113026188, 0.0000001);
}

TEST(suite, test14) {
  EXPECT_NEAR(Calculate("sin(4-2)"), 0.90929742682, 0.0000001);
}

TEST(suite, test15) {
  EXPECT_NEAR(Calculate("cos(6+3)-sin(4-2)"), -1.82042768871, 0.0000001);
}

TEST(suite, test16) { EXPECT_NEAR(Calculate("23^6"), 148035889, 0.0000001); }

TEST(suite, test17) { EXPECT_DOUBLE_EQ(Calculate("5mod2"), 1); }

TEST(suite, test18) { EXPECT_DOUBLE_EQ(Calculate("10mod(2+4)"), 4); }

TEST(suite, test19) { EXPECT_DOUBLE_EQ(Calculate("-2+5"), 3); }

TEST(suite, test20) { EXPECT_DOUBLE_EQ(Calculate("2^-3"), 0.125); }

TEST(suite, test21) {
  EXPECT_NEAR(Calculate("2^-3^-5"), 0.99715160685, 0.0000001);
}

TEST(suite, test22) {
  EXPECT_NEAR(Calculate("2^3^sqrt(5)-log(ln(-8+20)/tan(0.5))"), 3246.03076629,
              0.0000001);
}

TEST(suite, test23) {
  EXPECT_NEAR(Calculate("2.135*7.895-6.001+4.25"), 15.104825, 0.0000001);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}