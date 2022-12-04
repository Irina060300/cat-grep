void str_parser(grep_flags *grep_flags, int argc, char *argv[],
                pattern_list **cur, int *index) {
  FILE *file = NULL;
  char *estr = NULL, *pattern = NULL;
  size_t size = 0;
  ssize_t read = 0;
  int count = 0, len = 0, len_e = 0, c = 1, h = 0, ill = 1, ill_f = 0, fl = 0;
  for (int i = 1; i < argc; i += c) {
    len = strlen(argv[i]), c = 1;
    char path[len];
    if (check_e(grep_flags, argc, argv)) {
      if (argv[i][0] == '-')
        flag_processing(file, &estr, len, size, pattern, read, cur, argc, &c,
                        grep_flags, len_e, ill, i, argv, &count);
      else
        index[h++] = i;
    } else if (argv[i][0] == '-' && argv[i][1] != '\0') {
      for (int j = 1; j < len; j++) {
        if (argv[i][j] == 'f' && j == len - 1 && i < argc - 1) {
          file = fopen(argv[i + 1], "r");
          fl = -1;
          read_pat_file(file, argv, i, cur, &estr, pattern, size, read, &ill_f,
                        grep_flags, fl, path);
          c = 2;
          count = 1;
        } else if (argv[i][j] == 'f' && j == len - 1 && i == argc - 1)
          grep_flags->i_f = 'f';
        else if (argv[i][j] == 'f' && j < len - 1) {
          len_e = len - j - 1;
          fl = 1;
          for (int k = 0; k < len_e; k++) {
            path[k] = argv[i][k + j + 1];
          }
          path[len_e] = '\0';
          file = fopen(path, "r");
          read_pat_file(file, argv, i, cur, &estr, pattern, size, read, &ill_f,
                        grep_flags, fl, path);
          count = 1;
          break;
        } else {
          init_struct(argv, i, grep_flags, j, ill);
          if (grep_flags->illegal)
            ill++;
        }
      }
    } else if (!(argv[i][0] == '-' && argv[i][1] != '\0') && count == 0) {
      *cur = push_stdin(argv, *cur, i);
      count = 1;
    } else
      index[h++] = i;
  }
  free(estr); // for macos
}

void flag_processing(FILE *file, char **estr, int len, size_t size,
                     char *pattern, ssize_t read, pattern_list **cur, int argc,
                     int *c, grep_flags *grep_flags, int len_e, int ill, int i,
                     char *argv[], int *count) {
  char path[len];
  int fl = 0;
  for (int j = 1; j < len; j++) {
    if (argv[i][j] != 'e' && argv[i][j] != 'f') {
      init_struct(argv, i, grep_flags, j, ill);
      if (grep_flags->illegal)
        ill++;
    } else if ((argv[i][j] == 'e' || argv[i][j] == 'f') && j == len - 1 &&
               i < argc - 1) {
      if (argv[i][j] == 'e')
        *cur = push_stdin(argv, *cur, i + 1);
      else {
        fl = -1;
        path[0] = '\0';
        file = fopen(argv[i + 1], "r");
        read_pat_file(file, argv, i, cur, estr, pattern, size, read, count,
                      grep_flags, fl, path);
      }
      *c = 2;
    } else if ((argv[i][j] == 'e' || argv[i][j] == 'f') && j == len - 1 &&
               i == argc - 1) {
      if (argv[i][j] == 'e')
        grep_flags->ill_e = 'e';
      else
        grep_flags->i_f = 'f';
    } else if ((argv[i][j] == 'e' || argv[i][j] == 'f') && j < len - 1) {
      len_e = len - j - 1;
      if (argv[i][j] == 'e') {
        *cur = push_e(argv, *cur, len_e, i, j);
        break;
      } else {
        fl = 1;
        for (int k = 0; k < len_e; k++)
          path[k] = argv[i][k + j + 1];
        path[len_e] = '\0';
        file = fopen(path, "r");
        read_pat_file(file, argv, i - 1, cur, estr, pattern, size, read, count,
                      grep_flags, fl, path);
        break;
      }
    }
  }
}
void read_pat_file(FILE *file, char *argv[], int i, pattern_list **cur,
                   char **estr, char *pattern, size_t size, ssize_t read,
                   int *count, grep_flags *grep_flags, int fl, char *path) {
  if (file == NULL && *count == 0 && (fl == 1 || fl == -1)) {
    if (fl == -1) {
      if (strlen(argv[i + 1]) <= 255)
        strcpy(grep_flags->ill_f, argv[i + 1]);
      else
        (grep_flags->i_f = 'f');
    }
    if (fl == 1) {
      if (strlen(path) <= 255)
        strcpy(grep_flags->ill_f, path);
      else
        (grep_flags->i_f = 'f');
    }
    (*count)++;
  } else if (file) {
    while ((read = getline(estr, &size, file)) != -1) {
      pattern = malloc(sizeof(char) * size);
      strcpy(pattern, *estr);
      if (strlen(pattern) > 1 && pattern[strlen(pattern) - 1] == '\n')
        pattern[strlen(pattern) - 1] = '\0';
      if (pattern[strlen(pattern) - 1] == '$') {
        pattern[strlen(pattern) - 1] = '\n';
      }
      *cur = push_v(pattern, *cur); 
    }
    fclose(file);
    // free(*estr); //for ubunta
  }
}
