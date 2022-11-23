#include "s21_grep.h"

int main(int argc, char *argv[]) {
    grep_flags grep_flags = {0};
    check_s(argv, argc, &grep_flags);
    if (argc > 1) {
        pattern_list *tmp = malloc(sizeof(pattern_list));
        int *index = calloc(argc, sizeof(int));
        tmp->pattern = NULL;
        tmp->next = NULL;
        pattern_list *cur = tmp;
        str_parser(&grep_flags, argc, argv, &cur, index);
        if (!print_pt_errors(&grep_flags)) {
            int c_count, h = 0, str_number, path_count = 0;
            FILE *file = NULL;
            while (index[path_count]) path_count++;
            char *estr = NULL;
            while (index[h]) {
                str_number = 1;
                c_count = 0;
                file = fopen(argv[index[h]], "r");
                if (file != NULL) {
                    // size_t size = 0;
                    // ssize_t read = 0, read_next = 0;
                    // while ((read = getline(&estr, &size, file)) != -1) {
                    //     int find = check_pattern(estr, tmp, &grep_flags);
                    //     if (!find &&!(grep_flags.c || grep_flags.l)) {
                    //             if (path_count > 1 && !grep_flags.h) printf("%s:", argv[index[h]]);
                    //             if (grep_flags.n) printf("%d:", str_number);
                    //             printf("%s", estr);
                    //     } else if (!find) c_count++;
                    //     read_next = getline(&estr, &size, file);
                    //     if (read_next != -1) fseek(file, -read_next, SEEK_CUR);
                    //     else if (read_next == -1 && !find && !grep_flags.c && !grep_flags.l && estr[read - 1] != '\n') printf("\n");
                    //     str_number++;
                    // }
                    print_strs(&estr, file, &grep_flags, &tmp, argv, &str_number, path_count, &c_count, index, h);
                    // if (grep_flags.c && grep_flags.l) {
                    //     if (c_count) {
                    //         if(!grep_flags.h) printf("%s:", argv[index[h]]);
                    //         printf("1\n%s\n", argv[index[h]]);
                    //     } else {
                    //         if (!grep_flags.h) printf("%s:", argv[index[h]]);
                    //         printf("0\n");
                    //     }
                    // } else if (grep_flags.c) {
                    //     if (path_count > 1 && !grep_flags.h) printf("%s:", argv[index[h]]);
                    //     printf("%d\n", c_count);
                    // } else if (c_count && grep_flags.l) printf("%s\n", argv[index[h]]);
                    fclose(file);
                    free(estr);
                } else if (!grep_flags.s) fprintf(stderr, "grep: %s: No such file or directory\n", argv[index[h]]);
                h++;
            }
        }
        //listprint(tmp);
        deletelem(tmp);
        free(index);
    } else {
        if(!grep_flags.s) fprintf(stderr, "Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for more information.\n");
    }
    return 0;
}
void print_strs(char **estr, FILE *file, grep_flags *grep_flags, pattern_list **tmp, char *argv[], int *str_number, \
int path_count, int *c_count, int *index, int h) {
    size_t size = 0;
    ssize_t read = 0, read_next = 0;
    while ((read = getline(estr, &size, file)) != -1) {
        int find = check_pattern(*estr, *tmp, grep_flags);
        if (!find &&!(grep_flags->c || grep_flags->l)) {
                if (path_count > 1 && !grep_flags->h) printf("%s:", argv[index[h]]);
                if (grep_flags->n) printf("%d:", *str_number);
                printf("%s", *estr);
        } else if (!find) (*c_count)++;
        read_next = getline(estr, &size, file);
        if (read_next != -1) fseek(file, -read_next, SEEK_CUR);
        else if (read_next == -1 && !find && !grep_flags->c && !grep_flags->l && (*estr)[read - 1] != '\n') printf("\n");
        (*str_number)++;
    }
    if (grep_flags->c && grep_flags->l) {
        if (*c_count) {
            if(!grep_flags->h) printf("%s:", argv[index[h]]);
            printf("1\n%s\n", argv[index[h]]);
        } else {
            if (!grep_flags->h) printf("%s:", argv[index[h]]);
            printf("0\n");
        }
    } else if (grep_flags->c) {
        if (path_count > 1 && !grep_flags->h) printf("%s:", argv[index[h]]);
        printf("%d\n", (*c_count));
    } else if ((*c_count) && grep_flags->l) printf("%s\n", argv[index[h]]);
}

pattern_list *push_stdin(char *argv[], pattern_list *cur, int i) {
    pattern_list *add = malloc(sizeof(pattern_list)); // 
    add->pattern = argv[i];
    add->flag = 0;
    add->next = NULL;
    cur->next = add;
    return add;
}

void deletelem(pattern_list *head) {
  pattern_list *temp;
  while(head) {
    temp = head->next;
    if(head->next && temp->flag == 1) free(temp->pattern);
    free(head);
    head = temp;
  }
}


void listprint(pattern_list *lst) {
  pattern_list *p;
  p = lst->next;
  do {
    printf("pattern: %s\n", p->pattern);
    p = p->next;
  } while (p != NULL);
}

int check_e(grep_flags *grep_flags, int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        int len = strlen(argv[i]);
        if (argv[i][0] == '-') {
            for (int j = 1; j < len; j++) {
                if(argv[i][j] == 'e') grep_flags->e = 1;
            }
        }
    }
    return grep_flags->e;
}

pattern_list *push_e(char *argv[], pattern_list *cur, int len_e, int i, int j) {
    pattern_list *add = malloc(sizeof(pattern_list));
    for (int k = 0; k < len_e; k++) argv[i][k] = argv[i][k + j + 1];
    argv[i][len_e] = '\0';
    add->pattern = argv[i];
    add->flag = 0;
    add->next = NULL;
    cur->next = add;
    return add;
}
void init_struct(char *argv[], int i, grep_flags *grep_flags, int j, int ill) {
    if (argv[i][j] == 'i') grep_flags->i = 1;
    else if (argv[i][j] == 'v') grep_flags->v = 1;
    else if (argv[i][j] == 'c') grep_flags->c = 1;
    else if (argv[i][j] == 'l') grep_flags->l = 1;
    else if (argv[i][j] == 'n') grep_flags->n = 1;
    else if (argv[i][j] == 'h') grep_flags->h = 1;
    else if (argv[i][j] == 'f') grep_flags->f = 1;
    else if (argv[i][j] == 'h') grep_flags->h = 1;
    else if (argv[i][j] == 's') grep_flags->s = 1;
    else if (ill == 1 && argv[i][j] != 'e') grep_flags->illegal = argv[i][j];
}


void str_parser(grep_flags *grep_flags, int argc, char *argv[], pattern_list **cur, int *index) {
    FILE *file = NULL;
    char *estr, *pattern = NULL;
    size_t size = 0;
    ssize_t read = 0;
    int count = 0, len = 0, len_e = 0, c = 1, h = 0, ill = 1, ill_f = 0, fl = 0;
    for (int i = 1; i < argc; i += c) {
        len = strlen(argv[i]), c = 1;
        char path[len];
        if (check_e(grep_flags, argc, argv)) {
            if (argv[i][0] == '-') flag_processing(file, &estr, len ,size, pattern,read, cur,\
            argc,  &c, grep_flags, len_e, ill, i, argv, &count);
            else index[h++] = i;
        } else if (argv[i][0] == '-' && argv[i][1] != '\0') {
            for (int j = 1; j < len; j++){
                if (argv[i][j] == 'f' && j == len - 1 && i < argc - 1) {
                    file = fopen(argv[i + 1], "r");
                    fl = -1;
                    read_pat_file(file, argv, i, cur, &estr, pattern, size, read, &ill_f, grep_flags, fl, path);
                    c = 2;
                    count = 1;
                } else if(argv[i][j] == 'f' && j == len - 1 && i == argc - 1) grep_flags->i_f = 'f';
                else if (argv[i][j] == 'f' && j < len - 1) {
                    len_e = len - j - 1;
                    fl = 1;
                    for (int k = 0; k < len_e; k++) {
                        path[k] = argv[i][k + j + 1];
                    }
                    path[len_e] = '\0';
                    file = fopen(path, "r");
                    read_pat_file(file, argv, i, cur, &estr, pattern, size, read, &ill_f, grep_flags, fl, path);
                    count = 1;
                    break;
                } else {
                    init_struct(argv, i, grep_flags, j, ill);
                    if (grep_flags->illegal) ill++;
                }
            } 
        } else if(!(argv[i][0] == '-' && argv[i][1] != '\0') && count == 0) {
            *cur = push_stdin(argv, *cur, i);
            count = 1;
        } else {
            index[h++] = i;
        }
    }
}

void flag_processing(FILE *file, char **estr, int len , size_t size, char *pattern, ssize_t read,\
pattern_list **cur, int argc, int *c, grep_flags *grep_flags, int len_e, int ill, int i, char *argv[], int *count) { 
    char path[len];
    int fl = 0;
    for(int j = 1; j < len; j++) {
        if (argv[i][j] != 'e' && argv[i][j] != 'f') {
            init_struct(argv, i, grep_flags, j, ill);
            if (grep_flags->illegal) ill++;
        } else if ((argv[i][j] == 'e' || argv[i][j] == 'f') && j == len - 1 && i < argc - 1) {
                if (argv[i][j] == 'e') *cur = push_stdin(argv, *cur, i + 1);
                else {
                    fl = -1;
                    file = fopen(argv[i + 1], "r");
                    read_pat_file(file, argv, i, cur, estr, pattern, size, read, count, grep_flags, fl, path);
                }
                *c = 2; 
        } else if((argv[i][j] == 'e' || argv[i][j] == 'f') && j == len - 1 && i == argc - 1) {
           if (argv[i][j] == 'e' ) grep_flags->ill_e = 'e';
           else grep_flags->i_f = 'f';
        } else if ((argv[i][j] == 'e' || argv[i][j] == 'f') && j < len - 1) {
            len_e = len - j - 1;
            if (argv[i][j] == 'e') {
                *cur = push_e(argv, *cur, len_e, i, j);
                break;
            } else {
                fl = 1;
                for (int k = 0; k < len_e; k++) path[k] = argv[i][k + j + 1];
                path[len_e] = '\0';
                file = fopen(path, "r");
                read_pat_file(file, argv, i - 1, cur, estr, pattern, size, read, count, grep_flags, fl, path);
                break;
            }
        }
    }
}
void read_pat_file(FILE *file, char *argv[], int i, pattern_list **cur, char **estr, char *pattern,\
size_t size, ssize_t read, int *count, grep_flags *grep_flags, int fl, char *path) {
    if (file == NULL && *count == 0 && (fl == 1 || fl == -1)) {
        if (fl == -1) {
            strcpy(grep_flags->ill_f, argv[i+1]);
        }
        if (fl == 1) {
            strcpy(grep_flags->ill_f, path);
        }
        (*count)++;
    } else if (file != NULL){
        while ((read = getline(estr, &size, file)) != -1) {
            pattern = malloc(sizeof(char) * size);
            strcpy(pattern, *estr);
            if (strlen(pattern) > 1 && pattern[read - 1] == '\n') pattern[read - 1] = '\0';
            *cur = push_v(pattern, *cur);
        }
        fclose(file);
        free(*estr);
    }
}
pattern_list *push_v(char *pattern, pattern_list *cur) {
    pattern_list *add = malloc(sizeof(pattern_list)); // 
    add->pattern = pattern;
    add->flag = 1;
    add->next = NULL;
    cur->next = add;
    return add;
}

int check_pattern(char *estr, pattern_list *tmp, grep_flags *grep_flags) {
    pattern_list *p;
    p = tmp->next;
    regex_t regex;
    int reti, find, step = 0, fl = 0;
    do {
        if (grep_flags->i == 1) reti = regcomp(&regex, p->pattern, REG_ICASE);
        else reti = regcomp(&regex, p->pattern, 0);
        if (!reti) find = regexec(&regex, estr, 0, NULL, 0);
        if (p->pattern[0] == '.' && estr[0] == '\n') find = 1;
        if (p->pattern[0] == '\n' && estr[(int)strlen(estr) - 1] != '\n') find = 0;
        if (find == 0) fl++;
        step++;
        p = p->next;
        regfree(&regex);
    } while (p != NULL); 
    if (grep_flags->v && fl == 0) find = 0;
    else if (grep_flags->v && fl > 0) find = 1;
    else if (!grep_flags->v && fl > 0) find = 0;
    return find;
}

void check_s(char *argv[], int argc, grep_flags *grep_flags) {
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 's' && argv[i][2] == '\0') {
            grep_flags->s = 1;
            break;
        }
    }
}

int print_pt_errors (grep_flags *grep_flags) {
    int count = 0;
    if (grep_flags->illegal != '\0') {
        if(!grep_flags->s) {
            fprintf(stderr, "grep: invalid option -- '%c'\n\
Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for more information.\n", grep_flags->illegal);
            count++;
        }
    } else if (grep_flags->ill_f[0] != '\0') { 
        if (!grep_flags->s) {
            fprintf(stderr, "grep: %s: No such file or directory\n", grep_flags->ill_f);
            count++;
        }
    } else if(grep_flags->ill_e) {
        if(!grep_flags->s) {
            fprintf(stderr, "grep: option requires an argument -- 'e'\n\
Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for more information.\n");
            count++;
        }
    } else if(grep_flags->i_f) {
        if(!grep_flags->s) {
            fprintf(stderr, "grep: option requires an argument -- 'f'\n\
Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for more information.\n");
            count++;
        }
    }
    return count;
}