enum ExpressionType
{
    PLUS,
    MINUS,
    DIV,
    MUL,
    MOD
};

struct ExpressionNode
{
    int id;
    int intValue;
    double doubleValue;
    enum ExpressionType type;
    struct ExpressionNode * left;
    struct ExpressionNode * right;
};

struct DoWhileStatementNode
{
    int id;
};

struct WhileStatementNode
{
    int id;
};
