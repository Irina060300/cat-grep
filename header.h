#ifndef HEADER_H_
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
    int path;
} cat_flags;
int init_struct(char *argv[], cat_flags *cat_flags, int argc);
void create_str(char strs[][10000], FILE *file, int *i);
void cat_s(char strs[][10000], int *len);
void cat_E(char strs[][10000], int len);
void cat_T(char strs[][10000], int len);
#endif  //  HEADER_H_