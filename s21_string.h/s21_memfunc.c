#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *out = s21_NULL;
  const unsigned char *pstr = str;
  while (n--) {
    if (*pstr == c) {
      out = (void *)pstr;
      break;
    }
    pstr++;
  }
  return out;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int out = 0;
  const char *pstr1 = str1;
  const char *pstr2 = str2;
  while (n--) {
    if (*pstr1 != *pstr2) {
      out = (*pstr1 - *pstr2);
      break;
    }
    pstr1++;
    pstr2++;
  }
  return out;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  const unsigned char *psrc = src;
  unsigned char *pdest = dest;
  while (n--) *pdest++ = *psrc++;

  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *pstr = str;
  while (n--) *pstr++ = c;

  return str;
}