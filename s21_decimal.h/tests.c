#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"
#include "s21_decimal_helper.h"

#define SUITE_NAME "Unit"
#define TCASE_NAME "Tests"

// add tests

START_TEST(add_1_test) {
  s21_decimal num = {{1, 0, 0, 0}};
  s21_decimal num2 = {{1, 0, 0, 0}};
  s21_decimal res = {0};
  s21_decimal answer = {{2, 0, 0, 0}};

  s21_add(num, num2, &res);
  ck_assert_int_eq(res.bits[0], answer.bits[0]);
  ck_assert_int_eq(res.bits[1], answer.bits[1]);
  ck_assert_int_eq(res.bits[2], answer.bits[2]);
  ck_assert_int_eq(res.bits[3], answer.bits[3]);
}
END_TEST

START_TEST(add_2_test) {
  s21_decimal num1 = {{-1, -1, 56648, 0}};
  s21_decimal num2 = {{44, 369, 1687, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  int status = s21_add(num1, num2, &res);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 43);
  ck_assert_int_eq(res.bits[1], 369);
  ck_assert_int_eq(res.bits[2], 58336);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(add_3_test) {
  s21_decimal num1 = {{-1, -1, -1688, 0}};
  s21_decimal num2 = {{44, 369, 1687, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_add(num1, num2, &res);
  ck_assert_int_eq(status, 1);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(add_4_test) {
  s21_decimal num1 = {
      {(unsigned int)-1, (unsigned int)-1, 56648, (unsigned int)-2147483648}};
  s21_decimal num2 = {{44, 369, 1687, (unsigned int)-2147483648}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_add(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 43);
  ck_assert_int_eq(res.bits[1], 369);
  ck_assert_int_eq(res.bits[2], 58336);
  ck_assert_int_eq(res.bits[3], (unsigned int)-2147483648);
}
END_TEST

START_TEST(add_5_test) {
  s21_decimal num1 = {{(unsigned int)-1, (unsigned int)-1, (unsigned int)-1688,
                       (unsigned int)-2147483648}};
  s21_decimal num2 = {{44, 369, 1687, (unsigned int)-2147483648}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_add(num1, num2, &res);
  ck_assert_int_eq(status, 2);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(add_6_test) {
  s21_decimal num1 = {{45, 0, 10, (unsigned int)-2147483648}};
  // print_decimal(num1);
  s21_decimal num2 = {{67, 0, 0, (unsigned int)-2147352576}};
  // print_decimal(num2);
  s21_decimal res = {{0, 0, 0, 0}};

  int status = s21_add(num1, num2, &res);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 4567);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 1000);
  ck_assert_int_eq(res.bits[3], (unsigned int)-2147352576);
}
END_TEST

START_TEST(add_7_test) {
  s21_decimal num1 = {{45, 0, 10, 65536}};

  s21_decimal num2 = {{67, 0, 0, 131072}};

  s21_decimal res = {{0, 0, 0, 0}};

  int status = s21_add(num1, num2, &res);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 517);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 100);
  ck_assert_int_eq(res.bits[3], 131072);
}
END_TEST

START_TEST(add_8_test) {
  s21_decimal num1 = {
      {(unsigned int)-2, (unsigned int)-1, (unsigned int)-1, 0}};
  s21_decimal num2 = {{5, 0, 0, 65536}};
  s21_decimal res = {{0, 0, 0, 0}};

  int status = s21_add(num1, num2, &res);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], (unsigned int)-2);
  ck_assert_int_eq(res.bits[1], (unsigned int)-1);
  ck_assert_int_eq(res.bits[2], (unsigned int)-1);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(add_9_test) {
  s21_decimal num1 = {{(unsigned int)-3, (unsigned int)-1, (unsigned int)-1,
                       (unsigned int)-2147483648}};
  s21_decimal num2 = {{7, 0, 0, (unsigned int)-2147418112}};
  s21_decimal res = {{2, 1, 4, 65536}};
  //   print_decimal(num1);
  // print_decimal(num2);
  // printf("\n!!!!!!!!\n");
  int status = s21_add(num1, num2, &res);
  // s21_decimal res2 = {{(unsigned int)-2, (unsigned int)-1, (unsigned
  // int)-1, (unsigned int)-2147483648}}; printf("\n!!!!!!!!\n");

  // print_decimal(res);
  // print_decimal(res2);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], (unsigned int)-2);
  ck_assert_int_eq(res.bits[1], (unsigned int)-1);
  ck_assert_int_eq(res.bits[2], (unsigned int)-1);
  ck_assert_int_eq(res.bits[3], (unsigned int)-2147483648);
}
END_TEST

START_TEST(add_10_test) {
  s21_decimal num1 = {{0, 0, 10, 0}};
  s21_decimal num2 = {{6, 0, 0, 589824}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_add(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 1000000000);
  ck_assert_int_eq(res.bits[3], 524288);
}
END_TEST

START_TEST(add_11_test) {
  s21_decimal num1 = {{0, 0, 13, (unsigned int)-2147483648}};
  s21_decimal num2 = {{4, 0, 0, (unsigned int)-2146893824}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_add(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 1300000000);
  ck_assert_int_eq(res.bits[3], (unsigned int)-2146959360);
}
END_TEST

START_TEST(add_12_test) {
  s21_decimal num1 = {{6, 7, 8, 0}};
  s21_decimal num2 = {{5, 4, 3, (unsigned int)-2147483648}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_add(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(res.bits[1], 3);
  ck_assert_int_eq(res.bits[2], 5);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(add_13_test) {
  s21_decimal num1 = {{3, 1, 3, 0}};
  s21_decimal num2 = {{5, 4, 8, (unsigned int)-2147483648}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_add(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 2);
  ck_assert_int_eq(res.bits[1], 3);
  ck_assert_int_eq(res.bits[2], 5);
  ck_assert_int_eq(res.bits[3], (unsigned int)-2147483648);
}
END_TEST

START_TEST(add_14_test) {
  s21_decimal num1 = {{6, 7, 8, (unsigned int)-2147483648}};
  s21_decimal num2 = {{5, 4, 3, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_add(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(res.bits[1], 3);
  ck_assert_int_eq(res.bits[2], 5);
  ck_assert_int_eq(res.bits[3], (unsigned int)-2147483648);
}
END_TEST

START_TEST(add_15_test) {
  s21_decimal num1 = {{3, 1, 3, (unsigned int)-2147483648}};
  s21_decimal num2 = {{5, 4, 8, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_add(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 2);
  ck_assert_int_eq(res.bits[1], 3);
  ck_assert_int_eq(res.bits[2], 5);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(add_16_test) {
  s21_decimal num1 = {{0, 0, 0, 0}};
  s21_decimal num2 = {{5, 0, 0, 65536}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_add(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 5);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 65536);
}
END_TEST

START_TEST(add_error) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal *result_our = NULL;
  int val = s21_add(src1, src2, result_our);
  ck_assert_int_eq(val, 1);
}
END_TEST

// sub tests

START_TEST(sub_1_test) {
  s21_decimal num1 = {{5, 4, 3, 0}};
  s21_decimal num2 = {{3, 1, 2, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_sub(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 2);
  ck_assert_int_eq(res.bits[1], 3);
  ck_assert_int_eq(res.bits[2], 1);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(sub_2_test) {
  s21_decimal num1 = {{(unsigned int)-1, (unsigned int)-1, (unsigned int)-1688,
                       (unsigned int)-2147483648}};
  s21_decimal num2 = {{44, 369, 1687, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  //     print_decimal(num1);
  // print_decimal(num2);
  // printf("\n!!!!!!!!\n");
  int status = s21_sub(num1, num2, &res);
  //   s21_decimal res2 = {{(unsigned int)43, (unsigned int)369, (unsigned
  //   int)0, (unsigned int)-2147483648}};
  // printf("\n!!!!!!!!\n");

  // print_decimal(res);
  // print_decimal(res2);
  ck_assert_int_eq(status, 2);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(sub_3_test) {
  s21_decimal num1 = {{10, 11, 12, (unsigned int)-2147483648}};
  s21_decimal num2 = {{11, 13, 15, (unsigned int)-2147483648}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_sub(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(res.bits[1], 2);
  ck_assert_int_eq(res.bits[2], 3);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(sub_4_test) {
  s21_decimal num1 = {
      {(unsigned int)-1, (unsigned int)-1, (unsigned int)-1688, 0}};
  s21_decimal num2 = {{44, 369, 1687, (unsigned int)-2147483648}};
  s21_decimal res = {{0, 0, 0, 0}};
  //   print_decimal(num1);
  // print_decimal(num2);
  // printf("\n!!!!!!!!\n");

  int status = s21_sub(num1, num2, &res);
  //     s21_decimal res2 = {{(unsigned int)43, (unsigned int)369, (unsigned
  //     int)0, 0}};
  // printf("\n!!!!!!!!\n");

  // print_decimal(res);
  // print_decimal(res2);
  ck_assert_int_eq(status, 1);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(sub_5_test) {
  s21_decimal num1 = {{45, 0, 10, (unsigned int)-2147483648}};
  s21_decimal num2 = {{67, 0, 1, (unsigned int)-2147352576}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_sub(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 4433);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 999);
  ck_assert_int_eq(res.bits[3], (unsigned int)-2147352576);
}
END_TEST

START_TEST(sub_6_test) {
  s21_decimal num1 = {{45, 0, 10, 65536}};
  s21_decimal num2 = {{67, 0, 0, 131072}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_sub(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 383);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 100);
  ck_assert_int_eq(res.bits[3], 131072);
}
END_TEST

START_TEST(sub_7_test) {
  s21_decimal num1 = {
      {(unsigned int)-2, (unsigned int)-1, (unsigned int)-1, 0}};
  s21_decimal num2 = {{5, 0, 0, 65536}};
  s21_decimal res = {{0, 0, 0, 0}};
  //     print_decimal(num1);
  // print_decimal(num2);
  // printf("\n!!!!!!!!\n");
  int status = s21_sub(num1, num2, &res);
  //       s21_decimal res2 = {{(unsigned int)-3, (unsigned int)-1, (unsigned
  //       int)-1, 0}};
  // printf("\n!!!!!!!!\n");

  // print_decimal(res);
  // print_decimal(res2);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], (unsigned int)-2);
  ck_assert_int_eq(res.bits[1], (unsigned int)-1);
  ck_assert_int_eq(res.bits[2], (unsigned int)-1);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(sub_8_test) {
  s21_decimal num1 = {{(unsigned int)-3, (unsigned int)-1, (unsigned int)-1,
                       (unsigned int)-2147483648}};
  s21_decimal num2 = {{7, 0, 0, (unsigned int)-2147418112}};
  s21_decimal res = {{2, 1, 4, 65536}};
  int status = s21_sub(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], (unsigned int)-4);
  ck_assert_int_eq(res.bits[1], (unsigned int)-1);
  ck_assert_int_eq(res.bits[2], (unsigned int)-1);
  ck_assert_int_eq(res.bits[3], (unsigned int)-2147483648);
}
END_TEST

START_TEST(sub_9_test) {
  s21_decimal num1 = {{0, 0, 10, 0}};
  s21_decimal num2 = {{6, 0, 0, 589824}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_sub(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], (unsigned int)-1);
  ck_assert_int_eq(res.bits[1], (unsigned int)-1);
  ck_assert_int_eq(res.bits[2], 999999999);
  ck_assert_int_eq(res.bits[3], 524288);
}
END_TEST

START_TEST(sub_10_test) {
  s21_decimal num1 = {{0, 0, 13, (unsigned int)-2147483648}};
  s21_decimal num2 = {{4, 0, 0, (unsigned int)-2146893824}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_sub(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 1300000000);
  ck_assert_int_eq(res.bits[3], (unsigned int)-2146959360);
}
END_TEST

START_TEST(sub_11_test) {
  s21_decimal num1 = {{6, 7, 8, 0}};
  s21_decimal num2 = {{5, 4, 3, (unsigned int)-2147483648}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_sub(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 11);
  ck_assert_int_eq(res.bits[1], 11);
  ck_assert_int_eq(res.bits[2], 11);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(sub_12_test) {
  s21_decimal num1 = {{3, 1, 3, 0}};
  s21_decimal num2 = {{5, 4, 8, (unsigned int)-2147483648}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_sub(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 8);
  ck_assert_int_eq(res.bits[1], 5);
  ck_assert_int_eq(res.bits[2], 11);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(sub_13_test) {
  s21_decimal num1 = {{6, 7, 8, (unsigned int)-2147483648}};
  s21_decimal num2 = {{5, 4, 3, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_sub(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 11);
  ck_assert_int_eq(res.bits[1], 11);
  ck_assert_int_eq(res.bits[2], 11);
  ck_assert_int_eq(res.bits[3], (unsigned int)-2147483648);
}
END_TEST

START_TEST(sub_14_test) {
  s21_decimal num1 = {{3, 1, 3, (unsigned int)-2147483648}};
  s21_decimal num2 = {{5, 4, 8, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_sub(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 8);
  ck_assert_int_eq(res.bits[1], 5);
  ck_assert_int_eq(res.bits[2], 11);
  ck_assert_int_eq(res.bits[3], (unsigned int)-2147483648);
}
END_TEST

START_TEST(sub_error) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal *result_our = NULL;
  int val = s21_sub(src1, src2, result_our);
  ck_assert_int_eq(val, 1);
}
END_TEST

// mul tests

START_TEST(mul_2x2) {
  s21_decimal num1 = {{2, 0, 0, 0}};
  s21_decimal num2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_mul(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 4);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(mul_24xminus6) {
  s21_decimal num1 = {{24, 0, 0, 0}};
  s21_decimal num2 = {{6, 0, 0, (unsigned int)-2147483648}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_mul(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 144);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], (unsigned int)-2147483648);
}
END_TEST

START_TEST(mul_minus500xminus3) {
  s21_decimal num1 = {{500, 0, 0, (unsigned int)-2147483648}};
  s21_decimal num2 = {{3, 0, 0, (unsigned int)-2147483648}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_mul(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 1500);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(mul_minus2x5) {
  s21_decimal num1 = {{2, 0, 0, 0}};
  s21_decimal num2 = {{5, 0, 0, (unsigned int)-2147483648}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_mul(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 10);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], (unsigned int)-2147483648);
}
END_TEST

START_TEST(mul_3x0point256) {
  s21_decimal num1 = {{3, 0, 0, 0}};
  s21_decimal num2 = {{256, 0, 0, 262144}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_mul(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 768);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 262144);
}
END_TEST

START_TEST(mul_9point213658xminus169point312846) {
  s21_decimal num1 = {{9213658, 0, 0, 393216}};
  s21_decimal num2 = {{169312846, 0, 0, (unsigned int)-2147090432}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_mul(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], (unsigned int)-1593398676);
  ck_assert_int_eq(res.bits[1], 363213);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], (unsigned int)-2146697216);
}
END_TEST

START_TEST(mul_3point21x30point336) {
  s21_decimal num1 = {{321, 0, 0, 131072}};
  s21_decimal num2 = {{30336, 0, 0, 196608}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_mul(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 9737856);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 327680);
}
END_TEST

START_TEST(mul_minus3point2xminus0point3) {
  s21_decimal num1 = {{32, 0, 0, (unsigned int)-2147418112}};
  s21_decimal num2 = {{3, 0, 0, (unsigned int)-2147418112}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_mul(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 96);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 131072);
}
END_TEST

START_TEST(mul_zero) {
  s21_decimal num1 = {{32, 0, 0, (unsigned int)-2147418112}};
  s21_decimal num2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_mul(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(mul_bigXfloat) {
  s21_decimal num1 = {{0, 0, 1, 0}};
  s21_decimal num2 = {{256, 0, 0, 917504}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_mul(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 256);
  ck_assert_int_eq(res.bits[3], 917504);
}
END_TEST

START_TEST(mul_overflow_positive) {
  s21_decimal num1 = {{0, 0, 5, 0}};
  s21_decimal num2 = {{(unsigned int)-1, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_mul(num1, num2, &res);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(mul_overflow_negative) {
  s21_decimal num1 = {{0, 0, 1, 0}};
  s21_decimal num2 = {{0, (unsigned int)-1, 0, (unsigned int)-2147483648}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_mul(num1, num2, &res);
  ck_assert_int_eq(status, 2);
}
END_TEST

START_TEST(mul_minusBigXminusBig) {
  s21_decimal num1 = {{0, 0, 1, (unsigned int)-2147483648}};
  s21_decimal num2 = {{0, -1, 0, (unsigned int)-2147483648}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_mul(num1, num2, &res);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(mul_normalXsmall) {
  s21_decimal num1 = {{200, 0, 0, 0}};
  s21_decimal num2 = {{2, 0, 0, 1703936}};
  s21_decimal res = {{0, 0, 0, 0}};
  // print_decimal(num1);
  // print_decimal(num2);
  // printf("\n!!!!!!!!\n");
  int status = s21_mul(num1, num2, &res);
  // s21_decimal res2 = {{(unsigned int)4, (unsigned int)0, (unsigned int)0,
  // (unsigned int)1572864}}; printf("\n!!!!!!!!\n");

  // print_decimal(res);
  // print_decimal(res2);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 400);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0b00011010 << 16);
}
END_TEST

START_TEST(mul_floatXsmall) {
  s21_decimal num1 = {{41152263, 0, 0, 1048576}};
  s21_decimal num2 = {{3, 0, 0, 917504}};
  s21_decimal res = {{0, 0, 0, 0}};
  // print_decimal(num1);
  // print_decimal(num2);
  // printf("\n!!!!!!!!\n");
  int status = s21_mul(num1, num2, &res);
  //   s21_decimal res2 = {{(unsigned int)1234566, (unsigned int)0, (unsigned
  //   int)0, (unsigned int)1835008}};
  // printf("\n!!!!!!!!\n");

  // print_decimal(res);
  // print_decimal(res2);
  // нужно разобраться
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 1234568);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 1835008);
}
END_TEST

START_TEST(mul_smallXsmall) {
  s21_decimal num1 = {{4, 0, 0, 1048576}};
  s21_decimal num2 = {{3, 0, 0, 1048576}};
  s21_decimal res = {{0, 0, 0, 0}};
  // print_decimal(num1);
  // print_decimal(num2);
  // printf("\n!!!!!!!!\n");
  int status = s21_mul(num1, num2, &res);
  //   s21_decimal res2 = {{(unsigned int)0, (unsigned int)0, (unsigned int)0,
  //   (unsigned int)0}};
  // printf("\n!!!!!!!!\n");

  // print_decimal(res);
  // print_decimal(res2);

  ck_assert_int_eq(status, 2);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(mul_bigXsmall) {
  s21_decimal num1 = {{0, 0, 1234000000, 393216}};
  s21_decimal num2 = {{1, 0, 0, 1835008}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_mul(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 1234);
  ck_assert_int_eq(res.bits[3], 1835008);
}
END_TEST

START_TEST(mul_error) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal *result_our = NULL;
  int val = s21_mul(src1, src2, result_our);
  ck_assert_int_eq(val, 1);
}
END_TEST

// div tests

START_TEST(div_1_test) {
  s21_decimal num1 = {{10, 0, 0, 0}};
  s21_decimal num2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 5);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(div_2_test) {
  s21_decimal num1 = {{10, 0, 0, 0}};
  s21_decimal num2 = {{4, 0, 0, (unsigned int)-2147483648}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 25);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], (unsigned int)-2147418112);
}
END_TEST

START_TEST(div_3_test) {
  s21_decimal num1 = {{10, 0, 0, 0}};
  s21_decimal num2 = {{3, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 894784853);
  ck_assert_int_eq(res.bits[1], (unsigned int)-819591186);
  ck_assert_int_eq(res.bits[2], 1807003620);
  ck_assert_int_eq(res.bits[3], 1835008);
}
END_TEST

START_TEST(div_4_test) {
  s21_decimal num1 = {{10, 0, 0, 0}};
  s21_decimal num2 = {{22, 0, 0, 65536}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  // printf("\n!!!!!!!!\n");

  // print_decimal(res);
  // print_decimal(res2);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 48806447);
  ck_assert_int_eq(res.bits[1], (unsigned int)-1898527489);
  ck_assert_int_eq(res.bits[2], (unsigned int)-1830871450);
  ck_assert_int_eq(res.bits[3], 1835008);
}
END_TEST

START_TEST(div_5_test) {
  s21_decimal num1 = {{10, 0, 0, 0}};
  s21_decimal num2 = {{1, 0, 0, 393216}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 10000000);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(div_6_test) {
  s21_decimal num1 = {{10, 0, 0, 0}};
  s21_decimal num2 = {{6, 0, 0, 1835008}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 447392427);
  ck_assert_int_eq(res.bits[1], 1737688055);
  ck_assert_int_eq(res.bits[2], 903501810);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(div_7_test) {
  s21_decimal num1 = {{10, 0, 0, 0}};
  s21_decimal num2 = {{658067456, 1164, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  //       print_decimal(num1);
  // print_decimal(num2);
  // printf("\n!!!!!!!!\n");
  int status = s21_div(num1, num2, &res);
  //    s21_decimal res2 = {{(unsigned int)2, (unsigned int)0, (unsigned int)0,
  //    (unsigned int)786432}};
  // printf("\n!!!!!!!!\n");

  // print_decimal(res);
  // print_decimal(res2);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 2);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 786432);
}
END_TEST

START_TEST(div_8_test) {
  s21_decimal num1 = {{10, 0, 0, 0}};
  s21_decimal num2 = {
      {1879048192, (unsigned int)-1291644761, (unsigned int)-500259693, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 1835008);
}
END_TEST

START_TEST(div_9_test) {
  s21_decimal num1 = {
      {(unsigned int)-1, (unsigned int)-1, (unsigned int)-1, 0}};
  s21_decimal num2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], (unsigned int)-2147483648);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(div_10_test) {
  s21_decimal num1 = {
      {(unsigned int)-1, (unsigned int)-1, (unsigned int)-1, 0}};
  s21_decimal num2 = {{4, 0, 0, (unsigned int)-2147483648}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 1073741824);
  ck_assert_int_eq(res.bits[3], (unsigned int)-2147483648);
}
END_TEST

START_TEST(div_11_test) {
  s21_decimal num1 = {
      {(unsigned int)-1, (unsigned int)-1, (unsigned int)-1, 0}};
  s21_decimal num2 = {{3, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 1431655765);
  ck_assert_int_eq(res.bits[1], 1431655765);
  ck_assert_int_eq(res.bits[2], 1431655765);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(div_12_test) {
  s21_decimal num1 = {
      {(unsigned int)-1, (unsigned int)-1, (unsigned int)-1, 0}};
  s21_decimal num2 = {{22, 0, 0, 65536}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 1171354717);
  ck_assert_int_eq(res.bits[1], (unsigned int)-780903145);
  ck_assert_int_eq(res.bits[2], 1952257861);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(div_13_test) {
  s21_decimal num1 = {
      {(unsigned int)-1, (unsigned int)-1, (unsigned int)-1, 0}};
  s21_decimal num2 = {{658067456, 1164, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 858993459);
  ck_assert_int_eq(res.bits[1], 858993459);
  ck_assert_int_eq(res.bits[2], 858993459);
  ck_assert_int_eq(res.bits[3], 786432);
}
END_TEST

START_TEST(div_14_test) {
  s21_decimal num1 = {
      {(unsigned int)-1, (unsigned int)-1, (unsigned int)-1, 0}};
  s21_decimal num2 = {
      {1879048192, (unsigned int)-1291644761, (unsigned int)-500259693, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 1227133513);
  ck_assert_int_eq(res.bits[1], (unsigned int)-1840700270);
  ck_assert_int_eq(res.bits[2], 613566756);
  ck_assert_int_eq(res.bits[3], 1835008);
}
END_TEST

START_TEST(div_15_test) {
  s21_decimal num1 = {
      {(unsigned int)-1, (unsigned int)-1, (unsigned int)-1, 0}};
  s21_decimal num2 = {{805306368, (unsigned int)-1167128797, 1626303258, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  //     print_decimal(num1);
  // print_decimal(num2);
  // printf("\n!!!!!!!!\n");
  int status = s21_div(num1, num2, &res);
  // s21_decimal res2 = {{(unsigned int)1431655766, (unsigned int)1431655765,
  // (unsigned int)1431655765, (unsigned int)1835008}}; printf("\n!!!!!!!!\n");

  // print_decimal(res);
  // print_decimal(res2);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 1431655765);
  ck_assert_int_eq(res.bits[1], 1431655765);
  ck_assert_int_eq(res.bits[2], 1431655765);
  ck_assert_int_eq(res.bits[3], 1835008);
}
END_TEST

START_TEST(div_16_test) {
  s21_decimal num1 = {
      {(unsigned int)-1, (unsigned int)-1, (unsigned int)-1, 1835008}};
  s21_decimal num2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], (unsigned int)-2147483648);
  ck_assert_int_eq(res.bits[3], 1835008);
}
END_TEST

START_TEST(div_17_test) {
  s21_decimal num1 = {
      {(unsigned int)-1, (unsigned int)-1, (unsigned int)-1, 1835008}};
  s21_decimal num2 = {{4, 0, 0, (unsigned int)-2147483648}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 1073741824);
  ck_assert_int_eq(res.bits[3], (unsigned int)-2145648640);
}
END_TEST

START_TEST(div_18_test) {
  s21_decimal num1 = {{1, 1, 1, 1835008}};
  s21_decimal num2 = {{0, 0, 0, (unsigned int)-2147483648}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 3);
}
END_TEST

START_TEST(div_19_test) {
  s21_decimal num1 = {
      {(unsigned int)-1, (unsigned int)-1, (unsigned int)-1, 0}};
  s21_decimal num2 = {{1, 0, 0, 393216}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(div_20_test) {
  s21_decimal num1 = {{1, 0, 0, 1835008}};
  s21_decimal num2 = {{4, 0, 0, (unsigned int)-2147483648}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_div(num1, num2, &res);
  ck_assert_int_eq(status, 2);
}
END_TEST

START_TEST(div_big_error) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal result_our = {{0, 0, 0, 0}};

  src1.bits[0] = 0b11111111111111111111111111111110;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b11111111111111111111111111111111;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000111000000000000000000;
  int val = s21_div(src1, src2, &result_our);
  ck_assert_int_eq(val, 1);
}
END_TEST

START_TEST(div_error) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal src2 = {{0, 0, 0, 0}};
  s21_decimal *result_our = NULL;
  int val = s21_div(src1, src2, result_our);
  ck_assert_int_eq(val, 1);
}
END_TEST

// comparasion tests

START_TEST(not_equal_zero) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_is_not_equal(val1, val2), 0);
}
END_TEST

START_TEST(not_equal_dif_exp) {
  s21_decimal val1 = {{0, 0, 1, 393216}};
  s21_decimal val2 = {{0, 0, 1, 196608}};

  ck_assert_int_eq(s21_is_not_equal(val1, val2), 1);
}
END_TEST

START_TEST(not_equal_dif_sign) {
  s21_decimal val1 = {{0, 0, 1, (unsigned int)-65536}};
  s21_decimal val2 = {{0, 0, 1, 65536}};

  ck_assert_int_eq(s21_is_not_equal(val1, val2), 1);
}
END_TEST

START_TEST(not_equal_dif_mantissa) {
  s21_decimal val1 = {{4, 3, 2, 0}};  // 3.6893488160304E+19
  s21_decimal val2 = {{1, 3, 4, 0}};  // 7.3786976307723E+19

  ck_assert_int_eq(s21_is_not_equal(val1, val2), 1);
}
END_TEST

START_TEST(not_equal_neg_zero) {
  s21_decimal val1 = {{0, 0, 0, (unsigned int)-2147483647}};
  s21_decimal val2 = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_is_not_equal(val1, val2), 0);
}
END_TEST

// ----------------is equal----------------- //

START_TEST(equal_zero) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_is_equal(val1, val2), 1);
}
END_TEST

START_TEST(equal_dif_exp) {
  s21_decimal val1 = {{1, 0, 0, 393216}};  // 0.000001
  s21_decimal val2 = {{1, 0, 0, 196608}};  // 0.001

  ck_assert_int_eq(s21_is_equal(val1, val2), 0);
}
END_TEST

START_TEST(equal_dif_sign) {
  s21_decimal val1 = {{0, 0, 1, (unsigned int)-65536}};
  s21_decimal val2 = {{0, 0, 1, 65536}};

  ck_assert_int_eq(s21_is_equal(val1, val2), 0);
}
END_TEST

START_TEST(equal_dif_mantissa) {
  s21_decimal val1 = {{4, 3, 2, 0}};  // 3.6893488160304E+19
  s21_decimal val2 = {{1, 3, 4, 0}};  // 7.3786976307723E+19

  ck_assert_int_eq(s21_is_equal(val1, val2), 0);
}
END_TEST

START_TEST(equal_neg_zero) {
  s21_decimal val1 = {{0, 0, 0, (unsigned int)-2147483647}};  // -0
  s21_decimal val2 = {{0, 0, 0, 0}};                          // 0

  ck_assert_int_eq(s21_is_equal(val1, val2), 1);
}
END_TEST

START_TEST(equal_neg_zero_2) {
  s21_decimal val1 = {{0, 0, 0, (unsigned int)-2147483648}};
  s21_decimal val2 = {{0, 0, 0, (unsigned int)-2147483648}};

  ck_assert_int_eq(s21_is_equal(val1, val2), 1);
}
END_TEST

// ----------------is less----------------- //

START_TEST(less_zero) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_is_less(val1, val2), 0);
}
END_TEST

START_TEST(less_dif_exp) {
  s21_decimal val1 = {{1, 0, 0, 393216}};  // 0.000001
  s21_decimal val2 = {{1, 0, 0, 196608}};  // 0.001

  ck_assert_int_eq(s21_is_less(val1, val2), 1);
}
END_TEST

START_TEST(less_dif_sign) {
  s21_decimal val1 = {{0, 0, 1, (unsigned int)65536}};
  s21_decimal val2 = {{0, 0, 1, 65536}};

  ck_assert_int_eq(s21_is_less(val1, val2), 0);
}
END_TEST

START_TEST(less_dif_mantissa) {
  s21_decimal val1 = {{4, 3, 2, 0}};  // 3.6893488160304E+19
  s21_decimal val2 = {{1, 3, 4, 0}};  // 7.3786976307723E+19

  ck_assert_int_eq(s21_is_less(val1, val2), 1);
}
END_TEST

START_TEST(less_dif_sign_float) {
  s21_decimal val1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  s21_decimal val2 = {
      {12, 0, 0, 0b10000000000000010000000000000000}};  //  -1.2;

  ck_assert_int_eq(s21_is_less(val1, val2), 0);
}
END_TEST

START_TEST(less_dif_float) {
  s21_decimal val1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  s21_decimal val2 = {{12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2;

  ck_assert_int_eq(s21_is_less(val1, val2), 0);
}
END_TEST

START_TEST(less_dif_float_2) {
  s21_decimal val1 = {
      {12345, 0, 0, 0b00000000000000110000000000000000}};  //  12.345
  s21_decimal val2 = {
      {1122345, 0, 0, 0b00000000000001010000000000000000}};  //  11.22345

  ck_assert_int_eq(s21_is_less(val1, val2), 0);
}
END_TEST

START_TEST(less_dif_neg_float) {
  s21_decimal val1 = {
      {55555, 0, 0, 0b10000000000001000000000000000000}};  //  -5.5555
  s21_decimal val2 = {{65, 0, 0, 0b10000000000000010000000000000000}};  //  -6.5

  ck_assert_int_eq(s21_is_less(val1, val2), 0);
}
END_TEST

START_TEST(less_eq_neg_num) {
  s21_decimal val1 = {{123, 0, 0, (unsigned int)-2147483648}};
  s21_decimal val2 = {{123, 0, 0, (unsigned int)-2147483648}};

  ck_assert_int_eq(s21_is_less(val1, val2), 0);
}
END_TEST

START_TEST(less_eq_num) {
  s21_decimal val1 = {{123, 0, 0, 0}};
  s21_decimal val2 = {{123, 0, 0, 0}};

  ck_assert_int_eq(s21_is_less(val1, val2), 0);
}
END_TEST

START_TEST(less_neg_zero) {
  s21_decimal val1 = {{0, 0, 0, (unsigned int)-2147483648}};
  s21_decimal val2 = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_is_less(val1, val2), 0);
}
END_TEST

START_TEST(less_neg_zero_2) {
  s21_decimal val1 = {{0, 0, 0, (unsigned int)-2147483648}};
  s21_decimal val2 = {{0, 0, 0, (unsigned int)-2147483648}};

  ck_assert_int_eq(s21_is_less(val1, val2), 0);
}
END_TEST

// ----------------is less or eqeal----------------- //

START_TEST(less_or_eq_zero) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_is_less_or_equal(val1, val2), 1);
}
END_TEST

START_TEST(less_or_eq_dif_exp) {
  s21_decimal val1 = {{1, 0, 0, 393216}};  // 0.000001
  s21_decimal val2 = {{1, 0, 0, 196608}};  // 0.001

  ck_assert_int_eq(s21_is_less_or_equal(val1, val2), 1);
}
END_TEST

START_TEST(less_or_eq_dif_sign) {
  s21_decimal val1 = {{0, 0, 1, (unsigned int)-65536}};
  s21_decimal val2 = {{0, 0, 1, 65536}};

  ck_assert_int_eq(s21_is_less_or_equal(val1, val2), 1);
}
END_TEST

START_TEST(less_or_eq_dif_mantissa) {
  s21_decimal val1 = {{4, 3, 2, 0}};  // 3.6893488160304E+19
  s21_decimal val2 = {{1, 3, 4, 0}};  // 7.3786976307723E+19

  ck_assert_int_eq(s21_is_less_or_equal(val1, val2), 1);
}
END_TEST

// ----------------is greater or eqeal----------------- //

START_TEST(greater_or_eq_zero) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_is_greater_or_equal(val1, val2), 1);
}
END_TEST

START_TEST(greater_or_eq_dif_exp) {
  s21_decimal val1 = {{1, 0, 0, 393216}};  // 0.000001
  s21_decimal val2 = {{1, 0, 0, 196608}};  // 0.001

  ck_assert_int_eq(s21_is_greater_or_equal(val1, val2), 0);
}
END_TEST

START_TEST(greater_or_eq_dif_sign) {
  s21_decimal val1 = {{0, 0, 1, (unsigned int)65536}};
  s21_decimal val2 = {{0, 0, 1, 65536}};

  ck_assert_int_eq(s21_is_greater_or_equal(val1, val2), 1);
}
END_TEST

START_TEST(greater_or_eq_dif_mantissa) {
  s21_decimal val1 = {{4, 3, 2, 0}};  // 3.6893488160304E+19
  s21_decimal val2 = {{1, 3, 4, 0}};  // 7.3786976307723E+19

  ck_assert_int_eq(s21_is_greater_or_equal(val1, val2), 0);
}
END_TEST

// ----------------is greater----------------- //

START_TEST(greater_zero) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_is_greater(val1, val2), 0);
}
END_TEST

START_TEST(greater_dif_exp) {
  s21_decimal val1 = {{1, 0, 0, 393216}};  // 0.000001
  s21_decimal val2 = {{1, 0, 0, 196608}};  // 0.001

  ck_assert_int_eq(s21_is_greater(val1, val2), 0);
}
END_TEST

START_TEST(greater_dif_sign) {
  s21_decimal val1 = {{0, 0, 1, (unsigned int)-65536}};
  s21_decimal val2 = {{0, 0, 1, 65536}};

  ck_assert_int_eq(s21_is_greater(val1, val2), 0);
}
END_TEST

START_TEST(greater_dif_mantissa) {
  s21_decimal val1 = {{4, 3, 2, 0}};  // 3.6893488160304E+19
  s21_decimal val2 = {{1, 3, 4, 0}};  // 7.3786976307723E+19

  ck_assert_int_eq(s21_is_greater(val1, val2), 0);
}
END_TEST

START_TEST(greater_dif_sign_float) {
  s21_decimal val1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  s21_decimal val2 = {
      {12, 0, 0, 0b10000000000000010000000000000000}};  //  -1.2;

  ck_assert_int_eq(s21_is_greater(val1, val2), 1);
}
END_TEST

START_TEST(greater_dif_float) {
  s21_decimal val1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  s21_decimal val2 = {{12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2;

  ck_assert_int_eq(s21_is_greater(val1, val2), 1);
}
END_TEST

START_TEST(greater_dif_float_2) {
  s21_decimal val1 = {
      {12345, 0, 0, 0b00000000000000110000000000000000}};  //  12.345
  s21_decimal val2 = {
      {1122345, 0, 0, 0b00000000000001010000000000000000}};  //  11.22345

  ck_assert_int_eq(s21_is_greater(val1, val2), 1);
}
END_TEST

START_TEST(greater_dif_neg_float) {
  s21_decimal val1 = {
      {55555, 0, 0, 0b10000000000001000000000000000000}};  //  -5.5555
  s21_decimal val2 = {{65, 0, 0, 0b10000000000000010000000000000000}};  //  -6.5

  ck_assert_int_eq(s21_is_greater(val1, val2), 1);
}
END_TEST

START_TEST(greater_eq_neg_num) {
  s21_decimal val1 = {{123, 0, 0, (unsigned int)-2147483648}};
  s21_decimal val2 = {{123, 0, 0, (unsigned int)-2147483648}};

  ck_assert_int_eq(s21_is_greater(val1, val2), 0);
}
END_TEST

START_TEST(greater_eq_num) {
  s21_decimal val1 = {{123, 0, 0, 0}};
  s21_decimal val2 = {{123, 0, 0, 0}};

  ck_assert_int_eq(s21_is_greater(val1, val2), 0);
}
END_TEST

START_TEST(greater_neg_zero) {
  s21_decimal val1 = {{0, 0, 0, (unsigned int)-2147483647}};
  s21_decimal val2 = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_is_greater(val1, val2), 0);
}
END_TEST

START_TEST(greater_neg_zero_2) {
  s21_decimal val1 = {{0, 0, 0, (unsigned int)-2147483648}};
  s21_decimal val2 = {{0, 0, 0, (unsigned int)-2147483648}};

  ck_assert_int_eq(s21_is_greater(val1, val2), 0);
}
END_TEST

// negate tests

START_TEST(test_s21_negate_minus_1) {
  unsigned int test = 1;
  s21_decimal value = {{test, 0, 0, 0x80000000}};
  s21_decimal result = {{test, 0, 0, 0x00000000}};

  s21_negate(value, &value);
  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_s21_negate_plus_1) {
  unsigned int test = 1;
  s21_decimal value = {{test, 0, 0, 0x00000000}};
  s21_decimal result = {{test, 0, 0, 0x80000000}};

  s21_negate(value, &value);
  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_s21_negate_error) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal *result_our = NULL;
  int val = s21_negate(src1, result_our);
  ck_assert_int_eq(val, 1);
}
END_TEST

// truncate tests

START_TEST(test_s21_truncate_1) {
  s21_decimal src1, result_our, result_origin;
  src1.bits[0] = 123456;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0b00000000000000110000000000000000;
  int val = s21_truncate(src1, &result_our);

  result_origin.bits[0] = 123;
  result_origin.bits[1] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[3] = 0;
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(val, 0);
}
END_TEST

START_TEST(test_s21_truncate_2) {
  s21_decimal src1, result_our, result_origin;
  src1.bits[0] = 87654;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0b10000000000001000000000000000000;
  int val = s21_truncate(src1, &result_our);
  result_origin.bits[0] = 8;
  result_origin.bits[1] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(val, 0);
}
END_TEST

START_TEST(test_s21_truncate_3) {
  s21_decimal src1, result_our, result_origin;
  src1.bits[0] = 87654;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0b10000000000001010000000000000000;
  // print_decimal(src1);

  // printf("\n!!!!!!!!\n");
  int val = s21_truncate(src1, &result_our);
  result_origin.bits[0] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[3] = 0;
  //   printf("\n%d", val);
  //  print_decimal(result_our);
  // print_decimal(result_origin);
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(val, 0);
}
END_TEST

START_TEST(test_s21_truncate_error) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal *result_our = NULL;
  int val = s21_truncate(src1, result_our);
  ck_assert_int_eq(val, 1);
}
END_TEST

// rounf tests

START_TEST(test_s21_round_1) {
  s21_decimal src1, result_our, result_origin;
  src1.bits[0] = 123456;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0b00000000000000110000000000000000;
  int val = s21_round(src1, &result_our);

  result_origin.bits[0] = 123;
  result_origin.bits[1] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[3] = 0;
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(val, 0);
}
END_TEST

START_TEST(test_s21_round_2) {
  s21_decimal src1, result_our, result_origin;
  src1.bits[0] = 87654;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0b10000000000001000000000000000000;
  int val = s21_round(src1, &result_our);
  result_origin.bits[0] = 9;
  result_origin.bits[1] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(val, 0);
}
END_TEST

START_TEST(test_s21_round_3) {
  s21_decimal src1, result_our, result_origin;
  src1.bits[0] = 11;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0b10000000000000010000000000000000;
  int val = s21_round(src1, &result_our);
  result_origin.bits[0] = 1;
  result_origin.bits[1] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(val, 0);
}
END_TEST

START_TEST(test_s21_round_4) {
  s21_decimal src1, result_our, result_origin;
  src1.bits[0] = 23;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0b10000000000000110000000000000000;
  int val = s21_round(src1, &result_our);
  result_origin.bits[0] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[3] = 0;
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(val, 0);
}
END_TEST

START_TEST(test_s21_round_5) {
  s21_decimal src1, result_our, result_origin;
  src1.bits[0] = 53;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0b00000000000000100000000000000000;
  int val = s21_round(src1, &result_our);
  result_origin.bits[0] = 1;
  result_origin.bits[1] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[3] = 0;
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(val, 0);
}
END_TEST

START_TEST(test_s21_round_error) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal *result_our = NULL;
  int val = s21_round(src1, result_our);
  ck_assert_int_eq(val, 1);
}
END_TEST

// floor tests

START_TEST(test_s21_floor_minus_0) {
  s21_decimal src1, result_our, result_origin;
  src1.bits[0] = 0;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0b10000000000000000000000000000000;
  int val = s21_floor(src1, &result_our);

  result_origin.bits[0] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[3] = 0;
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(val, 0);
}
END_TEST

START_TEST(test_s21_floor_0) {
  s21_decimal src1, result_our, result_origin;
  src1.bits[0] = 0;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0b00000000000000000000000000000000;
  int val = s21_floor(src1, &result_our);

  result_origin.bits[0] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[3] = 0;
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(val, 0);
}
END_TEST

START_TEST(test_s21_floor_1) {
  s21_decimal src1, result_our, result_origin;
  src1.bits[0] = 123456;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0b00000000000000110000000000000000;
  int val = s21_floor(src1, &result_our);

  result_origin.bits[0] = 123;
  result_origin.bits[1] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[3] = 0;
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(val, 0);
}
END_TEST

START_TEST(test_s21_floor_2) {
  s21_decimal src1, result_our, result_origin;
  src1.bits[0] = 87654;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0b10000000000001000000000000000000;
  int val = s21_floor(src1, &result_our);
  result_origin.bits[0] = 9;
  result_origin.bits[1] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(val, 0);
}
END_TEST

START_TEST(test_s21_floor_3) {
  s21_decimal src1, result_our, result_origin;
  src1.bits[0] = 11;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0b10000000000000010000000000000000;
  int val = s21_floor(src1, &result_our);
  result_origin.bits[0] = 2;
  result_origin.bits[1] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(val, 0);
}
END_TEST

START_TEST(test_s21_floor_4) {
  s21_decimal src1, result_our, result_origin;
  src1.bits[0] = 23;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0b10000000000000110000000000000000;
  int val = s21_floor(src1, &result_our);
  result_origin.bits[0] = 1;
  result_origin.bits[1] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(val, 0);
}
END_TEST

START_TEST(test_s21_floor_5) {
  s21_decimal src1, result_our, result_origin;
  src1.bits[0] = 23;
  src1.bits[1] = 0;
  src1.bits[2] = 0;
  src1.bits[3] = 0b00000000000000110000000000000000;
  int val = s21_floor(src1, &result_our);
  result_origin.bits[0] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[3] = 0;
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(val, 0);
}
END_TEST

START_TEST(test_s21_floor_error) {
  s21_decimal src1 = {{0, 0, 0, 0}};
  s21_decimal *result_our = NULL;
  int val = s21_floor(src1, result_our);
  ck_assert_int_eq(val, 1);
}
END_TEST

// dec2float

START_TEST(test_s21_dec_to_float_003f) {
  s21_decimal result = {{0, 0, 0, 0}};
  float check = 0.f;
  float test = 0.03;

  result.bits[0] = 0b01001010111100011001001011000000;
  result.bits[1] = 0b00111001010010010101100101000000;
  result.bits[2] = 0b00000000111110000010011101111000;
  result.bits[3] = 0b00000000000111000000000000000000;
  int err = s21_from_decimal_to_float(result, &check);
  ck_assert_ldouble_eq_tol(check, test, 1e-6);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(test_s21_dec_to_float_18122f) {
  s21_decimal result = {{0, 0, 0, 0}};
  float check = 0.f;
  float test = 18.122;
  result.bits[0] = 18122;
  result.bits[1] = 0;
  result.bits[2] = 0;
  result.bits[3] = 0b00000000000000110000000000000000;
  int err = s21_from_decimal_to_float(result, &check);
  ck_assert_ldouble_eq_tol(check, test, 1e-6);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(test_s21_dec_to_float_m003f) {
  s21_decimal result = {{0, 0, 0, 0}};
  float check = 0.f;
  float test = -0.03;
  result.bits[0] = 0b01001010111100011001001011000000;
  result.bits[1] = 0b00111001010010010101100101000000;
  result.bits[2] = 0b00000000111110000010011101111000;
  result.bits[3] = 0b10000000000111000000000000000000;
  int err = s21_from_decimal_to_float(result, &check);
  ck_assert_ldouble_eq_tol(check, test, 1e-6);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(test_s21_dec_to_float_18_122f) {
  s21_decimal result = {{0, 0, 0, 0}};
  float check = 0.f;
  result.bits[0] = 18122;
  result.bits[1] = 0;
  result.bits[2] = 0;
  result.bits[3] = 0;
  s21_set_exp(&result, 3);

  int err = s21_from_decimal_to_float(result, &check);
  ck_assert_float_eq(check, 18.122);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(test_s21_dec_to_float_m1812) {
  s21_decimal result = {{0, 0, 0, 0}};
  float check = 0.f;
  result.bits[0] = 1812;
  result.bits[1] = 0;
  result.bits[2] = 0;
  result.bits[3] = 0b10000000000000000000000000000000;
  int err = s21_from_decimal_to_float(result, &check);
  ck_assert_float_eq(check, -1812);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(test_s21_dec_to_float_16777215f) {
  s21_decimal result = {{0, 0, 0, 0}};
  float check = 0.f;
  result.bits[0] = 0XFFFFFF;
  result.bits[1] = 0;
  result.bits[2] = 0;
  result.bits[3] = 0;
  int err = s21_from_decimal_to_float(result, &check);
  ck_assert_float_eq(check, 16777215);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(test_s21_dec_to_float_12345_6789f) {
  s21_decimal result = {{0, 0, 0, 0}};
  float check = 0.f;
  result.bits[0] = 123456789;
  result.bits[1] = 0;
  result.bits[2] = 0;
  result.bits[3] = 0;
  s21_set_exp(&result, 4);
  int err = s21_from_decimal_to_float(result, &check);
  ck_assert_float_eq(check, 12345.6789);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(test_s21_dec_to_float_UNIT_MAX) {
  s21_decimal result = {{0, 0, 0, 0}};
  float check = 0.f;
  result.bits[0] = 4294967295;
  result.bits[1] = 4294967295;
  result.bits[2] = 0;
  result.bits[3] = 0;
  int err = s21_from_decimal_to_float(result, &check);
  ck_assert_float_eq(check, 0xFFFFFFFFFFFFFFFF);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(test_s21_dec_to_float_m1234_5678f) {
  s21_decimal result = {{0, 0, 0, 0}};
  float check = 0.f;
  result.bits[0] = 123456789;
  result.bits[1] = 0;
  result.bits[2] = 0;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_set_exp(&result, 4);
  int err = s21_from_decimal_to_float(result, &check);
  ck_assert_float_eq(check, -12345.6789F);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(test_s21_dec_to_float_2546_5f) {
  s21_decimal result = {{0, 0, 0, 0}};
  float check = 0.f;
  result.bits[0] = 25465;
  result.bits[1] = 0;
  result.bits[2] = 0;
  result.bits[3] = 0b00000000000000010000000000000000;
  s21_from_decimal_to_float(result, &check);
  char flt2str[1000];
  char check_result[1000];
  snprintf(flt2str, sizeof(flt2str), "%.6f", 2546.5);
  snprintf(check_result, sizeof(result), "%f", check);
  ck_assert_str_eq(check_result, flt2str);
}
END_TEST

START_TEST(test_s21_dec_to_float_m0_46453f) {
  s21_decimal result = {{0, 0, 0, 0}};
  float check = 0.f;
  result.bits[0] = 46453;
  result.bits[1] = 0;
  result.bits[2] = 0;
  result.bits[3] = 0b10000000000001010000000000000000;
  s21_from_decimal_to_float(result, &check);
  char flt2str[1000];
  char check_result[1000];
  snprintf(flt2str, sizeof(flt2str), "%.6f", -0.46453);
  snprintf(check_result, sizeof(check_result), "%f", check);
  ck_assert_str_eq(check_result, flt2str);
}
END_TEST

START_TEST(test_s21_dec_to_float_3_5f) {
  s21_decimal result = {{0, 0, 0, 0}};
  float check = 0.f;
  result.bits[0] = 35;
  result.bits[1] = 0;
  result.bits[2] = 0;
  result.bits[3] = 0b00000000000000010000000000000000;
  s21_from_decimal_to_float(result, &check);
  char flt2str[1000];
  char check_result[1000];
  snprintf(flt2str, sizeof(flt2str), "%.6f", 3.5);
  snprintf(check_result, sizeof(check_result), "%f", check);
  ck_assert_str_eq(check_result, flt2str);
}
END_TEST

START_TEST(test_s21_dec_to_float_4_5f) {
  s21_decimal result = {{0, 0, 0, 0}};
  float check = 0.f;
  result.bits[0] = 45;
  result.bits[1] = 0;
  result.bits[2] = 0;
  result.bits[3] = 0b00000000000000010000000000000000;
  s21_from_decimal_to_float(result, &check);
  char flt2str[1000];
  char check_result[1000];
  snprintf(flt2str, sizeof(flt2str), "%.6f", 4.5);
  snprintf(check_result, sizeof(check_result), "%f", check);
  ck_assert_str_eq(check_result, flt2str);
}
END_TEST

START_TEST(test_s21_dec_to_float_m4_5f) {
  s21_decimal result = {{0, 0, 0, 0}};
  float check = 0.f;
  result.bits[0] = 0b00000000000000000000000000101101;
  result.bits[1] = 0;
  result.bits[2] = 0;
  result.bits[3] = 0b10000000000000010000000000000000;
  s21_from_decimal_to_float(result, &check);
  char flt2str[1000];
  char check_result[1000];
  snprintf(flt2str, sizeof(flt2str), "%.6f", -4.5);
  snprintf(check_result, sizeof(check_result), "%f", check);
  ck_assert_str_eq(check_result, flt2str);
}
END_TEST

START_TEST(test_s21_dec_to_float_m5_49265f) {
  s21_decimal result = {{0, 0, 0, 0}};
  float check = 0.f;
  result.bits[0] = 0b00000000000010000110000110010001;
  result.bits[1] = 0;
  result.bits[2] = 0;
  result.bits[3] = 0b10000000000001010000000000000000;
  s21_from_decimal_to_float(result, &check);
  char flt2str[1000];
  char check_result[1000];
  snprintf(flt2str, sizeof(flt2str), "%.6f", -5.49265);
  snprintf(check_result, sizeof(flt2str), "%f", check);
  ck_assert_str_eq(check_result, flt2str);
}
END_TEST

START_TEST(test_s21_dec_to_float_2_508f) {
  s21_decimal result = {{0, 0, 0, 0}};
  float check = 0.f;
  result.bits[0] = 0b01100101111011101101100101011111;
  result.bits[1] = 0b01011100001001010100001101000110;
  result.bits[2] = 0b00000000000000000000000000000001;
  result.bits[3] = 0b00000000000100110000000000000000;
  s21_from_decimal_to_float(result, &check);
  char flt2str[1000];
  char check_result[1000];
  snprintf(flt2str, sizeof(flt2str), "%.6f", 2.50865312689741);
  snprintf(check_result, sizeof(check_result), "%f", check);
  ck_assert_str_eq(check_result, flt2str);
}
END_TEST

START_TEST(test_s21_dec_to_float_m18_122f) {
  s21_decimal result = {{0, 0, 0, 0}};
  float check = 0.f;
  result.bits[0] = 18122;
  result.bits[1] = 0;
  result.bits[2] = 0;
  result.bits[3] = 2147680256;
  int err = s21_from_decimal_to_float(result, &check);
  ck_assert_float_eq(check, -18.122);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(test_s21_dec_to_float_m1812f) {
  s21_decimal result = {{0, 0, 0, 0}};
  float check = 0.f;
  result.bits[0] = 1812;
  result.bits[1] = 0;
  result.bits[2] = 0;
  result.bits[3] = 0b10000000000000000000000000000000;
  int err = s21_from_decimal_to_float(result, &check);
  ck_assert_float_eq(check, -1812);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(test_s21_dec_to_float_m2345_09) {
  s21_decimal result = {{0, 0, 0, 0}};
  float check = 0.f;
  result.bits[0] = 23450987;
  result.bits[1] = 0;
  result.bits[2] = 0;
  result.bits[3] = 2147745792;
  int err = s21_from_decimal_to_float(result, &check);
  ck_assert_float_eq_tol(check, -2345.09, 1e-1);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(test_s21_dec_to_float_UINT_MAX_UINT_MAX) {
  s21_decimal result = {{0, 0, 0, 0}};
  float check = 0.f;
  result.bits[0] = 4294967295;
  result.bits[1] = 4294967295;
  result.bits[2] = 0;
  result.bits[3] = 0;
  int err = s21_from_decimal_to_float(result, &check);
  ck_assert_float_eq(check, 0xFFFFFFFFFFFFFFFF);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(test_s21_dec_to_float_scale_error) {
  s21_decimal result = {{0, 0, 0, 0}};
  float check = 1.1f;
  // float test = 0.f;
  // result.bits[0] = 0b01001010111100011001001011000000;
  // result.bits[1] = 0b00111001010010010101100101000000;
  // result.bits[2] = 0b00000000111110000010011101111000;
  result.bits[3] = 0b10000000000111010000000000000000;
  int err = s21_from_decimal_to_float(result, &check);
  // ck_assert_ldouble_eq_tol(check, test, 1e-6);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_s21_dec_to_float_null_error) {
  float *check = NULL;
  s21_decimal test = {{
      0,
      0,
      0,
      0,
  }};
  int val = s21_from_decimal_to_float(test, check);
  ck_assert_int_eq(val, 1);
}
END_TEST

// dec2int

START_TEST(test_s21_decimal_to_int_0) {
  int test = 0;
  int result = 0;
  s21_decimal value = {{test, 0, 0, 0}};

  s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(test, result);
}
END_TEST

START_TEST(test_s21_decimal_to_int_1) {
  int test = 1;
  int result = 0;
  s21_decimal value = {{test, 0, 0, 0}};

  s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(test, result);
}
END_TEST

START_TEST(test_s21_decimal_to_int_1234567) {
  int test = 12345678;
  int result = 0;
  s21_decimal value = {{test, 0, 0, 0}};

  s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(test, result);
}
END_TEST

START_TEST(test_s21_decimal_to_int_max) {
  int test = 2147483647;
  int result = 0;
  s21_decimal value = {{test, 0, 0, 0}};

  s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(test, result);
}
END_TEST

START_TEST(test_s21_decimal_to_int_max_scale_1) {
  int test = 2147483647 / 10;
  int result = 0;
  s21_decimal value = {{0, 0, 0, 0}};
  s21_zero_s21_decimal(&value);
  value.bits[0] = 0b01111111111111111111111111111111;
  value.bits[1] = 0b00000000000000000000000000000000;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b00000000000000010000000000000000;

  s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(test, result);
}
END_TEST

START_TEST(test_s21_decimal_to_int_max_scale_10) {
  int test = 2;
  int result = 0;
  s21_decimal value = {{0, 0, 0, 0}};
  s21_zero_s21_decimal(&value);
  value.bits[0] = 0b11111111111111111111111111110110;
  value.bits[1] = 0b00000000000000000000000000000100;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b00000000000010100000000000000000;

  s21_from_decimal_to_int(value, &result);

  ck_assert_int_eq(test, result);
}
END_TEST

START_TEST(test_s21_decimal_to_int_max_scale_28) {
  int test = 7;
  int result = 0;
  s21_decimal value = {{0, 0, 0, 0}};
  s21_zero_s21_decimal(&value);
  for (int i = 0; i < 96; i++) {
    s21_set_bit(&value, i, 1);
  }
  value.bits[3] = 0b00000000000111000000000000000000;

  s21_from_decimal_to_int(value, &result);

  ck_assert_int_eq(test, result);
}
END_TEST

START_TEST(test_s21_decimal_to_int_max_scale_29_error) {
  int result = 0;
  s21_decimal value = {{0, 0, 0, 0}};
  s21_zero_s21_decimal(&value);
  value.bits[0] = 0b11111111111111111111111111111111;
  value.bits[1] = 0b00000111111111111111111111111111;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b00000000000111010000000000000000;

  int status = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_s21_decimal_to_int_minus_1) {
  int test = -1;
  int result = 0;
  s21_decimal value = {{-test, 0, 0, 0x80000000}};

  s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(test, result);
}
END_TEST

START_TEST(test_s21_decimal_to_int_minus_1234567) {
  int test = -1234567;
  int result = 0;
  s21_decimal value = {{-test, 0, 0, 0x80000000}};

  s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(test, result);
}
END_TEST

START_TEST(test_s21_decimal_to_int_min_plus_1) {
  int test = -2147483648 + 1;
  int result = 0;
  s21_decimal value = {{-test, 0, 0, 0x80000000}};

  s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(test, result);
}
END_TEST

START_TEST(test_s21_decimal_to_int_min_plus_1_scale_1) {
  int test = -429496729;
  int result = 0;
  s21_decimal value = {{0, 0, 0, 0}};
  s21_zero_s21_decimal(&value);
  value.bits[0] = 0b11111111111111111111111111111110;
  value.bits[1] = 0b00000000000000000000000000000000;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b10000000000000010000000000000000;

  s21_from_decimal_to_int(value, &result);

  ck_assert_int_eq(test, result);
}
END_TEST

START_TEST(test_s21_decimal_to_int_min_plus_1_scale_10) {
  int test = -219;
  int result = 0;
  s21_decimal value = {{0, 0, 0, 0}};
  s21_zero_s21_decimal(&value);
  value.bits[0] = 0b11111111111111111111111111111111;
  value.bits[1] = 0b00000000000000000000000111111111;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b10000000000010100000000000000000;

  s21_from_decimal_to_int(value, &result);

  ck_assert_int_eq(test, result);
}
END_TEST

START_TEST(test_s21_decimal_to_int_min_plus_1_scale_28) {
  int test = -7;
  int result = 0;
  s21_decimal value = {{0, 0, 0, 0}};
  s21_zero_s21_decimal(&value);
  for (int i = 0; i < 96; i++) {
    s21_set_bit(&value, i, 1);
  }
  value.bits[3] = 0b10000000000111000000000000000000;

  s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(test, result);
}
END_TEST

START_TEST(test_s21_decimal_to_int_min_plus_1_scale_29_error) {
  int result = 0;
  s21_decimal value = {{0, 0, 0, 0}};
  s21_zero_s21_decimal(&value);
  value.bits[0] = 0b11111111111111111111111111111111;
  value.bits[1] = 0b00000111111111111111111111111111;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b10000000000111010000000000000000;

  int status = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_s21_decimal_to_int_big_number_error) {
  int result = 0;
  s21_decimal value = {{0, 0, 0, 0}};
  s21_zero_s21_decimal(&value);
  value.bits[0] = 0b00000000000000000000000000000000;
  value.bits[1] = 0b00000000000000000000000000000000;
  value.bits[2] = 0b00000001000000000000000000000000;
  value.bits[3] = 0b00000000000000000000000000000000;

  int status = s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_s21_decimal_to_int_null_error) {
  int *check = NULL;
  s21_decimal test = {{
      0,
      0,
      0,
      0,
  }};
  int val = s21_from_decimal_to_int(test, check);
  ck_assert_int_eq(val, 1);
}
END_TEST

START_TEST(test_s21_decimal_to_int_min) {
  int test = -2147483647;
  int result = 0;
  s21_decimal value = {
      {(unsigned int)2147483647, 0, 0, 0b10000000000000000000000000000000}};
  s21_from_decimal_to_int(value, &result);
  ck_assert_int_eq(test, result);
}
END_TEST

// float2dec

START_TEST(test_s21_from_float_to_decimal_003f) {
  s21_decimal value;
  s21_from_float_to_decimal(0.03F, &value);
  ck_assert_int_eq(value.bits[0], 3);
  ck_assert_int_eq(value.bits[1], 0);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq(value.bits[3], 0b00000000000000100000000000000000);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_m003f) {
  s21_decimal value;
  s21_from_float_to_decimal(-0.03F, &value);
  ck_assert_int_eq(value.bits[0], 3);
  ck_assert_int_eq(value.bits[1], 0);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq((unsigned)value.bits[3], 0b10000000000000100000000000000000);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_30f) {
  s21_decimal value;
  s21_from_float_to_decimal(3.0F, &value);
  ck_assert_int_eq(value.bits[0], 3);
  ck_assert_int_eq(value.bits[1], 0);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq(value.bits[3], 0);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_m30f) {
  s21_decimal value;
  s21_from_float_to_decimal(-3.0F, &value);
  ck_assert_int_eq(value.bits[0], 3);
  ck_assert_int_eq(value.bits[1], 0);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq((unsigned)value.bits[3], 0b10000000000000000000000000000000);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_0f) {
  s21_decimal value;
  s21_from_float_to_decimal(0.0F, &value);
  ck_assert_int_eq(value.bits[0], 0);
  ck_assert_int_eq(value.bits[1], 0);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq(value.bits[3], 0);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_105f) {
  s21_decimal value;
  s21_from_float_to_decimal(10.5F, &value);
  ck_assert_int_eq(value.bits[0], 105);
  ck_assert_int_eq(value.bits[1], 0);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq(value.bits[3], 65536);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_too_small) {
  s21_decimal value;
  int err = s21_from_float_to_decimal(1e-29F, &value);
  ck_assert_int_eq(value.bits[0], 0);
  ck_assert_int_eq(value.bits[1], 0);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq(value.bits[3], 0);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_div_mzero) {
  s21_decimal value;
  int err = s21_from_float_to_decimal(-1.0F / 0.0F, &value);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_div_zero) {
  s21_decimal value;
  int err = s21_from_float_to_decimal(1.0F / 0.0F, &value);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_small_num) {
  s21_decimal value;
  int err = s21_from_float_to_decimal(1.234567e-28F, &value);
  ck_assert_int_eq(value.bits[0], 1);
  ck_assert_int_eq(value.bits[1], 0);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq(value.bits[3], 1835008U);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_10209f) {
  s21_decimal value;
  s21_from_float_to_decimal(1.02E+09F, &value);
  ck_assert_int_eq(value.bits[0], 1020000000);
  ck_assert_int_eq(value.bits[1], 0);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq(value.bits[3], 0);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_NAN) {
  s21_decimal value;
  float nan_value = NAN;
  int err = s21_from_float_to_decimal(nan_value, &value);
  ck_assert_int_eq(err, 1);
  ck_assert_int_eq(value.bits[0], 0);
  ck_assert_int_eq(value.bits[1], 0);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq(value.bits[3], 0);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_12345678) {
  s21_decimal value;
  int err = s21_from_float_to_decimal(123456789.123456789F, &value);
  ck_assert_int_eq(value.bits[0], 123456800);
  ck_assert_int_eq(value.bits[1], 0);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq(value.bits[3], 0);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_00002f) {
  s21_decimal value;
  s21_from_float_to_decimal(0.000000002F, &value);
  ck_assert_int_eq(value.bits[0], 2);
  ck_assert_int_eq(value.bits[1], 0);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq(value.bits[3], 0b00000000000010010000000000000000);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_001f) {
  s21_decimal value;
  int err = s21_from_float_to_decimal(10000000000.000000001F, &value);
  ck_assert_int_eq(value.bits[0], 0b01010100000010111110010000000000);
  ck_assert_int_eq(value.bits[1], 0b00000000000000000000000000000010);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq(value.bits[3], 0);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_5454) {
  s21_decimal value;
  s21_from_float_to_decimal(-5454.353F, &value);
  ck_assert_int_eq(value.bits[0], 5454353);
  ck_assert_int_eq(value.bits[1], 0);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq((unsigned)value.bits[3], 0b10000000000000110000000000000000);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_m5492) {
  s21_decimal value;
  s21_from_float_to_decimal(-5.492654F, &value);
  ck_assert_int_eq(value.bits[0], 5492654);
  ck_assert_int_eq(value.bits[1], 0);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq((unsigned)value.bits[3], 0b10000000000001100000000000000000);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_7961) {
  s21_decimal value;
  s21_from_float_to_decimal(7.961328E+08F, &value);
  ck_assert_int_eq(value.bits[0], 796132800);
  ck_assert_int_eq(value.bits[1], 0);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq(value.bits[3], 0);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_m1234) {
  s21_decimal value;
  s21_from_float_to_decimal(-1.234568E+07F, &value);
  ck_assert_int_eq(value.bits[0], 12345680);
  ck_assert_int_eq(value.bits[1], 0);
  ck_assert_int_eq(value.bits[2], 0);
  ck_assert_int_eq((unsigned)value.bits[3], 0b10000000000000000000000000000000);
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_null_error) {
  float check = 0.f;
  s21_decimal *test = NULL;
  int val = s21_from_float_to_decimal(check, test);
  ck_assert_int_eq(val, 1);
}
END_TEST

// int2dec

START_TEST(test_s21_int_to_decimal_0) {
  int test = 0;
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal result = {{test, 0, 0, 0}};

  s21_from_int_to_decimal(test, &value);
  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_s21_int_to_decimal_1) {
  int test = 1;
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal result = {{test, 0, 0, 0}};

  s21_from_int_to_decimal(test, &value);
  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_s21_int_to_decimal_10) {
  int test = 10;
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal result = {{test, 0, 0, 0}};

  s21_from_int_to_decimal(test, &value);
  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_s21_int_to_decimal_1234567) {
  int test = 1234567;
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal result = {{test, 0, 0, 0}};

  s21_from_int_to_decimal(test, &value);
  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_s21_int_to_decimal_int_max) {
  int test = 2147483647;
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal result = {{test, 0, 0, 0}};

  s21_from_int_to_decimal(test, &value);
  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_s21_int_to_decimal_minus_1) {
  int test = -1;
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal result = {
      {-test, 0, 0, 0x80000000}};  // = 0x80000000 = -2147483648 = 2147483648

  // s21_init_decimal(&value);
  s21_from_int_to_decimal(test, &value);
  // result.bits[0] = 0b00000000000000000000000000000001;
  // result.bits[1] = 0b00000000000000000000000000000000;
  // result.bits[2] = 0b00000000000000000000000000000000;
  // result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_s21_int_to_decimal_minus_10) {
  int test = -10;
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal result = {{-test, 0, 0, 0x80000000}};

  // s21_init_decimal(&value);
  s21_from_int_to_decimal(test, &value);
  // result.bits[0] = 0b00000000000000000000000000001010;
  // result.bits[1] = 0b00000000000000000000000000000000;
  // result.bits[2] = 0b00000000000000000000000000000000;
  // result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_s21_int_to_decimal_minus_1234567) {
  int test = -1234567;
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal result = {{-test, 0, 0, 0x80000000}};

  // s21_init_decimal(&value);
  s21_from_int_to_decimal(test, &value);
  // result.bits[0] = 0b00000000000100101101011010000111;
  // result.bits[1] = 0b00000000000000000000000000000000;
  // result.bits[2] = 0b00000000000000000000000000000000;
  // result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_s21_int_to_decimal_int_min) {
  int test = -2147483647;
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal result = {{-test, 0, 0, 0x80000000}};

  // s21_init_decimal(&value);
  s21_from_int_to_decimal(test, &value);
  // result.bits[0] = 0b10000000000000000000000000000000;
  // result.bits[1] = 0b00000000000000000000000000000000;
  // result.bits[2] = 0b00000000000000000000000000000000;
  // result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(value.bits[0], result.bits[0]);
  ck_assert_int_eq(value.bits[1], result.bits[1]);
  ck_assert_int_eq(value.bits[2], result.bits[2]);
  ck_assert_int_eq(value.bits[3], result.bits[3]);
}
END_TEST

START_TEST(test_s21_int_max_to_decimal_to_int) {
  int test = 2147483647;
  int summary = 0;
  s21_decimal value = {{0, 0, 0, 0}};

  s21_from_int_to_decimal(test, &value);
  s21_from_decimal_to_int(value, &summary);
  s21_from_int_to_decimal(summary, &value);
  s21_from_decimal_to_int(value, &summary);
  s21_from_int_to_decimal(summary, &value);
  s21_from_decimal_to_int(value, &summary);
  s21_from_int_to_decimal(summary, &value);
  s21_from_decimal_to_int(value, &summary);
  s21_from_int_to_decimal(summary, &value);
  s21_from_decimal_to_int(value, &summary);
  s21_from_int_to_decimal(summary, &value);
  s21_from_decimal_to_int(value, &summary);
  ck_assert_int_eq(test, summary);
}
END_TEST

START_TEST(test_s21_int_to_decimal_null_error) {
  int check = 0;
  s21_decimal *test = NULL;
  int val = s21_from_int_to_decimal(check, test);
  ck_assert_int_eq(val, 1);
}
END_TEST

int main() {
  Suite *suite = suite_create(SUITE_NAME);
  TCase *tcase = tcase_create(TCASE_NAME);
  SRunner *srunner = srunner_create(suite);
  int nf;
  suite_add_tcase(suite, tcase);

  tcase_add_test(tcase, add_1_test);
  tcase_add_test(tcase, add_2_test);
  tcase_add_test(tcase, add_3_test);
  tcase_add_test(tcase, add_4_test);
  tcase_add_test(tcase, add_5_test);
  tcase_add_test(tcase, add_6_test);
  tcase_add_test(tcase, add_7_test);
  tcase_add_test(tcase, add_8_test);
  tcase_add_test(tcase, add_9_test);
  tcase_add_test(tcase, add_10_test);
  tcase_add_test(tcase, add_11_test);
  tcase_add_test(tcase, add_12_test);
  tcase_add_test(tcase, add_13_test);
  tcase_add_test(tcase, add_14_test);
  tcase_add_test(tcase, add_15_test);
  tcase_add_test(tcase, add_16_test);
  tcase_add_test(tcase, add_error);

  tcase_add_test(tcase, sub_1_test);
  tcase_add_test(tcase, sub_2_test);
  tcase_add_test(tcase, sub_3_test);
  tcase_add_test(tcase, sub_4_test);
  tcase_add_test(tcase, sub_5_test);
  tcase_add_test(tcase, sub_6_test);
  tcase_add_test(tcase, sub_7_test);
  tcase_add_test(tcase, sub_8_test);
  tcase_add_test(tcase, sub_9_test);
  tcase_add_test(tcase, sub_10_test);
  tcase_add_test(tcase, sub_11_test);
  tcase_add_test(tcase, sub_12_test);
  tcase_add_test(tcase, sub_13_test);
  tcase_add_test(tcase, sub_14_test);
  tcase_add_test(tcase, sub_error);

  tcase_add_test(tcase, mul_2x2);
  tcase_add_test(tcase, mul_24xminus6);
  tcase_add_test(tcase, mul_minus500xminus3);
  tcase_add_test(tcase, mul_minus2x5);
  tcase_add_test(tcase, mul_3x0point256);
  tcase_add_test(tcase, mul_9point213658xminus169point312846);
  tcase_add_test(tcase, mul_3point21x30point336);
  tcase_add_test(tcase, mul_minus3point2xminus0point3);
  tcase_add_test(tcase, mul_zero);
  tcase_add_test(tcase, mul_bigXfloat);
  tcase_add_test(tcase, mul_overflow_positive);
  tcase_add_test(tcase, mul_overflow_negative);
  tcase_add_test(tcase, mul_minusBigXminusBig);
  tcase_add_test(tcase, mul_normalXsmall);
  tcase_add_test(tcase, mul_floatXsmall);
  tcase_add_test(tcase, mul_smallXsmall);
  tcase_add_test(tcase, mul_bigXsmall);
  tcase_add_test(tcase, mul_error);

  tcase_add_test(tcase, div_1_test);
  tcase_add_test(tcase, div_2_test);
  tcase_add_test(tcase, div_3_test);
  tcase_add_test(tcase, div_4_test);
  tcase_add_test(tcase, div_5_test);
  tcase_add_test(tcase, div_6_test);
  tcase_add_test(tcase, div_7_test);
  tcase_add_test(tcase, div_8_test);
  tcase_add_test(tcase, div_9_test);
  tcase_add_test(tcase, div_10_test);
  tcase_add_test(tcase, div_11_test);
  tcase_add_test(tcase, div_12_test);
  tcase_add_test(tcase, div_13_test);
  tcase_add_test(tcase, div_14_test);
  tcase_add_test(tcase, div_15_test);
  tcase_add_test(tcase, div_16_test);
  tcase_add_test(tcase, div_17_test);
  tcase_add_test(tcase, div_18_test);
  tcase_add_test(tcase, div_19_test);
  tcase_add_test(tcase, div_20_test);
  tcase_add_test(tcase, div_big_error);
  tcase_add_test(tcase, div_error);

  tcase_add_test(tcase, not_equal_zero);
  tcase_add_test(tcase, not_equal_dif_exp);
  tcase_add_test(tcase, not_equal_dif_sign);
  tcase_add_test(tcase, not_equal_dif_mantissa);
  tcase_add_test(tcase, not_equal_neg_zero);
  tcase_add_test(tcase, equal_zero);
  tcase_add_test(tcase, equal_dif_exp);
  tcase_add_test(tcase, equal_dif_sign);
  tcase_add_test(tcase, equal_dif_mantissa);
  tcase_add_test(tcase, equal_neg_zero);
  tcase_add_test(tcase, equal_neg_zero_2);
  tcase_add_test(tcase, less_zero);
  tcase_add_test(tcase, less_dif_exp);
  tcase_add_test(tcase, less_dif_sign);
  tcase_add_test(tcase, less_dif_mantissa);
  tcase_add_test(tcase, less_dif_sign_float);
  tcase_add_test(tcase, less_dif_float);
  tcase_add_test(tcase, less_dif_float_2);
  tcase_add_test(tcase, less_dif_neg_float);
  tcase_add_test(tcase, less_eq_neg_num);
  tcase_add_test(tcase, less_eq_num);
  tcase_add_test(tcase, less_neg_zero);
  tcase_add_test(tcase, less_neg_zero_2);
  tcase_add_test(tcase, less_or_eq_zero);
  tcase_add_test(tcase, less_or_eq_dif_exp);
  tcase_add_test(tcase, less_or_eq_dif_sign);
  tcase_add_test(tcase, less_or_eq_dif_mantissa);
  tcase_add_test(tcase, greater_or_eq_zero);
  tcase_add_test(tcase, greater_or_eq_dif_exp);
  tcase_add_test(tcase, greater_or_eq_dif_sign);
  tcase_add_test(tcase, greater_or_eq_dif_mantissa);
  tcase_add_test(tcase, greater_zero);
  tcase_add_test(tcase, greater_dif_exp);
  tcase_add_test(tcase, greater_dif_sign);
  tcase_add_test(tcase, greater_dif_mantissa);
  tcase_add_test(tcase, greater_dif_sign_float);
  tcase_add_test(tcase, greater_dif_float);
  tcase_add_test(tcase, greater_dif_float_2);
  tcase_add_test(tcase, greater_dif_neg_float);
  tcase_add_test(tcase, greater_eq_neg_num);
  tcase_add_test(tcase, greater_eq_num);
  tcase_add_test(tcase, greater_neg_zero);
  tcase_add_test(tcase, greater_neg_zero_2);

  tcase_add_test(tcase, test_s21_negate_minus_1);
  tcase_add_test(tcase, test_s21_negate_plus_1);
  tcase_add_test(tcase, test_s21_negate_error);

  tcase_add_test(tcase, test_s21_truncate_1);
  tcase_add_test(tcase, test_s21_truncate_2);
  tcase_add_test(tcase, test_s21_truncate_3);
  tcase_add_test(tcase, test_s21_truncate_error);

  tcase_add_test(tcase, test_s21_round_1);
  tcase_add_test(tcase, test_s21_round_2);
  tcase_add_test(tcase, test_s21_round_3);
  tcase_add_test(tcase, test_s21_round_4);
  tcase_add_test(tcase, test_s21_round_5);
  tcase_add_test(tcase, test_s21_round_error);

  tcase_add_test(tcase, test_s21_floor_minus_0);
  tcase_add_test(tcase, test_s21_floor_0);
  tcase_add_test(tcase, test_s21_floor_1);
  tcase_add_test(tcase, test_s21_floor_2);
  tcase_add_test(tcase, test_s21_floor_3);
  tcase_add_test(tcase, test_s21_floor_4);
  tcase_add_test(tcase, test_s21_floor_5);
  tcase_add_test(tcase, test_s21_floor_error);

  tcase_add_test(tcase, test_s21_dec_to_float_003f);
  tcase_add_test(tcase, test_s21_dec_to_float_18122f);
  tcase_add_test(tcase, test_s21_dec_to_float_m003f);
  tcase_add_test(tcase, test_s21_dec_to_float_18_122f);
  tcase_add_test(tcase, test_s21_dec_to_float_m1812);
  tcase_add_test(tcase, test_s21_dec_to_float_16777215f);
  tcase_add_test(tcase, test_s21_dec_to_float_12345_6789f);
  tcase_add_test(tcase, test_s21_dec_to_float_UNIT_MAX);
  tcase_add_test(tcase, test_s21_dec_to_float_m1234_5678f);
  tcase_add_test(tcase, test_s21_dec_to_float_2546_5f);
  tcase_add_test(tcase, test_s21_dec_to_float_m0_46453f);
  tcase_add_test(tcase, test_s21_dec_to_float_3_5f);
  tcase_add_test(tcase, test_s21_dec_to_float_4_5f);
  tcase_add_test(tcase, test_s21_dec_to_float_m4_5f);
  tcase_add_test(tcase, test_s21_dec_to_float_m5_49265f);
  tcase_add_test(tcase, test_s21_dec_to_float_2_508f);
  tcase_add_test(tcase, test_s21_dec_to_float_m18_122f);
  tcase_add_test(tcase, test_s21_dec_to_float_m1812f);
  tcase_add_test(tcase, test_s21_dec_to_float_16777215f);
  tcase_add_test(tcase, test_s21_dec_to_float_m2345_09);
  tcase_add_test(tcase, test_s21_dec_to_float_UINT_MAX_UINT_MAX);
  tcase_add_test(tcase, test_s21_dec_to_float_scale_error);
  tcase_add_test(tcase, test_s21_dec_to_float_null_error);

  tcase_add_test(tcase, test_s21_decimal_to_int_0);
  tcase_add_test(tcase, test_s21_decimal_to_int_1);
  tcase_add_test(tcase, test_s21_decimal_to_int_1234567);
  tcase_add_test(tcase, test_s21_decimal_to_int_max);
  tcase_add_test(tcase, test_s21_decimal_to_int_max_scale_1);
  tcase_add_test(tcase, test_s21_decimal_to_int_max_scale_10);
  tcase_add_test(tcase, test_s21_decimal_to_int_max_scale_28);
  tcase_add_test(tcase, test_s21_decimal_to_int_max_scale_29_error);
  tcase_add_test(tcase, test_s21_decimal_to_int_minus_1);
  tcase_add_test(tcase, test_s21_decimal_to_int_minus_1234567);
  tcase_add_test(tcase, test_s21_decimal_to_int_min_plus_1);
  tcase_add_test(tcase, test_s21_decimal_to_int_min_plus_1_scale_1);
  tcase_add_test(tcase, test_s21_decimal_to_int_min_plus_1_scale_10);
  tcase_add_test(tcase, test_s21_decimal_to_int_min_plus_1_scale_28);
  tcase_add_test(tcase, test_s21_decimal_to_int_min_plus_1_scale_29_error);
  tcase_add_test(tcase, test_s21_decimal_to_int_big_number_error);
  tcase_add_test(tcase, test_s21_decimal_to_int_null_error);
  tcase_add_test(tcase, test_s21_decimal_to_int_min);

  tcase_add_test(tcase, test_s21_from_float_to_decimal_003f);
  tcase_add_test(tcase, test_s21_from_float_to_decimal_m003f);
  tcase_add_test(tcase, test_s21_from_float_to_decimal_30f);
  tcase_add_test(tcase, test_s21_from_float_to_decimal_m30f);
  tcase_add_test(tcase, test_s21_from_float_to_decimal_0f);
  tcase_add_test(tcase, test_s21_from_float_to_decimal_105f);
  tcase_add_test(tcase, test_s21_from_float_to_decimal_too_small);
  tcase_add_test(tcase, test_s21_from_float_to_decimal_div_mzero);
  tcase_add_test(tcase, test_s21_from_float_to_decimal_div_zero);
  tcase_add_test(tcase, test_s21_from_float_to_decimal_small_num);
  tcase_add_test(tcase, test_s21_from_float_to_decimal_10209f);
  tcase_add_test(tcase, test_s21_from_float_to_decimal_NAN);
  tcase_add_test(tcase, test_s21_from_float_to_decimal_12345678);
  tcase_add_test(tcase, test_s21_from_float_to_decimal_00002f);
  tcase_add_test(tcase, test_s21_from_float_to_decimal_001f);
  tcase_add_test(tcase, test_s21_from_float_to_decimal_5454);
  tcase_add_test(tcase, test_s21_from_float_to_decimal_m5492);
  tcase_add_test(tcase, test_s21_from_float_to_decimal_7961);
  tcase_add_test(tcase, test_s21_from_float_to_decimal_m1234);
  tcase_add_test(tcase, test_s21_from_float_to_decimal_null_error);

  tcase_add_test(tcase, test_s21_int_to_decimal_0);
  tcase_add_test(tcase, test_s21_int_to_decimal_1);
  tcase_add_test(tcase, test_s21_int_to_decimal_10);
  tcase_add_test(tcase, test_s21_int_to_decimal_1234567);
  tcase_add_test(tcase, test_s21_int_to_decimal_int_max);
  tcase_add_test(tcase, test_s21_int_to_decimal_minus_1);
  tcase_add_test(tcase, test_s21_int_to_decimal_minus_10);
  tcase_add_test(tcase, test_s21_int_to_decimal_minus_1234567);
  tcase_add_test(tcase, test_s21_int_to_decimal_int_min);
  tcase_add_test(tcase, test_s21_int_max_to_decimal_to_int);
  tcase_add_test(tcase, test_s21_int_to_decimal_null_error);

  srunner_run_all(srunner, CK_ENV);
  nf = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  return nf == 0 ? 0 : 1;
}
