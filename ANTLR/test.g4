grammar test;		
root:	expr ;
expr:	expr MULT expr
    |	expr PLUS expr
    |	INT
    |	'(' expr ')'
    ;
NEWLINE : [\r\n]+ -> skip;
PLUS    : '+' ;
MULT    : '*' ;
INT     : [0-9]+ ;