#include "defines.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <file to parse> <output file>\n", argv[0]);
        return 1;
    }

    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    if (!in || !out) {
        if (!in)
            printf("Could not open input file '%s' for reading\n", argv[1]);
        if (!out)
            printf("Could not open output file '%s' for writing\n", argv[2]);
        return 2;
    }

    const int OPTION_NUM = 1;
    const char *OPTION_NAMES[OPTION_NUM] = {"Fix names"};
    int options[OPTION_NUM] = {};
    int ans = 0;
    do {
        for (int i = 0; i < OPTION_NUM; i++)
            printf("%d - %s\n", i, OPTION_NAMES[i]);
        printf("Enable/disable option (%d for all or -1 to finish): ", OPTION_NUM);
        scanf("%d", &ans);
        if (ans >= OPTION_NUM) {
            for (int i = 0; i < OPTION_NUM; i++)
                options[i] = 1;
            break;
        }
        if (ans >= 0) {
            options[ans] = !options[ans];
            printf("%s\n", (options[ans]) ? "Enabled" : "Disabled");
        }
    } while (ans >= 0);

    const FileFunc OPTION_FUNC[OPTION_NUM] = {FixCase};
    for (int i = 0; i < OPTION_NUM; i++)
        if (options[i]) {
            (*OPTION_FUNC[i])(in, out);
        }

    printf("Done\n");
    return 0;
}
