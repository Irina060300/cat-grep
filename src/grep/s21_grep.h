#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <getopt.h>
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
int check_e(grep_flags *grep_flags, int argc, char *argv[]);
void init_struct(char *argv[], int i, grep_flags *grep_flags, int j, int ill);
pattern_list *push_stdin(char *argv[], pattern_list *cur, int i);
pattern_list *push_e(char *argv[], pattern_list *cur, int len_e, int i, int j);
void listprint(pattern_list *lst);
void str_parser(grep_flags *grep_flags, int argc, char *argv[], pattern_list **cur, int *index);
int check_pattern(char *estr, pattern_list *tmp, grep_flags *grep_flags);
void check_s(char *argv[], int argc, grep_flags *grep_flags);
int print_pt_errors (grep_flags *grep_flags);
void deletelem( pattern_list *tmp);
pattern_list *push_v(char *pattern, pattern_list *cur);
void flag_processing(FILE * file, char **estr, int len , size_t size, char *pattern, ssize_t read,\
pattern_list **cur, int argc, int *c, grep_flags *grep_flags, int len_e, int ill, int i, char *argv[], int *count);
void read_pat_file(FILE *file, char *argv[], int i, pattern_list **cur, char **estr, char *pattern,\
size_t size, ssize_t read, int *count, grep_flags *grep_flags, int fl, char *path);
void print_strs(char **estr, FILE *file, grep_flags *grep_flags,\
 pattern_list **tmp, char *argv[], int *str_number, int path_count, int *c_count, int *index, int h);
