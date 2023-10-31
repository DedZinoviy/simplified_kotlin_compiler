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