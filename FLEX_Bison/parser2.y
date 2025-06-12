%{
    #include <stdio.h>
    #include <stdlib.h>

    extern FILE *yyin;
    extern int yylex();
    void yyerror(const char *s);
%}

/* Token Definitions */
%union {
    char* word;
    int number;
}

%token <word> NUMBER
%token <word> PLUS 
%left PLUS

%%
expr: //Left-hand side
        expr PLUS term     { printf("A sum!"); } // Right-hand side
    |   term               {}
    ;

term: NUMBER            { printf("A number!"); }
    ;
%%


/* Error Handling */
void yyerror(const char *s) {
    extern char *yytext;
    fprintf(stderr, "Error: %s near \"%s\"\n", s, yytext);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("Error opening file");
        return 1;
    }

    yyin = input_file;

    printf("Parsing...\n");
    yyparse();
    printf("Parsing completed.\n");

    fclose(input_file);
    return 0;
}
