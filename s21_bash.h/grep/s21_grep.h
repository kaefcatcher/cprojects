#ifndef S21_GREP_H
#define S21_GREP_H

#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FILES 10
#define MAX_NAME_LENGTH 25
typedef struct args {
  int case_sensitive;
  int invert_match;
  int print_count;
  int print_filename;
  int print_line_number;
  int flag_e;
  int file_pattern;
  int suppress_warning;
  char files[MAX_FILES][MAX_NAME_LENGTH];
  char** patterns;
  int file_count;
} args;

#endif