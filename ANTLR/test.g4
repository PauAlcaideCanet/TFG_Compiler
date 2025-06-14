grammar test;

root:	e ;

e:	    e PLUS t
    |	t
    ;

t:      t MULT f
    |   f
    ;

f:      OPEN_PAR e CLOSE_PAR
    |	INT
    ;

NEWLINE : [\r\n]+ -> skip;
PLUS    : '+' ;
MULT    : '*' ;
OPEN_PAR: '(' ;
CLOSE_PAR: ')' ;
INT     : [0-9]+ ;