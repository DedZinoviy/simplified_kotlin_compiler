%token IF ELSE VAL VAR CLASS PUBLIC PROTECTED PRIVATE INTERNAL ENDL WHILE DO FUNC FOR SUPER THIS
%token ID

%token INT_LITERAL CHAR_LITERAL DOUBLE_LITERAL STRING_LITERAL TRUE_LITERAL FALSE_LITERAL

%nonassoc ENDL
%right '=' PLUS_ASSIGNMENT MINUS_ASSIGNMENT MUL_ASSIGNMENT DIV_ASSIGNMENT MOD_ASSIGNMENT
%left EQUAL NOT_EQUAL
%left '>' '<' GREATER_EQUAL LESS_EQUAL 
%left IN
%left RANGE
%left '+' '-'
%left '*' '/' '%'
%left UMINUS UPLUS
%right PREF_INCREMENT PREF_DECREMENT
%left POST_INCREMENT POST_DECREMENT '.' ENDL
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

SimpleExpression: INT_LITERAL
                | CHAR_LITERAL
                | DOUBLE_LITERAL
                | STRING_LITERAL
                | TRUE_LITERAL
                | FALSE_LITERAL
                | ID
                | SUPER
                | THIS
                | '(' SimpleExpression ')'
                | SimpleExpression '.' EndlOpt ID
                | SimpleExpression '.' EndlOpt ID '(' ExpressionList ')'
                | SimpleExpression '.' EndlOpt ID '(' ')'
                | SimpleExpression EndlList '.' EndlOpt ID
                | SimpleExpression EndlList '.' EndlOpt ID '(' ExpressionList ')'
                | SimpleExpression EndlList '.' EndlOpt ID '(' ')'
                | ID '(' ExpressionList ')'
                | ID '(' ')'
                | SimpleExpression '+' EndlOpt SimpleExpression
                | SimpleExpression '-' EndlOpt SimpleExpression
                | SimpleExpression '*' EndlOpt SimpleExpression
                | SimpleExpression '/' EndlOpt SimpleExpression
                | SimpleExpression '%' EndlOpt SimpleExpression
                | SimpleExpression '<' EndlOpt SimpleExpression
                | SimpleExpression '>' EndlOpt SimpleExpression
                | SimpleExpression GREATER_EQUAL EndlOpt SimpleExpression
                | SimpleExpression LESS_EQUAL EndlOpt SimpleExpression
                | SimpleExpression EQUAL EndlOpt SimpleExpression
                | SimpleExpression NOT_EQUAL EndlOpt SimpleExpression
                | SimpleExpression '=' EndlOpt SimpleExpression
                | SimpleExpression PLUS_ASSIGNMENT EndlOpt SimpleExpression
                | SimpleExpression MINUS_ASSIGNMENT EndlOpt SimpleExpression
                | SimpleExpression MUL_ASSIGNMENT EndlOpt SimpleExpression
                | SimpleExpression DIV_ASSIGNMENT EndlOpt SimpleExpression
                | SimpleExpression MOD_ASSIGNMENT EndlOpt SimpleExpression
                | SimpleExpression RANGE EndlOpt SimpleExpression
                | '-' EndlOpt SimpleExpression %prec UMINUS
                | '+' EndlOpt SimpleExpression %prec UPLUS
                | PREF_INCREMENT EndlOpt SimpleExpression
                | PREF_DECREMENT EndlOpt SimpleExpression
                | SimpleExpression POST_DECREMENT
                | SimpleExpression POST_INCREMENT
                ;

BlockStatement: '{' EndlOpt StatementList '}'
               | '{' EndlOpt '}'
               ;
              
IfStatement: IF '(' SimpleExpression ')' BlockStatement
           | IF '(' SimpleExpression ')' SimpleExpression
           | IF '(' SimpleExpression ')' BlockStatement ELSE BlockStatement
           ;

WhileStatement: WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')' EndlOpt Statement
              | WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')' EndlOpt BlockStatement
              ;

DoWhileStatement: DO EndlOpt BlockStatement EndlOpt WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')'
                | DO EndlOpt Statement WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')'
                ;

ForStatement: FOR '(' VarDeclarationList IN SimpleExpression')' EndlOpt BlockStatement
            | FOR '(' VarDeclarationList IN SimpleExpression')' EndlOpt Statement
            ;

StatementList: Statement
             | StatementList Statement
             ;

Statement: ';'
         | SimpleExpression EndlList
         | SimpleExpression ';'
         | VarStmt ';'
         | ValStmt ';'
         | WhileStatement
         | DoWhileStatement EndlList
         | DoWhileStatement ';'
         | ForStatement
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
           | ValStmt
           | VarStmt
           ;
       
ClassDeclaration: CLASS ID
                | CLASS ID '{' EndlOpt '}'
                | CLASS ID '{' EndlOpt ClassVisibilityMemberList '}'
                | CLASS ID '(' VarDeclarationList ')' '{' EndlOpt '}'
                | CLASS ID '(' VarDeclarationList ')' '{' EndlOpt ClassVisibilityMemberList '}'
                ;

Visibility: PRIVATE
          | PROTECTED
          | INTERNAL
          | PUBLIC
          ;

StatementTerminator: ENDL
                   | ';'
                   ;

KotlinFileElement: FunctionDeclaration EndlList
                 | ClassDeclaration EndlList
                 | FunctionDeclaration ';'
                 | ClassDeclaration ';'
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
