void FixCase(FILE *in, FILE *out) {
    char word[MAX_WORD], newWord[MAX_WORD];
    while (FilterName(in, out, word)) {
        if (isalpha(word[0]) && !isupper(word[1])) {
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
    }
}
