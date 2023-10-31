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
    NOT_EQUAL
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
};

/*------------------------------------ ExpressionList -------------------------------------*/

struct ExpressionListNode
{
    int id;
    struct ExpressionNode * first;
    struct ExpressionNode * last;
};

/*------------------------------------ DoWhile -------------------------------------*/

struct DoWhileStatementNode
{
    int id;
};

/*------------------------------------ While -------------------------------------*/

struct WhileStatementNode
{
    int id;
};

/*------------------------------------ Statement -------------------------------------*/

struct StatementNode
{
    int id;
    struct ExpressionNode * expr;
    struct WhileStatementNode * whl;
    struct DoWhileStatementNode * dwhl;
};