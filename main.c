#include "header.h"

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        cat_flags cat_flags;
        int k = init_struct(argv, &cat_flags, argc);
        if (k >= 1) {
            char **strs = malloc(sizeof(char *) * ARRAY_SIZE);
            int len;
            // printf("%d\n", cat_flags.T);
            FILE *file;
            int h = 0;
            // char **strs = malloc(sizeof(char *) * ARRAY_SIZE);
            while (h < k) {
                file = fopen(cat_flags.path[h], "r");
                if (file != NULL) {
                    // char strs[500][10000];
                    // for (int i = 0; i < ARRAY_SIZE; i++) {
                    //     strs[i] = malloc(sizeof(char) * ARRAY_SIZE);
                    // }
                    len = 0;
                    create_str(strs, file, &len);

                    /* char *estr = NULL;
                     ssize_t size = 0;
                     int i = 0;
                     ssize_t read;
                     while ((read = getline(&estr, &size, file)) != -1) {
                         // printf("%s", estr);
                         strs[i] = malloc(sizeof(char) * strlen(estr));
                         strcpy(strs[i], estr);
                         i = i + 1;
                     }
                     printf("i = %d\n", i);
                     free(estr);
                     int len = i;
                     */
                    if (cat_flags.s == 1) cat_s(strs, &len);
                    if (cat_flags.T == 1) cat_T(strs, len);
                    if (cat_flags.E == 1) cat_E(strs, len);
                    // printf("len = %d\n", len);
                    for (int i = 0; i < len; i++) {
                        if (cat_flags.b == 1) {
                            if (strs[i][0] == '\n' || (strs[i][0] == '$' && strs[i][1] == '\n')) {
                                printf("%s", strs[i]);
                            } else {
                                printf("%6d\t%s", h + 1, strs[i]);
                                h++;
                            }
                        } else if (cat_flags.n == 1) {
                            printf("%6d\t%s", i + 1, strs[i]);
                        } else {
                            printf("%s", strs[i]);
                        }
                    }
                    // for (int i = 0; i < 500; i++) {
                    //     for (int j = 0; j < 10000; j++) {
                    //         strs[i][j] = '\0';
                    //     }
                    // }

                } else {
                    printf("Wrong path");
                }
                h++;
            }
            for (int i = 0; i < len - 1; i++) {
                free(strs[i]);
            }
            free(strs);
        } else {
            printf("Incorrect input");
        }
    } else {
        printf("No data");
    }
    return 0;
}
