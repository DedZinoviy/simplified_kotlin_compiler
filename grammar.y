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
              | WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')' EndlOpt BlockStatement EndlList
              | WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')' EndlOpt BlockStatement ';' EndlOpt
              ;

DoWhileStatement: DO EndlOpt BlockStatement EndlOpt WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')' EndlList
                | DO EndlOpt Statement WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')' EndlList
                | DO EndlOpt BlockStatement EndlOpt WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')' ';' EndlOpt
                | DO EndlOpt Statement WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')' ';' EndlOpt
                ;

ForStatement: FOR '(' VarDeclarationList IN SimpleExpression')' EndlOpt BlockStatement EndlList
            | FOR '(' VarDeclarationList IN SimpleExpression')' EndlOpt BlockStatement ';' EndlOpt
            | FOR '(' VarDeclarationList IN SimpleExpression')' EndlOpt Statement
            ;

StatementList: Statement
             | StatementList Statement
             ;

Statement: ';' EndlOpt
         | SimpleExpression EndlList
         | SimpleExpression ';' EndlOpt
         | VarStmt
         | ValStmt
         | MultiDeclararion
         | WhileStatement
         | DoWhileStatement
         | ForStatement
         ;         

ValStmt: VAL EndlOpt VarDeclaration EndlList
       | VAL EndlOpt VarDeclaration ';' EndlOpt
       | VAL EndlOpt ID EndlOpt '=' EndlOpt SimpleExpression EndlList
       | VAL EndlOpt ID EndlOpt '=' EndlOpt SimpleExpression ';' EndlOpt
       | VAL EndlOpt VarDeclaration EndlOpt '=' EndlOpt SimpleExpression EndlList
       | VAL EndlOpt VarDeclaration EndlOpt '=' EndlOpt SimpleExpression ';' EndlOpt
       ;

VarStmt: VAR EndlOpt VarDeclaration EndlList
       | VAR EndlOpt VarDeclaration ';' EndlOpt
       | VAR EndlOpt ID EndlOpt '=' EndlOpt SimpleExpression EndlList
       | VAR EndlOpt ID EndlOpt '=' EndlOpt SimpleExpression ';' EndlOpt
       | VAR EndlOpt VarDeclaration EndlOpt '=' EndlOpt SimpleExpression EndlList
       | VAR EndlOpt VarDeclaration EndlOpt '=' EndlOpt SimpleExpression ';' EndlOpt
       ; 

IdList: ID
      | IdList ',' ID
      ;

MultiDeclararion: VAL EndlOpt '('VarDeclaration')' EndlOpt '=' EndlOpt SimpleExpression EndlList
                | VAL EndlOpt '('IdList')' EndlOpt '=' EndlOpt SimpleExpression EndlList
                | VAR EndlOpt '('VarDeclaration')' EndlOpt '=' EndlOpt SimpleExpression EndlList
                | VAR EndlOpt '('IdList')' EndlOpt '=' EndlOpt SimpleExpression EndlList
                | VAL EndlOpt '('VarDeclaration')' EndlOpt '=' EndlOpt SimpleExpression ';' EndlOpt
                | VAL EndlOpt '('IdList')' EndlOpt '=' EndlOpt SimpleExpression ';' EndlOpt
                | VAR EndlOpt '('VarDeclaration')' EndlOpt '=' EndlOpt SimpleExpression ';' EndlOpt 
                | VAR EndlOpt '('IdList')' EndlOpt '=' EndlOpt SimpleExpression ';' EndlOpt
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
                     | ';'
                     ;

ClassVisibilityMemberList: ClassVisibilityMember
                         | ClassVisibilityMemberList ClassVisibilityMember
                         ;

ClassMember: FunctionDeclaration
           | ValStmt
           | VarStmt
           | MultiDeclararion
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
                 | FunctionDeclaration ';' EndlOpt
                 | ClassDeclaration ';' EndlOpt
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
