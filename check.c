#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *file;
  file = fopen("a.txt", "r");
  int h = fseek(file, -1, SEEK_END);
  char *estr = NULL;
  ssize_t size = 0;
  ssize_t read;
  read = getline(&estr, &size, file);
  printf("read = %ld\n", read);
  printf("%d", (int)'\n');
  return 0;
}