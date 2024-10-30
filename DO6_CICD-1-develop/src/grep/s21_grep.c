#include "s21_grep.h"

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  Flags flags = {0};
  int noerror = 1;
  parser_flag(argc, argv, &flags, &noerror);
  if (noerror) {
    if (flags.flag_c || flags.flag_l) {
      flags_c_and_l(flags);
    } else
      output(flags);
  }
  return 0;
}

void parser_flag(int argc, char *argv[], Flags *flags, int *noerror) {
  const struct option long_option;
  int opt;
  if (argc == 1) {
    fprintf(stderr,
            "usage: grep [-abcDEregerrHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "
            "[-C[num]]\n\t[-e pattern] [-f file] [--binary-files=value] "
            "[--color=when]\n\t[--context[=num]] [--directories=action] "
            "[--label] [--line-buffered]\n\t[--null] [pattern] [file ...]");
    exit(1);
  } else {
    while ((opt = getopt_long(argc, argv, "e:ivclnhsf:o", &long_option,
                              NULL)) != -1) {
      if (opt == 'i') {
        flags->flag_i = true;
      } else if (opt == 'v') {
        flags->flag_v = true;
      } else if (opt == 'c') {
        flags->flag_c = true;
      } else if (opt == 'l') {
        flags->flag_l = true;
      } else if (opt == 'n') {
        flags->flag_n = true;
      } else if (opt == 'h') {
        flags->flag_h = true;
      } else if (opt == 's') {
        flags->flag_s = true;
      } else if (opt == 'f') {
        flags->flag_f = true;
        strcpy(flags->pattern_file[flags->pattern_files_amount], optarg);
        flags->pattern_files_amount++;
      } else if (opt == 'e') {
        flags->flag_e = true;
        if (strlen(flags->pattern) == 0) {
          strcat(flags->pattern, optarg);
        } else {
          strcat(flags->pattern, "|");
          strcat(flags->pattern, optarg);
        }
      } else if (opt == 'o') {
        flags->flag_o = true;
      }

      else if (opt == '?') {
        if (!flags->flag_s)
          fprintf(stderr, "grep: Invalid flag -- '%c'\n", opt);
        *noerror = 0;
      }
    }
    if (*noerror != 0) {
      if (flags->flag_f) {
        patern_from_file(flags);
      }
      if (!flags->flag_e && !flags->flag_f) {
        strcat(flags->pattern, argv[optind]);
        optind++;
      }
      for (int i = (int)optind; i < argc; i++) {
        strcpy(flags->file_name[flags->files_amount], argv[i]);
        flags->files_amount++;
      }
    }
  }
}

void output(Flags flags) {
  int iflag = 0;
  if (flags.flag_i) {
    iflag = REG_ICASE;
  }
  regex_t re;
  regcomp(&re, flags.pattern, iflag | REG_EXTENDED);
  FILE *file = NULL;
  for (int i = 0; i < flags.files_amount; i++) {
    file = fopen(flags.file_name[i], "r");
    if (file == NULL) {
      if (!flags.flag_s) {
        fprintf(stderr, "grep: %s: No such file or directory\n",
                flags.file_name[i]);
      }
      continue;
    }
    int linenumber = 1;
    while (feof(file) == 0) {
      char str[LONG_LINE];
      if (fgets(str, LONG_LINE, file) != NULL) {
        int printnow = regexec(&re, str, 0, NULL, 0);
        if (!flags.flag_v && printnow == 0) {
          if (!flags.flag_h && flags.files_amount > 1) {
            printf("%s:", flags.file_name[i]);
          }
          if (flags.flag_n) {
            printf("%d:", linenumber);
          }
          if (flags.flag_o) {
            flag_o(str, &re);
          }
          if (!flags.flag_o) {
            printf("%s", str);
          }
          if (str[(int)strlen(str) - 1] != '\n') {
            printf("\n");
          }
        } else if (flags.flag_v && !printnow == 0) {
          if (!flags.flag_h && flags.files_amount > 1) {
            printf("%s:", flags.file_name[i]);
          }
          if (flags.flag_n) {
            printf("%d:", linenumber);
          }
          { printf("%s", str); }
          if (str[(int)strlen(str) - 1] != '\n') {
            printf("\n");
          }
        }
        linenumber++;
      }
    }
    fclose(file);
  }
  regfree(&re);
}
void flags_c_and_l(Flags flags) {
  int iflag = 0;
  if (flags.flag_i) {
    iflag = REG_ICASE;
  }
  regex_t re;
  regcomp(&re, flags.pattern, iflag | REG_EXTENDED);
  FILE *file = NULL;
  for (int i = 0; i < flags.files_amount; i++) {
    int match_counter = 0;
    file = fopen(flags.file_name[i], "r");
    if (file == NULL) {
      if (!flags.flag_s) {
        fprintf(stderr, "grep: %s: No such file or directory\n",
                flags.file_name[i]);
      }
      continue;
    }
    while (feof(file) == 0) {
      char str[LONG_LINE];
      if (fgets(str, LONG_LINE, file) != NULL) {
        int printnow = regexec(&re, str, 0, NULL, 0);
        if (!flags.flag_v && printnow == 0) {
          match_counter++;
        } else if (flags.flag_v && !printnow == 0) {
          match_counter++;
        }
      }
    }
    if (flags.flag_c && !flags.flag_l) {
      if (flags.files_amount > 1 && !flags.flag_h) {
        printf("%s:", flags.file_name[i]);
      }
      printf("%d\n", match_counter);
    }
    if (!flags.flag_c && flags.flag_l && match_counter) {
      printf("%s\n", flags.file_name[i]);
    } else if (flags.flag_c && flags.flag_l) {
      if (match_counter) {
        if (!flags.flag_h && flags.files_amount > 1) {
          printf("%s:", flags.file_name[i]);
        }
        printf("1\n");
        printf("%s\n", flags.file_name[i]);
      } else if (!match_counter) {
        if (!flags.flag_h) {
          printf("%s:", flags.file_name[i]);
        }
        printf("0\n");
      }
    }
    fclose(file);
  }
  regfree(&re);
}

void patern_from_file(Flags *flags) {
  for (int i = 0; i < flags->pattern_files_amount; i++) {
    FILE *patt = NULL;
    patt = fopen(flags->pattern_file[i], "r");
    if (patt == NULL) {
      if (!flags->flag_s) {
        fprintf(stderr, "grep: %s: No such file or directory\n",
                flags->file_name[i]);
      }
      continue;
    }
    while (feof(patt) == 0) {
      char filepat[LONG_NAME];
      if (fgets(filepat, LONG_NAME, patt) != NULL) {
        if (filepat[strlen(filepat) - 1] == '\n' && strlen(filepat) != 1) {
          filepat[strlen(filepat) - 1] = '\0';
        }
        if (strlen(filepat) > 0) {
          if (strlen(flags->pattern) == 0) {
            strcat(flags->pattern, filepat);
          } else {
            strcat(flags->pattern, "|");
            strcat(flags->pattern, filepat);
          }
        }
      }
    }
    fclose(patt);
  }
}

void flag_o(char *str, const regex_t *re) {
  regmatch_t match[1];
  char *ostr = str;
  while (regexec(re, ostr, 1, match, 0) == 0) {
    if (ostr[strlen(ostr) - 1] == '\n') {
      printf("%.*s\n", (int)(match[0].rm_eo - match[0].rm_so),
             ostr + match[0].rm_so);
    } else {
      printf("%.*s", (int)(match[0].rm_eo - match[0].rm_so),
             ostr + match[0].rm_so);
    }
    ostr = ostr + (int)match[0].rm_eo;
  }
}