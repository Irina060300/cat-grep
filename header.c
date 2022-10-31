#include "header.h"

int init_struct(int *i, char *argv[], cat_flags *cat_flags, int argc) {
    cat_flags->b = 0;
    cat_flags->n = 0;
    cat_flags->e = 0;
    cat_flags->v = 0;
    cat_flags->t = 0;
    cat_flags->T = 0;
    cat_flags->s = 0;
    cat_flags->E = 0;
    cat_flags->illegal = 0;
    int count_path = 0;
    int h = 0;
    while(*i < argc) {
        if (argv[*i][0] == '-' && argv[*i][1] != '-') {
            for (int j = 1; j < strlen(argv[*i]); j++) {
                if (argv[*i][j] == 'b') cat_flags->b = 1;
                else if (argv[*i][j] == 'v') cat_flags->v = 1;
                else if (argv[*i][j] == 'n') cat_flags->n = 1;
                else if (argv[*i][j] == 's') cat_flags->s = 1;
                else if (argv[*i][j] == 'E') cat_flags->E = 1;
                else if (argv[*i][j] == 'e') {
                    cat_flags->E = 1;
                    cat_flags->v = 1;
                }
                else if (argv[*i][j] == 'T') cat_flags->T = 1;
                else if (argv[*i][j] == 't') {
                    cat_flags->v = 1;
                    cat_flags->T = 1;
                } else {
                    cat_flags->illegal = 1;
                }
            }
            *i = *i + 1;
        } else {
            break;
        }
    }
    // while (i < argc) {
    //     if (argv[i][0] == '-' && argv[i][1] == 'b' && argv[i][2] == '\0') {
    //         cat_flags->b = 1;
    //     } else if (argv[i][0] == '-' && argv[i][1] == 'n' && argv[i][2] == '\0') {
    //         cat_flags->n = 1;
    //     } else if (argv[i][0] == '-' && argv[i][1] == 'e' && argv[i][2] == '\0') {
    //         cat_flags->e = 1;
    //     } else if (argv[i][0] == '-' && argv[i][1] == 'v' && argv[i][2] == '\0') {
    //         cat_flags->v = 1;
    //     } else if (argv[i][0] == '-' && argv[i][1] == 't' && argv[i][2] == '\0') {
    //         cat_flags->t = 1;
    //     } else if (argv[i][0] == '-' && argv[i][1] == 's' && argv[i][2] == '\0') {
    //         cat_flags->s = 1;
    //     } else if (argv[i][0] == '-' && argv[i][1] == 'E' && argv[i][2] == '\0') {
    //         cat_flags->E = 1;
    //     } else if (argv[i][0] == '-' && argv[i][1] == 'T' && argv[i][2] == '\0') {
    //         cat_flags->T = 1;
    //     } else {
    //         for (int j = 0; j < strlen(argv[i]); j++) {
    //             cat_flags->path[h][j] = argv[i][j];
    //             // printf("dfgsdfgsdfg");
    //         }
    //         // printf("cap = %d\n", cat_flags->path);
    //         count_path += 1;
    //         h++;
    //     }
    //     i++;
    // }
    // return count_path;
    return *i;
}
void create_str(char **strs, FILE *file, int *i) {
    char *estr = NULL;
    // char str[500];
    // while (1) {
        // estr = fgets(str, 500 * sizeof(char), file);
        // // printf("%6d\t%s", *i + 1, strs[*i]);
        // if (feof(file) != 0) {
        //     if (estr == NULL) {
        //         break;
        //     }
        // }
        // for (int j = 0; j < strlen(estr); j++) {
        //     strs[*i][j] = estr[j];
        // }
        // // printf("%d ", *i);
        // // printf("yes\n");
        // *i = *i + 1;
        ssize_t len = 0;
        ssize_t read;
        while ((read = getline(&estr, &len, file)) != -1) {
            // printf("%s", estr);
            strs[*i] = malloc(sizeof(char) * strlen(estr));
            strcpy(strs[*i], estr);
            *i = *i + 1;
            
        }
        free(estr);
        // printf("%s\n", estr);
        // if (feof(file) != 0) {
        //     if (estr == NULL) {
        //         break;
        //     }
        // }
    //     strcpy(strs[*i], estr);
    //     *i = *i + 1;
    // }
}

void cat_s(char **strs, int *len) {
    int flag;
    int i;
    int h = 0, count = 0;
    while (1) {
        flag = 0;
        for (i = 0; i < *len - 1; i++) {
            if (strs[i][0] == '\n' && strs[i + 1][0] == '\n') flag++;
        }
        if (flag <= 0) break;
        for (i = 0; i < *len - 1; i++) {
            if (strs[i][0] == '\n' && strs[i + 1][0] == '\n') {
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
            // for (j = j + 1; j < strlen(strs[i]); j++) {
            //     strs[i][j] = '\0';
            // }
        }

        *len = *len - 1;
    }
}
void cat_E(char **strs, int len) {
    for (int i = 0; i < len; i++) {
        int len_str;
        len_str = strlen(strs[i]);
        if (strs[i][len_str - 1] == '\n') {
            strs[i][len_str - 1] = '$';
            strs[i][len_str] = '\n';
            strs[i][len_str + 1] = '\0';
        } else {
            // printf("%s", strs[i]);
            strs[i][len_str] = '$';
            strs[i][len_str + 1] = '\0';
        }
    }
}

void cat_T(char **strs, int len) {
    for (int i = 0; i < len; i++) {
        int len_str = strlen(strs[i]);
        for (int j = 0; j < len_str + 1; j++) {
            if (strs[i][j] == '\t') {
                int k;
                // printf("i = %d, j = %d, len_str = %d\n", i, j, len_str);
                for (int k = len_str; k >= j; k--) {
                    strs[i][k] = strs[i][k - 1];
                }
                strs[i][j] = '^';
                strs[i][j + 1] = 'I';
                len_str++;
            }
        }
    }
}