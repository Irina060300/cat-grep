#include "header.h"

int init_struct(char *argv[], cat_flags *cat_flags, int argc) {
    int i = 0;
    cat_flags->b = 0;
    cat_flags->n = 0;
    cat_flags->e = 0;
    cat_flags->v = 0;
    cat_flags->t = 0;
    cat_flags->s = 0;
    cat_flags->E = 0;
    int count_path = 0;
    while (i < argc) {
        if (argv[i][0] == '-' && argv[i][1] == 'b' && argv[i][2] == '\0') {
            cat_flags->b = 1;
        } else if (argv[i][0] == '-' && argv[i][1] == 'n' && argv[i][2] == '\0') {
            cat_flags->n = 1;
        } else if (argv[i][0] == '-' && argv[i][1] == 'e' && argv[i][2] == '\0') {
            cat_flags->e = 1;
        } else if (argv[i][0] == '-' && argv[i][1] == 'v' && argv[i][2] == '\0') {
            cat_flags->v = 1;
        } else if (argv[i][0] == '-' && argv[i][1] == 't' && argv[i][2] == '\0') {
            cat_flags->t = 1;
        } else if (argv[i][0] == '-' && argv[i][1] == 's' && argv[i][2] == '\0') {
            cat_flags->s = 1;
        } else if (argv[i][0] == '-' && argv[i][1] == 'E' && argv[i][2] == '\0') {
            cat_flags->E = 1;
        } else if (argv[i][0] == '-' && argv[i][1] == 'T' && argv[i][2] == '\0') {
            cat_flags->T = 1;
        } else {
            if (i != 0) {
                // printf("gg\n");
                cat_flags->path = i;
                // printf("cap = %d\n", cat_flags->path);
                count_path += 1;
            }
        }
        i++;
    }
    return count_path;
}
void create_str(char strs[][10000], FILE *file, int *i) {
    char *estr;
    char str[500];
    while (1) {
        estr = fgets(str, 255 * sizeof(char), file);
        // printf("%6d\t%s", *i + 1, strs[*i]);
        if (feof(file) != 0) {
            if (estr == NULL) {
                break;
            } else {
                printf("Read mistake");
            }
        }
        for (int j = 0; j < strlen(estr); j++) {
            strs[*i][j] = estr[j];
        }
        *i = *i + 1;
    }
}

void cat_s(char strs[][10000], int *len) {
    int flag;
    int i;
    int h = 0, count = 0;
    while (1) {
        flag = 0;
        for (i = 0; i < *len - 1; i++) {
            if (strs[i][1] == '\n' && strs[i + 1][1] == '\n') flag++;
        }
        if (flag > 0) {
            for (i = 0; i < *len - 1; i++) {
                if (strs[i][1] == '\n' && strs[i + 1][1] == '\n') {
                    h = i + 1;
                    break;
                }
            }
            for (i = h; i < *len - 1; i++) {
                int j;
                for (j = 0; j < strlen(strs[i + 1]); j++) {
                    strs[i][j] = strs[i + 1][j];
                }
                strs[i][j] = '\0';
                // printf("%s", strs[i]);
            }

            *len = *len - 1;
            // for (i = 0; i < *len; i++) {
            //     printf("%6d\t%s", i + 1, strs[i]);
            // }
            // count++;
            // if (count == 6) break;
        } else
            break;
    }
}