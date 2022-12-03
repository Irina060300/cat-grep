#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
typedef struct pattern_list {
    char *pattern;
    struct pattern_list *next;
    int flag;
} pattern_list;

typedef struct grep_flags {
    int e, i, v, c, l, n, h, s, f, o;
    char illegal, ill_e;
} grep_flags;
int check_e(grep_flags *grep_flags, int argc, char *argv[]);
//void init_struct(int len, char *argv[], int i, grep_flags *grep_flags);
void init_struct(int len, char *argv[], int i, grep_flags *grep_flags, int j, int ill);
pattern_list *push_stdin(char *argv[], pattern_list *cur, int i);
// pattern_list *push_e(char *argv[], pattern_list *cur, int len_e, int i);
pattern_list *push_e(char *argv[], pattern_list *cur, int len_e, int i, int j);
void listprint(pattern_list *lst);
void str_parser(grep_flags *grep_flags, int argc, char *argv[], pattern_list **cur, int *index);
int check_pattern(char *estr, pattern_list *lst, grep_flags *grep_flags);
void check_s(char *argv[], int argc, grep_flags *grep_flags);
int print_pt_errors (grep_flags *grep_flags);
pattern_list * deletelem(pattern_list *lst, pattern_list *root);

