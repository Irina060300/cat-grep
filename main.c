#include "header.h"

int main(int argc, char *argv[]) {
    cat_flags cat_flags = {0};
    int i = init_struct(argv, &cat_flags, argc);
    if (cat_flags.illegal != 0) {
        printf("cat: illegal option -- %c\nusage: cat [-benstuv] [file ...]\n", cat_flags.illegal);
    } else if(cat_flags.illegal_long[0] !='\0') {
        printf("cat: illegal option '%s'\nusage: cat [-benstuv] [file ...]\n", cat_flags.illegal_long);
    } else {
        FILE *file;
        while (i < argc) {
            file = fopen(argv[i], "r");
            if (file != NULL) {
                int num = 1;
                char *estr = NULL;
                ssize_t size = 0;
                ssize_t read;
                int flag = 0;
                while ((read = getline(&estr, &size, file)) != -1) {
                    if (cat_flags.b == 1) {
                        if (estr[0] != '\n') {
                            printf("%6d\t", num);
                            num++;
                        }
                    } else if (cat_flags.n == 1) {
                        printf("%6d\t", num);
                        num++;
                    }
                    for (int j = 0; j < strlen(estr); j++) {
                        if (estr[j] == '\t') {
                            if (cat_flags.T == 1)
                                printf("%s", "^I");
                            else
                                printf("%c", estr[j]);
                        } else if (estr[j] == '\n') {
                            if (cat_flags.E == 1)
                                printf("%s", "$\n");
                            else
                                printf("%c", estr[j]);
                        } else if ((int)estr[j] >= 0 && (int)estr[j] <= 31) {
                            if (cat_flags.v == 1) {
                                printf("%c", '^');
                                printf("%c", (char)(int)estr[j] + 64);
                            } else
                                printf("%c", estr[j]);
                        } else if ((int)estr[j] == 127) {
                            if (cat_flags.v == 1) {
                                printf("%c", '^');
                                printf("%c", (char)(int)estr[j] - 64);
                            } else
                                printf("%c", estr[j]);
                        } else
                            printf("%c", estr[j]);
                    }
                    if (cat_flags.s == 1 && estr[0] == '\n') {
                        while (estr[0] == '\n') {
                            if ((read = getline(&estr, &size, file)) == -1) {
                                flag++;
                                break;
                            }
                        }
                        if (flag == 0) fseek(file, -strlen(estr), SEEK_CUR);
                    }
                }
                free(estr);
            } else {
                printf("cat: %s: No such file or directory\n", argv[i]);
            }
            i++;
        }
    }
    return 0;
}