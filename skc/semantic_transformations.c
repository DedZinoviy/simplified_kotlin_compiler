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

/*! [PRIVATE] Заменить узлы непосредственных литаралов на комбинацию из создания объекта и доступа к полю _value этого класса в Primary constructor.
* \param[in,out] constr изменяемый узел Primaru COnstructor.
*/
static void _replaceLiteralsToObjectsInPrimaryConstructor(struct PrimaryConstructorNode * constr);

/*! [PRIVATE] Заменить узлы непосредственных литаралов на комбинацию из создания объекта и доступа к полю _value этого класса в Param List.
* \param[in,out] paramList изменяемый узел Class Param List.
*/
static void _replaceLiteralsToObjectsInClassParamList(struct ClassParamListNode * paramList);

/*! [PRIVATE] Заменить узлы непосредственных литаралов на комбинацию из создания объекта и доступа к полю _value этого класса в Class Param.
* \param[in,out] classParam изменяемый узел ClassParam.
*/
static void _replaceLiteralsToObjectsInClassParam(struct ClassParamNode * classParam);

/*! [PRIVATE] Заменить узлы непосредственных литаралов на комбинацию из создания объекта и доступа к полю _value этого класса в Class Member List.
* \param[in,out] memberList изменяемый узел Class Member List.
*/
static void _replaceLiteralsToObjectsInClassMemberList(struct ClassMemberListNode * memberList);

/*! [PRIVATE] Заменить узлы непосредственных литаралов на комбинацию из создания объекта и доступа к полю _value этого класса в Class Member.
* \param[in,out] member изменяемый узел Class Member.
*/
static void _replaceLiteralsToObjectsInClassMember(struct ClassMemberNode * member);

/*! Заменить узлы непосредственных литералов на комбинацию из создания объекта и доступа к полю _value этого класса.
* \param[in,out] root дерево программы - указатель на узел KotlinFile.
*/
void replaceLiteralsToObjects(struct KotlinFileNode * root)
{
    _replaceLiteralsToObjectsInKotlinElementList(root->elemList); // Заменить все литералы на объекты в дочернем узле.
}

static void _replaceLiteralsToObjectsInExpression(struct ExpressionNode * expression)
{
    if ((expression->type == _FUNC_CALL || expression->type == _METHOD_ACCESS) && expression->params != NULL) _replaceLiteralsToObjectsInExpressionList(expression->params);

    if (expression->left != NULL) _replaceLiteralsToObjectsInExpression(expression->left);
    if (expression->right != NULL) _replaceLiteralsToObjectsInExpression(expression->right);

    if (expression->type == _INT_LIT)
    {
        expression->type = _FUNC_CALL;
        expression->identifierString = "Int";
        expression->fromLit = _FROM_INT;
        expression->params = NULL;
    }
    else if (expression->type == _DOUBLE_LIT) 
    {
        expression->type = _FUNC_CALL;
        expression->identifierString = "Double";
        expression->fromLit = _FROM_DOUBLE;
        expression->params = NULL;
    }
    else if (expression->type == _BOOLEAN_LIT) 
    {
        expression->type = _FUNC_CALL;
        expression->identifierString = "Boolean";
        expression->fromLit = _FROM_BOOLEAN;
        expression->params = NULL;
    }
    else if (expression->type == _CHAR_LIT) 
    {
        expression->type = _FUNC_CALL;
        expression->identifierString = "Char";
        expression->fromLit = _FROM_CHAR;
        expression->params = NULL;
    }
    else if (expression->type == _STRING_LIT) 
    {
        expression->type = _FUNC_CALL;
        expression->identifierString = "String";
        expression->fromLit = _FROM_STRING;
        expression->params = NULL;
    }

    if (expression->next != NULL) _replaceLiteralsToObjectsInExpression(expression->next);
}

static void _replaceLiteralsToObjectsInExpressionList(struct ExpressionListNode * expressionList)
{
    if (expressionList->first != NULL)
    {
        _replaceLiteralsToObjectsInExpression(expressionList->first);
    }
}

static void _replaceLiteralsToObjectsInStatement(struct StatementNode * statement)
{
    switch (statement->type)
    {
        case _EXPRESSION:
            _replaceLiteralsToObjectsInExpression(statement->expression);
            break;
        case _WHILE:
            if (statement->condition != NULL) _replaceLiteralsToObjectsInExpression(statement->condition);
            if (statement->singleBody != NULL) _replaceLiteralsToObjectsInStatement(statement->singleBody);
            if (statement->complexBody != NULL) _replaceLiteralsToObjectsInStatementList(statement->complexBody);
            break;
        case _DOWHILE:
            if (statement->condition != NULL) _replaceLiteralsToObjectsInExpression(statement->condition);
            if (statement->singleBody != NULL) _replaceLiteralsToObjectsInStatement(statement->singleBody);
            if (statement->complexBody != NULL) _replaceLiteralsToObjectsInStatementList(statement->complexBody);
            break;
        case _FOR:
            if (statement->condition != NULL) _replaceLiteralsToObjectsInExpression(statement->condition);
            if (statement->singleBody != NULL) _replaceLiteralsToObjectsInStatement(statement->singleBody);
            if (statement->complexBody != NULL) _replaceLiteralsToObjectsInStatementList(statement->complexBody);
            break;
        case _RETURN:
            if (statement->expression != NULL) _replaceLiteralsToObjectsInExpression(statement->expression);
            break;
        case _VAL:
            if (statement->expression != NULL) _replaceLiteralsToObjectsInExpression(statement->expression);
            break;
        case _VAR:
            if (statement->expression != NULL) _replaceLiteralsToObjectsInExpression(statement->expression);
            break;
        case _MULTI_VAL:
            if (statement->expression != NULL) _replaceLiteralsToObjectsInExpression(statement->expression);
            break;
        case _MULTI_VAR:
            if (statement->expression != NULL) _replaceLiteralsToObjectsInExpression(statement->expression);
            break;
        default: break;
    }
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
    if (clas->constr != NULL) {_replaceLiteralsToObjectsInPrimaryConstructor(clas->constr);}
    if (clas->base != NULL) {_replaceLiteralsToObjectsInExpression(clas->base);}
    if (clas->members != NULL) {_replaceLiteralsToObjectsInClassMemberList(clas->members);}
}

static void _replaceLiteralsToObjectsInPrimaryConstructor(struct PrimaryConstructorNode * constr)
{
    if(constr->params != NULL) _replaceLiteralsToObjectsInClassParamList(constr->params);
}

static void _replaceLiteralsToObjectsInClassParamList(struct ClassParamListNode * paramList)
{
    if (paramList->first != NULL) _replaceLiteralsToObjectsInClassParam(paramList->first);
}

static void _replaceLiteralsToObjectsInClassParam(struct ClassParamNode * classParam)
{
    if (classParam->expr != NULL) _replaceLiteralsToObjectsInExpression(classParam->expr);
    if (classParam->next != NULL) _replaceLiteralsToObjectsInClassParam(classParam->next);
}

static void _replaceLiteralsToObjectsInClassMemberList(struct ClassMemberListNode * memberList)
{
    if (memberList->first != NULL) _replaceLiteralsToObjectsInClassMember(memberList->first);
}

static void _replaceLiteralsToObjectsInClassMember(struct ClassMemberNode * member)
{
    switch (member->type)
    {
    case _METHOD:
        _replaceLiteralsToObjectsInFunction(member->method);
        break;
    case _FIELD:
        _replaceLiteralsToObjectsInStatement(member->stmt);
        break;
    default:
        break;
    }
    if (member->next != NULL) _replaceLiteralsToObjectsInClassMember(member->next);
}



/* ------------------------- void replaceModifyingAssignments(struct KotlinFileNode * root) ------------------------- */

/*! Заменить узлы модифицирующих присваиваний на кобинацию из арифметиеской операции и присваивания.
* \param[in,out] root дерево программы - указатель на узел KotlinFile.
*/
void replaceModifyingAssignments(struct KotlinFileNode * root)
{
    
}



/* ------------------------- void checkModifierLists(struct KotlinFileNode * root) ------------------------- */

/*! [PRIVATE] Проверить модификаторы доступа в KotlinFileElementList.
* \param[in,out] elemList изменяемый узел KotlinFileElementList.
*/
static void _checkModifierListsInKotlinFileElementList(struct KotlinFileElementListNode * elemList);

/*! [PRIVATE] Заполнить перечень модификаторов класса.
* \param[in, out] head заполняемый перечень модификаторов класса.
* \param[in] modList список модификаторов класса, по которому осуществляется заполнение.
*/
static void _fillModifierTableForClass(struct ModifierHead * head, struct ModifierListNode * modList);

/*! [PRIVATE] Добавить отметку о наличии модификатора в списке в перечень модификаторов.
* \param[in,out] head изменяемый перечень модификаторов.
* \param[in] mod узел обозреваемого модификатора.
*/
static void _addModifierTableForClass(struct ModifierHead * head, struct ModifierNode * mod);

/*! [PRIVATE] Проверить модификаторы доступа в KotlinFileElement.
* \param[in,out] elem изменяемый узел KotlinFileElement.
*/
static void _checkModifierListsInKotlinFileElement(struct KotlinFileElementNode * elem);

static void _checkModifierListsInKotlinFileElementList(struct KotlinFileElementListNode * elemList)
{
    if(elemList->first != NULL) // Проверить список модификаторов у первого элемента списка, если список не пустой.
    {
        _checkModifierListsInKotlinFileElement(elemList->first);
    }
}

static void _fillModifierTableForClass(struct ModifierHead * head, struct ModifierListNode * modList)
{
    if (modList->first != NULL)
    {
        _addModifierTableForClass(head, modList->first);
    }
}

static void _addModifierTableForClass(struct ModifierHead * head, struct ModifierNode * mod)
{
    switch (mod->type)
    {
        case _PUBLIC:
            if (head->isPublic != 0) return; // Сообщить об ошибке, если уже имеется такой модификатор.
            else 
            {
                if (head->isInternal != 0 || head->isPrivate != 0) return; // Сообщить об ошибке, если имеются взаимоисключающие присваивания.
                else head->isPublic = 1;
            }
            break;
        case _PRIVATE:
            if (head->isPrivate != 0) return; // Сообщить об ошибке, если уже имеется такой модификатор.
            else 
            {
                if (head->isInternal != 0 || head->isPublic != 0) return; // Сообщить об ошибке, если имеются взаимоисключающие присваивания.
                else head->isPrivate = 1;
            }
            break;
        case _PROTECTED:
            return; // Сообщить об ошибке в связи с неприменимостью модификатора.
            break;
        case _INTERNAL:
            if (head->isInternal != 0) return; // Сообщить об ошибке, если уже имеется такой модификатор.
            else 
            {
                if (head->isPrivate != 0 || head->isPublic != 0) return; // Сообщить об ошибке, если имеются взаимоисключающие присваивания.
                else head->isInternal = 1;
            }
            break;
        case _OPEN:
            break;
        case _OVERRIDE:
            return; // Сообщить об ошибке в связи с неприменимостью модификатора.
            break;
        case _FINAL:
            break;
    }
    if (mod->next != NULL)
    {
        _checkModifierInClass(head, mod->next);
    }
}

static void _checkModifierListsInKotlinFileElement(struct KotlinFileElementNode * elem)
{
    if (elem->type == _CLASS) // Если элемент является классом...
    {
        // Создать список модификаторов, если таковой отсутствует.
        if (elem->modifiers == NULL)
        {
            elem->modifiers = createModifierListNode(createPublicModifierNode());
        }
        // Заполнить список модфикаторов, если отсутствует какой-либо из модификаторов.
    }
    else if (elem->type == _FUNCTION) // Иначе если элемент является функцией...
    {
        // Создать список модификаторов, если таковой отсутствует.
        if (elem->modifiers == NULL)
        {
            elem->modifiers = createModifierListNode(createPublicModifierNode());
        }
        // Заполнить список модфикаторов, если отсутствует какой-либо из модификаторов.
    }
    if (elem->next != NULL) // Проверить модификаторы доступа у следующего элемента, если таковой имеется.
    {
        _checkModifierListsInKotlinFileElement(elem->next);
    }
}

/*! Проверить списки модификаторов на наличие взаимоиключающих модификаторов. Проверить применяемые модификаторы и сущности на совместимость.
* \param[in,out] root дерево программы - указатель на узел KotlinFile.
*/
void checkModifierLists(struct KotlinFileNode * root)
{
    if (root->elemList != NULL)
    {
        _checkModifierListsInKotlinFileElementList(root->elemList);
    }
}
