#include "semantic_transformations.h"

/* ------------------------- void replaceLiteralsToObjects(struct KotlinFileNode * root) ------------------------- */

/*! [PRIVATE] Заменить узлы непосредственных литаралов на комбинацию из создания объекта и доступа к полю _value этого класса в Expression.
* \param[in,out] expression изменяемый узел Expression.
*/
static void _replaceLiteralsToObjectsInExpression(struct ExpressionNode * expression);

/*! [PRIVATE] Заменить узлы непосредственных литаралов на комбинацию из создания объекта и доступа к полю _value этого класса в ExpressionList.
* \param[in,out] expressionList изменяемый узел ExpressionList.
*/
static void _replaceLiteralsToObjectsInExpressionList(struct ExpressionListNode * expressionList);

/*! [PRIVATE] Заменить узлы непосредственных литаралов на комбинацию из создания объекта и доступа к полю _value этого класса в Statement.
* \param[in,out] statement изменяемый узел Statement.
*/
static void _replaceLiteralsToObjectsInStatement(struct StatementNode * statement);

/*! [PRIVATE] Заменить узлы непосредственных литаралов на комбинацию из создания объекта и доступа к полю _value этого класса в StatementList.
* \param[in,out] statementList изменяемый узел StatementList.
*/
static void _replaceLiteralsToObjectsInStatementList(struct StatementListNode * statementList);

/*! [PRIVATE] Заменить узлы непосредственных литаралов на комбинацию из создания объекта и доступа к полю _value этого класса в KotlinFileElementList.
* \param[in,out] elemList изменяемый узел KotlinFileElementList.
*/
static void _replaceLiteralsToObjectsInKotlinElementList(struct KotlinFileElementListNode * elemList);

/*! [PRIVATE] Заменить узлы непосредственных литаралов на комбинацию из создания объекта и доступа к полю _value этого класса в KotlinFileElement.
* \param[in,out] elem изменяемый узел KotlinFileElement.
*/
static void _replaceLiteralsToObjectsInKotlinElement(struct KotlinFileElementNode * elem);

/*! [PRIVATE] Заменить узлы непосредственных литаралов на комбинацию из создания объекта и доступа к полю _value этого класса в Function.
* \param[in,out] func изменяемый узел Function.
*/
static void _replaceLiteralsToObjectsInFunction(struct FunctionNode * func);

/*! [PRIVATE] Заменить узлы непосредственных литаралов на комбинацию из создания объекта и доступа к полю _value этого класса в Class.
* \param[in,out] cls изменяемый узел Class.
*/
static void _replaceLiteralsToObjectsInClass(struct ClassNode * clas);

/*! Заменить узлы непосредственных литералов на комбинацию из создания объекта и доступа к полю _value этого класса.
* \param[in,out] root дерево программы - указатель на узел KotlinFile.
*/
void replaceLiteralsToObjects(struct KotlinFileNode * root)
{
    _replaceLiteralsToObjectsInKotlinElementList(root->elemList); // Заменить все литералы на объекты в дочернем узле.
}

static void _replaceLiteralsToObjectsInExpression(struct ExpressionNode * expression)
{

}

static void _replaceLiteralsToObjectsInExpressionList(struct ExpressionListNode * expressionList)
{

}

static void _replaceLiteralsToObjectsInStatement(struct StatementNode * statement)
{
    if (statement->next != NULL) // Заменить литералы на объекты, если есть следующий Statement.
    {
        _replaceLiteralsToObjectsInStatement(statement->next);
    }
}

static void _replaceLiteralsToObjectsInStatementList(struct StatementListNode * statementList)
{
    if (statementList->first != NULL) // Заменить литералы на объекты в списке, если имеется хотя бы один Statement.
    {
        _replaceLiteralsToObjectsInStatement(statementList->first);
    }
}

static void _replaceLiteralsToObjectsInKotlinElementList(struct KotlinFileElementListNode * elemList)
{
    if (elemList->first != NULL) // Заменить литералы на объекты в списке, если в списке имеется хотя бы один элемент.
    {
        _replaceLiteralsToObjectsInKotlinElement(elemList->first);
    }
}

static void _replaceLiteralsToObjectsInKotlinElement(struct KotlinFileElementNode * elem)
{
    switch (elem->type) // Заменить литералы на объекты в зависимости от типа элемента.
    {
    case _FUNCTION:
        _replaceLiteralsToObjectsInFunction(elem->func);
        break;
    case _CLASS:
        _replaceLiteralsToObjectsInClass(elem->clas);
        break;
    case _EMPT:
        break;
    default:
        break;
    }
    if (elem->next != NULL) // Заменить литералы на объекты, если есть следующий элемент.
    {
        _replaceLiteralsToObjectsInKotlinElement(elem->next);
    }
}

static void _replaceLiteralsToObjectsInFunction(struct FunctionNode * func)
{
    if (func->body != NULL)
    {
        _replaceLiteralsToObjectsInStatementList(func->body);
    }
}

static void _replaceLiteralsToObjectsInClass(struct ClassNode * clas)
{

}



/* ------------------------- void replaceModifyingAssignments(struct KotlinFileNode * root) ------------------------- */

/*! Заменить узлы модифицирующих присваиваний на кобинацию из арифметиеской операции и присваивания.
* \param[in,out] root дерево программы - указатель на узел KotlinFile.
*/
void replaceModifyingAssignments(struct KotlinFileNode * root)
{
    
}



/* ------------------------- void checkModifierLists(struct KotlinFileNode * root) ------------------------- */

/*! Проверить списки модификаторов на наличие взаимоиключающих модификаторов. Проверить применяемые модификаторы и сущности на совместимость.
* \param[in,out] root дерево программы - указатель на узел KotlinFile.
*/
void checkModifierLists(struct KotlinFileNode * root)
{

}
