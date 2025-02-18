grammar test;

root:	expr;

expr:	expr '*' expr
    |	expr '+' expr
    |	INT
    |	'(' expr ')'
    ;

NEWLINE : [ \r\n]+ -> skip;
INT     : [0-9]+ ;