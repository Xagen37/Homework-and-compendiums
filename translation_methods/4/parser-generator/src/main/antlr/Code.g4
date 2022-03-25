grammar Code;

// $antlr-format useTab false
// $antlr-format alignColons trailing
// $antlr-format alignFirstTokens true
// $antlr-format indentWidth 2
// $antlr-format reflowComments false
// $antlr-format breakBeforeParens true
// $antlr-format columnLimit 150

// grammar ...;
// start ::= ...;
// ... rules ...;
// ... terminals ...;

header : GRAMMAR grammarName = TERMINAL SEMICOL rules terms EOF;

rules   : oneRule+;
oneRule : NONTERM ruleLeft IS ruleRight SEMICOL;

ruleLeft      : attributeList? toReturn?;
toReturn      : RETURN attributeList;
attributeList : LSQRE attribute (COMMA attribute)* RSQRE;
attribute     : type = TERMINAL name = NONTERM;

ruleRight : product (VERTSLASH product)*;
product   : statement+;
statement : TERMINAL CODE? | NONTERM ARGS? CODE? | EPS CODE?;

terms : term+;
term  : TERMINAL IS expr = (STRING | REGEX) SEMICOL;

COMMA     : ',';
EPS       : '!EPS!';
GRAMMAR   : 'grammar';
IS        : '::=';
RETURN    : 'return';
SEMICOL   : ';';
VERTSLASH : '|';
LSQRE     : '[';
RSQRE     : ']';

NONTERM        : LOWERCASE IDENT;
TERMINAL       : UPPERCASE IDENT;
CODETOK        : (UPPERCASE | LOWERCASE | UNDERSCORE) IDENT;
ARGS           : LBRAC .+? RBRAC; // ( ... )
CODE           : LCURL LDUCK .+? RDUCK RCURL; // {< ... >}
STRING         : QUOTE (~'"')+? QUOTE; // ' ... '
REGEX          : DQUOTE (~'\'')+? DQUOTE; // " ... "

fragment DIGIT      : [0-9];
fragment LOWERCASE  : [a-z];
fragment UPPERCASE  : [A-Z];
fragment UNDERSCORE : '_';
fragment IDENT      : (UPPERCASE | LOWERCASE | UNDERSCORE | DIGIT)*;
fragment DQUOTE     : '"';
fragment QUOTE      : '\'';
fragment LDUCK      : '<';
fragment RDUCK      : '>';
fragment LCURL      : '{';
fragment RCURL      : '}';
fragment LBRAC      : '(';
fragment RBRAC      : ')';

WHITESPACE : [ \t\n\r] -> skip;
