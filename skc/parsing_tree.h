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
struct ExpressionNode * createPlusAssignmentExpressioNode(struct ExpressionNode * leftOperand, struct ExpressionNode * rightOperand);

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
struct ModifierNode * createPrivateModiferNode();

/*! Создать узел модификатора PUBLIC.
* \return указатель на узел модификатора PUBLIC.
*/
struct ModifierNode * createPublicModiferNode();

/*! Создать узел модификатора PROTECTED.
* \return указатель на узел модификатора PROTECTED.
*/
struct ModifierNode * createProtectedeModiferNode();

/*! Создать узел модификатора INTERNAL.
* \return указатель на узел модификатора INTERNAL.
*/
struct ModifierNode * createInternalModiferNode();

/*! Создать узел модификатора OVERRIDE.
* \return указатель на узел модификатора OVERRIDE.
*/
struct ModifierNode * createOverrideModiferNode();

/*! Создать узел модификатора OPEN.
* \return указатель на узел модификатора OPEN.
*/
struct ModifierNode * createOpenModiferNode();



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
