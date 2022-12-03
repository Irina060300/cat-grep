#include "s21_grep.h"


//FIX SHEPATTERN
int main(int argc, char *argv[]) {
    grep_flags grep_flags = {0};
    check_s(argv, argc, &grep_flags);
    if (argc > 1) {
        pattern_list *head = malloc(sizeof(pattern_list));
        int *index = calloc(argc, sizeof(int));
        head->pattern = NULL;
        pattern_list *cur = head, *tmp = head;
        str_parser(&grep_flags, argc, argv, &cur, index);
        if (!print_pt_errors(&grep_flags)) {
            int c_count, h = 0, str_number, path_count = 0;
            FILE *file;
            while (index[path_count]) {
                path_count++;
            }
            char *estr = NULL;
            while (index[h]) {
                str_number = 1;
                c_count = 0;
                file = fopen(argv[index[h]], "r");
                if (file != NULL) {
                    size_t size = 0;
                    ssize_t read = 0, read_next = 0;
                    while ((read = getline(&estr, &size, file)) != -1) {
                        int find = check_pattern(estr, tmp, &grep_flags);
                        if (!find) {
                            if (!(grep_flags.c || grep_flags.l)) {
                                if (path_count > 1 && !grep_flags.h) printf("%s:", argv[index[h]]);
                                if (grep_flags.n) printf("%d:", str_number);
                                printf("%s", estr);
                            } else {
                               c_count++;
                            }
                        }
                        read_next = getline(&estr, &size, file);
                        if (read_next != -1) {
                            fseek(file, -read_next, SEEK_CUR);
                        } else if (read_next == -1 && !find && !grep_flags.c && !grep_flags.l && estr[read - 1] != '\n'){
                            printf("\n");
                        }   
                        str_number++;
                    }
                    if (grep_flags.c && grep_flags.l) {
                        if (c_count) {
                            if(!grep_flags.h) printf("%s:", argv[index[h]]);
                            printf("1\n%s\n", argv[index[h]]);
                        } else {
                            if (!grep_flags.h) printf("%s:", argv[index[h]]);
                            printf("0\n");
                        }
                    } else if (grep_flags.c) {
                        if (path_count > 1 && !grep_flags.h) printf("%s:", argv[index[h]]);
                        printf("%d\n", c_count);
                    } else if (c_count && grep_flags.l) printf("%s\n", argv[index[h]]);
                    fclose(file);
                } else {
                    if (!grep_flags.s) fprintf(stderr, "grep: %s: No such file or directory\n", argv[index[h]]);
                }
                h++;
            }
        }
    } else {
        if(!grep_flags.s) fprintf(stderr, "Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for more information.\n");
    }
}

pattern_list *push_stdin(char *argv[], pattern_list *cur, int i) {
    pattern_list *add = malloc(sizeof(pattern_list));
    add->pattern = argv[i];
    add->flag = 0;
    add->next = NULL;
    cur->next = add;
    return add;
}

pattern_list * deletelem(pattern_list *lst, pattern_list *root){
  pattern_list *temp;
  temp = root;
  while (temp->next != lst) {
    temp = temp->next;
  }
  temp->next = lst->next; 
  free(lst); 
  return(temp);
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
void init_struct(int len, char *argv[], int i, grep_flags *grep_flags, int j, int ill) {
    if (argv[i][j] == 'i') grep_flags->i = 1;
    else if (argv[i][j] == 'v') grep_flags->v = 1;
    else if (argv[i][j] == 'c') grep_flags->c = 1;
    else if (argv[i][j] == 'l') grep_flags->l = 1;
    else if (argv[i][j] == 'n') grep_flags->n = 1;
    else if (argv[i][j] == 'h') grep_flags->h = 1;
    else if (ill == 1 && argv[i][j] != 'e') grep_flags->illegal = argv[i][j];
}
void str_parser(grep_flags *grep_flags, int argc, char *argv[], pattern_list **cur, int *index) {
    int count = 0, len = 0, len_e = 0, c = 1, h = 0, ill = 1;
    for (int i = 1; i < argc; i += c) {
        if (check_e(grep_flags, argc, argv)) {
            len = strlen(argv[i]);
            if (argv[i][0] == '-') {
                for(int j = 1; j < len; j++) {
                    if (argv[i][j] != 'e') {
                        init_struct(len, argv, i, grep_flags, j, ill);
                        if (grep_flags->illegal) ill++;
                        c = 1;
                    } else if (argv[i][j] == 'e') {
                        if (j == len - 1 && i < argc - 1) {
                            *cur = push_stdin(argv, *cur, i + 1);
                            c = 2;
                        } else if(j == len - 1 && i == argc - 1) grep_flags->ill_e = 'e';
                        else {
                            len_e = len - j - 1;
                            *cur = push_e(argv, *cur, len_e, i, j);
                            c = 1;
                            break;
                        }
                    }
                }
            } else {
                c = 1;
                index[h] = i;
                h++;
            }
        } else if (argv[i][0] == '-' && argv[i][1] != '\0') {
                len = strlen(argv[i]);
                for (int j = 1; j < len; j++){
                    init_struct(len, argv, i, grep_flags, j, ill);
                    if (grep_flags->illegal) ill++;
                } 
        } else if(!(argv[i][0] == '-' && argv[i][1] != '\0') && count == 0) {
            *cur = push_stdin(argv, *cur, i);
            count = 1;
        } else  {
            index[h++] = i;
        }
    }
}

int check_pattern(char *estr, pattern_list *lst, grep_flags *grep_flags) {
    pattern_list *p;
    size_t size = 10;
    p = lst->next;
    int fl = 0;
    regex_t regex;
    int reti, find, step = 0, ct = 0;
    do {
        if (grep_flags->i == 1) reti = regcomp(&regex, p->pattern, REG_ICASE);
        else reti = regcomp(&regex, p->pattern, 0);
        if (!reti) find = regexec(&regex, estr, 0, NULL, 0);
        if (p->pattern[0] == '.' && estr[0] == '\n') find = 1;
        if (find == 0) fl++;
        step++;
        p = p->next;
    } while (p != NULL); 
    if (grep_flags->v && fl == 0) {
            find = 0;
    } else if (grep_flags->v && fl == step) {
        find = 1;
    } else if (fl > 0) find = 0;
    regfree(&regex);
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
    } else if(grep_flags->ill_e) {
        if(!grep_flags->s) {
            fprintf(stderr, "grep: option requires an argument -- 'e'\n\
Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for more information.");
            count++;
        }
    }
    return count;
}
