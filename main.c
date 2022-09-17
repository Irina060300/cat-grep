#include "header.h"

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        cat_flags cat_flags;
        if (init_struct(argv, &cat_flags, argc) == 1) {
            // printf("%d\n", cat_flags.T);
            FILE *file;
            file = fopen(argv[cat_flags.path], "r");
            if (file != NULL) {
                char strs[500][10000];
                int len = 0;
                // len += 1;
                create_str(strs, file, &len);
                if (cat_flags.s == 1) cat_s(strs, &len);
                if (cat_flags.T == 1) cat_T(strs, len);
                if (cat_flags.E == 1) cat_E(strs, len);
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
            }

        } else {
            printf("Extra symbols");
        }
    }
    return 0;
}
