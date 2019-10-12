void FixCase(FILE *in, FILE *out) {
    char word[MAX_WORD], newWord[MAX_WORD];
    while (FilterName(in, out, word)) {
        if (isalpha(word[0]) && !isupper(word[1]) && word[1] != '_') {
            int j = 1;
            newWord[0] = tolower(word[0]);
            for (int i = 1; word[i] != '\0'; i++) {
                if (isupper(word[i])) {
                    newWord[j] = '_';
                    j++;
                    newWord[j] = tolower(word[i]);
                }
                else
                    newWord[j] = word[i];
                j++;
            }
            newWord[j] = '\0';
            fprintf(out, "%s", newWord);
        }
        else
            fprintf(out, "%s", word);
    }
}

void DeleteComments(FILE *in, FILE *out) {
    char cPrev = fgetc(in);
    char c = fgetc(in);

    while (c != EOF) {
        if (cPrev == '/') {
            if (c == '/') {
                cPrev = GoToSymbol(in, out, '\n', 0);
                c = fgetc(in);
                continue;
            }
            else if (c == '*') {
                do {
                    cPrev = GoToSymbol(in, out, '*', 0);
                    c = fgetc(in);
                } while (c != '/' && c != EOF);
                cPrev = fgetc(in);
                c = fgetc(in);
                continue;
            }
        }
        fputc(cPrev, out);
        cPrev = c;
        c = fgetc(in);
    }

    if (cPrev != EOF)
        fputc(cPrev, out);
}
