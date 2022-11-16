#include "header.h"

int main(int argc, char *argv[]) {
  cat_flags cat_flags = {0};
  int i = init_struct(argv, &cat_flags, argc);
  if (cat_flags.illegal)
    fprintf(stderr,
            "cat: illegal option -- %c\nusage: cat [-benstuv] [file ...]\n",
            cat_flags.illegal);
  else if (cat_flags.illegal_long)
    fprintf(stderr,
            "cat: illegal option -- -\nusage: cat [-benstuv] [file ...]\n");
  else if (i < argc)
    file_processing(i, argc, argv, cat_flags);
  return 0;
}