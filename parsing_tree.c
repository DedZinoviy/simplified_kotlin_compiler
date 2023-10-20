#include <stdlib.h>

/*------------------------------------ Expression -------------------------------------*/

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

/*! Создать узел оператора сложения (+).
\param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
\param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
\return указатель на созданный экземпляр узла сложения.
*/
struct ExpressionNode * createPlusExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    return NULL;
}

/*! Создать узел оператора вычитания (-).
\param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
\param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
\return указатель на созданный экземпляр узла вычитания.
*/
struct ExpressionNode * createMinusExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    return NULL;
}

/*! Создать узел оператора умножения (*).
\param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
\param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
\return указатель на созданный экземпляр узла умножения.
*/
struct ExpressionNode * createMulExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    return NULL;
}

/*! Создать узел оператора деления (/).
\param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
\param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
\return указатель на созданный экземпляр узла деления.
*/
struct ExpressionNode * createDivExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    return NULL;
}

/*! Создать узел оператора получния остатка от деления (%).
\param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
\param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
\return указатель на созданный экземпляр узла остатка от деления.
*/
struct ExpressionNode * createModExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    return NULL;
}

struct DoWhileStatementNode
{
    int id;
};

struct WhileStatementNode
{
    int id;
};
