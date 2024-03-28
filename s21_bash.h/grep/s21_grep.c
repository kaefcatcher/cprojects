#include "s21_grep.h"

#define MAX_LINE_LENGTH 1024

char *strcasestr(const char *haystack, const char *needle) {
  while (*haystack) {
    const char *h = haystack;
    const char *n = needle;

    while (*h && *n &&
           tolower((unsigned char)*h) == tolower((unsigned char)*n)) {
      h++;
      n++;
    }

    if (!*n) {
      return (char *)haystack;
    }

    haystack++;
  }

  return NULL;
}

char **readPatternsFromFile(const char *filename, int suppress_warning) {
  FILE *file = fopen(filename, "r");
  if (file) {
    char **patterns = NULL;
    char buffer[MAX_LINE_LENGTH];
    size_t count = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
      size_t len = strlen(buffer);
      if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
      }

      patterns = realloc(patterns, (count + 2) * sizeof(char *));
      patterns[count] = strdup(buffer);

      if (patterns[count] == NULL) {
        fprintf(stderr, "Error allocating memory for pattern\n");
        fclose(file);

        for (size_t i = 0; i < count; ++i) {
          free(patterns[i]);
        }
        free(patterns);

        exit(EXIT_FAILURE);
      }

      ++count;
    }

    patterns[count] = NULL;
    fclose(file);
    return patterns;
  }

  if (!suppress_warning) {
    fprintf(stderr, "Error opening file %s\n", filename);
  }

  exit(EXIT_FAILURE);
}

struct args parse_input(int argc, char *argv[]) {
  struct args args_ = {.case_sensitive = 1,
                       .invert_match = 0,
                       .print_count = 0,
                       .print_filename = 0,
                       .print_line_number = 0,
                       .flag_e = 0,
                       .file_pattern = 0,
                       .suppress_warning = 0,
                       .file_count = 0,
                       .patterns = NULL};
  struct option long_options[] = {{"ignore-case", no_argument, NULL, 'i'},
                                  {"invert-match", no_argument, NULL, 'v'},
                                  {"count", no_argument, NULL, 'c'},
                                  {"file", required_argument, NULL, 'l'},
                                  {"line-number", no_argument, NULL, 'n'},
                                  {"head", no_argument, NULL, 'h'},
                                  {"search-string", no_argument, NULL, 's'},
                                  {"extended-regexp", no_argument, NULL, 'e'},
                                  {"file", required_argument, NULL, 'f'},
                                  {0, 0, 0, 0}};

  int opt;

  while ((opt = getopt_long(argc, argv, "eivclnhsf", long_options, NULL)) !=
         -1) {
    switch (opt) {
      case 'e':
        args_.flag_e = 1;
        args_.patterns = realloc(args_.patterns, 2 * sizeof(char *));
        if (args_.patterns == NULL) {
          fprintf(stderr, "Error allocating memory for patterns\n");
          exit(EXIT_FAILURE);
        }
        args_.patterns[0] = strdup(argv[optind]);
        args_.patterns[1] = NULL;
        break;
      case 'i':
        args_.case_sensitive = 0;
        break;
      case 'v':
        args_.invert_match = 1;
        break;
      case 'c':
        args_.print_count = 1;
        break;
      case 'l':
        args_.print_filename = 1;
        break;
      case 'n':
        args_.print_line_number = 1;
        break;
      case 'h':
        args_.print_filename = 0;
        break;
      case 's':
        args_.suppress_warning = 1;
        break;
      case 'f':
        args_.file_pattern = 1;
        args_.patterns =
            readPatternsFromFile(argv[optind], args_.suppress_warning);

        break;
      default:
        fprintf(stderr, "Usage: [options] <pattern>  <filename>\n");
        exit(EXIT_FAILURE);
    }
  }
  if (!args_.file_pattern && !args_.flag_e) {
    if (args_.patterns != NULL) {
      for (int i = 0; args_.patterns[i] != NULL; ++i) {
        free(args_.patterns[i]);
      }
      free(args_.patterns);
    }

    args_.patterns = malloc(2 * sizeof(char *));
    if (args_.patterns == NULL) {
      fprintf(stderr, "Error allocating memory for patterns\n");
      exit(EXIT_FAILURE);
    }
    args_.patterns[0] = strdup(argv[optind]);
    args_.patterns[1] = NULL;
  }

  if (args_.patterns[0][0] == '\0') {
    fprintf(stderr, "Error: Search expression is missing\n");
    exit(EXIT_FAILURE);
  }
  for (int i = optind + 1; i < argc; i++) {
    strcpy(args_.files[args_.file_count], argv[i]);
    args_.file_count++;
  }
  return args_;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Usage: [options] <pattern>  <filename>\n");
    exit(EXIT_FAILURE);
  }

  FILE *file;
  char line[MAX_LINE_LENGTH];
  struct args args_ = parse_input(argc, argv);
  int lastCharWasNewline = 1;

  for (int i = 0; i < args_.file_count; i++) {
    char *filename = malloc(MAX_NAME_LENGTH);
    strcpy(filename, args_.files[i]);

    if (filename != NULL) {
      if ((file = fopen(filename, "r")) == NULL) {
        if (!args_.suppress_warning) {
          fprintf(stderr, "Error opening file %s\n", filename);
        }
        free(filename);
        for (int i = 0; args_.patterns[i] != NULL; ++i) {
          free(args_.patterns[i]);
        }
        free(args_.patterns);
        return EXIT_FAILURE;
      }

      int line_number = 0;
      int closed = 0;
      int printban = 0;
      if (args_.print_count) {
        printban = 1;
      }
      int match_in_file = 0;
      while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        line_number++;
        char *line_to_search = strdup(line);

        if (line_to_search == NULL) {
          fprintf(stderr, "Error allocating memory for line_to_search\n");
          free(line_to_search);
          break;
        }

        int match_count = 0;
        for (int pattern_index = 0; args_.patterns[pattern_index] != NULL;
             pattern_index++) {
          char *search_str = strdup(args_.patterns[pattern_index]);
          char *search_result = args_.case_sensitive
                                    ? strstr(line_to_search, search_str)
                                    : strcasestr(line_to_search, search_str);

          int match = (search_result != NULL);

          if ((match && !args_.invert_match) ||
              (!match && args_.invert_match)) {
            match_count++;
          }

          free(search_str);
        }

        if (match_count > 0) {
          match_in_file += match_count;
          if (!printban) {
            if (args_.print_filename) {
              printf("%s\n", filename);
              fclose(file);
              closed = 1;
              free(line_to_search);
              break;
            } else {
              if (args_.file_count > 1) {
                if (args_.print_line_number) {
                  printf("%s:%d:", filename, line_number);
                }

                printf("%s", line);
                lastCharWasNewline = (line[strlen(line) - 1] == '\n');
              } else {
                if (args_.print_line_number) {
                  printf("%d:", line_number);
                }

                printf("%s", line);
                lastCharWasNewline = (line[strlen(line) - 1] == '\n');
              }
            }
          }
        }

        free(line_to_search);
      }

      if (args_.print_count) {
        if (args_.file_count > 1) {
          printf("%s:%d\n", filename, match_in_file);
          lastCharWasNewline = 1;
        } else {
          printf("%d\n", match_in_file);
          lastCharWasNewline = 1;
        }
      }
      if (!closed) {
        fclose(file);
      }

      free(filename);
    }
  }

  if (!lastCharWasNewline) {
    printf("\n");
  }

  for (int i = 0; args_.patterns[i] != NULL; ++i) {
    free(args_.patterns[i]);
  }
  free(args_.patterns);

  return EXIT_SUCCESS;
}
