#include "defines.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <file to parse> <output file>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], argv[2]) == 0) {
        printf("Are you sure you want to use the same file name? You won't be able to recover your old data.\n");
        char ans = 0;
        printf("y/n: ");
        while (tolower(ans) != 'y' && tolower(ans) != 'n')
            scanf("%c", &ans);
        if (tolower(ans) == 'n') {
            printf("Parsing canceled.\n");
            return 0;
        }
    }

    FILE *in = fopen(argv[1], "r");
    if (!in) {
        printf("Could not open input file '%s' for reading\n", argv[1]);
        return 2;
    }

    // choosing options
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

    // working on files
    const FileFunc OPTION_FUNC[OPTION_NUM] = {FixCase};
    FILE *tmpOut = tmpfile();
    for (int i = 0; i < OPTION_NUM; i++)
        if (options[i]) {
            (*OPTION_FUNC[i])(in, tmpOut);
            fclose(in);
            in = tmpOut;
            rewind(in);
            tmpOut = tmpfile();
        }
    fclose (tmpOut);

    // saving the result
    FILE *out = fopen(argv[2], "w");
    if (!out) {
        printf("Could not open output file '%s' for writing\n", argv[2]);
        printf("No changes saved.\n");
        return 3;
    }
    GoToSymbol(in, out, EOF, 1);
    printf("Done\n");
    fclose(out);

    return 0;
}
