#include "s21_decimal_helper.h"

#include <math.h>
#include <stdlib.h>

unsigned int s21_int_to_bin(unsigned int k) {
  return (k == 0 || k == 1 ? k : ((k % 2) + 10 * s21_int_to_bin(k / 2)));
}

int s21_get_part(int bit) { return (int)(bit / 32); }

unsigned int s21_get_bit(s21_decimal dnum, int bit) {
  unsigned int working_bits;
  working_bits = dnum.bits[s21_get_part(bit)];
  bit = bit - s21_get_part(bit) * 32;
  return ((working_bits & (1 << bit)) >> bit);
}

void s21_set_bit(s21_decimal *dnum, int bit, int value) {
  int index = s21_get_part(bit);
  int bit_position = bit % 32;
  if (value == 1) {
    dnum->bits[index] |= (1 << bit_position);
  } else {
    dnum->bits[index] &= ~(1 << bit_position);
  }
}

int s21_get_exp_in_bin(s21_decimal dnum) {
  unsigned int buffer = 0b11111111;
  return s21_int_to_bin(((buffer << 15) & dnum.bits[3]) >> 15);
}

int s21_get_exp(s21_decimal dnum) {
  int mask = 0b11111111;
  mask <<= 16;
  mask = dnum.bits[3] & mask;
  mask >>= 16;
  return mask;
}

int s21_set_exp(s21_decimal *num, int exp) {
  int result = 0;
  if (exp < 256 && exp >= 0) {
    for (int i = 0; i < 8; i++) {
      s21_set_bit(num, i + 16 + 96, exp % 2);
      exp >>= 1;
    }
  } else {
    result = 1;
  }
  return result;
}

void s21_shift_left(s21_decimal *number) {
  unsigned int low_last_bit = s21_get_bit(*number, 31);
  unsigned int mid_last_bit = s21_get_bit(*number, 63);

  number->bits[0] <<= 1;
  number->bits[1] <<= 1;
  number->bits[2] <<= 1;

  s21_set_bit(number, 32, low_last_bit);
  s21_set_bit(number, 64, mid_last_bit);
}

void s21_shift_right(s21_decimal *number) {
  int low_last_bit = s21_get_bit(*number, 32);
  int mid_last_bit = s21_get_bit(*number, 64);

  number->bits[0] >>= 1;
  number->bits[1] >>= 1;
  number->bits[2] >>= 1;

  s21_set_bit(number, 31, low_last_bit);
  s21_set_bit(number, 63, mid_last_bit);
}

int s21_get_sign(s21_decimal dnum) { return s21_get_bit(dnum, 127); }
void s21_set_sign(s21_decimal *dnum, int sign) { s21_set_bit(dnum, 127, sign); }

int s21_compare(unsigned int a, unsigned int b) {
  unsigned int fb = 1 << (sizeof(a) * 8 - 1);

  while (!((a ^ b) & fb)) {
    a <<= 1;
    b <<= 1;
    if (!a && !b) return 0;
  }
  if (a & fb)
    return 1;
  else
    return -1;
}

int s21_get_bit_big(s21_big_decimal *num, int cur_bit) {
  int bit;
  if ((num->bits[cur_bit / 32] & (1 << cur_bit % 32)) == 0) {
    bit = 0;
  } else {
    bit = 1;
  }

  return bit;
}

void s21_set_bit_big(s21_big_decimal *num, int bit, int result) {
  if (result == 1) {
    num->bits[bit / 32] = num->bits[bit / 32] | (1 << bit % 32);
  } else if (result == 0) {
    num->bits[bit / 32] = num->bits[bit / 32] & ~(1 << bit % 32);
  }
}

unsigned int s21_division_with_rest_for10(s21_big_decimal val1,
                                          s21_big_decimal *res) {
  s21_big_decimal val2 = {0};
  val2.bits[0] = 10;
  s21_zeroes_left_big(&val2);
  int q = 0;
  s21_big_decimal part = {0};
  s21_big_decimal part_next = {0};
  s21_big_decimal sum = {0};
  s21_big_decimal before_sum = {0};
  while (s21_is_zero_big_decimal(val1) &&
         s21_is_greater_or_equal_big_decimal(val1, val2)) {
    q = 0;
    s21_zero_big_decimal(&part);
    s21_zero_big_decimal(&before_sum);
    part_next = val2;
    part = val2;
    s21_zeroes_left_big(&val1);
    while (s21_is_greater_or_equal_big_decimal(val1, part_next)) {
      if (q == 0) {
        int difference_elder_bit =
            val1.one_position_left - val2.one_position_left;
        if (difference_elder_bit > 2) {
          q = difference_elder_bit - 1;
          s21_shift_left_big(&part_next, q);
        }
      }
      part = part_next;
      s21_shift_left_big(&part_next, 1);
      q++;
    }
    q--;
    s21_set_bit_big(&before_sum, q, 1);
    s21_sum_mantissa(&sum, &before_sum, &sum);
    if (s21_is_greater_or_equal_big_decimal(val1, part))
      s21_sub_mantis_big(val1, part, &val1);
  }

  sum.exponenta = val1.exponenta - 1;
  sum.sign = val1.sign;
  *res = sum;
  return val1.bits[0];
}

int s21_big_to_s21decimal(s21_decimal *result, s21_big_decimal *result_big) {
  int status = 0;
  s21_zeroes_left_big(result_big);
  s21_big_decimal ten = {0};
  ten.bits[0] = 10;
  int diff = 0;
  s21_big_decimal copy_result_big_x = *result_big;
  while (result_big->exponenta > 28) {
    if (s21_compare_mantis_big(result_big, &ten) >= 0) {
      s21_division_with_rest_for10(*result_big, result_big);
      diff++;
    } else {
      status = 2;
      s21_zero_s21_decimal(result);
      break;
    }
  }
  if (!status) {
    if (diff > 0) s21_bank_round(copy_result_big_x, result_big, diff);

    diff = 0;
    if (s21_go_beyond_big_decimal_s21(result_big)) {
      if (result_big->exponenta < 1) {
        status = 1;
      } else {
        copy_result_big_x = *result_big;
        while (s21_go_beyond_big_decimal_s21(result_big) &&
               (result_big->exponenta > 0)) {
          s21_division_with_rest_for10(*result_big, result_big);
          diff++;
        }
        if (diff > 0) s21_bank_round(copy_result_big_x, result_big, diff);
      }
    }

    if (s21_go_beyond_big_decimal_s21(result_big)) status = 1;

    if ((status == 1) && result_big->sign) status = 2;

    if (!status) {
      if (result_big->sign) s21_set_sign(result, 1);
      s21_big_to_s21decimal_95(result_big, result);
      s21_set_exp(result, result_big->exponenta);
    }
  }
  return status;
}

void s21_bank_round(s21_big_decimal copy_result_big_x,
                    s21_big_decimal *result_big, int exp_diff) {
  s21_big_decimal one = {0};
  one.bits[0] = 1;
  s21_big_decimal ostatok_xy = {0};
  s21_big_decimal half = {0};
  half.bits[0] = 5;
  half.exponenta = 1;

  if (exp_diff > 0) exp_diff--;
  s21_big_decimal copy_result_big_y = *result_big;
  s21_normalize_big(&copy_result_big_x, &copy_result_big_y);

  s21_sub_mantis_big(copy_result_big_x, copy_result_big_y, &ostatok_xy);
  ostatok_xy.sign = 0;
  s21_multiply_10_mantis_big(&half, exp_diff);

  int compare_res = s21_compare_mantis_big(&ostatok_xy, &half);
  if (compare_res == 1) {
    s21_sum_mantissa(result_big, &one, result_big);
  } else if (compare_res == 0) {
    if (s21_get_bit_big(result_big, 0) == 1)
      s21_sum_mantissa(result_big, &one, result_big);
  }
}

int s21_go_beyond_big_decimal_s21(s21_big_decimal *big) {
  int result = 0;
  for (int i = 3; i < 8; i++) {
    if (big->bits[i] != 0) {
      result = 1;
      break;
    }
  }

  return result;
}

void s21_zero_s21_decimal(s21_decimal *value) {
  value->bits[0] = value->bits[1] = value->bits[2] = value->bits[3] = 0;
}

int s21_is_greater_or_equal_big_decimal(s21_big_decimal value_1,
                                        s21_big_decimal value_2) {
  int result = 1;
  for (int i = 7; i >= 0; i--) {
    if (value_1.bits[i] > value_2.bits[i]) {
      result = 1;
      break;
    } else if (value_1.bits[i] < value_2.bits[i]) {
      result = 0;
      break;
    }
  }
  return result;
}

int is_greater_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2) {
  int result = 0, out = 0;
  for (int i = 7; i >= 0 && !result && !out; i--) {
    if (value_1.bits[i] || value_2.bits[i]) {
      if (value_1.bits[i] > value_2.bits[i]) {
        result = 1;
      }
      if (value_1.bits[i] != value_2.bits[i]) out = 1;
    }
  }
  return result;
}

int s21_is_zero_big_decimal(s21_big_decimal big) {
  int result = 0;
  for (int i = 7; i >= 0; i--) {
    if (big.bits[i] != 0) {
      result = 1;
      break;
    }
  }
  return result;
}

int s21_is_zero_s21_decimal(s21_decimal value) {
  int res = 0;
  for (int i = 2; i >= 0; i--) {
    if (value.bits[i] != 0) {
      res = 1;
      break;
    }
  }
  return res;
}

void s21_sub_mantis_big(s21_big_decimal value_1, s21_big_decimal value_2,
                        s21_big_decimal *result) {
  int tmp = 0, res = 0;
  for (int i = 0; i <= 255; i++) {
    res = s21_get_bit_big(&value_1, i) - s21_get_bit_big(&value_2, i) - tmp;
    tmp = res < 0;
    res = abs(res);
    s21_set_bit_big(result, i, res % 2);
  }
}

int s21_multiply_10_mantis_big(s21_big_decimal *bvalue, int def) {
  int status = 0;

  s21_decimal ten_s = {0};
  s21_from_int_to_decimal(10, &ten_s);
  s21_big_decimal ten = {0};
  s21_init_big(ten_s, &ten);

  for (int i = 1; i <= def; i++) {
    if (s21_multiply_mantis_big(*bvalue, &ten, bvalue)) status = 1;
  }
  bvalue->exponenta += def;
  return status;
}

int s21_compare_mantis_big(s21_big_decimal *bvalue1, s21_big_decimal *bvalue2) {
  int result = 0;
  for (int i = 255; i >= 0; i--) {
    int rvalue1 = 0, rvalue2 = 0;
    rvalue1 = s21_get_bit_big(bvalue1, i);
    rvalue2 = s21_get_bit_big(bvalue2, i);
    if (rvalue1 != rvalue2) {
      result = rvalue1 - rvalue2;
      break;
    }
  }
  return result;
}

void s21_big_to_s21decimal_95(s21_big_decimal *result_big,
                              s21_decimal *result) {
  for (int i = 0; i < 3; i++) {
    result->bits[i] = result_big->bits[i];
  }
}

int s21_sum_mantissa(s21_big_decimal *bvalue_1, s21_big_decimal *bvalue_2,
                     s21_big_decimal *result) {
  int status = 0;
  int tmp = 0;
  int var = 0;

  for (int i = 0; i <= 255; i++) {
    var = (s21_get_bit_big(bvalue_1, i) + s21_get_bit_big(bvalue_2, i) + tmp);
    if (var == 3) {
      tmp = 1;
      s21_set_bit_big(result, i, 1);
    } else if (var == 2) {
      tmp = 1;
      s21_set_bit_big(result, i, 0);
    } else if (var == 1) {
      s21_set_bit_big(result, i, 1);
      tmp = 0;
    } else if (var == 0) {
      s21_set_bit_big(result, i, 0);
      tmp = 0;
    }
  }
  if (tmp == 1) status = 1;
  return status;
}

void s21_normalize_big(s21_big_decimal *bvalue_1, s21_big_decimal *bvalue_2) {
  int def = bvalue_1->exponenta - bvalue_2->exponenta;
  if (def > 0) {
    s21_multiply_10_mantis_big(bvalue_2, def);
    s21_zeroes_left_big(bvalue_2);
  } else if (def < 0) {
    s21_multiply_10_mantis_big(bvalue_1, -def);
    s21_zeroes_left_big(bvalue_1);
  }
}

int s21_multiply_mantis_big(s21_big_decimal bvalue_1, s21_big_decimal *bvalue_2,
                            s21_big_decimal *result) {
  int status = 0;

  s21_zero_big_decimal(result);

  s21_zeroes_left_big(bvalue_2);
  s21_zeroes_left_big(&bvalue_1);

  for (int i = 0; i <= bvalue_2->one_position_left; i++) {
    if (i != 0)
      if (s21_shift_left_big(&bvalue_1, 1) == 1) {
        status = 1;
        break;
      }
    if (s21_get_bit_big(bvalue_2, i))
      if (s21_sum_mantissa(result, &bvalue_1, result)) status = 1;
  }

  int equal_znak = (bvalue_1.sign == bvalue_2->sign);
  if (!equal_znak) result->sign = 1;

  result->exponenta = bvalue_1.exponenta + bvalue_2->exponenta;

  return status;
}

void s21_zero_mantisa_big(s21_big_decimal *result) {
  for (int i = 0; i < 8; i++) {
    result->bits[i] = 0;
  }
}

void s21_zero_big_decimal(s21_big_decimal *result) {
  s21_zero_mantisa_big(result);
  result->exponenta = 0;
  result->sign = 0;
  result->one_position_left = 0;
  result->one_right = 0;
}

int s21_shift_left_big(s21_big_decimal *bvalue, int def) {
  int status = 0;

  s21_zeroes_left_big(bvalue);

  if ((255 - bvalue->one_position_left) < def) status = 1;

  for (int i = bvalue->one_position_left; i >= 0; i--) {
    if ((i + def) <= 255) {
      s21_set_bit_big(bvalue, i + def, s21_get_bit_big(bvalue, i));
    }
  }
  for (int i = 0; i < def; i++) {
    s21_set_bit_big(bvalue, i, 0);
  }
  s21_zeroes_left_big(bvalue);

  return status;
}

void s21_zeroes_left_big(s21_big_decimal *bvalue) {
  int i = 255;
  while (1) {
    if (s21_get_bit_big(bvalue, i) != 0) {
      bvalue->one_position_left = i;
      break;
    }
    i--;
    if (!(i >= 0)) break;
  }
  if (i == -1) {
    bvalue->one_position_left = -1;
  }
  for (int j = 0; j <= 255; j++) {
    if (s21_get_bit_big(bvalue, j) != 0) {
      bvalue->one_right = j;
      break;
    }
  }
}

void s21_init_big(s21_decimal value, s21_big_decimal *big) {
  big->exponenta = s21_get_exp(value);
  big->sign = s21_get_sign(value);
  big->bits[0] = value.bits[0];
  big->bits[1] = value.bits[1];
  big->bits[2] = value.bits[2];
  s21_zeroes_left_big(big);
}

void s21_division(s21_big_decimal val1, s21_big_decimal val2,
                  s21_big_decimal *res) {
  int scale_dif = (val1.exponenta - val2.exponenta);
  int q = 0;
  s21_big_decimal part = {0};
  s21_big_decimal part_next = {0};
  s21_big_decimal sum = {0};
  s21_big_decimal before_sum = {0};
  while (s21_is_zero_big_decimal(val1) && sum.exponenta < 31) {
    while (is_greater_big_decimal(val2, val1)) {
      s21_multiply_10_mantis_big(&val1, 1);
      s21_multiply_10_mantis_big(&sum, 1);
    }
    q = 0;
    s21_zero_big_decimal(&part);
    s21_zero_big_decimal(&before_sum);
    part_next = val2;
    part = val2;
    s21_zeroes_left_big(&val1);
    while (s21_is_greater_or_equal_big_decimal(val1, part_next)) {
      if (q == 0) {
        int difference_elder_bit =
            val1.one_position_left - val2.one_position_left;
        if (difference_elder_bit > 2) {
          q = difference_elder_bit - 2;
          s21_shift_left_big(&part_next, q);
        }
      }
      part = part_next;
      s21_shift_left_big(&part_next, 1);
      q++;
    }
    q--;
    s21_set_bit_big(&before_sum, q, 1);
    s21_sum_mantissa(&sum, &before_sum, &sum);
    if (s21_is_greater_or_equal_big_decimal(val1, part))
      s21_sub_mantis_big(val1, part, &val1);
  }
  sum.exponenta += scale_dif;
  if (scale_dif < 0) {
    s21_multiply_10_mantis_big(&sum, -scale_dif);
  }
  *res = sum;
}