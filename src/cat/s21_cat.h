#define _GNU_SOURCE
#ifndef S21_CAT_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cat_flags {
  int n;
  int b;
  int e;
  int v;
  int s;
  int t;
  int E;
  int T;
  char illegal;
  int illegal_long;
} cat_flags;
int init_struct(char *argv[], cat_flags *cat_flags, int argc);
void cat_b(int *num, const char *estr);
void cat_T(char *estr, int j, cat_flags cat_flags);
void cat_n(int *num);
void cat_E(char *estr, int j, cat_flags cat_flags);
void cat_v(char *estr, int j, cat_flags cat_flags);
void cat_s(cat_flags cat_flags, char **estr, ssize_t read, size_t size,
           FILE *file, int *flag);
void file_processing(int i, int argc, char *argv[], cat_flags cat_flags);
#endif  //  S21_CAT_H_