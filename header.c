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
                } else {
                    cat_flags->illegal = argv[i][j];
                }
            }
            i += 1;
        } else if (argv[i][0] == '-' && argv[i][1] == '-') {
            if (strcmp(argv[i], "--number-nonblank") == 0)
                cat_flags->b = 1;
            else if (strcmp(argv[i], "--number") == 0)
                cat_flags->n = 1;
            else if (strcmp(argv[i], "--squeeze-blank") == 0)
                cat_flags->s = 1;
            else
                strcpy(cat_flags->illegal_long, argv[i]);
            i += 1;
        } else {
            break;
        }
    }
    return i;
}
