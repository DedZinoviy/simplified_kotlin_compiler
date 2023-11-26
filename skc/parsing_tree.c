#include <stdlib.h>
#include "parsing_tree.h"

int ID = 0;

/*------------------------------------ Expression -------------------------------------*/

/*! Создать узел идентификатора.
* \param[in] idStr указатель на строку, представляющую идентификатор.
* \return указатель на созданный экземпляр узла идентификатора.
*/
struct ExpressionNode* createIDExpression(char* idStr) 
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = IDENTIFIER;
    node->identifierString = idStr;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    node->id = ID++;
    return node;
}

/*! Создать узел Expression на основе целочисленной литеральной констаты.
* \param[in] value значение целочисленной литеральной константы.
* \return указатель на созданный экземпляр узла целочисленной литеральной константы.
*/
struct ExpressionNode* createIntLiteralExpressionNode(int value)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = INT_LIT;
    node->intValue = value;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    node->id = ID++;
    return node;
}

/*! Создать узел Expression на основе литеральной констаты числа с плавающей точкой двойной точности.
* \param[in] value значение литеральной константы числа с плавающей точкой двойной точности.
* \return указатель на созданный экземпляр узла литеральной константы числа с плавающей точкой двойной точности.
*/
struct ExpressionNode* createDoubleLiteralExpressionNode(double value)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = DOUBLE_LIT;
    node->doubleValue = value;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    node->id = ID++;
    return node;
}

/*! Создать узел Expression на основе логической литеральной констаты true.
* \return указатель на созданный экземпляр узла логической литеральной константы true.
*/
struct ExpressionNode* createTrueLiteralExpressionNode()
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = BOOLEAN_LIT;
    node->boolValue = 1;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    node->id = ID++;
    return node;
}

/*! Создать узел Expression на основе логической литеральной констаты false.
* \return указатель на созданный экземпляр узла логической литеральной константы false.
*/
struct ExpressionNode* createFalseLiteralExpressionNode()
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = BOOLEAN_LIT;
    node->boolValue = 0;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    node->id = ID++;
    return node;
}

/*! Создать узел Expression на основе литеральной символьной констаты.
* \param[in] value значение литеральной символьной константы.
* \return указатель на созданный экземпляр узла литеральной символьной константы.
*/
struct ExpressionNode* createCharLiteralExpressionNode(char value)
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = CHAR_LIT;
    node->charValue = value;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    return node;
}

/*! Создать узел Expression на основе литеральной строковой констаты.
* \param[in] value значение литеральной строковой константы.
* \return указатель на созданный экземпляр узла литеральной строковой константы.
*/
struct ExpressionNode* createStringLiteralExpressionNode(struct stringBuffer * value)
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = STRING_LIT;
    node->stringValue = value;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    return node;
}

/*! Создать узел оператора дизъюнкции (||).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла дизъюнкции.
*/
struct ExpressionNode * createDisjExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = DISJUNCTION;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    node->id = ID++;
    return node;
}

/*! Создать узел оператора конъюнкции (&&).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла конъюнкции.
*/
struct ExpressionNode * createConjExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = CONJUNCTION;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    node->id = ID++;
    return node;
}

/*! Создать узел оператора сложения (+).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла сложения.
*/
struct ExpressionNode * createPlusExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = PLUS;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    node->id = ID++;
    return node;
}

/*! Создать узел оператора вычитания (-).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла вычитания.
*/
struct ExpressionNode * createMinusExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = MINUS;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    node->id = ID++;
    return node;
}

/*! Создать узел оператора умножения (*).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла умножения.
*/
struct ExpressionNode * createMulExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = MUL;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    node->id = ID++;
    return node;
}

/*! Создать узел оператора деления (/).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла деления.
*/
struct ExpressionNode * createDivExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = DIV;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    node->id = ID++;
    return node;
}

/*! Создать узел оператора получния остатка от деления (%).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла остатка от деления.
*/
struct ExpressionNode * createModExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = MOD;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    node->id = ID++;
    return node;
}

/*! Создать узел оператора сравнения "больше" (>).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла оператора сравнения "больше".
*/
struct ExpressionNode* createGreatExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = GREAT;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    node->id = ID++;
    return node;
}

/*! Создать узел оператора сравнения "меньше" (<).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла оператора сравнения "меньше".
*/
struct ExpressionNode* createLessExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = LESS;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    node->id = ID++;
    return node;
}

/*! Создать узел оператора сравнения "больше или равно" (>=).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла оператора сравнения "больше или равно".
*/
struct ExpressionNode* createGreatEqualExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = GREAT_EQUAL;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    node->id = ID++;
    return node;
}

/*! Создать узел оператора сравнения "меньше или равно" (<=).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла оператора сравнения "меньше или равно".
*/
struct ExpressionNode* createLessEqualExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = LESS_EQUAL;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    node->id = ID++;
    return node;
}

/*! Создать узел оператора сравнения "равно" (==).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла оператора сравнения "равно".
*/
struct ExpressionNode* createEqualExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = EQUAL;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    node->id = ID++;
    return node;
}

/*! Создать узел оператора сравнения "не равно" (!=).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла оператора сравнения "не равно".
*/
struct ExpressionNode* createNotEqualExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand)
{
    struct ExpressionNode* node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->type = NOT_EQUAL;
    node->left = leftOperand;
    node->right = rightOperand;
    node->next = NULL;
    node->id = ID++;
    return node;
}

/*! Создать узел вызова функции.
* \param[in] idStr строка-идентификатор (имя) функции.
* \param[in] list список параметров-аргументов функции; NULL, если список пустой.
* \return указатель на созданный узел Expression.
*/
struct ExpressionNode* createFunctionCallExpressionNode(char * idStr, struct ExpressionListNode * list)
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = FUNC_CALL;
    node->identifierString = idStr;
    node->params = list;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    return node;
}

/*! Создать узел доступа к полю-члену класса.
* \param[in] object объект, на котором вызывается операция доступа к члену.
* \param[in] membId идентификатор поля-члена класса.
* \return указатель на созданный узел доступа к члену класса.
*/
struct ExpressionNode* createFieldAccessExpressionNode(struct ExpressionNode * object, char * membId)
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = FIELD_ACCESS;
    node->identifierString = membId;
    node->left = object;
    node->next = NULL;
    node->params = NULL;
    node->right = NULL;
    return node;
}

/*! Создать узел доступа к методу-члену класса.
* \param[in] object объект, на котором вызывается операция доступа к члену.
* \param[in] membId идентификатор метода-члена класса.
* \param[in] paramList список параметров метода-члена класса.
* \return указатель на созданный узел доступа к члену класса.
*/
struct ExpressionNode* createMethodAccessExpressionNode(struct ExpressionNode * object, char * membId, struct ExpressionListNode * paramList)
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = FIELD_ACCESS;
    node->identifierString = membId;
    node->left = object;
    node->next = NULL;
    node->params = paramList;
    node->right = NULL;
    return node;
}

/*! Создать узел оператора присваивания.
* \param[in] leftOperand указатель на левый операнд присваивания.
* \param[in] rightOperand указатель на правый операнд присваивания.
* \return указатель на созданный узел оператора присваивания.
*/
struct ExpressionNode * createAssignmentExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = ASSIGNMENT;
    node->left = leftOperand;
    node->next = NULL;
    node->params = NULL;
    node->right = rightOperand;
    return node;
}

/*! Создать узел оператора присваивания со сложением.
* \param[in] leftOperand указатель на левый операнд присваивания.
* \param[in] rightOperand указатель на правый операнд присваивания.
* \return указатель на созданный узел оператора присваивания со сложением.
*/
struct ExpressionNode * createPlusAssignmentExpressioNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = PLUS_ASSIGNMENT;
    node->left = leftOperand;
    node->next = NULL;
    node->params = NULL;
    node->right = rightOperand;
    return node;
}

/*! Создать узел оператора присваивания с вычитанием.
* \param[in] leftOperand указатель на левый операнд присваивания.
* \param[in] rightOperand указатель на правый операнд присваивания.
* \return указатель на созданный узел оператора присваивания с вычитанием.
*/
struct ExpressionNode * createMinusAssignmentExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = MINUS_ASSIGNMENT;
    node->left = leftOperand;
    node->next = NULL;
    node->params = NULL;
    node->right = rightOperand;
    return node;
}

/*! Создать узел оператора присваивания с умножением.
* \param[in] leftOperand указатель на левый операнд присваивания.
* \param[in] rightOperand указатель на правый операнд присваивания.
* \return указатель на созданный узел оператора присваивания с умножением.
*/
struct ExpressionNode * createMulAssignmentExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = MUL_ASSIGNMENT;
    node->left = leftOperand;
    node->next = NULL;
    node->params = NULL;
    node->right = rightOperand;
    return node;
}

/*! Создать узел оператора присваивания с делением.
* \param[in] leftOperand указатель на левый операнд присваивания.
* \param[in] rightOperand указатель на правый операнд присваивания.
* \return указатель на созданный узел оператора присваивания с делением.
*/
struct ExpressionNode * createDivAssignmentExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = DIV_ASSIGNMENT;
    node->left = leftOperand;
    node->next = NULL;
    node->params = NULL;
    node->right = rightOperand;
    return node;
}

/*! Создать узел оператора присваивания со взятием остатка.
* \param[in] leftOperand указатель на левый операнд присваивания.
* \param[in] rightOperand указатель на правый операнд присваивания.
* \return указатель на созданный узел оператора присваивания со взятием остатка.
*/
struct ExpressionNode * createModAssignmentExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = MOD_ASSIGNMENT;
    node->left = leftOperand;
    node->next = NULL;
    node->params = NULL;
    node->right = rightOperand;
    return node;
}

/*! Создать узел оператора круглых скобок.
* \param[in] innerExpression внутреннее выражение в круглых скобках.
* \return ссылка на узел оператора круглых скобок.
*/
struct ExpressionNode * createBracketExpressionNode(struct ExpressionNode * innerExpression)
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = BRACKETS;
    node->left = innerExpression;
    node->next = NULL;
    node->params = NULL;
    node->right = NULL;
    return node;
}

/*! Создать узел выражения идентификатора.
* \param[in] ident строка идентификатора.
* \return указатель на узел Expression ID.
*/
struct ExpressionNode * createIDExpressionNode(char * ident)
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = IDENTIFIER;
    node->identifierString = ident;
    node->left = NULL;
    node->next = NULL;
    node->params = NULL;
    node->right = NULL;
    return node;
}

/*! Создать узел указателя на рассматриваемый объект This.
* \return указатель на узел рассматриваемого объекта This.
*/
struct ExpressionNode * createThisExpressionNode()
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = THIS;
    node->left = NULL;
    node->next = NULL;
    node->params = NULL;
    node->right = NULL;
    return node;
}

/*! Создать узел указателя на объект родительского класса Super.
* \return указатель на узел объекта родительского класса Super.
*/
struct ExpressionNode * createSuperExpressionNode()
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = SUPER;
    node->left = NULL;
    node->next = NULL;
    node->params = NULL;
    node->right = NULL;
    return node;
}

/*! Создать узел оператора создания диапазона.
* \param[in] leftOperand указатель на левый операнд.
* \param[in] rightOperand указатель на правый операнд.
* \return указатель на созданный узел оператора создания диапазона.
*/
struct ExpressionNode * createRangeExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand)
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = RANGE;
    node->left = leftOperand;
    node->next = NULL;
    node->params = NULL;
    node->right = rightOperand;
    return node;
}

/*! Создать узел оператора префиксного инкремента.
* \param[in] value указатель на инкрементируемый Expression.
* \return указатель на узел оператора префиксного инкремента.
*/
struct ExpressionNode * createPrefIncrementExpressionNode(struct ExpressionNode * value)
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = PREF_INCREMENT;
    node->left = NULL;
    node->next = NULL;
    node->params = NULL;
    node->right = value;
    return node;
}

/*! Создать узел оператора префиксного декремента.
* \param[in] value указатель на декрементируемый Expression.
* \return указатель на узел оператора префиксного декремента.
*/
struct ExpressionNode * createPrefDecrementExpressionNode(struct ExpressionNode * value)
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = PREF_DECREMENT;
    node->left = NULL;
    node->next = NULL;
    node->params = NULL;
    node->right = value;
    return node;
}

/*! Создать узел оператора постфиксного инкремента.
* \param[in] value указатель на инкрементируемый Expression.
* \return указатель на узел оператора постфиксного инкремента.
*/
struct ExpressionNode * createPostIncrementExpressionNode(struct ExpressionNode * value)
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = POST_INCREMENT;
    node->left = value;
    node->next = NULL;
    node->params = NULL;
    node->right = NULL;
    return node;
}

/*! Создать узел оператора постфиксного декремента.
* \param[in] value указатель на инкрементируемый Expression.
* \return указатель на узел оператора постфиксного декремента.
*/
struct ExpressionNode * createPostDecrementExpressionNode(struct ExpressionNode * value)
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = POST_DECREMENT;
    node->left = value;
    node->next = NULL;
    node->params = NULL;
    node->right = NULL;
    return node;
}

/*! Создать узел оператора унарного плюса.
* \param[in] value указатель на опреанд.
* \return указатель на узел оператора унарного плюса.
*/
struct ExpressionNode * createUnaryPlusExpressionNode(struct ExpressionNode * value)
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = UNARY_PLUS;
    node->left = NULL;
    node->next = NULL;
    node->params = NULL;
    node->right = value;
    return node;
}

/*! Создать узел оператора унарного минуса.
* \param[in] value указатель на операнд.
* \return указатель на узел оператора унарного минуса.
*/
struct ExpressionNode * createUnaryMinusExpressionNode(struct ExpressionNode * value)
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = UNARY_MINUS;
    node->left = NULL;
    node->next = NULL;
    node->params = NULL;
    node->right = value;
    return node;
}

/*! Создать узел оператора логического отрицания.
* \param[in] value указатель на операнд.
* \return указатель на узел оператора логического отрицания.
*/
struct ExpressionNode * createNotExpressionNode(struct ExpressionNode * value)
{
    struct ExpressionNode * node = (struct ExpressionNode*)malloc(sizeof(struct ExpressionNode));
    node->id = ID++;
    node->type = NOT;
    node->left = NULL;
    node->next = NULL;
    node->params = NULL;
    node->right = value;
    return node;
}


/*------------------------------------ ExpressionList -------------------------------------*/

/*! Создать узел списка Expression.
* \param[in] firstChild указатель на первый элемент списка; для пустого списка - NULL.
* \return указатель на созданный экземпляр узла списка Expression.
*/
struct ExpressionListNode * createExpressionListNode(struct ExpressionNode * firstChild)
{
    struct ExpressionListNode * node = (struct ExpressionListNode*)malloc(sizeof(struct ExpressionListNode));
    node->first = firstChild;
    node->last = firstChild;
    node->id = ID++;
    return node;
}

/*! Добавить ExpressionNode к списку Expression.
* \param[in,out] list список, к которому добавляется новый узел.
* \param[in] expression добавляемый узел Expression.
* \return измененный список Expression (тот же самый, что и параметр list). 
*/
struct ExpressionListNode * addExpressionToExpressionList(struct ExpressionListNode * list, struct ExpressionNode * expression)
{
    list->last->next = expression;
    list->last = expression;
    return list;
}



/*------------------------------------ Statement -------------------------------------*/

/*! Создать узел StatementNode на основе узла ExpressionNode.
* \param[in] expr указатель на экземпляр ExpressionNode, на основе которого создается StatementNode.
* \return указатель на созданный экземпляр StatementNode.
*/
struct StatementNode * createStatementFromExpression(struct ExpressionNode * expr)
{
    struct StatementNode * stmt = (struct StatementNode*)malloc(sizeof(struct StatementNode));
    stmt->type = EXPRESSION;
    stmt->expression = expr;
    stmt->complexBody = NULL;
    stmt->condition = NULL;
    stmt->singleBody = NULL;
    stmt->complexBody = NULL;
    stmt->id = ID++;
    stmt->next = NULL;
    stmt->varDeclList = NULL;
    return stmt;
}

/*! Создать узел StatementNode для цикла while с одним Statement в качесвте тела.
* \param[in] cond Условие выполнения цикла - указатель на узел  Expression.
* \param[in] stmt Тело цикла, состоящее из одного узла Statement.
* \return Созданный узел Statement.
*/
struct StatementNode * createStatementFromWhileWithSingleBody(struct ExpressionNode * cond, struct StatementNode * stmt)
{
    struct StatementNode * statement = (struct StatementNode*)malloc(sizeof(struct StatementNode));
    statement->type = WHILE;
    statement->condition = cond;
    statement->singleBody = stmt;
    statement->complexBody = NULL;
    statement->expression = NULL;
    statement->id = ID++;
    statement->next = NULL;
    stmt->varDeclList = NULL;
    return statement;
}

/*! Создать узел StatementNode для цикла while со списком Statement (BlockStatement) в качестве тела.
* \param[in] cond Условие выполнения цикла - указатель на узел  Expression.
* \param[in] stmtList Тело цикла, состоящее из узла StatementList.
* \return Созданный узел Statement.
*/
struct StatementNode * createStatementFromWhileWithComplexBody(struct ExpressionNode * cond, struct StatementListNode * stmtList)
{
    struct StatementNode * statement = (struct StatementNode*)malloc(sizeof(struct StatementNode));
    statement->type = WHILE;
    statement->condition = cond;
    statement->singleBody = NULL;
    statement->complexBody = stmtList;
    statement->expression = NULL;
    statement->id = ID++;
    statement->next = NULL;
    statement->varDeclList = NULL;
    return statement;
}

/*! Создать узел StatementNode для цикла do..while с одним Statement в качесвте тела.
* \param[in] cond Условие выполнения цикла - указатель на узел  Expression.
* \param[in] stmt Тело цикла, состоящее из одного узла Statement.
* \return Созданный узел Statement.
*/
struct StatementNode * createStatementFromDoWhileWithSingleBody(struct ExpressionNode * cond, struct StatementNode * stmt)
{
    struct StatementNode * statement = (struct StatementNode*)malloc(sizeof(struct StatementNode));
    statement->type = DOWHILE;
    statement->condition = cond;
    statement->singleBody = stmt;
    statement->complexBody = NULL;
    statement->expression = NULL;
    statement->id = ID++;
    statement->next = NULL;
    stmt->varDeclList = NULL;
    return statement;
}

/*! Создать узел StatementNode для цикла do..while со списком Statement (BlockStatement) в качестве тела.
* \param[in] cond Условие выполнения цикла - указатель на узел  Expression.
* \param[in] stmtList Тело цикла, состоящее из узла StatementList.
* \return Созданный узел Statement.
*/
struct StatementNode * createStatementFromDoWhileWithComplexBody(struct ExpressionNode * cond, struct StatementListNode * stmtList)
{
    struct StatementNode * statement = (struct StatementNode*)malloc(sizeof(struct StatementNode));
    statement->type = DOWHILE;
    statement->condition = cond;
    statement->singleBody = NULL;
    statement->complexBody = stmtList;
    statement->expression = NULL;
    statement->id = ID++;
    statement->next = NULL;
    statement->varDeclList = NULL;
    return statement;
}

/*! Создать пустой узел Statement.
* \return указатель на пустой узел Statement.
*/
struct StatementNode * createEmptyStatement()
{
    struct StatementNode * node = (struct StatementNode*)malloc(sizeof(struct StatementNode));
    node->id = ID++;
    node->type = EMPTY;
    node->expression = NULL;
    node->condition = NULL;
    node->complexBody = NULL;
    node->singleBody = NULL;
    node->next= NULL;
    node->varDeclList = NULL;
    return node;
}

/*! Создать узел Val Statement без явного указания типа.
* \param[in] valId идентификатор переменной.
* \param[in] expr выражение, результат которого присваивается Val; может быть NULL, если ничего не присаивается.
* \return созданный узел ValStmt.
*/
struct StatementNode * createValStatement(char * valId, struct ExpressionNode * expr)
{
    struct StatementNode * node = (struct StatementNode*)malloc(sizeof(struct StatementNode));
    node->id = ID++;
    node->type = VAL;
    node->complexBody = NULL;
    node->condition = NULL;
    node->next = NULL;
    node->singleBody = NULL;
    node->expression = expr;
    node->varValId = valId;
    node->varDeclList = NULL;
    return node;
}

/*! Создать узел Val Statement с явным указаением типа.
* \param[in] valId идентификатор переменной.
* \param[in] type тип переменной.
* \param[in] expr выражение, результат которого присваивается Val; может быть NULL, если ничего не присаивается.
* \return созданный узел ValStmt.
*/
struct StatementNode * createValStatementWithType(char * valId, char * type ,struct ExpressionNode * expr)
{
    struct StatementNode * node = (struct StatementNode*)malloc(sizeof(struct StatementNode));
    node->id = ID++;
    node->type = VAL;
    node->complexBody = NULL;
    node->condition = NULL;
    node->next = NULL;
    node->singleBody = NULL;
    node->expression = expr;
    node->varValId = valId;
    node->varValType = type;
    node->varDeclList = NULL;
    return node;
}

/*! Создать узел Val Statement с явным указаением типа через VarDeclaration.
* \param[in] decl узел объявления переменной.
* \param[in] expr выражение, результат которого присваивается Val; может быть NULL, если ничего не присаивается.
* \return созданный узел ValStmt.
*/
struct StatementNode * createValStatementFromVarDeclaration(struct VarDeclarationNode * decl, struct ExpressionNode * expr)
{
    struct StatementNode * node = (struct StatementNode*)malloc(sizeof(struct StatementNode));
    node->id = ID++;
    node->type = VAL;
    node->next = NULL;
    node->varValId = decl->identifier;
    node->varValType = decl->type;
    node->expression = expr;
    node->condition = NULL;
    node->complexBody = NULL;
    node->singleBody = NULL;
    node->varDeclList = NULL;
    return node;
}

/*! Создать узел Var Statement без явного указания типа.
* \param[in] varId идентификатор переменной.
* \param[in] expr выражение, результат которого присваивается Var; может быть NULL, если ничего не присаивается.
* \return созданный узел VarStmt.
*/
struct StatementNode * createVarStatement(char * varId, struct ExpressionNode * expr)
{
    struct StatementNode * node = (struct StatementNode*)malloc(sizeof(struct StatementNode));
    node->id = ID++;
    node->type = VAR;
    node->complexBody = NULL;
    node->condition = NULL;
    node->next = NULL;
    node->singleBody = NULL;
    node->expression = expr;
    node->varValId = varId;
    node->varDeclList = NULL;
    return node;
}

/*! Создать узел Var Statement с явным указаением типа.
* \param[in] varId идентификатор переменной.
* \param[in] type тип переменной.
* \param[in] expr выражение, результат которого присваивается Var; может быть NULL, если ничего не присаивается.
* \return созданный узел VarStmt.
*/
struct StatementNode * createVarStatementWithType(char * varId, char * type ,struct ExpressionNode * expr)
{
    struct StatementNode * node = (struct StatementNode*)malloc(sizeof(struct StatementNode));
    node->id = ID++;
    node->type = VAR;
    node->complexBody = NULL;
    node->condition = NULL;
    node->next = NULL;
    node->singleBody = NULL;
    node->expression = expr;
    node->varValId = varId;
    node->varValType = type;
    node->varDeclList = NULL;
    return node;
}

/*! Создать узел Var Statement с явным указаением типа через VarDeclaration.
* \param[in] decl узел объявления переменной.
* \param[in] expr выражение, результат которого присваивается Var; может быть NULL, если ничего не присаивается.
* \return созданный узел VarStmt.
*/
struct StatementNode * createVarStatementFromVarDeclaration(struct VarDeclarationNode * decl, struct ExpressionNode * expr)
{
    struct StatementNode * node = (struct StatementNode*)malloc(sizeof(struct StatementNode));
    node->id = ID++;
    node->type = VAR;
    node->next = NULL;
    node->varValId = decl->identifier;
    node->varValType = decl->type;
    node->expression = expr;
    node->condition = NULL;
    node->complexBody = NULL;
    node->singleBody = NULL;
    node->varDeclList = NULL;
    return node;
}

/*! Создать узел Statement на основе цикла FOR с простым телом.
* \param[in] list указатель на список переменных, работу по которым производит цикл FOR.
* \param[in] cond указатель на узел условия работы цикла FOR.
* \param[in] stmt Тело цикла, состоящее из одного узла Statement.
* \return указатель на созданный узел Statement цикла FOR.
*/
struct StatementNode * createForStatementWithSingleBody(struct VarDeclarationListNode * list, struct ExpressionNode * cond, struct StatementNode * stmt)
{
    struct StatementNode * node = (struct StatementNode*)malloc(sizeof(struct StatementNode));
    node->id = ID++;
    node->type = FOR;
    node->next = NULL;
    node->varValId = NULL;
    node->varValType = NULL;
    node->expression = NULL;
    node->condition = cond;
    node->singleBody = stmt;
    node->complexBody = NULL;
    node->varDeclList = list;
    return node;
}

/*! Создать узел Statement на основе цикла FOR с простым телом.
* \param[in] varDeclList указатель на список переменных, работу по которым производит цикл FOR.
* \param[in] cond указатель на узел условия работы цикла FOR.
* \param[in] stmtList Тело цикла, состоящее из узла StatementList.
* \return указатель на созданный узел Statement цикла FOR.
*/
struct StatementNode * createForStatementWithComplexBody(struct VarDeclarationListNode * varDeclList, struct ExpressionNode * cond, struct StatementListNode * stmtList)
{
    struct StatementNode * node = (struct StatementNode*)malloc(sizeof(struct StatementNode));
    node->id = ID++;
    node->type = FOR;
    node->next = NULL;
    node->varValId = NULL;
    node->varValType = NULL;
    node->expression = NULL;
    node->condition = cond;
    node->singleBody = NULL;
    node->complexBody = stmtList;
    node->varDeclList = varDeclList;
    return node;
}



/*------------------------------------ StatementList -------------------------------------*/

/*! Создать узел списка Statement.
* \param[in] firstChild указатель на первый элемент списка; для пустого списка - NULL.
* \return указатель на созданный экземпляр узла списка Statement.
*/
struct StatementListNode * createStatementListNode(struct StatementNode * firstChild)
{
    struct StatementListNode * node = (struct StatementListNode*)malloc(sizeof(struct StatementListNode));
    node->first = firstChild;
    node->last = firstChild;
    node->id = ID++;
    return node;
}

/*! Добавить StatementNode к списку Statement.
* \param[in,out] list список, к которому добавляется новый узел.
* \param[in] statement добавляемый узел Statement.
* \return измененный список Statement (тот же самый, что и параметр list). 
*/
struct StatementListNode * addStatementToStatementList(struct StatementListNode * list, struct StatementNode * statement)
{
    list->last->next = statement;
    list->last = statement;
    return list;
}



/*------------------------------------ VarDeclaration -------------------------------------*/

/*! Создать узел VarDeclaration на основе идентификатора и его типа.
* \param[in] ident строка - наименование идентификатора.
* \param[in] typ строка - тип идентификатора.
* \return указатель на узел VarDeclaration.
*/
struct VarDeclarationNode * createVarDeclarationNode(char * ident, char * typ)
{
    struct VarDeclarationNode * node = (struct VarDeclarationNode*)malloc(sizeof(struct VarDeclarationNode));
    node->id = ID++;
    node->identifier = ident;
    node->type = typ;
    node->next = NULL;
    return node;
}



/*------------------------------------ VarDeclarationList -------------------------------------*/

/*! Создать узел списка VarDeclaration на основе узла VarDeclaration.
* \param[in] firstNode указатель на первый узел списка.
* \return указатель на узел списка VarDeclarationList.
*/
struct VarDeclarationListNode * createVarDeclarationListNode(struct VarDeclarationNode * firstNode)
{
    struct VarDeclarationListNode * node = (struct VarDeclarationListNode*)malloc(sizeof(struct VarDeclarationListNode));
    node->first = firstNode;
    node->last = firstNode;
    node->id = ID++;
    return node;
}

/*! Добавить VarDeclarationNode к списку VarDeclaration.
* \param[in,out] list список, к которому добавляется новый узел.
* \param[in] varDecl добавляемый узел VarDeclaration.
* \return измененный список VarDeclaration (тот же самый, что и параметр list). 
*/
struct VarDeclarationListNode * addVarDeclToVarDeclarationListNode(struct VarDeclarationListNode * list, struct VarDeclarationNode * varDecl)
{
    list->last->next = varDecl;
    list->last = varDecl;
    return list;
}



/*------------------------------------ Function -------------------------------------*/

/*! Создать узел функции.
* \param[in] ident идентификатор (название) функции.
* \param[in] pars список параметров функции.
* \param[in] ret возвращаемое значение функции.
* \param[in] bod тело функции.
* \return Указатель на созданный узел функции.
*/
struct FunctionNode * createFunctionNode(char * ident, struct VarDeclarationListNode * pars, char * ret, struct StatementListNode * bod)
{
    struct FunctionNode * node = (struct FunctionNode*)malloc(sizeof(struct FunctionNode));
    node->id = ID++;
    node->identifier = ident;
    node->params = pars;
    node->returnValue = ret;
    node->body = bod;
    return node;
}



/*------------------------------------ Modifier -------------------------------------*/

/*! Создать узел модификатора PRIVATE.
* \return указатель на узел модификатора PRIVATE.
*/
struct ModifierNode * createPrivateModiferNode()
{
    struct ModifierNode * node = (struct ModifierNode*)malloc(sizeof(struct ModifierNode));
    node->id = ID++;
    node->type = PRIVATE;
    node->next = NULL;
    return node;
}

/*! Создать узел модификатора PUBLIC.
* \return указатель на узел модификатора PUBLIC.
*/
struct ModifierNode * createPublicModiferNode()
{
    struct ModifierNode * node = (struct ModifierNode*)malloc(sizeof(struct ModifierNode));
    node->id = ID++;
    node->type = PUBLIC;
    node->next = NULL;
    return node;
}

/*! Создать узел модификатора PROTECTED.
* \return указатель на узел модификатора PROTECTED.
*/
struct ModifierNode * createProtectedeModiferNode()
{
    struct ModifierNode * node = (struct ModifierNode*)malloc(sizeof(struct ModifierNode));
    node->id = ID++;
    node->type = PROTECTED;
    node->next = NULL;
    return node;
}

/*! Создать узел модификатора INTERNAL.
* \return указатель на узел модификатора INTERNAL.
*/
struct ModifierNode * createInternalModiferNode()
{
    struct ModifierNode * node = (struct ModifierNode*)malloc(sizeof(struct ModifierNode));
    node->id = ID++;
    node->type = INTERNAL;
    node->next = NULL;
    return node;
}

/*! Создать узел модификатора OVERRIDE.
* \return указатель на узел модификатора OVERRIDE.
*/
struct ModifierNode * createOverrideModiferNode()
{
    struct ModifierNode * node = (struct ModifierNode*)malloc(sizeof(struct ModifierNode));
    node->id = ID++;
    node->type = OVERRIDE;
    node->next = NULL;
    return node;
}

/*! Создать узел модификатора OPEN.
* \return указатель на узел модификатора OPEN.
*/
struct ModifierNode * createOpenModiferNode()
{
    struct ModifierNode * node = (struct ModifierNode*)malloc(sizeof(struct ModifierNode));
    node->id = ID++;
    node->type = OPEN;
    node->next = NULL;
    return node;
}



/*------------------------------------ ModifierList -------------------------------------*/

/*! Создать новый узел списка модификаторов на основе узла модификатора.
* \param[in] mod указатель на узел модификатора, на основе которого осздается список.
* \return Указатель на созданный узел списка модификаторов.
*/
struct ModifierListNode * createModifierListNode(struct ModifierNode * mod)
{
    struct ModifierListNode * node = (struct ModifierListNode*)malloc(sizeof(struct ModifierListNode));
    node->id = ID++;
    node->first = mod;
    node->last = mod;
    return node;
}

/*! Добавить узел модификатора к списку узлов модификаторов.
* \param[in] modList список узлов модификаторов, в который добавляется новый модификатор.
* \param[in] mod добавляемый узел модификатора.
* \return указатель на обновленный список.
*/
struct ModifierListNode * addModifierToList(struct ModifierListNode * modList, struct ModifierNode * mod)
{
    modList->last->next = mod;
    modList->last = mod;
    return modList;
}
