// includes
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// some defines
typedef void (*FileFunc) (FILE *, FILE *);
#define MAX_WORD 512
#define LINE_COMMENT_TYPE 0
#define LONG_COMMENT_TYPE 1
#define SYMBOL_TYPE 2
#define STRING_TYPE 3

#define DO_NOTHING

// utility.c
    int FilterName(FILE *in, FILE *out, char *word);
    char GoThroughSymbols(FILE *in, FILE *out, int type, int copyEnabled);
    char GoToSymbol(FILE *in, FILE *out, char symbol, int copyEnabled);

// operations.c
    void FixCase(FILE *in, FILE *out);
    void DeleteComments(FILE *in, FILE *out);

// other files
#include "utility.c"
#include "operations.c"
