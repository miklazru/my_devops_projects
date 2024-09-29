#include "s21_grep.h"

int main(int argc, char **argv) {
  Grep_flags FLAG = {0};

  if (argc < 3) {
    fprintf(stderr, "ERROR: need ./s21_grep flags pattern file");
  } else {
    process_flags(argc, argv, &FLAG);
    count_file(&FLAG, argc);
    get_string_search(&FLAG, argv);
    GREPS(argv, &FLAG, argc);
  }

  return 0;
}

void process_flags(int argc, char *argv[], Grep_flags *flags) {
  int c = 0;
  while ((c = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (c) {
      case 'e':
        flags->flag_e = 1;
        if (strlen(flags->pattern) > 0) {
          strcat(flags->pattern, "|");
        }
        strcat(flags->pattern, optarg);
        break;
      case 'i':
        flags->flag_i = 1;
        break;
      case 'v':
        flags->flag_v = 1;
        break;
      case 'c':
        flags->flag_c = 1;
        break;
      case 'l':
        flags->flag_l = 1;
        break;
      case 'n':
        flags->flag_n = 1;
        break;
      case 's':
        flags->flag_s = 1;
        break;
      case 'h':
        flags->flag_h = 1;
        break;
      case 'f':
        flags->flag_f = 1;
        f_flag(flags);
        break;
      case 'o':
        flags->flag_o = 1;
        break;
      case '?':
        fprintf(stderr, "ERROR: invalid flag!\n");
        break;
    }
  }
}

void count_file(Grep_flags *a, int argc) { a->fileCount = argc - optind; }
void get_string_search(Grep_flags *flags, char *argv[]) {
  if (!flags->flag_e && !flags->flag_f) {
    strcpy(flags->pattern, argv[optind]);
    flags->fileCount--;
  }
}

void GREPS(char **argv, Grep_flags *flags, int argc) {
  char buffer[1000];
  int line_counting = 0;
  int ret;
  int num = 0;
  regex_t regex;
  regcomp(&regex, flags->pattern,
          REG_EXTENDED | (flags->flag_i ? REG_ICASE : 0));

  int begin = argc - flags->fileCount;
  for (int i = begin; i < argc; i++) {
    FILE *f = fopen(argv[i], "r");

    if (f == NULL) {
      if (flags->flag_s == 0) {
        printf("ERROR: Failed to open file '%s'.\n", argv[i]);
        continue;
      } else
        continue;
    }
    while (fgets(buffer, 1000, f) != NULL) {
      line_counting++;
      ret = regexec(&regex, buffer, 0, NULL, 0);
      if (flags->flag_v) {
        ret = !ret;
      }
      if (ret == 0) {
        num++;
        if (flags->flag_l) {
          if (flags->flag_c) {
            if (flags->fileCount > 1 && flags->flag_h == 0) {
              printf("%s:\n", argv[i]);
            }

            printf("1\n");
          }

          printf("%s\n", argv[i]);
          break;
        } else if (!flags->flag_c) {
          if (flags->fileCount > 1 && !flags->flag_h) {
            printf("%s:", argv[i]);
          }
          if (flags->flag_n) {
            printf("%d:", line_counting);
          }
          if (flags->flag_o) {
            o_flag(buffer, flags);
          } else {
            output(buffer);
          }
        }
      }
    }
    if (flags->flag_c) {
      if (flags->flag_l == 0 || num == 0) {
        if (flags->fileCount > 1 && flags->flag_h == 0) {
          printf("%s:", argv[i]);
        }
        printf("%d\n", num);
      }
    }
    fclose(f);
    num = 0;
  }

  regfree(&regex);
}

void f_flag(Grep_flags *flags) {
  FILE *file = fopen(optarg, "r");

  if (file != NULL) {
    char buffer[1000];
    while (fgets(buffer, 1000, file) != NULL) {
      if (strlen(flags->pattern) > 0) strcat(flags->pattern, "|");

      if (buffer[strlen(buffer) - 1] == '\n') buffer[strlen(buffer) - 1] = '\0';

      strcat(flags->pattern, buffer);
    }
    fclose(file);
  } else {
    fprintf(stderr, "ERROR: file %s doesn't exist\n", optarg);
    exit(1);
  }
}

void o_flag(char *buffer, Grep_flags *flags) {
  regex_t regex;
  int result;
  regmatch_t num[1];

  result =
      regcomp(&regex, flags->pattern, flags->flag_i ? REG_ICASE : REG_EXTENDED);

  while (*buffer) {
    result = regexec(&regex, buffer, 1, num, 0);
    if (result == REG_NOMATCH && flags->flag_v) {
      output(buffer);
      break;
    } else if (result == 0) {
      for (int i = num[0].rm_so; i < num[0].rm_eo; i++) {
        printf("%c", buffer[i]);
      }
      printf("\n");
      buffer += num[0].rm_eo;

    } else {
      buffer++;
    }
  }
}
void output(char *buffer) {
  printf("%s", buffer);
  if (buffer[strlen(buffer) - 1] != '\n') printf("\n");
}