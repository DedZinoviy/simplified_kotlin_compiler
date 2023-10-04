%token IF ELSE VAL VAR
%token ID

%token INT_LITERAL CHAR_LITERAL DOUBLE_LITERAL STRING_LITERAL TRUE_LITERAL FALSE_LITERAL

%right '=' PLUS_ASSIGNMENT MINUS_ASSIGNMENT MUL_ASSIGNMENT DIV_ASSIGNMENT MOD_ASSIGNMENT
%left EQUAL NOT_EQUAL
%left '>' '<' GREATER_EQUAL LESS_EQUAL 
%left '+' '-'
%left '*' '/' '%'
%left UMINUS UPLUS
%left POST_INCREMENT POST_DECREMENT
%right PREF_INCREMENT PREF_DECREMENT

%% 

ExpressionList: SimpleExpression
              | ExpressionList ',' SimpleExpression
              ;

SimpleExpression: Literal
                | OperatorExpression
                | ID
                | '(' SimpleExpression ')'
                | SimpleExpression '.' ID
                | SimpleExpression '.' ID '(' ExpressionList ')'
                | ID '(' ExpressionList ')'
                ;

Literal: INT_LITERAL
       | CHAR_LITERAL
       | DOUBLE_LITERAL
       | STRING_LITERAL
       | TRUE_LITERAL
       | FALSE_LITERAL
       ;

OperatorExpression: SimpleExpression '+' SimpleExpression
                  | SimpleExpression '-' SimpleExpression
                  | SimpleExpression '*' SimpleExpression
                  | SimpleExpression '/' SimpleExpression
                  | SimpleExpression '%' SimpleExpression
                  | SimpleExpression '<' SimpleExpression
                  | SimpleExpression '>' SimpleExpression
                  | SimpleExpression GREATER_EQUAL SimpleExpression
                  | SimpleExpression LESS_EQUAL SimpleExpression
                  | SimpleExpression EQUAL SimpleExpression
                  | SimpleExpression NOT_EQUAL SimpleExpression
                  | SimpleExpression PLUS_ASSIGNMENT SimpleExpression
                  | SimpleExpression MINUS_ASSIGNMENT SimpleExpression
                  | SimpleExpression MUL_ASSIGNMENT SimpleExpression
                  | SimpleExpression DIV_ASSIGNMENT SimpleExpression
                  | SimpleExpression MOD_ASSIGNMENT SimpleExpression
                  ;

Type: ID
    ;

Statement: SimpleExpression
         | VarStmt
         | ValStmt
         ;

ValStmt: VAL ID ':' Type
       | VAL ID '=' SimpleExpression
       | VAL ID ':' Type '=' SimpleExpression
       ;

VarStmt: VAR ID ':' Type
       | VAR ID '=' SimpleExpression
       | VAR ID ':' Type '=' SimpleExpression
       ;
       