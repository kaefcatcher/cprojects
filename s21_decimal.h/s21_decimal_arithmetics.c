#include "s21_decimal_arithmetics.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0;
  if (result) {
    int equal_signs = 0;
    s21_zero_s21_decimal(result);

    s21_big_decimal bvalue_1 = {0};
    s21_init_big(value_1, &bvalue_1);
    s21_big_decimal bvalue_2 = {0};
    s21_init_big(value_2, &bvalue_2);
    s21_big_decimal result_b = {0};

    s21_normalize_big(&bvalue_1, &bvalue_2);

    if (s21_get_sign(value_1) == s21_get_sign(value_2)) equal_signs = 1;

    if (equal_signs) {
      s21_sum_mantissa(&bvalue_1, &bvalue_2, &result_b);
      result_b.sign = bvalue_1.sign;
    } else {
      int s21_compare = s21_compare_mantis_big(&bvalue_1, &bvalue_2);
      if (s21_compare > 0) {
        s21_sub_mantis_big(bvalue_1, bvalue_2, &result_b);
        result_b.sign = bvalue_1.sign;
      } else if (s21_compare < 0) {
        s21_sub_mantis_big(bvalue_2, bvalue_1, &result_b);
        result_b.sign = bvalue_2.sign;
      }
    }

    result_b.exponenta = bvalue_1.exponenta;
    status = s21_big_to_s21decimal(result, &result_b);

  } else {
    status = 1;
  }
  return status;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0;
  if (result) {
    int equal_signs = 0;
    s21_zero_s21_decimal(result);
    s21_set_sign(&value_2, !s21_get_sign(value_2));

    s21_big_decimal bvalue_1 = {0};
    s21_init_big(value_1, &bvalue_1);
    s21_big_decimal bvalue_2 = {0};
    s21_init_big(value_2, &bvalue_2);
    s21_big_decimal result_b = {0};

    s21_normalize_big(&bvalue_1, &bvalue_2);

    if (s21_get_sign(value_1) == s21_get_sign(value_2)) equal_signs = 1;

    if (equal_signs) {
      s21_sum_mantissa(&bvalue_1, &bvalue_2, &result_b);
      result_b.sign = bvalue_1.sign;
    } else {
      int s21_compare = s21_compare_mantis_big(&bvalue_1, &bvalue_2);
      if (s21_compare > 0) {
        s21_sub_mantis_big(bvalue_1, bvalue_2, &result_b);
        result_b.sign = bvalue_1.sign;
      } else if (s21_compare < 0) {
        s21_sub_mantis_big(bvalue_2, bvalue_1, &result_b);
        result_b.sign = bvalue_2.sign;
      }
    }

    result_b.exponenta = bvalue_1.exponenta;
    status = s21_big_to_s21decimal(result, &result_b);

  } else {
    status = 1;
  }
  return status;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0;
  if (result) {
    int equal_signs = 0;

    s21_zero_s21_decimal(result);

    s21_big_decimal bvalue_1 = {0};
    s21_init_big(value_1, &bvalue_1);
    s21_big_decimal bvalue_2 = {0};
    s21_init_big(value_2, &bvalue_2);
    s21_big_decimal result_b = {0};

    if (s21_get_sign(value_1) == s21_get_sign(value_2)) equal_signs = 1;

    if (s21_multiply_mantis_big(bvalue_1, &bvalue_2, &result_b)) status = 1;

    if (equal_signs) {
      result_b.sign = 0;
    } else {
      result_b.sign = 1;
    }

    s21_zeroes_left_big(&result_b);
    if (result_b.one_position_left == -1) {
      result_b.sign = 0;
      result_b.exponenta = 0;
    }

    if (!status) status = s21_big_to_s21decimal(result, &result_b);

  } else {
    status = 1;
  }
  return status;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0;
  int zero1 = 0;
  if (!s21_is_zero_s21_decimal(value_1)) zero1 = 1;

  if (result) {
    s21_zero_s21_decimal(result);

    if (s21_is_zero_s21_decimal(value_2)) {
      s21_big_decimal bvalue1 = {0}, bvalue2 = {0}, b_result = {0};
      s21_init_big(value_1, &bvalue1);
      s21_init_big(value_2, &bvalue2);

      s21_division(bvalue1, bvalue2, &b_result);

      if (s21_get_sign(value_1) != s21_get_sign(value_2)) b_result.sign = 1;
      if (!status) status = s21_big_to_s21decimal(result, &b_result);

    } else {
      status = 3;
    }
    if (status || zero1) s21_zero_s21_decimal(result);
  } else {
    status = 1;
  }
  return status;
}