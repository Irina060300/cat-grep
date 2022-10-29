#include "header.h"

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        cat_flags cat_flags;
        int k = init_struct(argv, &cat_flags, argc);
        if (k >= 1) {
            // printf("%d\n", cat_flags.T);
            FILE *file;
            int h = 0;
            while (h < k) {
                file = fopen(cat_flags.path[h], "r");
                if (file != NULL) {
                    char strs[500][10000];
                    int len = 0;
                    // len += 1;
                    create_str(strs, file, &len);
                    if (cat_flags.s == 1) {
                        cat_s(strs, &len);
                    }
                    if (cat_flags.T == 1) {
                        cat_T(strs, len);
                    }
                    if (cat_flags.E == 1) {
                        cat_E(strs, len);
                    }
                    int h = 0;
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
                    for (int i = 0; i < 500; i++) {
                        for (int j = 0; j < 10000; j++) {
                            strs[i][j] = '\0';
                        }
                    }
                } else {
                    printf("Wrong path");
                }
                h++;
            }

        } else {
            printf("Incorrect input");
        }
    } else {
        printf("No data");
    }
    return 0;
}
