%{
    #include <stdio.h>
    #include <stdlib.h>

    extern FILE *yyin;
    extern int yylex();
    void yyerror(const char *s);
%}

%union {
    char *word;    // Correct way to store strings in union
}


/* Token Definitions */
%token PLUS 
%token MULT
%token OPEN_PAR
%token CLOSE_PAR
%token <word> NUMBER


/* Grammar Rules */
%%

e:
      e PLUS t         { printf("A sum has been encountered!\n"); }
    | t
    ;

t:
      t MULT f         { printf("A multiplication has been encountered!\n"); }
    | f
    ;

f:
      OPEN_PAR e CLOSE_PAR   { printf("Parenthesis encountered!\n"); }
    | NUMBER                 { printf("Number encountered: %s\n", $1); free($1); }
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
