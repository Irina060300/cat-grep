#include "header.h"

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        cat_flags cat_flags;
        if (init_struct(argv, &cat_flags, argc) == 1) {
            FILE *file;
            file = fopen(argv[cat_flags.path], "r");
            if (file != NULL) {
                char strs[500][10000];
                int len = 0;
                create_str(strs, file, &len);
                // len += 1;
                cat_s(strs, &len);
                cat_E(strs, len);
                // int h = 0;
                for (int i = 0; i < len; i++) {
                    printf("%s", strs[i]);
                }
            }

        } else {
            printf("Extra symbols");
        }
    }
    return 0;
}
