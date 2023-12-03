typedef union {
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
} YYSTYPE;
#define	IF	258
#define	ELSE	259
#define	VAL	260
#define	VAR	261
#define	CLASS	262
#define	PUBLIC	263
#define	PROTECTED	264
#define	PRIVATE	265
#define	INTERNAL	266
#define	ENDL	267
#define	WHILE	268
#define	DO	269
#define	FUNC	270
#define	FOR	271
#define	SUPER	272
#define	THIS	273
#define	OVERRIDE	274
#define	OPEN	275
#define	CONSTRUCTOR	276
#define	ID	277
#define	INT_LITERAL	278
#define	CHAR_LITERAL	279
#define	DOUBLE_LITERAL	280
#define	STRING_LITERAL	281
#define	TRUE_LITERAL	282
#define	FALSE_LITERAL	283
#define	INCREMENT	284
#define	DECREMENT	285
#define	PLUS_ASSIGNMENT	286
#define	MINUS_ASSIGNMENT	287
#define	MUL_ASSIGNMENT	288
#define	DIV_ASSIGNMENT	289
#define	MOD_ASSIGNMENT	290
#define	DISJ	291
#define	CONJ	292
#define	EQUAL	293
#define	NOT_EQUAL	294
#define	GREATER_EQUAL	295
#define	LESS_EQUAL	296
#define	IN	297
#define	RANGE	298
#define	UMINUS	299
#define	UPLUS	300
#define	PREF_INCREMENT	301
#define	PREF_DECREMENT	302
#define	POST_INCREMENT	303
#define	POST_DECREMENT	304


extern YYSTYPE yylval;
