#ifndef GREPFLAGSTRUCT_H
#define GREPFLAGSTRUCT_H

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LONG_PATTERN 8192
#define QUANT 100
#define LONG_NAME 2048
#define LONG_LINE 2048

typedef struct {
  bool flag_e;  // шаблон
  bool flag_i;
  bool flag_v;
  bool flag_c;
  bool flag_l;
  bool flag_n;
  bool flag_h;
  bool flag_s;
  bool flag_f;
  bool flag_o;
  char pattern[LONG_PATTERN];
  char file_name[QUANT][LONG_NAME];
  char pattern_file[QUANT][LONG_NAME];
  int files_amount;
  int pattern_files_amount;  // =0;
} Flags;

void parser_flag(int argc, char *argv[], Flags *flags, int *noerror);
void output(Flags flags);
void flags_c_and_l(Flags flags);
void patern_from_file(Flags *flags);
void flag_o(char *str, const regex_t *re);

#endif