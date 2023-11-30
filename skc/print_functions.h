#pragma once
#include "nodes.h"


/*! Сгегнерировать строку в DOT-формате для дальнейшей визуализации для узла Expression.
* \param[in] node Визуализироваемый узел.
* \return Строка кода на языке DOT из узла Expression.
*/
char * generateDotFromExpression(struct ExpressionNode * node);

/*! Сгегнерировать строку в DOT-формате для дальнейшей визуализации для узла ExpressionList.
* \param[in] listNode Визуализироваемый узел.
* \return Строка кода на языке DOT из узла ExpressionList.
*/
char * generateDotFromExpressionList(struct ExpressionListNode * listNode);

/*! Сгегнерировать строку в DOT-формате для дальнейшей визуализации для узла Statement.
* \param[in] stmt Визуализироваемый узел.
* \return Строка кода на языке DOT из узла Statement.
*/
char * generateDotFromStatement(struct StatementNode * stmt);

/*! Сгегнерировать строку в DOT-формате для дальнейшей визуализации для узла StatementList.
* \param[in] stmtList Визуализироваемый узел.
* \return Строка кода на языке DOT из узла StatementList.
*/
char * generateDotFromStatementList(struct StatementListNode * stmtList);

/*! Динамичски склеить две строки и вернуть ссылку на новую строку.
* \param[in] firstStr первая строка для склейки.
* \param[in] secStr вторая строка для склейки.
* \return Новая склеенная строка.
*/
char * concat(char * firstStr, char * secStr);

/*! Сгенерировать DOT-строку для дочерних узллов Expression бинарной операции.
* \param[in] node узел, для дочерних узлов которого формируется DOT-строка.
* \return DOT-строка с дочерними узлами.
*/
char* generateStrForBinOperation(struct ExpressionNode* node);

/*! Сгенерировать DOT-строку для файла Kotlin. Строка будет содержать корневую структуру направленного графа digraph prg.
* \param[in] node Визуализироваемый узел.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromKotlinFile(struct KotlinFileNode * node);

/*! Сгенерировать DOT-строку для списка элементов файла Kotlin.
* \param[in] node Узел списка элементов файла Kotlin.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromKotlinFileElementList(struct KotlinFileElementListNode * node);

/*! Сгенерировать DOT-строку для элемента файла Kotlin.
* \param[in] node Узел элемента файла Kotlin.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromKotlinFileElement(struct KotlinFileElementNode * node);

/*! Сгенерировать DOT-строку для узла модификатора.
* \param[in] node Узел модификатора.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromModifier(struct ModifierNode * node);

/*! Сгенерировать DOT-строку для узла списка модификаторов.
* \param[in] node Узел списка модификаторов.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromModifierList(struct ModifierListNode * node);

/*! Сгенерировать DOT-строку для узла функции.
* \param[in] node Узел функции.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromFunction(struct FunctionNode * node);

/*! Сгенерировать DOT-строку для узла объявления переменной.
* \param[in] node Узел объявления переменной.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromVarDeclaration(struct VarDeclarationNode * node);

/*! Сгенерировать DOT-строку для узла списка объявлений переменной.
* \param[in] node Узел списка объявлений переменной.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromVarDeclarationList(struct VarDeclarationListNode * node);

/*! Сгенерировать DOT-строку для узла класса.
* \param[in] node Узел класса.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromClass(struct ClassNode * node);

/*! Сгенерировать DOT-строку для узла первичного конструктора.
* \param[in] node Узел первичного конструктора.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromPrimaryConstructor(struct PrimaryConstructorNode * node);

/*! Сгенерировать DOT-строку для узла члена класса.
* \param[in] node Узел члена класса.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromClassMember(struct ClassMemberNode * node);

/*! Сгенерировать DOT-строку для узла списка членов класса.
* \param[in] node Узел списка членов класса.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromClassMemberList(struct ClassMemberListNode * node);

/*! Сгенерировать DOT-строку для узла списка параметров класса.
* \param[in] node Узел списка параметров класса.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromClassParamList(struct ClassParamListNode * node);

/*! Сгенерировать DOT-строку для узла параметра класса.
* \param[in] node Узел параметра класса.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromClassParam(struct ClassParamNode * node);
