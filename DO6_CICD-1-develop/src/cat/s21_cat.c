#include "s21_cat_module.h"

/*typedef struct {
  bool number_NonBlanc_b;
  bool markEnd_e;
  bool numberAll_n;
  bool squessze_blanc_s;
  bool tab_T;
  bool printNonPrintable_v;
  bool markEnd_E;
} flags;
*/

// Cat_flags Flags CatReadFlags(int argc, char* argv[]);
// void CatReadFile(FILE* file, Cat_flags flags, char* table);
// void Cat(int argc, char* argv[], Cat_flags Flags, char* table);

// flags CatReadFlags(int argc, char* argv[]);
// void CatReadFile(FILE* file, flags Cat_flags, char* table[N]);
// void Cat(int argc, char* argv[], flags Cat_flags, char* table[N]);
void CatSetTable(char* table[N]);
void CatSetNonPrintable(char* table[N]);
// void CatSetTab(char* table[N]);
// void CatSetEndl(char* table[N]);

flags CatReadFlags(int argc, char* argv[]) {
  struct option longOptions[] = {{"--number-nonblank", 0, NULL, 'b'},
                                 {"--number", 0, NULL, 'n'},
                                 {"--squeeze-blank", 0, NULL, 's'},
                                 {NULL, 0, NULL, 0}};
  flags Cat_flags = {false, false, false, false, false, false, false};
  int CurrentFlags = 0;
  while (CurrentFlags != -1) {
    switch (CurrentFlags =
                getopt_long(argc, argv, "+benstuvTE", longOptions, NULL)) {
      case 'b':
        Cat_flags.number_NonBlanc_b = true;  // нумерует только непустые строки
        break;
      case 'e':
        Cat_flags.markEnd_e = true;
        Cat_flags.printNonPrintable_v = true;
        // отображает символы конца строки как $ и все
        // скрытые символы тоже, кроме символа табуляции ^I
        break;
      case 'v':
        Cat_flags.printNonPrintable_v =
            true;  // показывать непечатаемые символы,
                   // КРОМЕ табуляции и конца строки
        break;
      case 'E':
        Cat_flags.markEnd_E =
            true;  // (GNU) отображает символы конца строки как $
        break;
      case 'n':
        Cat_flags.numberAll_n = true;  //  нумерует все строки при выводе
        break;
      case 's':
        Cat_flags.squessze_blanc_s =
            true;  // сжимает несколько смежных пустых строк
        break;
      case 't':
        Cat_flags.printNonPrintable_v = true;
        Cat_flags.tab_T = true;

        // отображает табы как ^I и все скрытые символы тоже, КРОМЕ
        // конца строки $
        break;
      case 'T':
        Cat_flags.tab_T = true;  // (GNU) отображает табы как ^I
        break;
    }
    // printf("\n%d", CurrentFlags);
  }
  return Cat_flags;
}

void CatReadFile(FILE* file, flags Cat_flags, char* table[N]) {
  // flags Cat_flags = CatReadFlags(argc, argv);
  // printf("\ninside catRead\n");
  int c = 0;

  int last;
  int line = 0;
  bool squeeze = false;
  last = '\n';

  while (fread(&c, 1, 1, file) > 0) {
    // printf("\ninside while fread\n");
    // printf("\n%d\n", c);
    if (last == '\n') {
      if (Cat_flags.squessze_blanc_s && c == '\n') {
        if (squeeze) continue;
        squeeze = true;
      } else
        squeeze = false;
      if (Cat_flags.number_NonBlanc_b) {
        if (c != '\n') printf("%6i\t", ++line);
      } else if (Cat_flags.numberAll_n) {
        printf("%6i\t", ++line);
      }
    }
    if (!*table[c])
      printf("%c", '\0');
    else
      printf("%s", table[c]);
    last = c;
  }
}

void Cat(int argc, char* argv[], flags Cat_flags, char* table[N]) {
  // printf("\ninside cat\n");
  // printf("\n%d\n", argc);
  // bool noFile = 1;
  for (char **filename = &argv[1], **end = &argv[argc]; filename != end;
       ++filename) {
    // printf("\ninside chicle\n");
    if (**filename == '-') continue;
    FILE* file = fopen(*filename, "rb");
    if (errno) {
      fprintf(stderr, "%s", argv[0]);
      perror(*filename);
      // printf("\nno file\n");
      continue;
    }
    CatReadFile(file, Cat_flags, table);
    fclose(file);
    // noFile = 0;
  }
  // if (noFile) CatReadFile(stdin, Cat_flags, table);
}

void CatSetTab(char* table[N]) { table['\t'] = "^I"; }

void CatSetEndl(char* table[N]) { table['\n'] = "$\n"; }

int main(int argc, char* argv[N]) {
  flags Cat_flags = CatReadFlags(argc, argv);
  // printf("\nafter read flags\n");
  char* table[N];
  // printf("\nafter set table\n");
  CatSetTable(table);

  if (Cat_flags.markEnd_e) CatSetEndl(table);
  if (Cat_flags.tab_T) CatSetTab(table);
  if (Cat_flags.printNonPrintable_v) CatSetNonPrintable(table);
  if (Cat_flags.markEnd_E) CatSetEndl(table);

  Cat(argc, argv, Cat_flags, table);
  return 0;
}
