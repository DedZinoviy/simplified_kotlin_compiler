/*------------------------------------ Expression -------------------------------------*/

enum ExpressionType
{
    IDENTIFIER,
    BOOLEAN_LIT,
    INT_LIT,
    DOUBLE_LIT,
    PLUS,
    MINUS,
    DIV,
    MUL,
    MOD,
    LESS,
    GREAT,
    LESS_EQUAL,
    GREAT_EQUAL,
    EQUAL,
    NOT_EQUAL,
    FUNC_CALL,
    BRACKETS,
    FIELD_ACCESS,
    METHOD_ACCESS
};

struct ExpressionNode
{
    int id;
    int intValue;
    int boolValue;
    double doubleValue;
    char* identifierString;
    enum ExpressionType type;
    struct ExpressionNode * left;
    struct ExpressionNode * right;
    struct ExpressionNode * next;
    struct ExpressionListNode * params;  
};

/*------------------------------------ ExpressionList -------------------------------------*/

struct ExpressionListNode
{
    int id;
    struct ExpressionNode * first;
    struct ExpressionNode * last;
};

/*------------------------------------ Statement -------------------------------------*/

enum StatementType
{
    EXPRESSION,
    WHILE,
    DOWHILE,
    FOR,
    EMPTY,
    VAR,
    VAL
};

struct StatementListNode;

struct StatementNode
{
    int id;
    enum StatementType type;
    char * varValId;
    char * varValType;
    struct ExpressionNode * expression;
    struct ExpressionNode * condition;
    struct StatementNode * singleBody;
    struct StatementListNode * complexBody;
    struct StatementNode * next;
};

/*------------------------------------ StatementList -------------------------------------*/

struct StatementListNode
{
    int id;
    struct StatementNode * first;
    struct StatementNode * last;
};
