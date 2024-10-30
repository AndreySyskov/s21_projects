
#ifndef CAT
#define CAT
#include <errno.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 256

typedef struct {
  bool number_NonBlanc_b;
  bool markEnd_e;
  bool numberAll_n;
  bool squessze_blanc_s;
  bool tab_T;
  bool printNonPrintable_v;
  bool markEnd_E;
} flags;

flags CatReadFlags(int argc, char* argv[]);
void CatReadFile(FILE* file, flags Cat_flags, char* table[N]);
void Cat(int argc, char* argv[], flags Cat_flags, char* table[N]);
// void CatSetTable(char* table[N]);
// void CatSetNonPrintable(char* table[N]);
void CatSetTab(char* table[N]);
void CatSetEndl(char* table[N]);
#endif
