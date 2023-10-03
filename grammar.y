%token IF ELSE VAL VAR
%token ID

%token INT_LITERAL CHAR_LITERAL DOUBLE_LITERAL STRING_LITERAL TRUE_LITERAL FALSE_LITERAL

%right '=' PLUS_ASSIGNMENT MINUS_ASSIGNMENT MUL_ASSIGNMENT DIV_ASSIGNMENT MOD_ASSIGNMENT
%left EQUAL NOT_EQUAL
$left GREATER LESS GREATER_EQUAL LESS_EQUAL 
%left '+' '-'
%left '*' '/' '%'
%left UMINUS UPLUS
%left POST_INCREMENT POST_DECREMENT
%right PREF_INCREMENT PREF_DECREMENT

%% 

SimpleExpression: Literal
                | ID
                | '(' SimpleExpression ')'
                | SimpleExpression '.' ID
                ;

Literal: INT_LITERAL
       | CHAR_LITERAL
       | DOUBLE_LITERAL
       | STRING_LITERAL
       | TRUE_LITERAL
       | FALSE_LITERAL
       ;

Type: ID
    ;

ValStmt: VAL ID ':' Type
       ;

VarStmt: VAR ID ':' Type
       ;
       