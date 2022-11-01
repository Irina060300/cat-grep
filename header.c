#include "header.h"

int init_struct(char *argv[], cat_flags *cat_flags, int argc) {
    int i = 1;
    while (i < argc) {
        if (argv[i][0] == '-' && argv[i][1] != '-' && argv[i][1] != '\0' && fopen(argv[i], "r") == NULL) {
            for (int j = 1; j < strlen(argv[i]); j++) {
                if (argv[i][j] == 'b')
                    cat_flags->b = 1;
                else if (argv[i][j] == 'v')
                    cat_flags->v = 1;
                else if (argv[i][j] == 'n')
                    cat_flags->n = 1;
                else if (argv[i][j] == 's')
                    cat_flags->s = 1;
                else if (argv[i][j] == 'E')
                    cat_flags->E = 1;
                else if (argv[i][j] == 'e') {
                    cat_flags->E = 1;
                    cat_flags->v = 1;
                } else if (argv[i][j] == 'T')
                    cat_flags->T = 1;
                else if (argv[i][j] == 't') {
                    cat_flags->v = 1;
                    cat_flags->T = 1;
                } else
                    cat_flags->illegal = argv[i][j];
            }
            i += 1;
        } else if (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] != '\0' && fopen(argv[i], "r") == NULL) {
            if (strcmp(argv[i], "--number-nonblank") == 0)
                cat_flags->b = 1;
            else if (strcmp(argv[i], "--number") == 0)
                cat_flags->n = 1;
            else if (strcmp(argv[i], "--squeeze-blank") == 0)
                cat_flags->s = 1;
            else
                cat_flags->illegal_long = 1;
            i += 1;
        } else
            break;
    }
    return i;
}

void cat_b(int *num, char *estr) {
    if (estr[0] != '\n') {
        printf("%6d\t", *num);
        *num = *num + 1;
    }
}

void cat_n(int *num, char *estr) {
    printf("%6d\t", *num);
    *num = *num + 1;
}

void cat_T(char *estr, int j, cat_flags cat_flags) {
    if (cat_flags.T == 1)
        printf("%s", "^I");
    else
        printf("%c", estr[j]);
}
void cat_E(char *estr, int j, cat_flags cat_flags) {
    if (cat_flags.E == 1)
        printf("%s", "$\n");
    else
        printf("%c", estr[j]);
}
void cat_v(char *estr, int j, cat_flags cat_flags) {
    if (cat_flags.v == 1 && (int)estr[j] >= 0 && (int)estr[j] <= 31) {
        printf("%c", '^');
        printf("%c", (char)(int)estr[j] + 64);
    } else if (cat_flags.v == 1 && (int)estr[j] == 127) {
        printf("%c", '^');
        printf("%c", (char)(int)estr[j] - 64);
    } else {
        printf("%c", estr[j]);
    }
}

void cat_s(cat_flags cat_flags, char *estr, ssize_t read, size_t size, FILE *file, int *flag) {
    if (cat_flags.s == 1 && estr[0] == '\n') {
        while (estr[0] == '\n') {
            if ((read = getline(&estr, &size, file)) == -1) {
                *flag = *flag + 1;
                break;
            }
        }
        if (*flag == 0) fseek(file, -strlen(estr), SEEK_CUR);
    }
}

void file_processing(int i, int argc, char *argv[], cat_flags cat_flags) {
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
                if (cat_flags.b == 1) cat_b(&num, estr);
                else if (cat_flags.n == 1) cat_n(&num, estr);
                for (int j = 0; j < strlen(estr); j++) {
                    if (estr[j] == '\t') cat_T(estr, j, cat_flags);
                    else if (estr[j] == '\n') cat_E(estr, j, cat_flags);
                    else if (((int)estr[j] >= 0 && (int)estr[j] <= 31) || (int)estr[j] == 127) cat_v(estr, j, cat_flags);
                    else printf("%c", estr[j]);
                }
                cat_s(cat_flags,estr, read, size, file, &flag);
            }
            free(estr);
            fclose(file);
        } else printf("cat: %s: No such file or directory\n", argv[i]);
        i++;
    }
}
