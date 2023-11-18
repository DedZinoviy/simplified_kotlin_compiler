#include "nodes.h"

/*------------------------------------ Expression -------------------------------------*/

/*! Создать узел идентификатора.
* \param[in] idStr указатель на строку, представляющую идентификатор.
* \return указатель на созданный экземпляр узла идентификатора.
*/
struct ExpressionNode* createIDExpression(char* idStr);

/*! Создать узел Expression на основе целочисленной литеральной констаты.
* \param[in] value значение целочисленной литеральной константы.
* \return указатель на созданный экземпляр узла целочисленной литеральной константы.
*/
struct ExpressionNode* createIntLiteralExpressionNode(int value);

/*! Создать узел Expression на основе литеральной констаты числа с плавающей точкой двойной точности.
* \param[in] value значение литеральной константы числа с плавающей точкой двойной точности.
* \return указатель на созданный экземпляр узла литеральной константы числа с плавающей точкой двойной точности.
*/
struct ExpressionNode* createDoubleLiteralExpressionNode(double value);

/*! Создать узел Expression на основе логической литеральной констаты true.
* \return указатель на созданный экземпляр узла логической литеральной константы true.
*/
struct ExpressionNode* createTrueLiteralExpressionNode();

/*! Создать узел Expression на основе логической литеральной констаты false.
* \return указатель на созданный экземпляр узла логической литеральной константы false.
*/
struct ExpressionNode* createFalseLiteralExpressionNode();

/*! Создать узел оператора сложения (+).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла сложения.
*/
struct ExpressionNode * createPlusExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand);

/*! Создать узел оператора вычитания (-).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла вычитания.
*/
struct ExpressionNode * createMinusExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand);

/*! Создать узел оператора умножения (*).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла умножения.
*/
struct ExpressionNode * createMulExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand);

/*! Создать узел оператора деления (/).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла деления.
*/
struct ExpressionNode * createDivExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand);

/*! Создать узел оператора получния остатка от деления (%).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла остатка от деления.
*/
struct ExpressionNode * createModExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand);

/*! Создать узел оператора сравнения "больше" (>).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла оператора сравнения "больше".
*/
struct ExpressionNode* createGreatExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand);

/*! Создать узел оператора сравнения "меньше" (<).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла оператора сравнения "меньше".
*/
struct ExpressionNode* createLessExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand);

/*! Создать узел оператора сравнения "больше или равно" (>=).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла оператора сравнения "больше или равно".
*/
struct ExpressionNode* createGreatEqualExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand);

/*! Создать узел оператора сравнения "меньше или равно" (<=).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла оператора сравнения "меньше или равно".
*/
struct ExpressionNode* createLessEqualExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand);

/*! Создать узел оператора сравнения "равно" (==).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла оператора сравнения "равно".
*/
struct ExpressionNode* createEqualExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand);

/*! Создать узел оператора сравнения "не равно" (!=).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла оператора сравнения "не равно".
*/
struct ExpressionNode* createNotEqualExpressionNode(struct ExpressionNode* leftOperand, struct ExpressionNode* rightOperand);

/*! Создать узел вызова функции.
* \param[in] idStr строка-идентификатор (имя) функции.
* \param[in] list список параметров-аргументов функции; NULL, если список пустой.
* \return указатель на созданный узел Expression.
*/
struct ExpressionNode* createFunctionCallExpressionNode(char * idStr, struct ExpressionListNode * list);

/*! Создать узел доступа к полю-члену класса.
* \param[in] object объект, на котором вызывается операция доступа к члену.
* \param[in] membId идентификатор поля-члена класса.
* \return указатель на созданный узел доступа к члену класса.
*/
struct ExpressionNode* createFieldAccessExpressionNode(struct ExpressionNode * object, char * membId);

/*! Создать узел доступа к методу-члену класса.
* \param[in] object объект, на котором вызывается операция доступа к члену.
* \param[in] membId идентификатор метода-члена класса.
* \param[in] paramList список параметров метода-члена класса.
* \return указатель на созданный узел доступа к члену класса.
*/
struct ExpressionNode* createMethodAccessExpressionNode(struct ExpressionNode * object, char * membId, struct ExpressionListNode * paramList);



/*------------------------------------ ExpressionList -------------------------------------*/

/*! Создать узел списка Expression.
* \param[in] firstChild указатель на первый элемент списка; для пустого списка - NULL.
* \return указатель на созданный экземпляр узла списка Expression.
*/
struct ExpressionListNode * createExpressionListNode(struct ExpressionNode * firstChild);

/*! Добавить ExpressionNode к списку Expression.
* \param[in,out] list список, к которому добавляется новый узел.
* \param[in] expression добавляемый узел Expression.
* \return измененный список Expression (тот же самый, что и параметр list). 
*/
struct ExpressionListNode * addExpressionToExpressionList(struct ExpressionListNode * list, struct ExpressionNode * expression);



/*------------------------------------ Statement -------------------------------------*/

/*! Создать узел StatementNode на основе узла ExpressionNode.
* \param[in] expr указатель на экземпляр ExpressionNode, на основе которого создается StatementNode.
* \return указатель на созданный экземпляр StatementNode.
*/
struct StatementNode * createStatementFromExpression(struct ExpressionNode * expr);

/*! Создать узел StatementNode для цикла while с одним Statement в качесвте тела.
* \param[in] cond Условие выполнения цикла - указатель на узел  Expression.
* \param[in] stmt Тело цикла, состоящее из одного узла Statement.
* \return Созданный узел Statement.
*/
struct StatementNode * createStatementFromWhileWithSingleBody(struct ExpressionNode * cond, struct StatementNode * stmt);

/*! Создать узел StatementNode для цикла while со списком Statement (BlockStatement) в качестве тела.
* \param[in] cond Условие выполнения цикла - указатель на узел  Expression.
* \param[in] stmtList Тело цикла, состоящее из узла StatementList.
* \return Созданный узел Statement.
*/
struct StatementNode * createStatementFromWhileWithComplexBody(struct ExpressionNode * cond, struct StatementListNode * stmtList);

/*! Создать пустой узел Statement.
* \return указатель на пустой узел Statement.
*/
struct StatementNode * createEmptyStatement();

/*! Создать узел Val Statement без явного указания типа.
* \param[in] valId идентификатор переменной.
* \param[in] expr выражение, результат которого присваивается Val; может быть NULL, если ничего не присаивается.
* \return созданный узел ValStmt.
*/
struct StatementNode * createValStatement(char * valId, struct ExpressionNode * expr);

/*! Создать узел Val Statement с явным указаением типа.
* \param[in] valId идентификатор переменной.
* \param[in] type тип переменной.
* \param[in] expr выражение, результат которого присваивается Val; может быть NULL, если ничего не присаивается.
* \return созданный узел ValStmt.
*/
struct StatementNode * createValStatementWithType(char * valId, char * type ,struct ExpressionNode * expr);


/*------------------------------------ StatementList -------------------------------------*/

/*! Создать узел списка Statement.
* \param[in] firstChild указатель на первый элемент списка; для пустого списка - NULL.
* \return указатель на созданный экземпляр узла списка Statement.
*/
struct StatementListNode * createStatementListNode(struct StatementNode * firstChild);

/*! Добавить StatementNode к списку Statement.
* \param[in,out] list список, к которому добавляется новый узел.
* \param[in] statement добавляемый узел Statement.
* \return измененный список Statement (тот же самый, что и параметр list). 
*/
struct StatementListNode * addStatementToStatementList(struct StatementListNode * list, struct StatementNode * statement);
