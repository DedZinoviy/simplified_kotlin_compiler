typedef union {
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
} YYSTYPE;
#define	IF	258
#define	ELSE	259
#define	PUBLIC	260
#define	PROTECTED	261
#define	PRIVATE	262
#define	INTERNAL	263
#define	ENDL	264
#define	WHILE	265
#define	DO	266
#define	FOR	267
#define	SUPER	268
#define	THIS	269
#define	OVERRIDE	270
#define	OPEN	271
#define	ARRAY	272
#define	RETURN	273
#define	ID	274
#define	VAL	275
#define	VAR	276
#define	CLASS	277
#define	CONSTRUCTOR	278
#define	FUNC	279
#define	INT_LITERAL	280
#define	CHAR_LITERAL	281
#define	DOUBLE_LITERAL	282
#define	STRING_LITERAL	283
#define	TRUE_LITERAL	284
#define	FALSE_LITERAL	285
#define	INCREMENT	286
#define	DECREMENT	287
#define	PLUS_ASSIGNMENT	288
#define	MINUS_ASSIGNMENT	289
#define	MUL_ASSIGNMENT	290
#define	DIV_ASSIGNMENT	291
#define	MOD_ASSIGNMENT	292
#define	DISJ	293
#define	CONJ	294
#define	EQUAL	295
#define	NOT_EQUAL	296
#define	GREATER_EQUAL	297
#define	LESS_EQUAL	298
#define	IN	299
#define	RANGE	300
#define	UMINUS	301
#define	UPLUS	302
#define	PREF_INCREMENT	303
#define	PREF_DECREMENT	304
#define	POST_INCREMENT	305
#define	POST_DECREMENT	306


extern YYSTYPE yylval;
