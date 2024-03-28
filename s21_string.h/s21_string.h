#ifndef S21_STRING_H
#define S21_STRING_H

#define s21_NULL (void *)0
typedef unsigned long s21_size_t;

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define FLAGS "-+"
#define SPECS "dfcsu"
#define length_ "hlL"
#define digits_ "0123456789"

typedef struct s21_Format {
  bool flag_minus;
  bool flag_plus;
  bool flag_space;
  bool flag_sharp;
  bool flag_zero;
  int width;
  int precision;
  int precision_set;
  char length;
  char specifier;
  int sign;
  bool point;

} s21_Format;

int s21_sprintf(char *str, const char *format, ...);
char *treatment(char *str, s21_Format *textformat, va_list *dop_values,
                s21_size_t *len);
void s21_default_precision(s21_Format *parameters);
char *s21_str_to_int(int *number, const char *format);
void s21_check_flags(const char *str_res, s21_Format *textformat);
void s21_move_str_right(char *str_res);
void s21_work_precision(char *str_res, s21_Format *textformat);
void s21_work_flag(char *str_res, s21_Format *textformat);
void s21_s_spec(char *str, va_list *dop_value, s21_Format *textformat);
void s21_u_spec(char *str_res, va_list *dop_value, s21_Format *textformat);
void s21_prosent_spec(char *str, s21_Format *textformat);
void s21_reverse_writing(char *str);
void s21_ul_to_str(char *str_res, unsigned long long number,
                   s21_Format *textformat);
void s21_spec_f(char *str, va_list *dop_values, s21_Format *textformat);
void s21_float_to_str(char *str, s21_Format *textformat, long double number);
void s21_spec_c(char *str, va_list *dop_values, s21_Format *textformat);
void s21_char_to_str(char *str, s21_Format *textformat, char ch);
void s21_wchar_to_str(char *str, s21_Format *textformat, wchar_t wchar);
int s21_compare_round(s21_Format *parameters, long double number);
void s21_spec_di(char *str, va_list *dop_values, s21_Format *textformat);
void s21_int_to_str(char *str, long double number, s21_Format *parameters);
void s21_make_string_width(s21_Format *parameters, char *str);
bool is_flag(char ch);
bool is_digit(char ch);
bool is_length(char ch);
bool is_specifier(char ch);

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strcat(char *dest, const char *src);
char *s21_strerror(int errnum);
void s21_errnum_tostring(char *str, int num);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

void *s21_insert(const char *src, const char *str, s21_size_t start_index);
char *s21_strcpy(char *dest, const char *src);
int s21_strcmp(const char *str1, const char *str2);
void *s21_trim(const char *src, const char *trim_chars);
void delete_first_letter(char *str);
void delete_left_part(char *result, const char *src, const char *trim_chars);
void delete_right_part(char *result, const char *src, const char *trim_chars);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
#endif
