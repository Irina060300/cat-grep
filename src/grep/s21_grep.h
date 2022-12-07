#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_
#define _POSIX_C_SOURCE 200809L
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pattern_list {
  char *pattern;
  struct pattern_list *next;
  int flag;
} pattern_list;

typedef struct grep_flags {
  int e, i, v, c, l, n, h, s, f, o;
  char illegal, ill_e, i_f;
  char ill_f[255];
} grep_flags;

typedef struct counters {
  int str_number, path_count, c_count, h;
  size_t size;
  ssize_t read, read_next;
} counters;

typedef struct pars {
  size_t size;
  ssize_t read;
  int len, len_e, c, ill, h, ill_f;
} pars;
int check_e(grep_flags *grep_flags, int argc, char *argv[]);
void init_struct(char *argv[], int i, grep_flags *grep_flags, int j, int ill);
pattern_list *push_stdin(char *argv[], pattern_list *cur, int i);
pattern_list *push_e(char *argv[], pattern_list *cur, int len_e, int i, int j);
void str_parser(grep_flags *grep_flags, int argc, char *argv[],
                pattern_list **cur, int *index);
int check_pattern(char *estr, pattern_list *tmp, grep_flags *grep_flags);
void check_s(char *argv[], int argc, grep_flags *grep_flags);
int print_pt_errors(grep_flags *grep_flags);
void deletelem(pattern_list *tmp);
pattern_list *push_v(char *pattern, pattern_list *cur);
void flag_processing(FILE *file, char **estr, char *pattern, pattern_list **cur,
                     int argc, grep_flags *grep_flags, int i, char *argv[],
                     pars *p);
void read_pat_file(FILE *file, char *argv[], int i, pattern_list **cur,
                   char **estr, char *pattern, grep_flags *grep_flags,
                   char *path, pars *p, int fl);
void flag_o_proccess(char *estr, grep_flags *grep_flags, FILE *file,
                     pattern_list *tmp);
void is_o(pattern_list *tmp, grep_flags *grep_flags);
void print_strs(char **estr, FILE *file, grep_flags *grep_flags,
                pattern_list *tmp, char *argv[], int *index, counters *cts);
int check_f(grep_flags *grep_flags, int argc, char *argv[]);
#endif  //  SRC_GREP_S21_GREP_H_
