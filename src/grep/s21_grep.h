
#include <errno.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  int flag_e;
  int flag_i;
  int flag_v;
  int flag_c;
  int flag_l;
  int flag_n;
  int flag_s;
  int flag_h;
  int flag_f;
  int flag_o;
  int fileCount;
  char pattern[1000];
} Grep_flags;

void process_flags(int argc, char *argv[], Grep_flags *flags);
void GREPS(char **argv, Grep_flags *flags, int argc);
void o_flag(char *buffer, Grep_flags *flags);
void f_flag(Grep_flags *flags);
void get_string_search(Grep_flags *flags, char *argv[]);
void count_file(Grep_flags *a, int argc);
void output(char *buffer);