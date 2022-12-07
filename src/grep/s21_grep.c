#include "s21_grep.h"

int main(int argc, char *argv[]) {
  grep_flags grep_flags = {0};
  check_s(argv, argc, &grep_flags);
  if (argc > 1) {
    int *index = calloc(argc, sizeof(int));
    pattern_list *tmp = malloc(sizeof(pattern_list));
    tmp->pattern = NULL;
    tmp->next = NULL;
    pattern_list *cur = tmp;
    str_parser(&grep_flags, argc, argv, &cur, index);
    if (!print_pt_errors(&grep_flags)) {
      if (tmp->next != NULL) {
        is_o(tmp, &grep_flags);
        FILE *file = NULL;
        char *estr = NULL;
        counters cts = {0};
        while (index[cts.path_count]) (cts.path_count)++;
        while (index[cts.h]) {
          cts.str_number = 1;
          cts.c_count = 0;
          file = fopen(argv[index[cts.h]], "r");
          if (file) {
            print_strs(&estr, file, &grep_flags, tmp, argv, index, &cts);
            fclose(file);
          } else if (!grep_flags.s)
            fprintf(stderr, "grep: %s: No such file or directory\n",
                    argv[index[cts.h]]);
          cts.h++;
        }
        free(estr);
      }
    }
    deletelem(tmp);
    free(index);
  } else {
    if (!grep_flags.s)
      fprintf(stderr,
              "Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep "
              "--help' for more information.\n");
  }
  return 0;
}

void is_o(pattern_list *tmp, grep_flags *grep_flags) {
  pattern_list *p;
  p = tmp->next;
  do {
    if (strcmp(p->pattern, "\n") == 0) {
      grep_flags->o = 0;
    }
    p = p->next;
  } while (p != NULL);
}

void print_strs(char **estr, FILE *file, grep_flags *grep_flags,
                pattern_list *tmp, char *argv[], int *index, counters *cts) {
  fseek(file, 0, SEEK_END);
  fseek(file, -1, SEEK_CUR);
  char c = fgetc(file);
  fseek(file, 0, SEEK_SET);
  while ((cts->read = getline(estr, &cts->size, file)) != -1) {
    int find = 0;
    find = check_pattern(*estr, tmp, grep_flags);
    if (!find && !(grep_flags->c || grep_flags->l)) {
      if (cts->path_count > 1 && !grep_flags->h)
        printf("%s:", argv[index[cts->h]]);
      if (grep_flags->n) printf("%d:", cts->str_number);
      if ((grep_flags->v && grep_flags->o) || !grep_flags->o)
        printf("%s", *estr);
      else
        flag_o_proccess(*estr, grep_flags, file, tmp->next);
    } else if (!find)
      cts->c_count++;
    cts->read_next = getline(estr, &cts->size, file);
    if (cts->read_next != -1) {
      fseek(file, -cts->read_next, SEEK_CUR);
    } else if ((!find && cts->read_next == -1) &&
               !(grep_flags->c || grep_flags->l) &&
               (!grep_flags->o || (grep_flags->v && grep_flags->o)) &&
               c != '\n')
      printf("\n");
    cts->str_number++;
  }
  if (grep_flags->c && grep_flags->l) {
    if (cts->c_count) {
      if (!grep_flags->h && cts->path_count > 1)
        printf("%s:", argv[index[cts->h]]);
      printf("1\n%s\n", argv[index[cts->h]]);
    } else {
      if (!grep_flags->h) printf("%s:", argv[index[cts->h]]);
      printf("0\n");
    }
  } else if (grep_flags->c) {
    if (cts->path_count > 1 && !grep_flags->h)
      printf("%s:", argv[index[cts->h]]);
    printf("%d\n", cts->c_count);
  } else if (cts->c_count && grep_flags->l)
    printf("%s\n", argv[index[cts->h]]);
}

void flag_o_proccess(char *estr, grep_flags *grep_flags, FILE *file,
                     pattern_list *tmp) {
  int reti, find;
  size_t cursor = 0;
  while (tmp != NULL) {
    char *str = calloc(sizeof(char), strlen(tmp->pattern) + 1);
    if (str) {
      regex_t regex;
      regmatch_t pmatch = {0};
      if (grep_flags->i)
        reti = regcomp(&regex, tmp->pattern, REG_ICASE);
      else
        reti = regcomp(&regex, tmp->pattern, 0);
      if (!reti) {
        find = 0;
        while (cursor < strlen(estr) && !find) {
          find = regexec(&regex, estr + cursor, 1, &pmatch, 0);
          if (!find) {
            int i = 0;
            for (i = pmatch.rm_so; i < pmatch.rm_eo; i++) {
              str[i - pmatch.rm_so] = estr[i + cursor];
            }
            str[strlen(str)] = '\0';
            if (str[strlen(str) - 1] != '\n')
              printf("%s\n", str);
            else
              printf("%s", str);
            flag_o_proccess(str, grep_flags, file, tmp->next);
            cursor += pmatch.rm_eo;
          }
        }
      }
      tmp = tmp->next;
      regfree(&regex);
      free(str);
    }
  }
}
pattern_list *push_stdin(char *argv[], pattern_list *cur, int i) {
  pattern_list *add = malloc(sizeof(pattern_list));  //
  add->pattern = argv[i];
  add->flag = 0;
  add->next = NULL;
  cur->next = add;
  return add;
}

void deletelem(pattern_list *head) {
  pattern_list *temp;
  while (head) {
    temp = head->next;
    if (head->next && temp->flag == 1) free(temp->pattern);
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
        if (argv[i][j] == 'e') grep_flags->e = 1;
      }
    }
  }
  return grep_flags->e;
}

int check_f(grep_flags *grep_flags, int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    int len = strlen(argv[i]);
    if (argv[i][0] == '-') {
      for (int j = 1; j < len; j++) {
        if (argv[i][j] == 'f') grep_flags->f = 1;
      }
    }
  }
  return grep_flags->f;
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
  if (argv[i][j] == 'i')
    grep_flags->i = 1;
  else if (argv[i][j] == 'v')
    grep_flags->v = 1;
  else if (argv[i][j] == 'c')
    grep_flags->c = 1;
  else if (argv[i][j] == 'l')
    grep_flags->l = 1;
  else if (argv[i][j] == 'n')
    grep_flags->n = 1;
  else if (argv[i][j] == 'h')
    grep_flags->h = 1;
  else if (argv[i][j] == 'f')
    grep_flags->f = 1;
  else if (argv[i][j] == 's')
    grep_flags->s = 1;
  else if (argv[i][j] == 'o')
    grep_flags->o = 1;
  else if (ill == 0 && argv[i][j] != 'e')
    grep_flags->illegal = argv[i][j];
}

void str_parser(grep_flags *grep_flags, int argc, char *argv[],
                pattern_list **cur, int *index) {
  FILE *file = NULL;
  char *estr = NULL, *pattern = NULL;
  pars p = {0};
  p.c = 1;
  int count = 0;
  int che_f = check_f(grep_flags, argc, argv);
  for (int i = 1; i < argc; i += p.c) {
    int fl = 0;
    p.len = strlen(argv[i]), p.c = 1;
    char path[p.len];
    if (check_e(grep_flags, argc, argv)) {
      if (argv[i][0] == '-')
        flag_processing(file, &estr, pattern, cur, argc, grep_flags, i, argv,
                        &p);
      else
        index[p.h++] = i;
    } else if (argv[i][0] == '-' && argv[i][1] != '\0') {
      for (int j = 1; j < p.len; j++) {
        if (argv[i][j] == 'f' && j == p.len - 1 && i < argc - 1) {
          file = fopen(argv[i + 1], "r");
          fl = -1, p.c = 2, count = 1;
          read_pat_file(file, argv, i, cur, &estr, pattern, grep_flags, path,
                        &p, fl);
        } else if (argv[i][j] == 'f' && j == p.len - 1 && i == argc - 1)
          grep_flags->i_f = 'f';
        else if (argv[i][j] == 'f' && j < p.len - 1) {
          p.len_e = p.len - j - 1;
          fl = 1;
          for (int k = 0; k < p.len_e; k++) path[k] = argv[i][k + j + 1];
          path[p.len_e] = '\0';
          file = fopen(path, "r");
          read_pat_file(file, argv, i, cur, &estr, pattern, grep_flags, path,
                        &p, fl);
          count = 1;
          break;
        } else {
          init_struct(argv, i, grep_flags, j, p.ill);
          if (grep_flags->illegal) p.ill++;
        }
      }
    } else if (!(argv[i][0] == '-' && argv[i][1] != '\0') && count == 0 &&
               che_f == 0) {
      *cur = push_stdin(argv, *cur, i);
      count = 1;
    } else
      index[p.h++] = i;
  }
  free(estr);
}

void flag_processing(FILE *file, char **estr, char *pattern, pattern_list **cur,
                     int argc, grep_flags *grep_flags, int i, char *argv[],
                     pars *p) {
  char path[p->len];
  int fl;
  for (int j = 1; j < p->len; j++) {
    if (argv[i][j] != 'e' && argv[i][j] != 'f') {
      init_struct(argv, i, grep_flags, j, p->ill);
      if (grep_flags->illegal) p->ill++;
    } else if ((argv[i][j] == 'e' || argv[i][j] == 'f') && j == p->len - 1 &&
               i < argc - 1) {
      if (argv[i][j] == 'e')
        *cur = push_stdin(argv, *cur, i + 1);
      else {
        fl = -1;
        path[0] = '\0';
        file = fopen(argv[i + 1], "r");
        read_pat_file(file, argv, i, cur, estr, pattern, grep_flags, path, p,
                      fl);
      }
      p->c = 2;
    } else if ((argv[i][j] == 'e' || argv[i][j] == 'f') && j == p->len - 1 &&
               i == argc - 1) {
      if (argv[i][j] == 'e')
        grep_flags->ill_e = 'e';
      else
        grep_flags->i_f = 'f';
    } else if ((argv[i][j] == 'e' || argv[i][j] == 'f') && j < p->len - 1) {
      p->len_e = p->len - j - 1;
      if (argv[i][j] == 'e') {
        *cur = push_e(argv, *cur, p->len_e, i, j);
        break;
      } else {
        fl = 1;
        for (int k = 0; k < p->len_e; k++) path[k] = argv[i][k + j + 1];
        path[p->len_e] = '\0';
        file = fopen(path, "r");
        read_pat_file(file, argv, i, cur, estr, pattern, grep_flags, path, p,
                      fl);
        break;
      }
    }
  }
}
void read_pat_file(FILE *file, char *argv[], int i, pattern_list **cur,
                   char **estr, char *pattern, grep_flags *grep_flags,
                   char *path, pars *p, int fl) {
  if (file == NULL && p->ill_f == 0 && (fl == 1 || fl == -1)) {
    if (fl == -1) {
      if (strlen(argv[i + 1]) <= 255)
        strcpy(grep_flags->ill_f, argv[i + 1]);
      else {
        fprintf(stderr, "grep: %s: File name too long\n", argv[i + 1]);
        exit(1);
      }
    }
    if (fl == 1) {
      if (strlen(path) <= 255)
        strcpy(grep_flags->ill_f, path);
      else {
        fprintf(stderr, "grep: %s: File name too long\n", path);
        exit(1);
      }
    }
    p->ill_f++;
  } else if (file) {
    while ((p->read = getline(estr, &p->size, file)) != -1) {
      pattern = malloc(sizeof(char) * p->size);
      strcpy(pattern, *estr);
      // pattern = strdup(*estr);
      if (strlen(pattern) > 1 && pattern[strlen(pattern) - 1] == '\n')
        pattern[strlen(pattern) - 1] = '\0';
      if (pattern[strlen(pattern) - 1] == '$') {
        pattern[strlen(pattern) - 1] = '\n';
      }
      *cur = push_v(pattern, *cur);
    }
    fclose(file);
  }
}
pattern_list *push_v(char *pattern, pattern_list *cur) {
  pattern_list *add = malloc(sizeof(pattern_list));  //
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
    if (grep_flags->i == 1)
      reti = regcomp(&regex, p->pattern, REG_ICASE);
    else
      reti = regcomp(&regex, p->pattern, 0);
    if (!reti) find = regexec(&regex, estr, 0, NULL, 0);
    if (p->pattern[0] == '.' && estr[0] == '\n') find = 1;
    if (p->pattern[0] == '\n' && estr[(int)strlen(estr) - 1] != '\n') find = 0;
    if (find == 0) fl++;
    step++;
    p = p->next;
    regfree(&regex);
  } while (p != NULL);
  if (grep_flags->v && fl == 0)
    find = 0;
  else if (grep_flags->v && fl > 0)
    find = 1;
  else if (!grep_flags->v && fl > 0)
    find = 0;
  return find;
}

void check_s(char *argv[], int argc, grep_flags *grep_flags) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] == 's' && argv[i][2] == '\0') {
      grep_flags->s = 1;
      break;
    }
  }
}

int print_pt_errors(grep_flags *grep_flags) {
  int count = 0;
  if (grep_flags->illegal != '\0') {
    fprintf(stderr,
            "grep: invalid option -- '%c'\n"
            "Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' "
            "for more information.\n",
            grep_flags->illegal);
    count++;
  } else if (grep_flags->ill_f[0] != '\0') {
    fprintf(stderr, "grep: %s: No such file or directory\n", grep_flags->ill_f);
    count++;
  } else if (grep_flags->ill_e == 'e') {
    fprintf(stderr,
            "grep: option requires an argument -- 'e'\n"
            "Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep "
            "--help' for more information.\n");
    count++;
  } else if (grep_flags->i_f == 'f') {
    fprintf(stderr,
            "grep: option requires an argument -- 'f'\n"
            "Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep "
            "--help' for more information.\n");
    count++;
  }
  return count;
}
