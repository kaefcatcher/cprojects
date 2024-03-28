#include "s21_cast.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>
#define INT_MAX 2147483647

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int status = SUCCESS;

  if (dst) {
    s21_zero_s21_decimal(dst);
    dst->bits[0] = abs(src);
    if (src < 0) {
      s21_set_sign(dst, 1);
    }
  } else {
    status = FAIL;
  }

  return status;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int res = 0;
  if (dst) {
    *dst = 0;
    int exp = s21_get_exp(src);
    s21_big_decimal full = {0};
    int special_case = 0;
    s21_init_big(src, &full);
    if (exp) {
      for (int i = 0; i < exp; i++) {
        s21_division_with_rest_for10(full, &full);
      }
    }
    s21_zeroes_left_big(&full);
    if (full.one_position_left > 30) res = 1;
    if (full.one_position_left == 31 && full.sign == 1) {
      int all_zeros = 1;
      for (int i = 30; i >= 0; i--) {
        if (s21_get_bit_big(&full, i)) {
          all_zeros = 0;
          break;
        }
      }
      if (all_zeros) {
        res = 0;
        special_case = 1;
        *dst = -INT_MAX;
      }
    }
    int bit = 0;
    for (int i = 30; i >= 0; i--) {
      bit = s21_get_bit_big(&full, i);
      *dst = *dst | bit << i;
    }
    if (full.sign == 1) {
      if (!special_case) *dst = ~(*dst) + 1;
    }
    if (exp > 28) res = 1;
  } else
    res = 1;
  return res;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int status = SUCCESS;

  if (dst) {
    s21_zero_s21_decimal(dst);
  } else {
    status = FAIL;
  }

  if (status || (0 < fabsf(src) && fabsf(src) < 1e-28) || isnan(src) ||
      isinf(src) || 79228162514264337593543950335.f < src) {
    status = FAIL;
  } else {
    char part[128] = {0};
    int scale = 0;
    int decimal_part = 0;
    int length = 0;
    sprintf(part, "%.7g", src);
    s21_get_float_part(part, &scale, &length, &decimal_part);
    if (scale < 0 && 28 < abs(scale) + length) {
      memset(part, 0, 128);

      sprintf(part, "%.*g", 29 - abs(scale), src);
      s21_get_float_part(part, &scale, &length, &decimal_part);
    }
    int number = abs(atoi(part));
    for (int i = 0; i < length; ++i) {
      number *= 10;
    }
    number += decimal_part;
    if (src < 0) {
      s21_set_sign(dst, 1);
    }
    if (scale < 0) {
      s21_set_exp(dst, abs(scale) + length);
    } else if (!scale) {
      s21_set_exp(dst, length);
    }
    for (int i = 0; number; ++i, number /= 2) {
      if (number % 2) {
        s21_set_bit(dst, i, 1);
      }
    }
    if (0 < scale - length) {
      s21_decimal s21_mul_by_10 = {{10, 0, 0, 0}};
      for (int i = 0; !status && i < scale - length; ++i) {
        status = s21_mul(*dst, s21_mul_by_10, dst);
      }
    }
  }

  return status;
}

void s21_get_float_part(char *part, int *scale, int *length,
                        int *decimal_part) {
  char *dot = strchr(part, '.');
  char *exponenta = strchr(part, 'e');

  *scale = 0;
  *decimal_part = 0;
  *length = 0;
  if (exponenta) {
    *exponenta++ = '\0';
    *scale = atoi(exponenta);
  }
  if (dot) {
    *dot++ = '\0';
    *length = strlen(dot);
    *decimal_part = atoi(dot);
  }
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int status = SUCCESS;
  unsigned int scale = s21_get_exp(src);

  if (!dst || 28 < scale) {
    status = FAIL;
  } else {
    *dst = 0.f;
    for (int i = 0; i < 96; ++i) {
      if (s21_get_bit(src, i)) {
        *dst += powf(2, i);
      }
    }
    *dst /= powf(10, scale);
    if (s21_get_sign(src)) {
      *dst *= -1;
    }
  }

  return status;
}
