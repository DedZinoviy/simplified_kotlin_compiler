#include <stdlib.h>
#include "nodes.h"

/*------------------------------------ Expression -------------------------------------*/

/*! Создать узел идентификатора.
\param[in] idStr указатель на строку, представляющую идентификатор.
\return указатель на созданный экземпляр узла идентификатора.
*/
struct ExpressionNode* createIDExpression(char* idStr) 
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = IDENTIFIER;
    node->identifierString = idStr;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    return node;
}

/*! Создать узел Expression на основе целочисленной литеральной констаты.
\param[in] value значение целочисленной литеральной константы.
\return указатель на созданный экземпляр узла целочисленной литеральной константы.
*/
struct ExpressionNode* createIntLiteralExpressionNode(int value)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = INT_LIT;
    node->intValue = value;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    return node;
}

/*! Создать узел Expression на основе литеральной констаты числа с плавающей точкой двойной точности.
\param[in] value значение литеральной константы числа с плавающей точкой двойной точности.
\return указатель на созданный экземпляр узла литеральной константы числа с плавающей точкой двойной точности.
*/
struct ExpressionNode* createDoubleLiteralExpressionNode(double value)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = DOUBLE_LIT;
    node->doubleValue = value;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    return node;
}

/*! Создать узел Expression на основе логической литеральной констаты true.
\return указатель на созданный экземпляр узла логической литеральной константы true.
*/
struct ExpressionNode* createTrueLiteralExpressionNode()
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = BOOLEAN_LIT;
    node->boolValue = 1;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    return node;
}

/*! Создать узел Expression на основе логической литеральной констаты false.
\return указатель на созданный экземпляр узла логической литеральной константы false.
*/
struct ExpressionNode* createFalseLiteralExpressionNode()
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = BOOLEAN_LIT;
    node->boolValue = 0;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    return node;
}

/*! Создать узел оператора сложения (+).
\param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
\param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
\return указатель на созданный экземпляр узла сложения.
*/
struct ExpressionNode * createPlusExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = PLUS;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    return node;
}

/*! Создать узел оператора вычитания (-).
\param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
\param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
\return указатель на созданный экземпляр узла вычитания.
*/
struct ExpressionNode * createMinusExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = MINUS;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    return node;
}

/*! Создать узел оператора умножения (*).
\param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
\param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
\return указатель на созданный экземпляр узла умножения.
*/
struct ExpressionNode * createMulExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = MUL;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    return node;
}

/*! Создать узел оператора деления (/).
\param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
\param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
\return указатель на созданный экземпляр узла деления.
*/
struct ExpressionNode * createDivExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = DIV;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    return node;
}

/*! Создать узел оператора получния остатка от деления (%).
\param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
\param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
\return указатель на созданный экземпляр узла остатка от деления.
*/
struct ExpressionNode * createModExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = MOD;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    return node;
}

/*! Создать узел оператора сравнения "больше" (>).
\param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
\param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
\return указатель на созданный экземпляр узла оператора сравнения "больше".
*/
struct ExpressionNode* createGreatExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = GREAT;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    return node;
}

/*! Создать узел оператора сравнения "меньше" (<).
\param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
\param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
\return указатель на созданный экземпляр узла оператора сравнения "меньше".
*/
struct ExpressionNode* createLessExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = LESS;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    return node;
}

/*! Создать узел оператора сравнения "больше или равно" (>=).
\param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
\param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
\return указатель на созданный экземпляр узла оператора сравнения "больше или равно".
*/
struct ExpressionNode* createGreatEqualExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = GREAT_EQUAL;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    return node;
}

/*! Создать узел оператора сравнения "меньше или равно" (<=).
\param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
\param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
\return указатель на созданный экземпляр узла оператора сравнения "меньше или равно".
*/
struct ExpressionNode* createLessEqualExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = LESS_EQUAL;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    return node;
}

/*! Создать узел оператора сравнения "равно" (==).
\param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
\param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
\return указатель на созданный экземпляр узла оператора сравнения "равно".
*/
struct ExpressionNode* createEqualExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = EQUAL;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    return node;
}

/*! Создать узел оператора сравнения "не равно" (!=).
\param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
\param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
\return указатель на созданный экземпляр узла оператора сравнения "не равно".
*/
struct ExpressionNode* createNotEqualExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = NOT_EQUAL;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    return node;
}



/*------------------------------------ ExpressionList -------------------------------------*/

/*! Создать узел списка Expression.
\param[in] firstChild указатель на первый элемент списка; для пустого списка - NULL.
\return указатель на созданный экземпляр узла списка Expression.
*/
struct ExpressionListNode * createExpressionListNode(struct ExpressionNode * firstChild)
{
    struct ExpressionListNode * node = (struct ExpressionListNode*)malloc(sizeof(struct ExpressionListNode));
    node->first = firstChild;
    node->last = firstChild;
    return node;
}

/*! Добавить ExpressionNode к списку Expression.
\param[in,out] list список, к которому добавляется новый узел.
\param[in] expression добавляемый узел Expression.
\return измененный список Expression (тот же самый, что и параметр list). 
*/
struct ExpressionListNode * addExpressionToExpressionList(struct ExpressionListNode * list, struct ExpressionNode * expression)
{
    list->last->next = expression;
    list->last = expression;
    return list;
}
