#include "s21_other.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int status = 0;
  if (result) {
    *result = value;
    s21_set_sign(result, !s21_get_sign(value));
  } else {
    status = 1;
  }
  return status;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int status = 0;
  if (result) {
    s21_zero_s21_decimal(result);
    s21_big_decimal bvalue = {0};
    s21_init_big(value, &bvalue);
    s21_big_decimal ten = {0};
    ten.bits[0] = 10;
    while ((bvalue.exponenta > 0) &&
           s21_is_greater_or_equal_big_decimal(bvalue, ten)) {
      s21_division_with_rest_for10(bvalue, &bvalue);
    }
    if (bvalue.exponenta > 0 &&
        !s21_is_greater_or_equal_big_decimal(bvalue, ten))
      s21_zero_big_decimal(&bvalue);
    else if (!status)
      s21_big_to_s21decimal(result, &bvalue);
  } else {
    status = 1;
  }

  return status;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int status = 0;
  if (result) {
    s21_zero_s21_decimal(result);
    s21_decimal s21_one = {{1, 0, 0, 0}};
    s21_decimal s21_half = {{2, 0, 0, 0}};
    s21_decimal s21_trunc = {{0, 0, 0, 0}};
    int sign = s21_get_sign(value);

    s21_div(s21_one, s21_half, &s21_half);

    s21_set_sign(&value, 0);

    s21_truncate(value, result);
    s21_sub(value, *result, &s21_trunc);

    if (s21_is_less(s21_half, s21_trunc)) {
      s21_add(*result, s21_one, result);
    }

    if (sign) {
      s21_set_sign(result, 1);
    }

    if (!result->bits[0] && !result->bits[1] && !result->bits[2]) {
      s21_set_sign(result, 0);
    }
  } else {
    status = 1;
  }

  return status;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int status = 0;
  if (result) {
    s21_zero_s21_decimal(result);
    s21_decimal s21_one = {{1, 0, 0, 0}};
    s21_decimal s21_trunc = {{0, 0, 0, 0}};

    s21_truncate(value, &s21_trunc);

    s21_sub(value, s21_trunc, result);

    if (s21_get_sign(*result)) {
      s21_sub(s21_trunc, s21_one, result);
    } else {
      *result = s21_trunc;
    }

    if (!result->bits[0] && !result->bits[1] && !result->bits[2])
      s21_set_sign(result, 0);

  } else {
    status = 1;
  }

  return status;
}