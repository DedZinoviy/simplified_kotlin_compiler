
%token IF ELSE VAL VAR CLASS PUBLIC PROTECTED PRIVATE INTERNAL ENDL WHILE DO FUNC FOR SUPER THIS OVERRIDE OPEN CONSTRUCTOR
%token ID

%token INT_LITERAL 
%token CHAR_LITERAL 
%token DOUBLE_LITERAL 
%token STRING_LITERAL 
%token TRUE_LITERAL FALSE_LITERAL
%token ARRAY RETURN

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


%% 
KotlinFile: EndlOpt KotlinFileElementList
          ;

KotlinFileElementList: KotlinFileElement
                     | KotlinFileElementList KotlinFileElement
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
                | SimpleExpression DISJ EndlOpt SimpleExpression
                | SimpleExpression CONJ EndlOpt SimpleExpression
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
                | INCREMENT EndlOpt SimpleExpression %prec PREF_INCREMENT
                | DECREMENT EndlOpt SimpleExpression %prec PREF_DECREMENT
                | '!' EndlOpt SimpleExpression
                | SimpleExpression DECREMENT %prec POST_DECREMENT
                | SimpleExpression INCREMENT %prec POST_INCREMENT
                | SimpleExpression '[' EndlOpt SimpleExpression EndlOpt ']'
                ;

Type: ID
    | ARRAY EndlOpt '<' EndlOpt Type EndlOpt '>'
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

ForStatement: FOR '(' ID IN SimpleExpression')' EndlOpt BlockStatement EndlList
            | FOR '(' ID IN SimpleExpression')' EndlOpt BlockStatement ';' EndlOpt
            | FOR '(' ID IN SimpleExpression')' EndlOpt Statement
            | FOR '(' '(' VarDeclIdList ')' IN SimpleExpression')' EndlOpt BlockStatement EndlList
            | FOR '(' '(' VarDeclIdList ')' IN SimpleExpression')' EndlOpt BlockStatement ';' EndlOpt
            | FOR '(' '(' VarDeclIdList ')' IN SimpleExpression')' EndlOpt Statement
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
         | ReturnStatement
         ;

ReturnStatement: RETURN EndlList
               | RETURN SimpleExpression EndlList
               | RETURN SimpleExpression ';' EndlOpt
               | RETURN ';' EndlOpt
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

VarDeclIdList: ID
             | VarDeclaration
             | VarDeclIdList ',' ID
             | VarDeclIdList ',' VarDeclaration
             ;

MultiDeclararion: VAL EndlOpt '(' VarDeclIdList ')' EndlOpt '=' EndlOpt SimpleExpression EndlList
                | VAR EndlOpt '(' VarDeclIdList ')' EndlOpt '=' EndlOpt SimpleExpression EndlList
                | VAL EndlOpt '(' VarDeclIdList ')' EndlOpt '=' EndlOpt SimpleExpression ';' EndlOpt
                | VAR EndlOpt '(' VarDeclIdList ')' EndlOpt '=' EndlOpt SimpleExpression ';' EndlOpt
                ;

VarDeclaration: ID EndlOpt ':' EndlOpt Type
              ;

VarDeclarationList: VarDeclaration
                  | VarDeclarationList EndlOpt ',' EndlOpt VarDeclaration
                  ;

FunctionDeclaration: FUNC EndlOpt ID EndlOpt '(' EndlOpt ')' EndlOpt BlockStatement  EndlOpt
                   | FUNC EndlOpt ID EndlOpt '(' EndlOpt ')' EndlOpt ':' EndlOpt Type EndlOpt BlockStatement  EndlOpt
                   | FUNC EndlOpt ID EndlOpt '(' EndlOpt VarDeclarationList EndlOpt ')' EndlOpt BlockStatement  EndlOpt
                   | FUNC EndlOpt ID EndlOpt '(' EndlOpt VarDeclarationList EndlOpt ')' EndlOpt ':' EndlOpt Type EndlOpt BlockStatement  EndlOpt
                   ;

ClassModifierMember: ClassMember
                   | MemberModifierList ClassMember
                   | ';' EndlOpt
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
           ;

ClassParam : ID ':' Type '=' SimpleExpression
           | ID ':' Type
           | VAL ID ':' Type '=' SimpleExpression
           | VAR ID ':' Type '=' SimpleExpression
           | VAL ID ':' Type
           | VAR ID ':' Type
           | MemberModifierList EndlOpt VAL ID ':' Type '=' SimpleExpression
           | MemberModifierList EndlOpt VAR ID ':' Type '=' SimpleExpression
           | MemberModifierList EndlOpt VAL ID ':' Type
           | MemberModifierList EndlOpt VAR ID ':' Type
           ;

ClassParamList: ClassParam
              | ClassParamList ',' ClassParam
              ;

PrimaryConstructor: CONSTRUCTOR EndlOpt '(' ')'
                  | MemberModifierList EndlOpt CONSTRUCTOR EndlOpt '(' ')'
                  | CONSTRUCTOR EndlOpt '(' ClassParamList ')'
                  | MemberModifierList EndlOpt CONSTRUCTOR EndlOpt '(' ClassParamList ')' 
                  | '(' ClassParamList ')'
                  | '(' ')'
                  ;
       
ClassDeclaration: CLASS EndlOpt ID EndlList
                | CLASS EndlOpt ID ';' EndlOpt
                | CLASS EndlOpt ID EndlOpt '{' EndlOpt '}' EndlOpt
                | CLASS EndlOpt ID EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt '{' EndlOpt '}' EndlOpt
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '(' ')' EndlOpt
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '(' ExpressionList ')' EndlOpt
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '{' EndlOpt '}' EndlOpt
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '(' ')' EndlOpt '{' EndlOpt '}' EndlOpt
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '(' ExpressionList ')' EndlOpt '{' EndlOpt '}' EndlOpt
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '(' ')' EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt
                | CLASS EndlOpt ID EndlOpt ':' EndlOpt ID EndlOpt '(' ExpressionList ')' EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '{' EndlOpt '}' EndlOpt
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '(' ')' EndlOpt '{' EndlOpt '}' EndlOpt
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '(' ExpressionList ')' EndlOpt '{' EndlOpt '}' EndlOpt
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '(' ')' EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '(' ExpressionList ')' EndlOpt '{' EndlOpt ClassModifierMemberList '}' EndlOpt
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '(' ')' EndlOpt
                | CLASS EndlOpt ID PrimaryConstructor EndlOpt ':' EndlOpt ID EndlOpt '(' ExpressionList ')' EndlOpt
                ;

ElementModifier: PUBLIC
               | PRIVATE
               | INTERNAL
               | OPEN
               ;

ElementModifierList: ElementModifier
                   | ElementModifierList EndlOpt ElementModifier
                   ;

KotlinFileElement: FunctionDeclaration
                 | ClassDeclaration
                 | ElementModifierList EndlOpt FunctionDeclaration
                 | ElementModifierList EndlOpt ClassDeclaration
                 | ';' EndlOpt
                 ;

EndlOpt: /* empty */
       | EndlList
       ;

EndlList: ENDL
        | EndlList ENDL
        ;
