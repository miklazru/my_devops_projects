#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  int flag_b;
  int flag_e;
  int flag_n;
  int flag_s;
  int flag_t;
  int flag_v;
  char *pattern;
} Cat_flags;

void process_flags(int argc, char *argv[], Cat_flags *flags);
void cat_with_flags(Cat_flags *flags, int argc, char *argv[]);
void Cat_init(Cat_flags *flags);
