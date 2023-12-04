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
       struct ClassMemberNode * member;
       struct ClassMemberListNode * memberList;
       struct ClassParamNode * classParam;
       struct ClassParamListNode * classParams;
       struct PrimaryConstructorNode * primConstr;
       struct ClassNode * cls;
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
%nonassoc '{' ':'
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
%type <mod>ElementModifier MemberModifier
%type <modList>ElementModifierList MemberModifierList
%type <elem>KotlinFileElement
%type <elemList>KotlinFileElementList
%type <file>KotlinFile
%type <member>ClassMember ClassModifierMember
%type <memberList>ClassModifierMemberList
%type <classParam>ClassParam
%type <classParams>ClassParamList
%type <primConstr>PrimaryConstructor
%type <cls>ClassDeclaration

%% 
KotlinFile: EndlOpt KotlinFileElementList {$$ = root = createKotlinFileNode($2);}
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

DoWhileStatement: DO EndlOpt BlockStatement EndlOpt WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')' EndlList {$$ = createStatementFromDoWhileWithComplexBody($9, $3);}
                | DO EndlOpt Statement WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')' EndlList {$$ = createStatementFromDoWhileWithSingleBody($8, $3);}
                | DO EndlOpt BlockStatement EndlOpt WHILE EndlOpt '(' EndlOpt SimpleExpression EndlOpt ')' ';' EndlOpt {$$ = createStatementFromDoWhileWithComplexBody($9, $3);}
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
             | VarDeclIdList ',' ID {$$ = addVarDeclToVarDeclarationListNode($1, createVarDeclarationNode($3, NULL));}
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

FunctionDeclaration: FUNC EndlOpt ID EndlOpt '(' EndlOpt ')' EndlOpt BlockStatement  EndlOpt {$$ = createFunctionNode($3, NULL, (char*)"Unit", $9);}
                   | FUNC EndlOpt ID EndlOpt '(' EndlOpt ')' EndlOpt ':' EndlOpt ID EndlOpt BlockStatement  EndlOpt {$$ = createFunctionNode($3, NULL, $11, $13);}
                   | FUNC EndlOpt ID EndlOpt '(' EndlOpt VarDeclarationList EndlOpt ')' EndlOpt BlockStatement  EndlOpt {$$ = createFunctionNode($3, $7, (char*)"Unit", $11);}
                   | FUNC EndlOpt ID EndlOpt '(' EndlOpt VarDeclarationList EndlOpt ')' EndlOpt ':' EndlOpt ID EndlOpt BlockStatement  EndlOpt {$$ = createFunctionNode($3, $7, $13, $15);}
                   ;

ClassModifierMember: ClassMember {$$ = $1;}
                   | MemberModifierList ClassMember {$$ = assignModsToClassMember($1, $2);}
                   | ';' EndlOpt {$$ = createEmptyClassMemberNode();}
                   ;

MemberModifier: PUBLIC {$$ = createPublicModifierNode();}
              | PRIVATE {$$ = createPrivateModifierNode();}
              | PROTECTED {$$ = createProtectedModifierNode();}
              | INTERNAL {$$ = createInternalModifierNode();}
              | OPEN {$$ = createOpenModifierNode();}
              | OVERRIDE {$$ = createOverrideModifierNode();}
              ;

MemberModifierList: MemberModifier {$$ = createModifierListNode($1);}
                  | MemberModifierList EndlOpt MemberModifier {$$ = addModifierToList($1, $3);}
                  ;

ClassModifierMemberList: ClassModifierMember {$$ = createClassMemberListNode($1);}
                       | ClassModifierMemberList ClassModifierMember {$$ = addClassMemberToListNode($1, $2);}
                       ;

ClassMember: FunctionDeclaration {$$ = createMethodClassMemberNode(NULL, $1);}
           | ValStmt {$$ = createFieldClassMemberNode(NULL, $1);}
           | VarStmt {$$ = createFieldClassMemberNode(NULL, $1);}
           ;

ClassParam : ID ':' ID '=' SimpleExpression {$$ = createClassParamNodeFromVarDecl(createVarDeclarationNode($1, $3), $5)}
           | ID ':' ID {$$ = createClassParamNodeFromVarDecl(createVarDeclarationNode($1, $3), NULL)}
           | VAL ID ':' ID '=' SimpleExpression {$$ = createClassParamNodeFromVarValStmt(createModifierListNode(createPublicModifierNode()), createValStatementFromVarDeclaration(createVarDeclarationNode($2, $4), $6));}
           | VAR ID ':' ID '=' SimpleExpression {$$ = createClassParamNodeFromVarValStmt(createModifierListNode(createPublicModifierNode()), createVarStatementFromVarDeclaration(createVarDeclarationNode($2, $4), $6));}
           | VAL ID ':' ID {$$ = createClassParamNodeFromVarValStmt(createModifierListNode(createPublicModifierNode()), createValStatementFromVarDeclaration(createVarDeclarationNode($2, $4), NULL));}
           | VAR ID ':' ID {$$ = createClassParamNodeFromVarValStmt(createModifierListNode(createPublicModifierNode()), createVarStatementFromVarDeclaration(createVarDeclarationNode($2, $4), NULL));}
           | MemberModifierList EndlOpt VAL ID ':' ID '=' SimpleExpression {$$ = createClassParamNodeFromVarValStmt($1, createValStatementFromVarDeclaration(createVarDeclarationNode($4, $6), $8));}
           | MemberModifierList EndlOpt VAR ID ':' ID '=' SimpleExpression {$$ = createClassParamNodeFromVarValStmt($1, createVarStatementFromVarDeclaration(createVarDeclarationNode($4, $6), $8));}
           | MemberModifierList EndlOpt VAL ID ':' ID {$$ = createClassParamNodeFromVarValStmt($1, createValStatementFromVarDeclaration(createVarDeclarationNode($4, $6), NULL));}
           | MemberModifierList EndlOpt VAR ID ':' ID {$$ = createClassParamNodeFromVarValStmt($1, createVarStatementFromVarDeclaration(createVarDeclarationNode($4, $6), NULL));}
           ;

ClassParamList: ClassParam {$$ = createClassParamListNode($1);}
              | ClassParamList ',' ClassParam {$$ = addClassParamToListNode($1, $3);}
              ;

PrimaryConstructor: CONSTRUCTOR EndlOpt '(' ')' {$$ = createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL);} 
                  | MemberModifierList EndlOpt CONSTRUCTOR EndlOpt '(' ')' {$$ = createPrimaryConstructor($1, NULL);} 
                  | CONSTRUCTOR EndlOpt '(' ClassParamList ')'{$$ = createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), $4);} 
                  | MemberModifierList EndlOpt CONSTRUCTOR EndlOpt '(' ClassParamList ')' {$$ = createPrimaryConstructor($1, $6);} 
                  | '(' ClassParamList ')' {$$ = createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), $2);} 
                  | '(' ')' {$$ = createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL);} 
                  ;
       
ClassDeclaration: CLASS EndlOpt ID EndlList {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL), NULL, createIDExpressionNode((char*)"Any"));}
                | CLASS EndlOpt ID ';' EndlOpt {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL), NULL, createIDExpressionNode((char*)"Any"));}
                | CLASS EndlOpt ID EndlOpt '{' EndlOpt '}' EndlOpt {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL), NULL, createIDExpressionNode((char*)"Any"));}
                | CLASS EndlOpt ID EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL), $7, createIDExpressionNode((char*)"Any"));}
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt {$$ = createClassNode($3, $4, NULL, createIDExpressionNode((char*)"Any"));}
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt '{' EndlOpt '}' EndlOpt {$$ = createClassNode($3, $4, NULL, createIDExpressionNode((char*)"Any"));}
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt {$$ = createClassNode($3, $4, $8, createIDExpressionNode((char*)"Any"));}
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL) , $11, createIDExpressionNode($7));}
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '(' ')' EndlOpt {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL) , NULL, createFunctionCallExpressionNode($7, NULL));}
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '(' ExpressionList ')' EndlOpt  {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL) , NULL, createFunctionCallExpressionNode($7, $10));}
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '{' EndlOpt '}' EndlOpt {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL) , NULL, createIDExpressionNode($7));}
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '(' ')' EndlOpt '{' EndlOpt '}' EndlOpt {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL) , NULL, createFunctionCallExpressionNode($7, NULL));}
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '(' ExpressionList ')' EndlOpt '{' EndlOpt '}' EndlOpt {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL) , NULL, createFunctionCallExpressionNode($7, $10));}
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '(' ')' EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL) , $14, createFunctionCallExpressionNode($7, NULL));}
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '(' ExpressionList ')' EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL) , $15, createFunctionCallExpressionNode($7, $10));}
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '{' EndlOpt '}' EndlOpt {$$ = createClassNode($3, $4 , NULL, createIDExpressionNode($8));}
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '(' ')' EndlOpt '{' EndlOpt '}' EndlOpt {$$ = createClassNode($3, $4 , NULL, createFunctionCallExpressionNode($8, NULL));}
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '(' ExpressionList ')' EndlOpt '{' EndlOpt '}' EndlOpt {$$ = createClassNode($3, $4 , NULL, createFunctionCallExpressionNode($11, NULL));}
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt {$$ = createClassNode($3, $4 , $12, createIDExpressionNode($8));}
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '(' ')' EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt {$$ = createClassNode($3, $4 , $15, createFunctionCallExpressionNode($8, NULL));}
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '(' ExpressionList ')' EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt {$$ = createClassNode($3, $4 , $16, createFunctionCallExpressionNode($8, $11));}
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt {$$ = createClassNode($3, $4 , NULL, createIDExpressionNode($8));}
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '(' ')' EndlOpt {$$ = createClassNode($3, $4 , NULL, createFunctionCallExpressionNode($8, NULL));}
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '(' ExpressionList ')' EndlOpt {$$ = createClassNode($3, $4 , NULL, createFunctionCallExpressionNode($8, $11));}
                ;

ElementModifier: PUBLIC {$$ = createPublicModifierNode();}
               | PRIVATE { $$ = createPrivateModifierNode();}
               | INTERNAL {$$ = createInternalModifierNode();}
               | OPEN {$$ = createOpenModifierNode();}
               ;

ElementModifierList: ElementModifier {$$ = createModifierListNode($1);}
                   | ElementModifierList EndlOpt ElementModifier {$$ = addModifierToList($1, $3);}
                   ;

KotlinFileElement: FunctionDeclaration {$$ = createElementFromFunction(createModifierListNode(createPublicModifierNode()), $1);}
                 | ClassDeclaration {$$ = createElementFromClass(createModifierListNode(createPublicModifierNode()), $1);}
                 | ElementModifierList EndlOpt FunctionDeclaration {$$ = createElementFromFunction($1, $3);}
                 | ElementModifierList EndlOpt ClassDeclaration {$$ = createElementFromClass($1, $3);}
                 | ';' EndlOpt {$$ = createEmptyElement();}
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