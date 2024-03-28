#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res = s21_NULL;
  s21_size_t j = 0, l = 0;
  s21_size_t len = s21_strlen(str) + s21_strlen(src) + 1;
  if (str && src && start_index <= s21_strlen(src)) {
    res = (char *)calloc(len, sizeof(char));
  }

  if (res) {
    for (s21_size_t i = 0; i < len; i++) {
      if (i >= start_index && i < s21_strlen(str) + start_index) {
        res[i] = str[j];
        j++;
      } else {
        res[i] = src[l];
        l++;
      }
    }
  }
  return (void *)res;
}

char *s21_strcpy(char *dest, const char *src) {
  unsigned int i = 0;
  while (src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  dest[i] = '\0';
  return dest;
}

void *s21_trim(const char *src, const char *trim_chars) {
  int is_error = 0;
  char *result = s21_NULL;
  if (src) {
    char default_chars[7] = " \t\n\v\r\f\0";
    if (trim_chars == s21_NULL || (int)s21_strlen(trim_chars) == 0)
      trim_chars = default_chars;
    result = (char *)calloc((int)s21_strlen(src) + 10, sizeof(char));
    if (result == s21_NULL) {
      is_error = 1;
    }
    s21_strcpy(result, (char *)src);
    delete_left_part(result, src, trim_chars);
    delete_right_part(result, src, trim_chars);
  } else {
    is_error = 1;
  }
  return is_error ? s21_NULL : (void *)result;
}

void delete_first_letter(char *str) {
  s21_size_t counter = 0;
  while (str[counter]) {
    str[counter] = str[counter + 1];
    counter++;
  }
}

void delete_left_part(char *result, const char *src, const char *trim_chars) {
  s21_size_t format_length = s21_strlen(trim_chars);
  s21_size_t str_length = s21_strlen(src);
  for (s21_size_t i = 0; i < str_length; i++) {
    int is_break = 0;
    for (s21_size_t j = 0; j < format_length; j++) {
      if (src[i] == trim_chars[j]) {
        delete_first_letter(result);
        break;
      }
      if (j == format_length - 1 && src[i] != trim_chars[format_length]) {
        is_break = 1;
      }
    }
    if (is_break) break;
  }
}

void delete_right_part(char *result, const char *src, const char *trim_chars) {
  s21_size_t format_length = s21_strlen(trim_chars);
  s21_size_t result_length = s21_strlen(result);
  for (int i = (int)result_length - 1; i >= 0; i--) {
    int is_break = 0;
    for (s21_size_t j = 0; j < format_length; j++) {
      if (result[i] == trim_chars[j]) {
        result[i] = '\0';
        break;
      }
      if (j == format_length - 1 && src[i] != trim_chars[format_length]) {
        is_break = 1;
      }
    }
    if (is_break) break;
  }
}

void *s21_to_upper(const char *str) {
  char *res = s21_NULL;
  if (str) {
    res = (char *)calloc(s21_strlen(str) + 1, sizeof(char));
  }
  if (res) {
    int i = 0;
    s21_strncpy(res, str, s21_strlen(str) + 1);
    while (str[i] != '\0') {
      if (str[i] >= 97 && str[i] <= 122) {
        res[i] -= 32;
      }
      i++;
    }
  }
  return (void *)res;
}

void *s21_to_lower(const char *str) {
  char *res = s21_NULL;
  if (str) {
    res = (char *)calloc(s21_strlen(str) + 1, sizeof(char));
  }
  if (res) {
    int i = 0;
    s21_strncpy(res, str, s21_strlen(str) + 1);
    while (str[i] != '\0') {
      if (str[i] >= 65 && str[i] <= 90) {
        res[i] += 32;
      }
      i++;
    }
  }
  return (void *)res;
}