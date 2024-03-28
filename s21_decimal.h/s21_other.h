#ifndef S21_OTHER_H
#define S21_OTHER_H

#include <stdio.h>

#include "s21_decimal.h"
#include "s21_decimal_helper.h"

int s21_negate(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);

#endif