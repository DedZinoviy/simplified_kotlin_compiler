%{
       #include "parsing_tree.h"
       void yyerror(char const * s);
       extern int yylex(void);
%}

%union {
       int intLit;
       char charLit;
       double doubleLit;
       struct stringBuffer * stringLit;
       char * ident;
       struct ExpressionNode * expression;
       struct ExpressionListNode * exprList;
}

%token IF ELSE VAL VAR CLASS PUBLIC PROTECTED PRIVATE INTERNAL ENDL WHILE DO FUNC FOR SUPER THIS OVERRIDE OPEN
%token ID

%token <intLit>INT_LITERAL 
%token <charLit>CHAR_LITERAL 
%token <doubleLit>DOUBLE_LITERAL 
%token <stringLit>STRING_LITERAL 
%token TRUE_LITERAL FALSE_LITERAL

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

%type <expression>SimpleExpression
%type <exprList>ExpressionList

%% 
KotlinFile: KotlinFileVisibilityElementList
          ;

KotlinFileVisibilityElementList: KotlinFileVisibilityElement
                               | KotlinFileVisibilityElementList KotlinFileVisibilityElement
                               ;

ExpressionList: SimpleExpression {$$ = createExpressionListNode($1);}
              | ExpressionList ',' SimpleExpression {$$ = addExpressionToExpressionList($1, $3);}
              ;

SimpleExpression: INT_LITERAL {$$ = createIntLiteralExpressionNode($1);}
                | CHAR_LITERAL {$$ = createCharLiteralExpressionNode($1);}
                | DOUBLE_LITERAL {$$ = createDoubleLiteralExpressionNode($1);}
                | STRING_LITERAL {$$ = createStringLiteralExpressionNode($1);}
                | TRUE_LITERAL {$$ = createTrueLiteralExpressionNode();}
                | FALSE_LITERAL {$$ = createFalseLiteralExpressionNode();}
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
                | SimpleExpression '+' EndlOpt SimpleExpression {$$ = createPlusExpressionNode($1, $4);}
                | SimpleExpression '-' EndlOpt SimpleExpression {$$ = createMinusExpressionNode($1, $4);}
                | SimpleExpression '*' EndlOpt SimpleExpression {$$ = createMulExpressionNode($1, $4);}
                | SimpleExpression '/' EndlOpt SimpleExpression {$$ = createDivExpressionNode($1, $4);}
                | SimpleExpression '%' EndlOpt SimpleExpression {$$ = createModExpressionNode($1, $4);}
                | SimpleExpression '<' EndlOpt SimpleExpression {$$ = createLessExpressionNode($1, $4);}
                | SimpleExpression '>' EndlOpt SimpleExpression {$$ = createGreatExpressionNode($1, $4);}
                | SimpleExpression GREATER_EQUAL EndlOpt SimpleExpression {$$ = createGreatEqualExpressionNode($1, $4);}
                | SimpleExpression LESS_EQUAL EndlOpt SimpleExpression {$$ = createLessEqualExpressionNode($1, $4);}
                | SimpleExpression EQUAL EndlOpt SimpleExpression {$$ = createEqualExpressionNode($1, $4);}
                | SimpleExpression NOT_EQUAL EndlOpt SimpleExpression {$$ = createNotEqualExpressionNode($1, $4);}
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

ClassModifierMember: ClassMember
                     | MemberModifierList ClassMember
                     | ';'
                     ;

MemberModifier: PUBLIC
              | PRIVATE
              | PROTECTED
              | INTERNAL
              | OPEN
              | OVERRIDE
              ;

MemberModifierList: MemberModifier
                  | MemberModifierList EndlOpt MemberModifier
                  ;

ClassModifierMemberList: ClassModifierMember
                         | ClassModifierMemberList ClassModifierMember
                         ;

ClassMember: FunctionDeclaration
           | ValStmt
           | VarStmt
           | MultiDeclararion
           ;
       
ClassDeclaration: CLASS ID
                | CLASS ID '{' EndlOpt '}'
                | CLASS ID '{' EndlOpt ClassModifierMemberList '}'
                | CLASS ID '(' VarDeclarationList ')' '{' EndlOpt '}'
                | CLASS ID '(' VarDeclarationList ')' '{' EndlOpt ClassModifierMemberList '}'
                | CLASS ID ':' ID
                | CLASS ID ':' ID '{' EndlOpt '}'
                | CLASS ID ':' ID '{' EndlOpt ClassModifierMemberList '}'
                | CLASS ID ':' ID '(' VarDeclarationList ')' '{' EndlOpt '}'
                | CLASS ID ':' ID '(' VarDeclarationList ')' '{' EndlOpt ClassModifierMemberList '}'
                ;

OpenClosedClassDeclaration: ClassDeclaration
                          | OPEN EndlOpt ClassDeclaration
                          ;

KotlinFileElement: FunctionDeclaration EndlList
                 | OpenClosedClassDeclaration EndlList
                 | FunctionDeclaration ';' EndlOpt
                 | OpenClosedClassDeclaration ';' EndlOpt
                 ;

KotlinFileVisibilityElement: KotlinFileElement
                           | PUBLIC KotlinFileElement
                           | PRIVATE KotlinFileElement
                           | INTERNAL KotlinFileElement
                           | ';'
                           ;

EndlOpt: /* empty */
       | EndlList
       ;

EndlList: ENDL
        | EndlList ENDL
        ;

%%

void yyerror(char const * s)
{
       printf("%s", s);
}
