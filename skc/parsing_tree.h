#pragma once
#include "nodes.h"

/// Ссылка на корневой узел программы.
struct KotlinFileNode * root;

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

/*! Создать узел Expression на основе литеральной символьной констаты.
* \param[in] value значение литеральной символьной константы.
* \return указатель на созданный экземпляр узла литеральной символьной константы.
*/
struct ExpressionNode* createCharLiteralExpressionNode(char value);

/*! Создать узел Expression на основе литеральной строковой констаты.
* \param[in] value значение литеральной строковой константы.
* \return указатель на созданный экземпляр узла литеральной строковой константы.
*/
struct ExpressionNode* createStringLiteralExpressionNode(struct stringBuffer * value);

/*! Создать узел оператора сложения (+).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла сложения.
*/
struct ExpressionNode * createPlusExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand);

/*! Создать узел оператора дизъюнкции (||).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла дизъюнкции.
*/
struct ExpressionNode * createDisjExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand);

/*! Создать узел оператора конъюнкции (&&).
* \param[in] leftOperand указатель на левый операнд - экземаляр ExpressionNode.
* \param[in] rightOperand указатель на правый операнд - экземаляр ExpressionNode.
* \return указатель на созданный экземпляр узла конъюнкции.
*/
struct ExpressionNode * createConjExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand);

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

/*! Создать узел оператора присваивания.
* \param[in] leftOperand указатель на левый операнд присваивания.
* \param[in] rightOperand указатель на правый операнд присваивания.
* \return указатель на созданный узел оператора присваивания.
*/
struct ExpressionNode * createAssignmentExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand);

/*! Создать узел оператора присваивания со сложением.
* \param[in] leftOperand указатель на левый операнд присваивания.
* \param[in] rightOperand указатель на правый операнд присваивания.
* \return указатель на созданный узел оператора присваивания со сложением.
*/
struct ExpressionNode * createPlusAssignmentExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand);

/*! Создать узел оператора присваивания с вычитанием.
* \param[in] leftOperand указатель на левый операнд присваивания.
* \param[in] rightOperand указатель на правый операнд присваивания.
* \return указатель на созданный узел оператора присваивания с вычитанием.
*/
struct ExpressionNode * createMinusAssignmentExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand);

/*! Создать узел оператора присваивания с умножением.
* \param[in] leftOperand указатель на левый операнд присваивания.
* \param[in] rightOperand указатель на правый операнд присваивания.
* \return указатель на созданный узел оператора присваивания с умножением.
*/
struct ExpressionNode * createMulAssignmentExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand);

/*! Создать узел оператора присваивания с делением.
* \param[in] leftOperand указатель на левый операнд присваивания.
* \param[in] rightOperand указатель на правый операнд присваивания.
* \return указатель на созданный узел оператора присваивания с делением.
*/
struct ExpressionNode * createDivAssignmentExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand);

/*! Создать узел оператора присваивания со взятием остатка.
* \param[in] leftOperand указатель на левый операнд присваивания.
* \param[in] rightOperand указатель на правый операнд присваивания.
* \return указатель на созданный узел оператора присваивания со взятием остатка.
*/
struct ExpressionNode * createModAssignmentExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand);

/*! Создать узел оператора круглых скобок.
* \param[in] innerExpression внутреннее выражение в круглых скобках.
* \return ссылка на узел оператора круглых скобок.
*/
struct ExpressionNode * createBracketExpressionNode(struct ExpressionNode * innerExpression);

/*! Создать узел выражения идентификатора.
* \param[in] ident строка идентификатора.
* \return указатель на узел Expression ID.
*/
struct ExpressionNode * createIDExpressionNode(char * ident);

/*! Создать узел указателя на рассматриваемый объект This.
* \return указатель на узел рассматриваемого объекта This.
*/
struct ExpressionNode * createThisExpressionNode();

/*! Создать узел указателя на объект родительского класса Super.
* \return указатель на узел объекта родительского класса Super.
*/
struct ExpressionNode * createSuperExpressionNode();

/*! Создать узел оператора создания диапазона.
* \param[in] leftOperand указатель на левый операнд.
* \param[in] rightOperand указатель на правый операнд.
* \return указатель на созданный узел оператора создания диапазона.
*/
struct ExpressionNode * createRangeExpressionNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand);

/*! Создать узел оператора префиксного инкремента.
* \param[in] value указатель на инкрементируемый Expression.
* \return указатель на узел оператора префиксного инкремента.
*/
struct ExpressionNode * createPrefIncrementExpressionNode(struct ExpressionNode * value);

/*! Создать узел оператора префиксного декремента.
* \param[in] value указатель на декрементируемый Expression.
* \return указатель на узел оператора префиксного декремента.
*/
struct ExpressionNode * createPrefDecrementExpressionNode(struct ExpressionNode * value);

/*! Создать узел оператора постфиксного инкремента.
* \param[in] value указатель на инкрементируемый Expression.
* \return указатель на узел оператора постфиксного инкремента.
*/
struct ExpressionNode * createPostIncrementExpressionNode(struct ExpressionNode * value);

/*! Создать узел оператора постфиксного декремента.
* \param[in] value указатель на инкрементируемый Expression.
* \return указатель на узел оператора постфиксного декремента.
*/
struct ExpressionNode * createPostDecrementExpressionNode(struct ExpressionNode * value);

/*! Создать узел оператора унарного плюса.
* \param[in] value указатель на опреанд.
* \return указатель на узел оператора унарного плюса.
*/
struct ExpressionNode * createUnaryPlusExpressionNode(struct ExpressionNode * value);

/*! Создать узел оператора унарного минуса.
* \param[in] value указатель на операнд.
* \return указатель на узел оператора унарного минуса.
*/
struct ExpressionNode * createUnaryMinusExpressionNode(struct ExpressionNode * value);

/*! Создать узел оператора логического отрицания.
* \param[in] value указатель на операнд.
* \return указатель на узел оператора логического отрицания.
*/
struct ExpressionNode * createNotExpressionNode(struct ExpressionNode * value);



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

/*! Создать узел StatementNode для цикла do..while с одним Statement в качесвте тела.
* \param[in] cond Условие выполнения цикла - указатель на узел  Expression.
* \param[in] stmt Тело цикла, состоящее из одного узла Statement.
* \return Созданный узел Statement.
*/
struct StatementNode * createStatementFromDoWhileWithSingleBody(struct ExpressionNode * cond, struct StatementNode * stmt);

/*! Создать узел StatementNode для цикла do..while со списком Statement (BlockStatement) в качестве тела.
* \param[in] cond Условие выполнения цикла - указатель на узел  Expression.
* \param[in] stmtList Тело цикла, состоящее из узла StatementList.
* \return Созданный узел Statement.
*/
struct StatementNode * createStatementFromDoWhileWithComplexBody(struct ExpressionNode * cond, struct StatementListNode * stmtList);

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

/*! Создать узел Val Statement с явным указаением типа через VarDeclaration.
* \param[in] decl узел объявления переменной.
* \param[in] expr выражение, результат которого присваивается Val; может быть NULL, если ничего не присаивается.
* \return созданный узел ValStmt.
*/
struct StatementNode * createValStatementFromVarDeclaration(struct VarDeclarationNode * decl, struct ExpressionNode * expr);

/*! Создать узел Var Statement без явного указания типа.
* \param[in] varId идентификатор переменной.
* \param[in] expr выражение, результат которого присваивается Var; может быть NULL, если ничего не присаивается.
* \return созданный узел VarStmt.
*/
struct StatementNode * createVarStatement(char * varId, struct ExpressionNode * expr);

/*! Создать узел Var Statement с явным указаением типа.
* \param[in] varId идентификатор переменной.
* \param[in] type тип переменной.
* \param[in] expr выражение, результат которого присваивается Var; может быть NULL, если ничего не присаивается.
* \return созданный узел VarStmt.
*/
struct StatementNode * createVarStatementWithType(char * varId, char * type ,struct ExpressionNode * expr);

/*! Создать узел Var Statement с явным указаением типа через VarDeclaration.
* \param[in] decl узел объявления переменной.
* \param[in] expr выражение, результат которого присваивается Var; может быть NULL, если ничего не присаивается.
* \return созданный узел VarStmt.
*/
struct StatementNode * createVarStatementFromVarDeclaration(struct VarDeclarationNode * decl, struct ExpressionNode * expr);

/*! Создать узел Statement на основе цикла FOR с простым телом.
* \param[in] list указатель на список переменных, работу по которым производит цикл FOR.
* \param[in] cond указатель на узел условия работы цикла FOR.
* \param[in] stmt Тело цикла, состоящее из одного узла Statement.
* \return указатель на созданный узел Statement цикла FOR.
*/
struct StatementNode * createForStatementWithSingleBody(struct VarDeclarationListNode * list, struct ExpressionNode * cond, struct StatementNode * stmt);

/*! Создать узел Statement на основе цикла FOR с простым телом.
* \param[in] varDeclList указатель на список переменных, работу по которым производит цикл FOR.
* \param[in] cond указатель на узел условия работы цикла FOR.
* \param[in] stmtList Тело цикла, состоящее из узла StatementList.
* \return указатель на созданный узел Statement цикла FOR.
*/
struct StatementNode * createForStatementWithComplexBody(struct VarDeclarationListNode * varDeclList, struct ExpressionNode * cond, struct StatementListNode * stmtList);

/*! Создать узел Statement для множественного объявления Val.
* \param[in] vals список объявлений переменных, для которых создается Val.
* \param[in] expr выражение, результат которого присваивается Val.
* \return указатель на созданный узел множественного объявления Val.
*/
struct StatementNode * createMultiDeclarationWithVal(struct VarDeclarationListNode * vals, struct ExpressionNode * expr);

/*! Создать узел Statement для множественного объявления Var.
* \param[in] vars список объявлений переменных, для которых создается Var.
* \param[in] expr выражение, результат которого присваивается Var.
* \return указатель на созданный узел множественного объявления Var.
*/
struct StatementNode * createMultiDeclarationWithVar(struct VarDeclarationListNode * vars, struct ExpressionNode * expr);



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



/*------------------------------------ VarDeclaration -------------------------------------*/

/*! Создать узел VarDeclaration на основе идентификатора и его типа.
* \param[in] ident строка - наименование идентификатора.
* \param[in] typ строка - тип идентификатора.
* \return указатель на узел VarDeclaration.
*/
struct VarDeclarationNode * createVarDeclarationNode(char * ident, char * typ);



/*------------------------------------ VarDeclarationList -------------------------------------*/

/*! Создать узел списка VarDeclaration на основе узла VarDeclaration.
* \param[in] firstNode указатель на первый узел списка.
* \return указатель на узел списка VarDeclarationList.
*/
struct VarDeclarationListNode * createVarDeclarationListNode(struct VarDeclarationNode * firstNode);

/*! Добавить VarDeclarationNode к списку VarDeclaration.
* \param[in,out] list список, к которому добавляется новый узел.
* \param[in] varDecl добавляемый узел VarDeclaration.
* \return измененный список VarDeclaration (тот же самый, что и параметр list). 
*/
struct VarDeclarationListNode * addVarDeclToVarDeclarationListNode(struct VarDeclarationListNode * list, struct VarDeclarationNode * varDecl);



/*------------------------------------ Function -------------------------------------*/

/*! Создать узел функции.
* \param[in] ident идентификатор (название) функции.
* \param[in] pars список параметров функции.
* \param[in] ret возвращаемое значение функции.
* \param[in] bod тело функции.
* \return Указатель на созданный узел функции.
*/
struct FunctionNode * createFunctionNode(char * ident, struct VarDeclarationListNode * pars, char * ret, struct StatementListNode * bod);



/*------------------------------------ Modifier -------------------------------------*/

/*! Создать узел модификатора PRIVATE.
* \return указатель на узел модификатора PRIVATE.
*/
struct ModifierNode * createPrivateModifierNode();

/*! Создать узел модификатора PUBLIC.
* \return указатель на узел модификатора PUBLIC.
*/
struct ModifierNode * createPublicModifierNode();

/*! Создать узел модификатора PROTECTED.
* \return указатель на узел модификатора PROTECTED.
*/
struct ModifierNode * createProtectedModifierNode();

/*! Создать узел модификатора INTERNAL.
* \return указатель на узел модификатора INTERNAL.
*/
struct ModifierNode * createInternalModifierNode();

/*! Создать узел модификатора OVERRIDE.
* \return указатель на узел модификатора OVERRIDE.
*/
struct ModifierNode * createOverrideModifierNode();

/*! Создать узел модификатора OPEN.
* \return указатель на узел модификатора OPEN.
*/
struct ModifierNode * createOpenModifierNode();



/*------------------------------------ ModifierList -------------------------------------*/

/*! Создать новый узел списка модификаторов на основе узла модификатора.
* \param[in] mod указатель на узел модификатора, на основе которого осздается список.
* \return Указатель на созданный узел списка модификаторов.
*/
struct ModifierListNode * createModifierListNode(struct ModifierNode * mod);

/*! Добавить узел модификатора к списку узлов модификаторов.
* \param[in] modList список узлов модификаторов, в который добавляется новый модификатор.
* \param[in] mod добавляемый узел модификатора.
* \return указатель на обновленный список.
*/
struct ModifierListNode * addModifierToList(struct ModifierListNode * modList, struct ModifierNode * mod);



/*------------------------------------ KotlinFileElement -------------------------------------*/

/*! Создать элемент файла Kotlin на основе функции.
* \param[in] modList список модификаторов элемента.
* \param[in] function функция, на основе которой создается элемент.
* \return указатель на экземпляр структуры-элемента Kotlin.
*/
struct KotlinFileElementNode * createElementFromFunction(struct ModifierListNode * modList, struct FunctionNode * function);

/*! Создать элемент файла Kotlin на основе класса.
* \param[in] modList список модификаторов элемента.
* \param[in] cls класс, на основе которого создается элемент.
* \return указатель на экземпляр структуры-элемента Kotlin.
*/
struct KotlinFileElementNode * createElementFromClass(struct ModifierListNode * modList, struct ClassNode * cls);

/*! Создать пустой элемент файла Kotlin.
* \return указатель на экземпляр структуры-элемента Kotlin.
*/
struct KotlinFileElementNode* createEmptyElement();


/*------------------------------------ KotlinFileElementList -------------------------------------*/

/*! Создать узел списка элементов файла Kotlin на основе элемента Kotlin.
* \param[in] elem элемент файла Kotlin, на основе которого создается список элементов Kotlin.
* \return указатель на список элементов файла Kotlin.
*/
struct KotlinFileElementListNode * createKotlinFileElementListNode(struct KotlinFileElementNode * elem);

/*! Добавить элемент файла Kotlin к списку элементов файла Kotlin.
* \param[in] elemList список элементов файла Kotlin, к которому добавляется новый элемент.
* \param[in] elem новый добавляемый элемет файла Kotlin.
* \return указатель на обновленный список элементов.
*/
struct KotlinFileElementListNode * addKotlinFileElementToList(struct KotlinFileElementListNode * elemList, struct KotlinFileElementNode * elem);



/*------------------------------------ KotlinFile -------------------------------------*/

/*! Создать корневой узел файла Kotlin на основе списка элементов файла.
* \param[in] elemList список элементов файла Kotlin, на основе которого создается файл Kotlin.
* \return указатель на корневой узел файла Kotlin.
*/
struct KotlinFileNode * createKotlinFileNode(struct KotlinFileElementListNode * elemList);



/*------------------------------------ Class Member -------------------------------------*/

/*! Создать узел пустого члена класса.
* \return указатель на узел пустого члена класса.
*/
struct ClassMemberNode * createEmptyClassMemberNode();

/*! Создать узел метода.
* \param[in] modList Указатель на узел списка модификаторов.
* \param[in] func Указатель на узел функции - определение метода.
* \return указатель на узел метода.
*/
struct ClassMemberNode * createMethodClassMemberNode(struct ModifierListNode * modList, struct FunctionNode * func);

/*! Создать узел поля класса.
* \param[in] modList Указатель на узел списка модификаторов.
* \param[in] stmt Указатель на узел объявления переменной.
* \return указатель на узел поля класса.
*/
struct ClassMemberNode * createFieldClassMemberNode(struct ModifierListNode * modList, struct StatementNode * stmt);

/*! Присвоить список модификаторов члену класса.
* \param[in] modList Указатель на присываиваемый узел списка модификаторов.
* \param[in] member Указатель на узел члена класса, которому требуется присвоить список модификаторов.
* \return Указатель на узел члена класса с присвоенным списком модификаторов.
*/
struct ClassMemberNode * assignModsToClassMember(struct ModifierListNode * modList, struct ClassMemberNode * member);



/*------------------------------------ Class Member List -------------------------------------*/

/*! Создать узел списка членов класса.
* \param[in] member Указатель на узел члена класса, на основе которого создается список.
* \return Указатель на созданный узел списка членов класса.
*/
struct ClassMemberListNode * createClassMemberListNode(struct ClassMemberNode * member);

/*! Добавить нового члена класса к списку членов класса.
* \param[in] memberList Указатель на узел списка членов класса, в который добавляется новый узел.
* \param[in] member Указатель на добавляемый узел члена класса.
* \return Указатель на изменный узел списка членов класса.
*/
struct ClassMemberListNode * addClassMemberToListNode(struct ClassMemberListNode * memberList, struct ClassMemberNode * member);



/*------------------------------------ Class Param -------------------------------------*/

/*! Создать узел параметра класса на основе узла объявления переменной.
* \param[in] varDecl указатель на узел объявления переменной, на основе которого создается параметр класса.
* \param[in] expression указатель на выражение, значение которого будет использоваться как параметр по умолчанию; в случае ненадобности передать NULL.
* \return указатель на узел параметра класса.
*/
struct ClassParamNode * createClassParamNodeFromVarDecl(struct VarDeclarationNode * varDecl, struct ExpressionNode * expression);

/*! Создать узел параметра класса на основе выражения переменной с целью дальнейшего преобразования в поле класса.
* \param[in] modList указатель на узел списка модификаторов, которые применятся к полю класса.
* \param[in] stmt указатель на узел выражения переменной VAL или VAR.
* \return указатель на узел параметра класса.
*/
struct ClassParamNode * createClassParamNodeFromVarValStmt(struct ModifierListNode * modList, struct StatementNode * stmt);



/*------------------------------------ Class Param List -------------------------------------*/

/*! Создать узел списка параметров класса на основе узла параметра класса.
* \param[in] param указатель на узел параметра класса, на основе которого создается список параметров.
* \return указатель на узел списка параметров класса.
*/
struct ClassParamListNode * createClassParamListNode(struct ClassParamNode * param);

/*! Добавить узел параметра класса к списку параметров класса.
* \param[in] paramList Указатель на узел списка параметров класса, в который добавляется новый узел.
* \param[in] param указатель на добавляемый узел параметра класса.
* \return указатель на измененный узел списка параметров класса.
*/
struct ClassParamListNode * addClassParamToListNode(struct ClassParamListNode * paramList, struct ClassParamNode * param);



/*------------------------------------ Primary Constructor -------------------------------------*/

/*! Создать узел первичного конструктора класса.
* \param[in] modList указатель на узел списка модификаторов для первичного конструктора.
* \param[in] paramList указатель на узел списка параметров класса, используемых первичным конструктором.
* \return указатель на узел первичного конструктора.
*/
struct PrimaryConstructorNode * createPrimaryConstructor(struct ModifierListNode * modList, struct ClassParamListNode * paramList);



/*------------------------------------ Class -------------------------------------*/

/*! Создать узел класса.
* \param[in] ident идентификатор класса.
* \param[in] constructor указатель на узел первичного конструктора класса.
* \param[in] memberList указатель на узел списка параметров класса; передать NULL в случае отсутствия тела класса.
* \param[in] parent указатель на выражение - родительский класс; в случае отсутсвия передать выражение идентификатора глобального суперкласса Any.
* \return указатель на созданный узел класса.
*/
struct ClassNode * createClassNode(char * ident, struct PrimaryConstructorNode * constructor, struct ClassMemberListNode * memberList, struct ExpressionNode * parent);
