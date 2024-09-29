#include "s21_cat.h"

int main(int argc, char **argv) {
  int flag_return = 1;
  Cat_flags flags;
  flags.pattern = argv[1];
  Cat_init(&flags);
  process_flags(argc, argv, &flags);
  if (flags.flag_b == 1 && flags.flag_n == 1) {
    flags.flag_n = 0;
  }

  if (flag_return == 1) {
    cat_with_flags(&flags, argc, argv);
  }

  return 0;
}

void process_flags(int argc, char *argv[], Cat_flags *flags) {
  struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                  {"number", 0, 0, 'n'},
                                  {"squeeze-blank", 0, 0, 's'},
                                  {0, 0, 0, 0}};

  int c;
  while ((c = getopt_long(argc, argv, "+beEvnstTv", long_options, NULL)) !=
         -1) {
    switch (c) {
      case 'b':
        flags->flag_b = 1;
        break;
      case 'e':
        flags->flag_e = 1;
        flags->flag_v = 1;
        break;
      case 'v':
        flags->flag_v = 1;
        break;
      case 'n':
        flags->flag_n = 1;
        break;
      case 's':
        flags->flag_s = 1;
        break;
      case 't':
        flags->flag_t = 1;
        flags->flag_v = 1;
        break;
      case 'T':
        flags->flag_t = 1;
        break;
      case 'E':
        flags->flag_e = 1;
        break;
      default: {
        exit(1);
      }
    }
  }
}

void cat_with_flags(Cat_flags *flags, int argc, char *argv[]) {
  char end = '\0';

  for (int i = optind; i < argc; i++) {
    int line_new = 1, line_number_b = 1, line_number_n = 1;
    FILE *file = fopen(argv[i], "r");
    if (file == NULL) {
      printf("error. file is null\n");
      continue;
    }
    int Count_template = 0;
    char previous = ' ';
    while ((end = fgetc(file)) != EOF) {
      if (flags->flag_b) {
        if ((end != '\n' && previous == '\n') || line_number_b == 1) {
          printf("%6d\t", line_number_b++);
        }
      }

      if (flags->flag_s) {
        if (end == '\n') Count_template++;
        if (end != '\n' && Count_template > 0) Count_template--;
        if (Count_template == 3) {
          Count_template--;
          continue;
        }
      }

      if (flags->flag_n) {
        if ((line_new && end != '\n') || (previous == '\n' && end == '\n')) {
          printf("%6d\t", line_number_n++);
          line_new = 0;
        }
      }
      if (flags->flag_e) {
        if (end == '\n') {
          printf("$");
        }
      }

      if (flags->flag_v) {
        if ((end >= 0 && end < 9) || (end > 10 && end < 32)) {
          putchar('^');
          end += 64;
        }
        if (end == 127) {
          printf("^?");
          continue;
        }
      }

      if (end == '\n' && end + 1 != EOF) {
        line_new = 1;
      }

      if (flags->flag_t) {
        if (end == '\t') {
          printf("^I");
          previous = '\t';
          continue;
        }
      }

      previous = end;
      putchar(end);
    }
    fclose(file);
  }
}

void Cat_init(Cat_flags *flags) {
  flags->flag_b = 0;
  flags->flag_e = 0;
  flags->flag_n = 0;
  flags->flag_s = 0;
  flags->flag_t = 0;
  flags->flag_v = 0;
}