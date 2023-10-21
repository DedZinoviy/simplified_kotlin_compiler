#include <stdlib.h>

/*------------------------------------ Expression -------------------------------------*/

enum ExpressionType
{
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

/*! Создать узел оператора сравнения "больше" (>).
\param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
\param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
\return указатель на созданный экземпляр узла оператора сравнения "больше".
*/
struct ExpressionNode* createGreatExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand)
{
    return NULL;
}

/*! Создать узел оператора сравнения "меньше" (<).
\param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
\param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
\return указатель на созданный экземпляр узла оператора сравнения "меньше".
*/
struct ExpressionNode* createLessExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand)
{
    return NULL;
}

/*! Создать узел оператора сравнения "больше или равно" (>=).
\param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
\param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
\return указатель на созданный экземпляр узла оператора сравнения "больше или равно".
*/
struct ExpressionNode* createGreatEqualExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand)
{
    return NULL;
}

/*! Создать узел оператора сравнения "меньше или равно" (<=).
\param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
\param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
\return указатель на созданный экземпляр узла оператора сравнения "меньше или равно".
*/
struct ExpressionNode* createLessEqualExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand)
{
    return NULL;
}

/*! Создать узел оператора сравнения "равно" (==).
\param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
\param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
\return указатель на созданный экземпляр узла оператора сравнения "равно".
*/
struct ExpressionNode* createEqualExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand)
{
    return NULL;
}

/*! Создать узел оператора сравнения "не равно" (!=).
\param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
\param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
\return указатель на созданный экземпляр узла оператора сравнения "не равно".
*/
struct ExpressionNode* createNotEqualExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand)
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
