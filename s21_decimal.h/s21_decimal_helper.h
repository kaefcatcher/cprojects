#ifndef S21_DECIMAL_HELPER_H
#define S21_DECIMAL_HELPER_H

#include <stdio.h>

#include "s21_decimal.h"

int s21_get_part(int bit);
unsigned int s21_get_bit(s21_decimal dnum, int bit);
void s21_set_bit(s21_decimal *dnum, int bit, int value);
unsigned int s21_int_to_bin(unsigned int k);
int s21_get_exp_in_bin(s21_decimal dnum);
int s21_get_exp(s21_decimal dnum);
int s21_set_exp(s21_decimal *num, int exp);
int s21_compare(unsigned int a, unsigned int b);
int s21_get_sign(s21_decimal dnum);
void s21_set_sign(s21_decimal *dnum, int sign);

void s21_shift_left(s21_decimal *number);
unsigned int s21_get_highestbit(s21_decimal dnum);
void s21_shift_right(s21_decimal *number);

int s21_get_bit_big(s21_big_decimal *num, int cur_bit);
void s21_set_bit_big(s21_big_decimal *num, int bit, int result);
unsigned int s21_division_with_rest_for10(s21_big_decimal val1,
                                          s21_big_decimal *res);

void s21_zero_s21_decimal(s21_decimal *value);

void s21_init_big(s21_decimal value, s21_big_decimal *big);
int s21_get_bit_big(s21_big_decimal *num, int cur_bit);
void s21_normalize_big(s21_big_decimal *bvalue_1, s21_big_decimal *bvalue_2);
int s21_multiply_10_mantis_big(s21_big_decimal *bvalue, int def);
int s21_multiply_mantis_big(s21_big_decimal bvalue_1, s21_big_decimal *bvalue_2,
                            s21_big_decimal *result);
void s21_zero_big_decimal(s21_big_decimal *result);
void s21_zero_mantisa_big(s21_big_decimal *result);
int s21_shift_left_big(s21_big_decimal *bvalue, int def);
int s21_sum_mantissa(s21_big_decimal *bvalue_1, s21_big_decimal *bvalue_2,
                     s21_big_decimal *result);
void s21_sub_mantis_big(s21_big_decimal value_1, s21_big_decimal value_2,
                        s21_big_decimal *result);
int s21_compare_mantis_big(s21_big_decimal *bvalue1, s21_big_decimal *bvalue2);
int s21_big_to_s21decimal(s21_decimal *result, s21_big_decimal *result_big);
void s21_big_to_s21decimal_95(s21_big_decimal *result_big, s21_decimal *result);
void s21_zeroes_left_big(s21_big_decimal *bvalue);
int s21_is_zero_big_decimal(s21_big_decimal big);
int s21_is_greater_or_equal_big_decimal(s21_big_decimal value_1,
                                        s21_big_decimal value_2);
void s21_bank_round(s21_big_decimal copy_result_big_x,
                    s21_big_decimal *result_big, int exp_diff);
int s21_go_beyond_big_decimal_s21(s21_big_decimal *big);
int s21_is_zero_s21_decimal(s21_decimal value);
void s21_division(s21_big_decimal val1, s21_big_decimal val2,
                  s21_big_decimal *res);
#endif