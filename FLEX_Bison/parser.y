%{
    #include <stdio.h>
    #include <stdlib.h>

    extern FILE *yyin;
    extern int yylex();
    void yyerror(const char *s);
%}

/* Token Definitions */
%token KEYWORD RETURN IDENTIFIER NUMBER
%token ASSIGN PLUS SEMICOLON
%token OPEN_PAREN CLOSE_PAREN OPEN_BRACE CLOSE_BRACE
%token UNRECOGNIZED
%left PLUS

/* Type Definitions */
%type <num> NUMBER expression
%type <word> IDENTIFIER
%type <character> ASSIGN PLUS SEMICOLON
%type <character> OPEN_PAREN CLOSE_PAREN OPEN_BRACE CLOSE_BRACE

%union {
    char character;   // for operators and punctuation
    char word[20];    // for IDENTIFIER and KEYWORD
    int num;          // for numbers
}

%%

/* Grammar Rules */
program:
    function
    ;

function:
    KEYWORD IDENTIFIER OPEN_PAREN CLOSE_PAREN OPEN_BRACE statements CLOSE_BRACE
    { printf("Valid function definition: %s\n", $2); }
    ;

statements:
    statements statement
    | /* empty */
    ;

statement:
    declaration
    | assignment
    | return_stmt
    ;

declaration:
    KEYWORD IDENTIFIER ASSIGN expression SEMICOLON
    { printf("Declaration: %s = %d\n", $2, $4); }
    | KEYWORD IDENTIFIER SEMICOLON
    { printf("Declaration: %s\n", $2); }
    ;

assignment:
    IDENTIFIER ASSIGN expression SEMICOLON
    { printf("Assignment: %s = %d\n", $1, $3); }
    ;

return_stmt:
    RETURN expression SEMICOLON
    { printf("Return statement: %d\n", $2); }
    ;

expression:
    NUMBER
    { $$ = $1; printf("The number is %d\n", $1); }
    | IDENTIFIER
    { printf("Identifier: %s\n", $1); }
    | expression PLUS expression
    { $$ = $1 + $3; printf("Result: %d\n", $$); }
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
