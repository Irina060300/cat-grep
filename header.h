#ifndef HEADER_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE
#define ARRAY_SIZE 15
typedef struct cat_flags {
    int n;
    int b;
    int e;
    int v;
    int s;
    int t;
    int E;
    int T;
    char path[100][100];
} cat_flags;
int init_struct(char *argv[], cat_flags *cat_flags, int argc);
void create_str(char **strs, FILE *file, int *i);
void cat_s(char **strs, int *len);
void cat_E(char **strs, int len);
void cat_T(char **strs, int len);
#endif  //  HEADER_H_