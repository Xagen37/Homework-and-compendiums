grammar Code;

// $antlr-format useTab false
// $antlr-format alignColons trailing
// $antlr-format alignFirstTokens true
// $antlr-format indentWidth 2
// $antlr-format reflowComments false
// $antlr-format breakBeforeParens true
// $antlr-format columnLimit 150

// operations: arithm, comparing, input via input(), output via print()
// variables: ints, floats, strings, bools
// control-flow: if-elif-else, for in range, while

file : expressions EOF;

expressions         : expression+;
expression          : TAB* (many_one_line_exprs | multi_line_expr);
multi_line_expr     : if_statement | elif_statement | else_statement | while_statement | for_statement;
many_one_line_exprs : one_line_expr (SEMICOL one_line_expr)* SEMICOL? NEW_LINE?;
one_line_expr       : var_ass | operation | BREAK | CONTINUE | print;

print : PRINT LPAR operation (COMMA operation)* RPAR;
input:
  FLOAT_TYPE LPAR INPUT LPAR RPAR RPAR
  | INT_TYPE LPAR INPUT LPAR RPAR RPAR
  | INPUT LPAR RPAR;

var_ass   : IDENTIFICATOR (COMMA IDENTIFICATOR)* '=' init (COMMA init)*;
init : operation | input;
operation : disj;

if_statement    : IF cond = operation COLON block = after_colon;
elif_statement  : ELIF cond = operation COLON block = after_colon;
else_statement  : ELSE COLON block = after_colon;
while_statement : WHILE cond = operation COLON block = after_colon;
for_statement   : FOR IDENTIFICATOR IN RANGE LPAR range RPAR COLON block = after_colon;
range           : (to = INT) | (from = INT) COMMA (to = INT) (COMMA step = INT)?;

after_colon : many_one_line_exprs | NEW_LINE expressions;

disj       : lhs = disj OR rhs = conj | val = conj;
conj       : lhs = conj AND rhs = negate | val = negate;
negate     : op = NOT arg = negate | val = comparison;
comparison : lhs = comparison op = COMPARE_OP rhs = sum_term | val = sum_term;
sum_term   : lhs = sum_term op = ADD_OP rhs = mul_term | val = mul_term;
mul_term   : lhs = mul_term op = MUL_OP rhs = term | val = term;
term       : op = ADD_OP arg = term | val = atom;
atom       : bool_lit | IDENTIFICATOR | STRING | NUM | INT | LPAR operation RPAR;
bool_lit   : TRUE | FALSE;

//------------------------------------------------------------------------------------

fragment DIGIT      : [0-9];
fragment LOWERCASE  : [a-z];
fragment UPPERCASE  : [A-Z];
fragment UNDERSCORE : '_';
fragment DOT        : '.';

AND         : 'and';
BREAK       : 'break';
BOOL_TYPE   : 'bool';
COMMA       : ',';
CONTINUE    : 'continue';
DEF         : 'def';
COLON       : ':';
ELIF        : 'elif';
ELSE        : 'else';
FALSE       : 'False';
FLOAT_TYPE  : 'float';
FOR         : 'for';
IF          : 'if';
INPUT       : 'input';
INT_TYPE    : 'int';
IN          : 'in';
NOT         : 'not';
OR          : 'or';
PRINT       : 'print';
RANGE       : 'range';
SEMICOL     : ';';
STRING_TYPE : 'string';
TRUE        : 'True';
WHILE       : 'while';
LPAR        : '(';
RPAR        : ')';

IDENTIFICATOR : (LOWERCASE | UPPERCASE | UNDERSCORE) ( LOWERCASE | UPPERCASE | DIGIT | UNDERSCORE)*;
COMPARE_OP    : '==' | '!=' | '<=' | '<' | '>=' | '>';
INT           : '-'? ([1-9] DIGIT* | '0');
NUM           : INT (DOT DIGIT*)?;
ADD_OP        : '+' | '-';
MUL_OP        : '*' | '/';
STRING        : '"' .*? '"' | '\'' .*? '\'';
NEW_LINE      : ('\r'? '\n' | '\r')+;
TAB           : ('\t' | '    ');

WHITESPACE : ' ' -> skip;
