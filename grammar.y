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
       struct StatementNode * statement;
       struct StatementListNode * stmtList;
       struct VarDeclarationNode * varDecl;
       struct VarDeclarationListNode * varDeclList;
       struct FunctionNode * function;
       struct ModifierNode * mod;
       struct ModifierListNode * modList;
       struct KotlinFileElementNode * elem;
       struct KotlinFileElementListNode * elemList;
       struct KotlinFileNode * file;
}

%token IF ELSE VAL VAR CLASS PUBLIC PROTECTED PRIVATE INTERNAL ENDL WHILE DO FUNC FOR SUPER THIS OVERRIDE OPEN CONSTRUCTOR
%token <ident>ID

%token <intLit>INT_LITERAL 
%token <charLit>CHAR_LITERAL 
%token <doubleLit>DOUBLE_LITERAL 
%token <stringLit>STRING_LITERAL 
%token TRUE_LITERAL FALSE_LITERAL

%nonassoc INCREMENT DECREMENT
%nonassoc ENDL
%right '=' PLUS_ASSIGNMENT MINUS_ASSIGNMENT MUL_ASSIGNMENT DIV_ASSIGNMENT MOD_ASSIGNMENT
%left DISJ
%left CONJ
%left EQUAL NOT_EQUAL
%left '>' '<' GREATER_EQUAL LESS_EQUAL 
%left IN
%left RANGE
%left '+' '-'
%left '*' '/' '%'
%left UMINUS UPLUS
%right PREF_INCREMENT PREF_DECREMENT '!'
%left POST_INCREMENT POST_DECREMENT '.'
%nonassoc '(' ')'

%start KotlinFile

%type <expression>SimpleExpression
%type <exprList>ExpressionList
%type <statement>Statement WhileStatement DoWhileStatement ForStatement ValStmt VarStmt MultiDeclararion
%type <stmtList>StatementList BlockStatement
%type <varDecl>VarDeclaration
%type <varDeclList>VarDeclarationList VarDeclIdList
%type <function>FunctionDeclaration
%type <mod>ElementModifier
%type <modList>ElementModifierList
%type <elem>KotlinFileElement
%type <elemList>KotlinFileElementList
%type <file>KotlinFile

%% 
KotlinFile: KotlinFileElementList {$$ = createKotlinFileNode($1);}
          ;

KotlinFileElementList: KotlinFileElement {$$ = createKotlinFileElementListNode($1);}
                     | KotlinFileElementList KotlinFileElement {$$ = addKotlinFileElementToList($1, $2);}
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
                | ID {$$ = createIDExpressionNode($1);}
                | SUPER {$$ = createSuperExpressionNode();}
                | THIS {$$ = createThisExpressionNode();}
                | '(' SimpleExpression ')' {$$ = createBracketExpressionNode($2);}
                | SimpleExpression '.' EndlOpt ID {$$ = createFieldAccessExpressionNode($1, $4);}
                | SimpleExpression '.' EndlOpt ID '(' ExpressionList ')' {$$ = createMethodAccessExpressionNode($1, $4, $6);}
                | SimpleExpression '.' EndlOpt ID '(' ')' {$$ = createMethodAccessExpressionNode($1, $4, NULL);}
                | SimpleExpression EndlList '.' EndlOpt ID {$$ = createFieldAccessExpressionNode($1, $5);}
                | SimpleExpression EndlList '.' EndlOpt ID '(' ExpressionList ')' {$$ = createMethodAccessExpressionNode($1, $5, $7);}
                | SimpleExpression EndlList '.' EndlOpt ID '(' ')' {$$ = createMethodAccessExpressionNode($1, $5, NULL);}
                | ID '(' ExpressionList ')' { $$ = createFunctionCallExpressionNode($1, $3);}
                | ID '(' ')' { $$ = createFunctionCallExpressionNode($1, NULL);}
                | SimpleExpression DISJ EndlOpt SimpleExpression {$$ = createDisjExpressionNode($1, $4);}
                | SimpleExpression CONJ EndlOpt SimpleExpression {$$ = createConjExpressionNode($1, $4);}
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
                | SimpleExpression '=' EndlOpt SimpleExpression {$$ = createAssignmentExpressionNode($1, $4);}
                | SimpleExpression PLUS_ASSIGNMENT EndlOpt SimpleExpression {$$ = createPlusAssignmentExpressionNode($1, $4);}
                | SimpleExpression MINUS_ASSIGNMENT EndlOpt SimpleExpression {$$ = createMinusAssignmentExpressionNode($1, $4);}
                | SimpleExpression MUL_ASSIGNMENT EndlOpt SimpleExpression {$$ = createMulAssignmentExpressionNode($1, $4);}
                | SimpleExpression DIV_ASSIGNMENT EndlOpt SimpleExpression {$$ = createDivAssignmentExpressionNode($1, $4);}
                | SimpleExpression MOD_ASSIGNMENT EndlOpt SimpleExpression {$$ = createModAssignmentExpressionNode($1, $4);}
                | SimpleExpression RANGE EndlOpt SimpleExpression {$$ = createRangeExpressionNode($1, $4);}
                | '-' EndlOpt SimpleExpression %prec UMINUS {$$ = createUnaryMinusExpressionNode($3);}
                | '+' EndlOpt SimpleExpression %prec UPLUS {$$ = createUnaryPlusExpressionNode($3);}
                | INCREMENT EndlOpt SimpleExpression %prec PREF_INCREMENT {$$ = createPrefIncrementExpressionNode($3);}
                | DECREMENT EndlOpt SimpleExpression %prec PREF_DECREMENT {$$ = createPrefDecrementExpressionNode($3);}
                | '!' EndlOpt SimpleExpression {$$ = createNotExpressionNode($3);}
                | SimpleExpression DECREMENT %prec POST_DECREMENT {$$ = createPostDecrementExpressionNode($1);}
                | SimpleExpression INCREMENT %prec POST_INCREMENT {$$ = createPostIncrementExpressionNode($1);}
                ;

BlockStatement: '{' EndlOpt StatementList '}' {$$ = $3;}
               | '{' EndlOpt '}' {$$ = createStatementListNode(NULL);}
               ;
              
IfStatement: IF '(' SimpleExpression ')' BlockStatement
           | IF '(' SimpleExpression ')' SimpleExpression
           | IF '(' SimpleExpression ')' BlockStatement ELSE BlockStatement
           ;

WhileStatement: WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')' EndlOpt Statement {$$ = createStatementFromWhileWithSingleBody($5, $9);}
              | WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')' EndlOpt BlockStatement EndlList {$$ = createStatementFromWhileWithComplexBody($5, $9);}
              | WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')' EndlOpt BlockStatement ';' EndlOpt {$$ = createStatementFromWhileWithComplexBody($5, $9);}
              ;

DoWhileStatement: DO EndlOpt BlockStatement EndlOpt WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')' EndlList {$$ = createStatementFromWhileWithComplexBody($9, $3);}
                | DO EndlOpt Statement WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')' EndlList {$$ = createStatementFromDoWhileWithSingleBody($8, $3);}
                | DO EndlOpt BlockStatement EndlOpt WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')' ';' EndlOpt {$$ = createStatementFromWhileWithComplexBody($9, $3);}
                | DO EndlOpt Statement WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')' ';' EndlOpt {$$ = createStatementFromDoWhileWithSingleBody($8, $3);}
                ;

ForStatement: FOR '(' ID IN SimpleExpression')' EndlOpt BlockStatement EndlList {$$ = createForStatementWithComplexBody(createVarDeclarationListNode(createVarDeclarationNode($3, NULL)), $5, $8);}
            | FOR '(' ID IN SimpleExpression')' EndlOpt BlockStatement ';' EndlOpt {$$ = createForStatementWithComplexBody(createVarDeclarationListNode(createVarDeclarationNode($3, NULL)), $5, $8);}
            | FOR '(' ID IN SimpleExpression')' EndlOpt Statement {$$ = createForStatementWithSingleBody(createVarDeclarationListNode(createVarDeclarationNode($3, NULL)), $5, $8);}
            | FOR '(' '(' VarDeclIdList ')' IN SimpleExpression')' EndlOpt BlockStatement EndlList {$$ = createForStatementWithComplexBody($4, $7, $10);}
            | FOR '(' '(' VarDeclIdList ')' IN SimpleExpression')' EndlOpt BlockStatement ';' EndlOpt {$$ = createForStatementWithComplexBody($4, $7, $10);}
            | FOR '(' '(' VarDeclIdList ')' IN SimpleExpression')' EndlOpt Statement {$$ = createForStatementWithSingleBody($4, $7, $10);}
            ;

StatementList: Statement {$$ = createStatementListNode($1);}
             | StatementList Statement {$$ = addStatementToStatementList($1, $2);}
             ;

Statement: ';' EndlOpt {$$ = createEmptyStatement();}
         | SimpleExpression EndlList {$$ = createStatementFromExpression($1);}
         | SimpleExpression ';' EndlOpt {$$ = createStatementFromExpression($1);}
         | VarStmt {$$ = $1;}
         | ValStmt {$$ = $1;}
         | MultiDeclararion {$$ = $1;}
         | WhileStatement {$$ = $1;}
         | DoWhileStatement {$$ = $1;}
         | ForStatement {$$ = $1;}
         ;         

ValStmt: VAL EndlOpt VarDeclaration EndlList {$$ = createValStatementFromVarDeclaration($3, NULL);}
       | VAL EndlOpt VarDeclaration ';' EndlOpt {$$ = createValStatementFromVarDeclaration($3, NULL);}
       | VAL EndlOpt ID EndlOpt '=' EndlOpt SimpleExpression EndlList {$$ = createValStatement($3, $7);}
       | VAL EndlOpt ID EndlOpt '=' EndlOpt SimpleExpression ';' EndlOpt {$$ = createValStatement($3, $7);}
       | VAL EndlOpt VarDeclaration EndlOpt '=' EndlOpt SimpleExpression EndlList {$$ = createValStatementFromVarDeclaration($3, $7);}
       | VAL EndlOpt VarDeclaration EndlOpt '=' EndlOpt SimpleExpression ';' EndlOpt {$$ = createValStatementFromVarDeclaration($3, $7);}
       ;

VarStmt: VAR EndlOpt VarDeclaration EndlList {$$ = createVarStatementFromVarDeclaration($3, NULL);}
       | VAR EndlOpt VarDeclaration ';' EndlOpt {$$ = createVarStatementFromVarDeclaration($3, NULL);}
       | VAR EndlOpt ID EndlOpt '=' EndlOpt SimpleExpression EndlList {$$ = createVarStatement($3, $7);}
       | VAR EndlOpt ID EndlOpt '=' EndlOpt SimpleExpression ';' EndlOpt {$$ = createVarStatement($3, $7);}
       | VAR EndlOpt VarDeclaration EndlOpt '=' EndlOpt SimpleExpression EndlList {$$ = createVarStatementFromVarDeclaration($3, $7);}
       | VAR EndlOpt VarDeclaration EndlOpt '=' EndlOpt SimpleExpression ';' EndlOpt {$$ = createVarStatementFromVarDeclaration($3, $7);}
       ; 

VarDeclIdList: ID {$$ = createVarDeclarationListNode(createVarDeclarationNode($1, NULL));}
             | VarDeclaration {$$ = createVarDeclarationListNode($1);}
             | VarDeclIdList ',' ID {$$ = addVarDeclToVarDeclarationListNode($1, createVarDeclarationNode($1, $3));}
             | VarDeclIdList ',' VarDeclaration {$$ = addVarDeclToVarDeclarationListNode($1, $3);}
             ;

MultiDeclararion: VAL EndlOpt '(' VarDeclIdList ')' EndlOpt '=' EndlOpt SimpleExpression EndlList {$$ = createMultiDeclarationWithVal($4, $9);}
                | VAR EndlOpt '(' VarDeclIdList ')' EndlOpt '=' EndlOpt SimpleExpression EndlList {$$ = createMultiDeclarationWithVar($4, $9);}
                | VAL EndlOpt '(' VarDeclIdList ')' EndlOpt '=' EndlOpt SimpleExpression ';' EndlOpt {$$ = createMultiDeclarationWithVal($4, $9);}
                | VAR EndlOpt '(' VarDeclIdList ')' EndlOpt '=' EndlOpt SimpleExpression ';' EndlOpt {$$ = createMultiDeclarationWithVar($4, $9);}
                ;

VarDeclaration: ID EndlOpt ':' EndlOpt ID {$$ = createVarDeclarationNode($1, $5);}
              ;

VarDeclarationList: VarDeclaration {$$ = createVarDeclarationListNode($1);}
                  | VarDeclarationList EndlOpt ',' EndlOpt VarDeclaration {$$ = addVarDeclToVarDeclarationListNode($1, $5);}
                  ;

FunctionDeclaration: FUNC EndlOpt ID EndlOpt '(' EndlOpt ')' EndlOpt BlockStatement {$$ = createFunctionNode($3, NULL, "Unit", $9);}
                   | FUNC EndlOpt ID EndlOpt '(' EndlOpt ')' EndlOpt ':' EndlOpt ID EndlOpt BlockStatement {$$ = createFunctionNode($3, NULL, $11, $13);}
                   | FUNC EndlOpt ID EndlOpt '(' EndlOpt VarDeclarationList EndlOpt ')' EndlOpt BlockStatement {$$ = createFunctionNode($3, $7, "Unit", $11);}
                   | FUNC EndlOpt ID EndlOpt '(' EndlOpt VarDeclarationList EndlOpt ')' EndlOpt ':' EndlOpt ID EndlOpt BlockStatement {$$ = createFunctionNode($3, $7, $13, $15);}
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

ClassParam : ID ':' ID '=' SimpleExpression
           | ID ':' ID
           | VAL ID ':' ID '=' SimpleExpression
           | VAR ID ':' ID '=' SimpleExpression
           | VAL ID ':' ID
           | VAR ID ':' ID
           | MemberModifierList VAL ID ':' ID '=' SimpleExpression
           | MemberModifierList VAR ID ':' ID '=' SimpleExpression
           | MemberModifierList VAL ID ':' ID
           | MemberModifierList VAR ID ':' ID
           ;

ClassParamList: ClassParam
              | ClassParamList ',' ClassParam
              ;

PrimaryConstructor: CONSTRUCTOR '(' ')'
                  | MemberModifierList CONSTRUCTOR '(' ')'
                  | CONSTRUCTOR '(' ClassParamList ')'
                  | MemberModifierList CONSTRUCTOR '(' ClassParamList ')'
                  | '(' ClassParamList ')'
                  | '(' ')'
                  ;
       
ClassDeclaration: CLASS EndlOpt ID
                | CLASS EndlOpt ID '{' EndlOpt '}'
                | CLASS EndlOpt ID '{' EndlOpt ClassModifierMemberList '}'
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt '{' EndlOpt '}'
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt '{' EndlOpt ClassModifierMemberList '}'
                | CLASS EndlOpt ID ':' EndlOpt ID
                | CLASS EndlOpt ID ':' EndlOpt ID '(' ')'
                | CLASS EndlOpt ID ':' EndlOpt ID '(' ExpressionList ')'
                | CLASS EndlOpt ID ':' EndlOpt ID '{' EndlOpt '}'
                | CLASS EndlOpt ID ':' EndlOpt ID '(' ')' '{' EndlOpt '}'
                | CLASS EndlOpt ID ':' EndlOpt ID '(' ExpressionList ')' '{' EndlOpt '}'
                | CLASS EndlOpt ID ':' EndlOpt ID '{' EndlOpt ClassModifierMemberList '}'
                | CLASS EndlOpt ID ':' EndlOpt ID '(' ')' '{' EndlOpt ClassModifierMemberList '}'
                | CLASS EndlOpt ID ':' EndlOpt ID '(' ExpressionList ')' '{' EndlOpt ClassModifierMemberList '}'
                | CLASS EndlOpt ID PrimaryConstructor ':' EndlOpt ID '{' EndlOpt '}'
                | CLASS EndlOpt ID PrimaryConstructor ':' EndlOpt ID '(' ')' '{' EndlOpt '}'
                | CLASS EndlOpt ID PrimaryConstructor ':' EndlOpt ID '(' ExpressionList ')' '{' EndlOpt '}'
                | CLASS EndlOpt ID PrimaryConstructor ':' EndlOpt ID  '{' EndlOpt ClassModifierMemberList '}'
                | CLASS EndlOpt ID PrimaryConstructor ':' EndlOpt ID '(' ')' '{' EndlOpt ClassModifierMemberList '}'
                | CLASS EndlOpt ID PrimaryConstructor ':' EndlOpt ID '(' ExpressionList ')' '{' EndlOpt ClassModifierMemberList '}'
                ;

ElementModifier: PUBLIC {$$ = createPublicModiferNode();}
               | PRIVATE { $$ = createPrivateModiferNode();}
               | INTERNAL {$$ = createInternalModiferNode();}
               | OPEN {$$ = createOpenModiferNode();}
               ;

ElementModifierList: ElementModifier {$$ = createModifierListNode($1);}
                   | ElementModifierList EndlOpt ElementModifier {$$ = addModifierToList($1, $3);}
                   ;

KotlinFileElement: FunctionDeclaration EndlList {$$ = createElementFromFunction(createModifierListNode(createPublicModiferNode()), $1);}
                 | ClassDeclaration EndlList
                 | FunctionDeclaration ';' EndlOpt {$$ = createElementFromFunction(createModifierListNode(createPublicModiferNode()), $1);}
                 | ClassDeclaration ';' EndlOpt
                 | ElementModifierList EndlOpt FunctionDeclaration EndlList {$$ = createElementFromFunction($1, $3);}
                 | ElementModifierList EndlOpt ClassDeclaration EndlList
                 | ElementModifierList EndlOpt FunctionDeclaration ';' EndlOpt {$$ = createElementFromFunction($1, $3);}
                 | ElementModifierList EndlOpt ClassDeclaration ';' EndlOpt
                 | ';' EndlOpt
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
