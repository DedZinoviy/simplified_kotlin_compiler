%token IF ELSE VAL VAR CLASS PUBLIC PROTECTED PRIVATE INTERNAL ENDL WHILE DO FUNC
%token ID

%token INT_LITERAL CHAR_LITERAL DOUBLE_LITERAL STRING_LITERAL TRUE_LITERAL FALSE_LITERAL

%right '=' PLUS_ASSIGNMENT MINUS_ASSIGNMENT MUL_ASSIGNMENT DIV_ASSIGNMENT MOD_ASSIGNMENT
%left EQUAL NOT_EQUAL
%left '>' '<' GREATER_EQUAL LESS_EQUAL 
%left IN
%left RANGE
%left '+' '-'
%left '*' '/' '%'
%left UMINUS UPLUS
%right PREF_INCREMENT PREF_DECREMENT
%left POST_INCREMENT POST_DECREMENT '.'
%nonassoc '(' ')'

%% 
KotlinFileVisibilityElementList: KotlinFileVisibilityElement
                               |  KotlinFileVisibilityElementList KotlinFileVisibilityElement
                               ;

ExpressionList_e: /* empty */
                | ExpressionList
                ;

ExpressionList: SimpleExpression
              | ExpressionList ',' SimpleExpression
              ;

SimpleExpression: Literal
                | OperatorExpression
                | ID
                | '(' SimpleExpression ')'
                | SimpleExpression '.' ID
                | SimpleExpression '.' ID '(' ExpressionList_e ')'
                | ID '(' ExpressionList_e ')'
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
                  | SimpleExpression RANGE SimpleExpression
                  | '-' SimpleExpression %prec UMINUS
                  | '+' SimpleExpression %prec UPLUS
                  | PREF_INCREMENT SimpleExpression
                  | PREF_DECREMENT SimpleExpression
                  | SimpleExpression POST_DECREMENT
                  | SimpleExpression POST_INCREMENT
                  ;

BlockStatement: '{' StatementList '}'
               | '{' '}'
               ;
              
IfStatement: IF '(' SimpleExpression ')' BlockStatement
           | IF '(' SimpleExpression ')' SimpleExpression
           | IF '(' SimpleExpression ')' BlockStatement ELSE BlockStatement
           ;

WhileStatement: WHILE '(' SimpleExpression ')' Statement
              | WHILE '(' SimpleExpression ')' BlockStatement
              ;

DoWhileStatement: DO BlockStatement WHILE '(' SimpleExpression ')'
                | DO Statement WHILE '(' SimpleExpression ')'
                ;

StatementList: Statement
             | StatementList Statement
             ;

Statement: StatementTerminator
         | SimpleExpression StatementTerminator
         | VarStmt StatementTerminator
         | ValStmt StatementTerminator
         | WhileStatement
         | DoWhileStatement
         ;

ValStmt: VAL VarDeclaration
       | VAL ID '=' SimpleExpression
       | VAL VarDeclaration '=' SimpleExpression
       ;

VarStmt: VAR VarDeclaration
       | VAR ID '=' SimpleExpression
       | VAR VarDeclaration '=' SimpleExpression
       ;

VarDeclaration: ID ':' ID
       ;

VarDeclarationList: VarDeclaration
                  | VarDeclarationList ',' VarDeclaration
                  ;

FunctionDeclaration: FUNC ID '(' ')' BlockStatement
        | FUNC ID '(' ')' ':' ID BlockStatement
        | FUNC ID '(' VarDeclarationList ')' BlockStatement
        | FUNC ID '(' VarDeclarationList ')' ':' ID BlockStatement
        ;

ClassVisibilityMember: ClassMember
                     | Visibility ClassMember
                     ;

ClassVisibilityMemberList: ClassVisibilityMember
                         | ClassVisibilityMemberList ClassVisibilityMember
                         ;

ClassMember: FunctionDeclaration StatementTerminator
           | ValStmt StatementTerminator
           | VarStmt StatementTerminator
           ;
       
ClassDeclaration: CLASS ID
                | CLASS ID '{' '}'
                | CLASS ID '{' ClassVisibilityMemberList '}'
                ;

Visibility: PRIVATE
          | PROTECTED
          | INTERNAL
          | PUBLIC
          ;

StatementTerminator: ENDL
                   | ';'
                   ;

KotlinFileElement: FunctionDeclaration
                 | ClassDeclaration
                 ;

KotlinFileVisibilityElement: KotlinFileElement
                           | PUBLIC KotlinFileElement
                           | PRIVATE KotlinFileElement
                           | INTERNAL KotlinFileElement
                           ;
