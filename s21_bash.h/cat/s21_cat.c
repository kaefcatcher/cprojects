#include "s21_cat.h"

struct args parse_input(int argc, char *argv[]) {
  struct args args_ = {.print_count = 0,
                       .count_blank = 1,
                       .squeeze = 0,
                       .eol = 0,
                       .tab = 0,
                       .file_count = 0};
  struct option long_options[] = {
      {"--number-nonblank", no_argument, NULL, 'i'},
      {"-E", no_argument, NULL, 'v'},
      {"--number", no_argument, NULL, 'c'},
      {"--squeeze-blank", required_argument, NULL, 'l'},
      {"-T", no_argument, NULL, 'n'},
      {0, 0, 0, 0}};

  int opt;
  while ((opt = getopt_long(argc, argv, "ebnst", long_options, NULL)) != -1) {
    switch (opt) {
      case 'e':
        args_.eol = 1;
        break;
      case 'b':
        args_.count_blank = 0;
        args_.print_count = 1;
        break;
      case 'n':
        args_.print_count = 1;
        break;
      case 's':
        args_.squeeze = 1;
        break;
      case 't':
        args_.tab = 1;
        break;
      default:
        fprintf(stderr, "Usage: [options] <filename>\n");
        exit(EXIT_FAILURE);
    }
  }

  for (int i = optind; i < argc; i++) {
    strcpy(args_.files[args_.file_count], argv[i]);
    args_.file_count++;
  }

  return args_;
}

void cat_with_flags(struct args args_, FILE *file, int *line_number) {
  char line[MAX_LINE_LENGTH];
  int prev_blank = 0;

  while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
    if (args_.squeeze && prev_blank && line[0] == '\n') {
      continue;
    }

    if (args_.count_blank) {
      if (args_.print_count) {
        printf("%6d\t", *line_number);
        (*line_number)++;
      }
    } else {
      if (args_.print_count && line[0] != '\n') {
        printf("%6d\t", *line_number);
        (*line_number)++;
      }
    }

    if (args_.tab) {
      for (int i = 0; line[i] != '\0'; ++i) {
        if (line[i] == '\t') {
          printf("^I");
        } else if (args_.eol && line[i] == '\n') {
          printf("$\n");
        } else {
          putchar(line[i]);
        }
      }
    } else {
      if (args_.eol) {
        if (line[strlen(line) - 1] == '\n') {
          line[strlen(line) - 1] = '$';
          fputs(line, stdout);
          printf("\n");
        } else {
          fputs(line, stdout);
        }
      } else {
        fputs(line, stdout);
      }
    }

    prev_blank = (line[0] == '\n');
  }
}

int main(int argc, char *argv[]) {
  FILE *file;
  struct args args_ = parse_input(argc, argv);

  for (int i = 0; i < args_.file_count; i++) {
    char *filename = malloc(MAX_NAME_LENGTH);
    strcpy(filename, args_.files[i]);

    if (filename != NULL) {
      if ((file = fopen(filename, "r")) != NULL) {
        int line_number = 1;
        cat_with_flags(args_, file, &line_number);

        fclose(file);
        free(filename);
      } else {
        printf("Error opening file %s\n", filename);
        free(filename);
        return EXIT_FAILURE;
      }
    } else {
      printf("Error allocating memory for filename\n");
      return EXIT_FAILURE;
    }
  }

  return 0;
}