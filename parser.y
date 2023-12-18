%{
       #include "modifier_head.h"
       #include "parsing_tree.h"
       void yyerror(char const * s);
       extern int yylex(void);
%}

%union {
       int intLit;
       char charLit;
       double doubleLit;
       struct stringBuffer * stringLit;
       struct ModifierHead * modHead;
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
       struct TypeNode * typ;
}

%token IF ELSE PUBLIC PROTECTED PRIVATE INTERNAL ENDL WHILE DO FOR SUPER THIS OVERRIDE OPEN ARRAY RETURN
%token <ident>ID
%token <modHead>VAL VAR CLASS CONSTRUCTOR FUNC

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
%nonassoc '(' ')' '[' ']'

%start KotlinFile

%type <expression>SimpleExpression
%type <exprList>ExpressionList
%type <statement>Statement WhileStatement DoWhileStatement ForStatement ValStmt VarStmt MultiDeclararion ReturnStatement
%type <stmtList>StatementList BlockStatement
%type <varDecl>VarDeclaration
%type <varDeclList>VarDeclarationList VarDeclIdList
%type <function>FunctionDeclaration
%type <mod>MemberModifier
%type <modList>MemberModifierList
%type <elem>KotlinFileElement
%type <elemList>KotlinFileElementList
%type <file>KotlinFile
%type <member>ClassMember ClassModifierMember
%type <memberList>ClassModifierMemberList
%type <classParam>ClassParam
%type <classParams>ClassParamList
%type <primConstr>PrimaryConstructor
%type <cls>ClassDeclaration
%type <typ>Type

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
                | SimpleExpression '[' EndlOpt SimpleExpression EndlOpt ']' {$$ = createArrayElementAccessExpression($1, $4);}
                | ARRAY '(' SimpleExpression ',' '{' SimpleExpression ';' '}' ')' {$$ = createArrayCreationExpression($3, $6);}
                | ARRAY '(' SimpleExpression ')' EndlOpt '{' EndlOpt SimpleExpression EndlOpt ';' '}' {$$ = createArrayCreationExpression($3, $8);}
                ;

Type: ID {$$ = createTypeFromClass($1);}
    | ARRAY EndlOpt '<' EndlOpt Type EndlOpt '>' {$$ = createTypeFromArray($5);}
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
         | ReturnStatement {$$ = $1;}
         ;

ReturnStatement: RETURN EndlList {$$ = createReturnStatement(NULL);}
               | RETURN SimpleExpression EndlList {$$ = createReturnStatement($2);}
               | RETURN SimpleExpression ';' EndlOpt {$$ = createReturnStatement($2);}
               | RETURN ';' EndlOpt {$$ = createReturnStatement(NULL);}
               ; 

ValStmt: VAL EndlOpt VarDeclaration EndlList {$$ = createValStatementFromVarDeclaration($3, NULL); $$->_tempHead = $1;}
       | VAL EndlOpt VarDeclaration ';' EndlOpt {$$ = createValStatementFromVarDeclaration($3, NULL); $$->_tempHead = $1;}
       | VAL EndlOpt ID EndlOpt '=' EndlOpt SimpleExpression EndlList {$$ = createValStatement($3, $7); $$->_tempHead = $1;}
       | VAL EndlOpt ID EndlOpt '=' EndlOpt SimpleExpression ';' EndlOpt {$$ = createValStatement($3, $7); $$->_tempHead = $1;}
       | VAL EndlOpt VarDeclaration EndlOpt '=' EndlOpt SimpleExpression EndlList {$$ = createValStatementFromVarDeclaration($3, $7); $$->_tempHead = $1;}
       | VAL EndlOpt VarDeclaration EndlOpt '=' EndlOpt SimpleExpression ';' EndlOpt {$$ = createValStatementFromVarDeclaration($3, $7); $$->_tempHead = $1;}
       ;

VarStmt: VAR EndlOpt VarDeclaration EndlList {$$ = createVarStatementFromVarDeclaration($3, NULL); $$->_tempHead = $1;}
       | VAR EndlOpt VarDeclaration ';' EndlOpt {$$ = createVarStatementFromVarDeclaration($3, NULL); $$->_tempHead = $1;}
       | VAR EndlOpt ID EndlOpt '=' EndlOpt SimpleExpression EndlList {$$ = createVarStatement($3, $7); $$->_tempHead = $1;}
       | VAR EndlOpt ID EndlOpt '=' EndlOpt SimpleExpression ';' EndlOpt {$$ = createVarStatement($3, $7); $$->_tempHead = $1;}
       | VAR EndlOpt VarDeclaration EndlOpt '=' EndlOpt SimpleExpression EndlList {$$ = createVarStatementFromVarDeclaration($3, $7); $$->_tempHead = $1;}
       | VAR EndlOpt VarDeclaration EndlOpt '=' EndlOpt SimpleExpression ';' EndlOpt {$$ = createVarStatementFromVarDeclaration($3, $7); $$->_tempHead = $1;}
       ; 

VarDeclIdList: ID {$$ = createVarDeclarationListNode(createVarDeclarationNode($1, NULL));}
             | VarDeclaration {$$ = createVarDeclarationListNode($1);}
             | VarDeclIdList ',' ID {$$ = addVarDeclToVarDeclarationListNode($1, createVarDeclarationNode($3, NULL));}
             | VarDeclIdList ',' VarDeclaration {$$ = addVarDeclToVarDeclarationListNode($1, $3);}
             ;

MultiDeclararion: VAL EndlOpt '(' VarDeclIdList ')' EndlOpt '=' EndlOpt SimpleExpression EndlList {$$ = createMultiDeclarationWithVal($4, $9); $$->_tempHead = $1;}
                | VAR EndlOpt '(' VarDeclIdList ')' EndlOpt '=' EndlOpt SimpleExpression EndlList {$$ = createMultiDeclarationWithVar($4, $9); $$->_tempHead = $1;}
                | VAL EndlOpt '(' VarDeclIdList ')' EndlOpt '=' EndlOpt SimpleExpression ';' EndlOpt {$$ = createMultiDeclarationWithVal($4, $9); $$->_tempHead = $1;}
                | VAR EndlOpt '(' VarDeclIdList ')' EndlOpt '=' EndlOpt SimpleExpression ';' EndlOpt {$$ = createMultiDeclarationWithVar($4, $9); $$->_tempHead = $1;}
                ;

VarDeclaration: ID EndlOpt ':' EndlOpt Type {$$ = createVarDeclarationNode($1, $5);}
              ;

VarDeclarationList: VarDeclaration {$$ = createVarDeclarationListNode($1);}
                  | VarDeclarationList EndlOpt ',' EndlOpt VarDeclaration {$$ = addVarDeclToVarDeclarationListNode($1, $5);}
                  ;

FunctionDeclaration: FUNC EndlOpt ID EndlOpt '(' EndlOpt ')' EndlOpt BlockStatement  EndlOpt {$$ = createFunctionNode($3, NULL, createTypeFromClass((char*)"Unit"), $9); $$->_tempHead = $1;}
                   | FUNC EndlOpt ID EndlOpt '(' EndlOpt ')' EndlOpt ':' EndlOpt Type EndlOpt BlockStatement  EndlOpt {$$ = createFunctionNode($3, NULL, $11, $13); $$->_tempHead = $1;}
                   | FUNC EndlOpt ID EndlOpt '(' EndlOpt VarDeclarationList EndlOpt ')' EndlOpt BlockStatement  EndlOpt {$$ = createFunctionNode($3, $7, createTypeFromClass((char*)"Unit"), $11); $$->_tempHead = $1;}
                   | FUNC EndlOpt ID EndlOpt '(' EndlOpt VarDeclarationList EndlOpt ')' EndlOpt ':' EndlOpt Type EndlOpt BlockStatement  EndlOpt {$$ = createFunctionNode($3, $7, $13, $15); $$->_tempHead = $1;}
                   | FUNC EndlOpt ID EndlOpt '(' EndlOpt ')' EndlOpt '=' EndlOpt SimpleExpression  EndlOpt {$$ = createFunctionNode($3, NULL, NULL, createStatementListNode(createReturnStatement($11))); $$->_tempHead = $1;}
                   | FUNC EndlOpt ID EndlOpt '(' EndlOpt ')' EndlOpt ':' EndlOpt Type EndlOpt '=' EndlOpt SimpleExpression EndlOpt {$$ = createFunctionNode($3, NULL, $11, createStatementListNode(createReturnStatement($15))); $$->_tempHead = $1;}
                   | FUNC EndlOpt ID EndlOpt '(' EndlOpt VarDeclarationList EndlOpt ')' EndlOpt '=' EndlOpt SimpleExpression EndlOpt {$$ = createFunctionNode($3, $7, NULL, createStatementListNode(createReturnStatement($13))); $$->_tempHead = $1;}
                   | FUNC EndlOpt ID EndlOpt '(' EndlOpt VarDeclarationList EndlOpt ')' EndlOpt ':' EndlOpt Type EndlOpt '=' EndlOpt SimpleExpression EndlOpt {$$ = createFunctionNode($3, $7, $13, createStatementListNode(createReturnStatement($17))); $$->_tempHead = $1;}
                   ;

ClassModifierMember: ClassMember {$$ = $1;}
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

ClassMember: FunctionDeclaration { 
              struct ModifierListNode * modList = NULL; if (isZeroHead($1->_tempHead)) {modList = createModifierListNode(createPublicModifierNode());}
              else {modList = createModifierListFrom($1->_tempHead);}
              $$ = createMethodClassMemberNode(modList, $1);}
           | ValStmt { 
              struct ModifierListNode * modList = NULL; if (isZeroHead($1->_tempHead)) {modList = createModifierListNode(createPublicModifierNode());
              modList = addModifierToList(modList, createFinalModifierNode());}
              else {modList = createModifierListFrom($1->_tempHead);}
              $$ = createFieldClassMemberNode(modList, $1);}
           | VarStmt {
              struct ModifierListNode * modList = NULL; if (isZeroHead($1->_tempHead)) {modList = createModifierListNode(createPublicModifierNode());
              modList = addModifierToList(modList, createFinalModifierNode());}
              else {modList = createModifierListFrom($1->_tempHead);}
              $$ = createFieldClassMemberNode(modList, $1);}
           ;

ClassParam : ID ':' Type '=' SimpleExpression {$$ = createClassParamNodeFromVarDecl(createVarDeclarationNode($1, $3), $5)}
           | ID ':' Type {$$ = createClassParamNodeFromVarDecl(createVarDeclarationNode($1, $3), NULL)}
           | VAL ID ':' Type '=' SimpleExpression {struct ModifierListNode * modList = NULL; if (isZeroHead($1)) {modList = createModifierListNode(createPublicModifierNode());
                     modList = addModifierToList(modList, createFinalModifierNode());}
                     else {modList = createModifierListFrom($1);}
              $$ = createClassParamNodeFromVarValStmt(modList, createValStatementFromVarDeclaration(createVarDeclarationNode($2, $4), $6));}
           | VAR ID ':' Type '=' SimpleExpression {struct ModifierListNode * modList = NULL; if (isZeroHead($1)) {modList = createModifierListNode(createPublicModifierNode());
                     modList = addModifierToList(modList, createFinalModifierNode());}
                     else {modList = createModifierListFrom($1);}
              $$ = createClassParamNodeFromVarValStmt(modList, createVarStatementFromVarDeclaration(createVarDeclarationNode($2, $4), $6));}
           | VAL ID ':' Type {struct ModifierListNode * modList = NULL; if (isZeroHead($1)) {modList = createModifierListNode(createPublicModifierNode());
                     modList = addModifierToList(modList, createFinalModifierNode());}
                     else {modList = createModifierListFrom($1);}
              $$ = createClassParamNodeFromVarValStmt(modList, createValStatementFromVarDeclaration(createVarDeclarationNode($2, $4), NULL));}
           | VAR ID ':' Type {struct ModifierListNode * modList = NULL; if (isZeroHead($1)) {modList = createModifierListNode(createPublicModifierNode());
                     modList = addModifierToList(modList, createFinalModifierNode());}
                     else {modList = createModifierListFrom($1);}
              $$ = createClassParamNodeFromVarValStmt(modList, createVarStatementFromVarDeclaration(createVarDeclarationNode($2, $4), NULL));}
           | MemberModifierList EndlOpt VAL ID ':' Type '=' SimpleExpression {$$ = createClassParamNodeFromVarValStmt($1, createValStatementFromVarDeclaration(createVarDeclarationNode($4, $6), $8));}
           | MemberModifierList EndlOpt VAR ID ':' Type '=' SimpleExpression {$$ = createClassParamNodeFromVarValStmt($1, createVarStatementFromVarDeclaration(createVarDeclarationNode($4, $6), $8));}
           | MemberModifierList EndlOpt VAL ID ':' Type {$$ = createClassParamNodeFromVarValStmt($1, createValStatementFromVarDeclaration(createVarDeclarationNode($4, $6), NULL));}
           | MemberModifierList EndlOpt VAR ID ':' Type {$$ = createClassParamNodeFromVarValStmt($1, createVarStatementFromVarDeclaration(createVarDeclarationNode($4, $6), NULL));}
           ;

ClassParamList: ClassParam {$$ = createClassParamListNode($1);}
              | ClassParamList ',' ClassParam {$$ = addClassParamToListNode($1, $3);}
              ;

PrimaryConstructor: CONSTRUCTOR EndlOpt '(' ')' {
                     struct ModifierListNode * modList = NULL; if (isZeroHead($1)) {modList = createModifierListNode(createPublicModifierNode());}
                     else {modList = createModifierListFrom($1);}
                     $$ = createPrimaryConstructor(modList, NULL);} 
                  | CONSTRUCTOR EndlOpt '(' ClassParamList ')'{
                     struct ModifierListNode * modList = NULL; if (isZeroHead($1)) {modList = createModifierListNode(createPublicModifierNode());}
                     else {modList = createModifierListFrom($1);}
                     $$ = createPrimaryConstructor(modList, $4);} 
                  | '(' ClassParamList ')' {$$ = createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), $2);} 
                  | '(' ')' {$$ = createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL);} 
                  ;
       
ClassDeclaration: CLASS EndlOpt ID EndlOpt {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL), NULL, createIDExpressionNode((char*)"Any"), $1);}
                | CLASS EndlOpt ID EndlOpt '{' EndlOpt '}' EndlOpt {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL), NULL, createIDExpressionNode((char*)"Any"), $1);}
                | CLASS EndlOpt ID EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL), $7, createIDExpressionNode((char*)"Any"), $1);}
                | CLASS EndlOpt ID EndlOpt PrimaryConstructor EndlOpt {$$ = createClassNode($3, $5, NULL, createIDExpressionNode((char*)"Any"), $1);}
                | CLASS EndlOpt ID EndlOpt PrimaryConstructor EndlOpt '{' EndlOpt '}' EndlOpt {$$ = createClassNode($3, $5, NULL, createIDExpressionNode((char*)"Any"), $1);}
                | CLASS EndlOpt ID EndlOpt PrimaryConstructor EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt {$$ = createClassNode($3, $5, $9, createIDExpressionNode((char*)"Any"), $1);}
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL) , $11, createIDExpressionNode($7), $1);}
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '(' ')' EndlOpt {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL) , NULL, createFunctionCallExpressionNode($7, NULL), $1);}
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '(' ExpressionList ')' EndlOpt  {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL) , NULL, createFunctionCallExpressionNode($7, $10), $1); }
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '{' EndlOpt '}' EndlOpt {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL) , NULL, createIDExpressionNode($7), $1); }
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '(' ')' EndlOpt '{' EndlOpt '}' EndlOpt {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL) , NULL, createFunctionCallExpressionNode($7, NULL), $1); }
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '(' ExpressionList ')' EndlOpt '{' EndlOpt '}' EndlOpt {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL) , NULL, createFunctionCallExpressionNode($7, $10), $1); }
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '(' ')' EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL) , $14, createFunctionCallExpressionNode($7, NULL), $1); }
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '(' ExpressionList ')' EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt {$$ = createClassNode($3, createPrimaryConstructor(createModifierListNode(createPublicModifierNode()), NULL) , $15, createFunctionCallExpressionNode($7, $10), $1); }
                | CLASS EndlOpt ID EndlOpt PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '{' EndlOpt '}' EndlOpt {$$ = createClassNode($3, $5 , NULL, createIDExpressionNode($9), $1); }
                | CLASS EndlOpt ID EndlOpt PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '(' ')' EndlOpt '{' EndlOpt '}' EndlOpt {$$ = createClassNode($3, $5 , NULL, createFunctionCallExpressionNode($9, NULL), $1); }
                | CLASS EndlOpt ID EndlOpt PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '(' ExpressionList ')' EndlOpt '{' EndlOpt '}' EndlOpt {$$ = createClassNode($3, $5 , NULL, createFunctionCallExpressionNode($12, NULL), $1); }
                | CLASS EndlOpt ID EndlOpt PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt {$$ = createClassNode($3, $5 , $13, createIDExpressionNode($9), $1); }
                | CLASS EndlOpt ID EndlOpt PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '(' ')' EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt {$$ = createClassNode($3, $5 , $16, createFunctionCallExpressionNode($9, NULL), $1); }
                | CLASS EndlOpt ID EndlOpt PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '(' ExpressionList ')' EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt {$$ = createClassNode($3, $5 , $17, createFunctionCallExpressionNode($9, $12), $1); }
                | CLASS EndlOpt ID EndlOpt PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt {$$ = createClassNode($3, $5 , NULL, createIDExpressionNode($9), $1); }
                | CLASS EndlOpt ID EndlOpt PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '(' ')' EndlOpt {$$ = createClassNode($3, $5 , NULL, createFunctionCallExpressionNode($9, NULL), $1); }
                | CLASS EndlOpt ID EndlOpt PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '(' ExpressionList ')' EndlOpt {$$ = createClassNode($3, $5 , NULL, createFunctionCallExpressionNode($9, $12), $1); }
                ;

KotlinFileElement: FunctionDeclaration { struct ModifierListNode * modList = NULL; if (isZeroHead($1->_tempHead)) {modList = createModifierListNode(createPublicModifierNode());}
                     else {modList = createModifierListFrom($1->_tempHead);}
                     $$ = createElementFromFunction(modList, $1);}
                 | ClassDeclaration { struct ModifierListNode * modList = NULL; if (isZeroHead($1->_tempHead)) {modList = createModifierListNode(createPublicModifierNode());
                     modList = addModifierToList(modList, createFinalModifierNode());}
                     else {modList = createModifierListFrom($1->_tempHead);}
                     $$ = createElementFromClass(modList, $1);}
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
       printf("%s\n", s);
}
