int FilterName(FILE *in, FILE *out, char *word) {
    int i = 0;
    char c = 0, cPrev = 0;
    while (!isalpha(c = fgetc(in))) {
        if (c == EOF)
            return 0;
        fputc(c, out);
        switch (c) {
            case '\'': c = GoThroughSymbols(in, out, SYMBOL_TYPE, 1); break;
            case '\"': c = GoThroughSymbols(in, out, STRING_TYPE, 1); break;
            case '/': /* fall through */ case '*':
                if (cPrev == '/') {
                    c = GoThroughSymbols(in, out, (c == '/') ? LINE_COMMENT_TYPE : LONG_COMMENT_TYPE, 1);
                    break;
                }
                /* fall through */
            default:
                cPrev = c;
                continue;
        }
        // if met one of the ignore conditions
        fputc(c, out);
        cPrev = c;
    }

    word[i] = c;
    i++;
    while (i < MAX_WORD - 1) {
        c = fgetc(in);
        if (!isalpha(c)) {
            ungetc(c, in);
            break;
        }
        if (c == EOF)
            break;
        word[i] = c;
        i++;
    }
    if (i >= MAX_WORD)
        printf("Error: too large word met. Dividing on parts.\n");
    word[i] = '\0';
    return 1;
}

char GoThroughSymbols(FILE *in, FILE *out, int type, int copyEnabled) {
    char c = 0;
    switch (type) {
        case SYMBOL_TYPE:
            return GoToSymbol(in, out, '\'', copyEnabled);
        case STRING_TYPE:
            return GoToSymbol(in, out, '\"', copyEnabled);
        case LINE_COMMENT_TYPE:
            return GoToSymbol(in, out, '\n', copyEnabled);
        case LONG_COMMENT_TYPE:
            while (GoToSymbol(in, out, '*', copyEnabled) != EOF) {
                if (copyEnabled)
                    fputc('*', out);
                c = fgetc(in);
                if (c == '/')
                    return '/';
                // else
                ungetc(c, in);
            }
            return EOF;
        default:
            printf("Error: unknown going through type. Ignored.\n");
            return ' ';
    }
    printf("Error: an unknown error occured during going through symbols. Trying to continue preprocessing\n");
    return ' ';
}

char GoToSymbol(FILE *in, FILE *out, char symbol, int copyEnabled) {
    char c = fgetc(in);
    while (c != symbol && c != EOF) {
        if (copyEnabled)
            fputc(c, out);
        c = fgetc(in);
    }
    return c;
}
