#ifndef S21_CAT_H
#define S21_CAT_H

#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FILES 10
#define MAX_NAME_LENGTH 25
typedef struct args {
  int print_count;
  int count_blank;
  int squeeze;
  int eol;
  int tab;
  char files[MAX_FILES][MAX_NAME_LENGTH];
  int file_count;
} args;

#endif