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

%start KotlinFile

%% 
KotlinFile: KotlinFileVisibilityElementList
          ;

KotlinFileVisibilityElementList: KotlinFileVisibilityElement
                               |  KotlinFileVisibilityElementList KotlinFileVisibilityElement
                               ;


ExpressionList: SimpleExpression
              | ExpressionList ',' SimpleExpression
              ;

SimpleExpression: Literal
                | OperatorExpression
                | ID
                | '(' SimpleExpression ')'
                | SimpleExpression '.' ID
                | SimpleExpression '.' ID '(' ExpressionList ')'
                | SimpleExpression '.' ID '(' ')'
                | ID '(' ExpressionList ')'
                | ID '(' ')'
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

WhileStatement: WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')' EndlOpt Statement
              | WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')' EndlOpt BlockStatement
              ;

DoWhileStatement: DO EndlOpt BlockStatement EndlOpt WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')'
                | DO EndlOpt Statement EndlOpt WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')'
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

ValStmt: VAL EndlOpt VarDeclaration
       | VAL EndlOpt ID EndlOpt '=' EndlOpt SimpleExpression
       | VAL EndlOpt VarDeclaration EndlOpt '=' EndlOpt SimpleExpression
       ;

VarStmt: VAR EndlOpt VarDeclaration
       | VAR EndlOpt ID EndlOpt '=' EndlOpt SimpleExpression
       | VAR EndlOpt VarDeclaration EndlOpt '=' EndlOpt SimpleExpression
       ;

VarDeclaration: ID EndlOpt ':' EndlOpt ID
              ;

VarDeclarationList: VarDeclaration
                  | VarDeclarationList EndlOpt ',' EndlOpt VarDeclaration
                  ;

FunctionDeclaration: FUNC EndlOpt ID EndlOpt '(' EndlOpt ')' EndlOpt BlockStatement
                   | FUNC EndlOpt ID EndlOpt '(' EndlOpt ')' EndlOpt ':' EndlOpt ID EndlOpt BlockStatement
                   | FUNC EndlOpt ID EndlOpt '(' EndlOpt  VarDeclarationList  EndlOpt ')' EndlOpt BlockStatement
                   | FUNC EndlOpt ID EndlOpt '(' EndlOpt VarDeclarationList  EndlOpt ')' EndlOpt ':' EndlOpt ID EndlOpt BlockStatement
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

EndlOpt: /* empty */
       | EndlList
       ;

EndlList: ENDL
        | EndlList ENDL
        ;
