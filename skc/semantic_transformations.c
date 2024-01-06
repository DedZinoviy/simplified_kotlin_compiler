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
* \return Возможная семантическая ошибка, связанная с модификаторами; NULL, если таковая отсуствует.
*/
static struct SemanticError * _checkModifierListsInKotlinFileElementList(struct KotlinFileElementListNode * elemList);

/*! [PRIVATE] Заполнить перечень модификаторов класса.
* \param[in, out] head заполняемый перечень модификаторов класса.
* \param[in] modList список модификаторов класса, по которому осуществляется заполнение.
* \return Возможная семантическая ошибка, связанная с модификаторами; NULL, если таковая отсуствует.
*/
static struct SemanticError * _fillModifierTableForClass(struct ModifierHead * head, struct ModifierListNode * modList);

/*! [PRIVATE] Добавить отметку о наличии модификатора в списке модификаторов класса в перечень модификаторов.
* \param[in,out] head изменяемый перечень модификаторов.
* \param[in] mod узел обозреваемого модификатора.
* \return Возможная семантическая ошибка, связанная с модификаторами; NULL, если таковая отсуствует.
*/
static struct SemanticError * _addModifierTableForClass(struct ModifierHead * head, struct ModifierNode * mod);

/*! [PRIVATE] Заполнить перечень модификаторов функции.
* \param[in, out] head заполняемый перечень модификаторов функции.
* \param[in] modList список модификаторов функции, по которому осуществляется заполнение.
* \return Возможная семантическая ошибка, связанная с модификаторами; NULL, если таковая отсуствует.
*/
static struct SemanticError * _fillModifierTableForFunction(struct ModifierHead * head, struct ModifierListNode * modList);

/*! [PRIVATE] Добавить отметку о наличии модификатора в списке модификаторов функции в перечень модификаторов.
* \param[in,out] head изменяемый перечень модификаторов.
* \param[in] mod узел обозреваемого модификатора.
* \return Возможная семантическая ошибка, связанная с модификаторами; NULL, если таковая отсуствует.
*/
static struct SemanticError * _addModifierTableForFunction(struct ModifierHead * head, struct ModifierNode * mod);

/*! [PRIVATE] Проверить модификаторы доступа в KotlinFileElement.
* \param[in,out] elem изменяемый узел KotlinFileElement.
* \return Возможная семантическая ошибка, связанная с модификаторами; NULL, если таковая отсуствует.
*/
static struct SemanticError * _checkModifierListsInKotlinFileElement(struct KotlinFileElementNode * elem);

/*! [PRIVATE] Проверить модификаторы доступа в классе Kotlin.
* \param[in,out] elem изменяемый узел класса Kotlin.
* \return Возможная семантическая ошибка, связанная с модификаторами; NULL, если таковая отсуствует.
*/
static struct SemanticError * _checkModifierListInClass(struct ClassNode * cls);

/*! [PRIVATE] Проверить модификаторы доступа в узле первичного коструктора.
* \param[in,out] elem изменяемый узел первичного конструктора.
* \return Возможная семантическая ошибка, связанная с модификаторами; NULL, если таковая отсуствует.
*/
static struct SementicError * _checkModifierListInPrimaryConstructor(struct PrimaryConstructorNode * constr);

/*! [PRIVATE] Заполнить перечень модификаторов метода.
* \param[in, out] head заполняемый перечень модификаторов метода.
* \param[in] modList список модификаторов метода, по которому осуществляется заполнение.
* \return Возможная семантическая ошибка, связанная с модификаторами; NULL, если таковая отсуствует.
*/
static struct SemanticError * _fillModifierTableForMethod(struct ModifierHead * head, struct ModifierListNode * modList);

/*! [PRIVATE] Добавить отметку о наличии модификатора в списке модификаторов метода в перечень модификаторов.
* \param[in,out] head изменяемый перечень модификаторов.
* \param[in] mod узел обозреваемого модификатора.
* \return Возможная семантическая ошибка, связанная с модификаторами; NULL, если таковая отсуствует.
*/
static struct SemanticError * _addModifierTableForMethod(struct ModifierHead * head, struct ModifierNode * mod);

/*! [PRIVATE] Заполнить перечень модификаторов первичного конструктора.
* \param[in, out] head заполняемый перечень модификаторов первичного конструктора.
* \param[in] modList список модификаторов первичного конструктора, по которому осуществляется заполнение.
* \return Возможная семантическая ошибка, связанная с модификаторами; NULL, если таковая отсуствует.
*/
static struct SemanticError * _fillModifierTableForPrimaryConstructor(struct ModifierHead * head, struct ModifierListNode * modList);

/*! [PRIVATE] Добавить отметку о наличии модификатора в списке модификаторов первичного конструктора в перечень модификаторов.
* \param[in,out] head изменяемый перечень модификаторов.
* \param[in] mod узел обозреваемого модификатора.
* \return Возможная семантическая ошибка, связанная с модификаторами; NULL, если таковая отсуствует.
*/
static struct SemanticError * _addModifierTableForPrimaryConstructor(struct ModifierHead * head, struct ModifierNode * mod);

static struct SemanticError * _checkModifierListsInKotlinFileElementList(struct KotlinFileElementListNode * elemList)
{
    if(elemList->first != NULL) // Проверить список модификаторов у первого элемента списка, если список не пустой.
    {
        return _checkModifierListsInKotlinFileElement(elemList->first);
    }
}

static struct SemanticError * _fillModifierTableForClass(struct ModifierHead * head, struct ModifierListNode * modList)
{
    if (modList->first != NULL)
    {
        return _addModifierTableForClass(head, modList->first);
    }
    return NULL;
}

static struct SemanticError * _addModifierTableForClass(struct ModifierHead * head, struct ModifierNode * mod)
{
    struct SemanticError * err = NULL; // Считать, что изначально ошибка не обнаружена.
    switch (mod->type)
    {
        case _PUBLIC:
            if (head->isPublic != 0) return createSemanticError(2, "The Public modifier has already been applied"); // Сообщить об ошибке, если уже имеется такой модификатор.
            else 
            {
                if (head->isInternal != 0 || head->isPrivate != 0) return createSemanticError(2, "The Incompatible visibility modifiers in class."); // Сообщить об ошибке, если имеются взаимоисключающие модификаторы.
                else head->isPublic = 1;
            }
            break;
        case _PRIVATE:
            if (head->isPrivate != 0) return createSemanticError(2, "The Private modifier has already been applied"); // Сообщить об ошибке, если уже имеется такой модификатор.
            else 
            {
                if (head->isInternal != 0 || head->isPublic != 0) return createSemanticError(2, "The Incompatible visibility modifiers in class."); // Сообщить об ошибке, если имеются взаимоисключающие модификаторы.
                else head->isPrivate = 1;
            }
            break;
        case _PROTECTED:
            return createSemanticError(2, "The Protected modifier cannot be applied to a class."); // Сообщить об ошибке в связи с неприменимостью модификатора.
            break;
        case _INTERNAL:
            if (head->isInternal != 0) return createSemanticError(2, "The Internal modifier has already been applied"); // Сообщить об ошибке, если уже имеется такой модификатор.
            else 
            {
                if (head->isPrivate != 0 || head->isPublic != 0) return createSemanticError(2, "The Incompatible visibility modifiers in class."); // Сообщить об ошибке, если имеются взаимоисключающие модификаторы.
                else head->isInternal = 1;
            }
            break;
        case _OPEN:
            if (head->isOpen != 0) return createSemanticError(2, "The Open modifier has already been applied"); // Сообщить об ошибке, если уже имеется такой модификатор.
            else
            {
                if (head->isFinal != 0) return createSemanticError(2, "The Incompatible Open/Final modifiers in class."); // Сообщить об ошибке, если имеются взаимоиключающие модификаторы.
                else head->isOpen = 1; 
            }
            break;
        case _OVERRIDE:
            return createSemanticError(2, "The Override modifier cannot be applied to a class."); // Сообщить об ошибке в связи с неприменимостью модификатора.
            break;
        case _FINAL:
            if (head->isFinal != 0) return createSemanticError(2, "The Final modifier has already been applied"); // Сообщить об ошибке, если уже имеется такой модификатор.
            else
            {
                if (head->isOpen != 0) return createSemanticError(2, "The Incompatible Open/Final modifiers in class."); // Сообщить об ошибке, если имеются взаимоиключающие модификаторы.
                else head->isFinal = 1; 
            }
            break;
    }
    if (mod->next != NULL)
    {
        err = _addModifierTableForClass(head, mod->next);
    }
    return err;
}

static struct SemanticError * _fillModifierTableForFunction(struct ModifierHead * head, struct ModifierListNode * modList)
{
    if (modList->first != NULL)
    {
        return _addModifierTableForFunction(head, modList->first);
    }
    return NULL;
}

static struct SemanticError * _addModifierTableForFunction(struct ModifierHead * head, struct ModifierNode * mod)
{
    struct SemanticError * err = NULL;
    switch (mod->type)
    {
        case _PUBLIC:
            if (head->isPublic != 0) return createSemanticError(2, "The Public modifier has already been applied"); // Сообщить об ошибке, если уже имеется такой модификатор.
            else
            {
                if (head->isInternal != 0 || head->isPrivate != 0) return createSemanticError(2, "The Incompatible visibility modifiers in function."); // Сообщить об ошибке, если имеются взаимоисключающие модификаторы.
                else head->isPublic = 1;
            }
            break;
        case _PRIVATE:
            if (head->isPrivate != 0) return createSemanticError(2, "The Private modifier has already been applied"); // Сообщить об ошибке, если уже имеется такой модификатор.
            else
            {
                if (head->isInternal != 0 || head->isPublic != 0) return createSemanticError(2, "The Incompatible visibility modifiers in function."); // Сообщить об ошибке, если имеются взаимоисключающие модификаторы.
                else head->isPrivate = 1;
            }
            break;
        case _PROTECTED:
            return createSemanticError(2, "Modifier Protected is not applicable to top level functions."); // Сообщить об ошибке в связи с неприменимостью модификатора.
            break;
        case _INTERNAL:
            if (head->isInternal != 0) return createSemanticError(2, "The Internal modifier has already been applied"); // Сообщить об ошибке, если уже имеется такой модификатор.
            else
            {
                if (head->isPublic != 0 || head->isPrivate != 0) return createSemanticError(2, "The Incompatible visibility modifiers in function."); // Сообщить об ошибке, если имеются взаимоисключающие модификаторы.
                else head->isInternal = 1;
            }
            break;
        case _OPEN:
            return createSemanticError(2, "Modifier Open is not applicable to top level functions."); // Сообщить об ошибке в связи с неприменимостью модификатора.
            break;
        case _OVERRIDE:
            return createSemanticError(2, "Modifier Override is not applicable to top level functions."); // Сообщить об ошибке в связи с неприменимостью модификатора.
            break;
        case _FINAL:
            return createSemanticError(2, "Modifier Final is not applicable to top level functions."); // Сообщить об ошибке в связи с неприменимостью модификатора.
            break;
    }
    if (mod->next != NULL) // Проверить следующий модификатор функции, если таковой имеется.
    {
        err = _addModifierTableForFunction(head, mod->next);
    }
    return err;
}

static struct SemanticError * _fillModifierTableForMethod(struct ModifierHead * head, struct ModifierListNode * modList)
{
    struct SemanticError * err = NULL;
    if (modList->first != NULL)
    {
        err = _addModifierTableForMethod(head, modList->first);
    }
    return err;
}

static struct SemanticError * _addModifierTableForMethod(struct ModifierHead * head, struct ModifierNode * mod)
{
    struct SemanticError * err = NULL; // Считать, что изначально ошибки не имеется.
    switch (mod->type) // По типу модификатора...
    {
        case _PRIVATE:
            if (head->isPrivate != 0) return createSemanticError(2, "The Private modifier has already been applied"); // Сообщить об ошибке, если уже имеется такой модификатор.
            else
            {
                if (head->isProtected != 0 || head->isPublic != 0 || head->isInternal != 0) return createSemanticError(2, "The Incompatible visibility modifiers in function."); // Сообщить об ошибке, если имеются взаимоисключающие модификаторы.
                else head->isPrivate = 1;
            }
            break;
        case _PUBLIC:
            if (head->isPublic != 0) return createSemanticError(2, "The Public modifier has already been applied"); // Сообщить об ошибке, если уже имеется такой модификатор.
            else
            {
                if (head->isProtected != 0 || head->isPrivate != 0 || head->isInternal != 0) return createSemanticError(2, "The Incompatible visibility modifiers in function."); // Сообщить об ошибке, если имеются взаимоисключающие модификаторы.
                else head->isPublic = 1;
            }
            break;
        case _PROTECTED:
            if (head->isProtected != 0) return createSemanticError(2, "The Protected modifier has already been applied"); // Сообщить об ошибке, если уже имеется такой модификатор.
            else
            {
                if (head->isPublic != 0 || head->isPrivate != 0 || head->isInternal != 0) return createSemanticError(2, "The Incompatible visibility modifiers in function."); // Сообщить об ошибке, если имеются взаимоисключающие модификаторы.
                else head->isProtected = 1;
            }
            break;
        case _INTERNAL:
            if (head->isInternal != 0) return createSemanticError(2, "The Internal modifier has already been applied"); // Сообщить об ошибке, если уже имеется такой модификатор.
            else
            {
                if (head->isProtected != 0 || head->isPrivate != 0 || head->isPublic != 0) return createSemanticError(2, "The Incompatible visibility modifiers in function."); // Сообщить об ошибке, если имеются взаимоисключающие модификаторы.
                else head->isInternal = 1;
            }
            break;
        case _OPEN:
            if (head->isOpen != 0) return createSemanticError(2, "The Open modifier has already been applied"); // Сообщить об ошибке, если уже имеется такой модификатор.
            else
            {
                if (head->isFinal != 0) return createSemanticError(2, "The Incompatible Open/Final modifiers in method."); // Сообщить об ошибке, если имеются взаимоиключающие модификаторы.
                else head->isOpen = 1;
            }
            break;
        case _FINAL:
            if (head->isFinal != 0) return createSemanticError(2, "The Final modifier has already been applied"); // Сообщить об ошибке, если уже имеется такой модификатор.
            else
            {
                if (head->isOpen != 0) return createSemanticError(2, "The Incompatible Open/Final modifiers in method."); // Сообщить об ошибке, если имеются взаимоиключающие модификаторы.
                else head->isFinal = 1;
            }
            break;
        case _OVERRIDE:
            if (head->isOverride != 0) return createSemanticError(2, "The Override modifier has already been applied"); // Сообщить об ошибке, если уже имеется такой модификатор.
            else head->isOverride = 1;
            break;
    }
    if (mod->next != NULL) // Проверить следующий модификатор, если таковой имеется.
    {
        err = _addModifierTableForMethod(head, mod->next);
    }
    return err;
}

static struct SemanticError * _fillModifierTableForPrimaryConstructor(struct ModifierHead * head, struct ModifierListNode * modList)
{
    struct SemanticError * err = NULL;
    if (modList->first != NULL)
    {
        err = _addModifierTableForPrimaryConstructor(head, modList->first);
    }
    return err;
}

static struct SemanticError * _addModifierTableForPrimaryConstructor(struct ModifierHead * head, struct ModifierNode * mod)
{
    struct SemanticError * err = NULL; // Считать, что изначально ошибка не обнаружена...
    switch (mod->type)
    {
        case _PRIVATE:
            if (head->isPrivate != 0) return createSemanticError(2, "The Private modifier has already been applied"); // Сообщить об ошибке, если уже имеется такой модификатор.
            else
            {
                if (head->isProtected != 0 || head->isPublic != 0 || head->isInternal != 0) return createSemanticError(2, "The Incompatible visibility modifiers in primary constructor."); // Сообщить об ошибке, если имеются взаимоисключающие модификаторы.
                else head->isPrivate = 1;
            }
            break;
        case _PUBLIC:
            if (head->isPublic != 0) return createSemanticError(2, "The Public modifier has already been applied"); // Сообщить об ошибке, если уже имеется такой модификатор.
            else
            {
                if (head->isProtected != 0 || head->isPrivate != 0 || head->isInternal != 0) return createSemanticError(2, "The Incompatible visibility modifiers in primary contructor."); // Сообщить об ошибке, если имеются взаимоисключающие модификаторы.
                else head->isPublic = 1;
            }
            break;
        case _PROTECTED:
            if (head->isProtected != 0) return createSemanticError(2, "The Protected modifier has already been applied"); // Сообщить об ошибке, если уже имеется такой модификатор.
            else
            {
                if (head->isPublic != 0 || head->isPrivate != 0 || head->isInternal != 0) return createSemanticError(2, "The Incompatible visibility modifiers in primary contructor."); // Сообщить об ошибке, если имеются взаимоисключающие модификаторы.
                else head->isProtected = 1;
            }
            break;
        case _INTERNAL:
            if (head->isInternal != 0) return createSemanticError(2, "The Internal modifier has already been applied"); // Сообщить об ошибке, если уже имеется такой модификатор.
            else
            {
                if (head->isProtected != 0 || head->isPrivate != 0 || head->isPublic != 0) return createSemanticError(2, "The Incompatible visibility modifiers in primary constructor."); // Сообщить об ошибке, если имеются взаимоисключающие модификаторы.
                else head->isInternal = 1;
            }
            break;
        case _OPEN:
            return createSemanticError(2, "Modifier Open is not applicable to primary constructors."); // Сообщить об ошибке в связи с неприменимостью модификатора.
            break;
        case _FINAL:
            return createSemanticError(2, "Modifier Final is not applicable to primary constructors."); // Сообщить об ошибке в связи с неприменимостью модификатора.
            break;
        case _OVERRIDE:
            return createSemanticError(2, "Modifier Override is not applicable to primary constructors."); // Сообщить об ошибке в связи с неприменимостью модификатора.
            break;
    }
    if (mod->next != NULL) // Проверить следующий модификатор, если таковой имеется.
    {
        err = _addModifierTableForPrimaryConstructor(head, mod->next);
    }
    return err;
}

static struct SemanticError * _checkModifierListsInKotlinFileElement(struct KotlinFileElementNode * elem)
{
    struct SemanticError * err = NULL; // Считать, что изначально ошибка модификаторов не обнаружена.
    if (elem->type == _CLASS) // Если элемент является классом...
    {
        // Создать список модификаторов, если таковой отсутствует.
        if (elem->modifiers == NULL)
        {
            elem->modifiers = createModifierListNode(createPublicModifierNode());
            elem->modifiers = addModifierToList(elem->modifiers, createFinalModifierNode());
        }
        else if (elem->modifiers->first == NULL) // Заполнить список модификаторов, если он пустой.
        {
            elem->modifiers = addModifierToList(elem->modifiers, createPublicModifierNode());
            elem->modifiers = addModifierToList(elem->modifiers, createFinalModifierNode());
        }
        else // Иначе.
        {
            struct ModifierHead * head = createEmptyModifierHead();
            err = _fillModifierTableForClass(head, elem->modifiers); // Заполнить перечень модификаторов.
            if (err != NULL) return err; // Сообщить об ошибке, если она возникла во время проверки (заполнения перечня).
            
            // Заполнить список модфикаторов, если отсутствует какой-либо из модификаторов.
            if (head->isFinal == 0 && head->isOpen == 0)
            {
                elem->modifiers = addModifierToList(elem->modifiers, createFinalModifierNode());
            }
            if (head->isInternal == 0 && head->isPublic == 0 && head->isPrivate == 0)
            {
                elem->modifiers = addModifierToList(elem->modifiers, createPublicModifierNode());
            }
        }
        err = _checkModifierListInClass(elem->clas);
    }
    else if (elem->type == _FUNCTION) // Иначе если элемент является функцией...
    {
        // Создать список модификаторов, если таковой отсутствует.
        if (elem->modifiers == NULL)
        {
            elem->modifiers = createModifierListNode(createPublicModifierNode());
        }
        else if (elem->modifiers->first == NULL) // Заполнить список модификаторов, если он пустой.
        {
            elem->modifiers = addModifierToList(elem->modifiers, createPublicModifierNode());
        }
        else // Иначе.
        {
            struct ModifierHead * head = createEmptyModifierHead();
            err = _fillModifierTableForFunction(head, elem->modifiers);
            if (err != NULL) return err; // Сообщить об ошибке, если она возникла во время проверки (заполнения перечня).
            // Заполнить список модификаторов, если отсутствует какой-либо из модификаторов.
            if (head->isPrivate == 0 && head->isPublic == 0 && head->isInternal == 0)
            {
                elem->modifiers = addModifierToList(elem->modifiers, createPublicModifierNode());
            }
        }
    }
    if (elem->next != NULL) // Проверить модификаторы доступа у следующего элемента, если таковой имеется.
    {
        err = _checkModifierListsInKotlinFileElement(elem->next);
    }

    return err;
}

static struct SemanticError * _checkModifierListInClass(struct ClassNode * cls)
{
    struct SemanticError * err = NULL; // Считать, что изначально ошибка отстуствует.
    if (cls->constr != NULL) // Проверить на ошибки модификаторов первичный конструктор, если таковой имеется.
    {
        err = _checkModifierListInPrimaryConstructor(cls->constr);
    }
    return err;
}

static struct SementicError * _checkModifierListInPrimaryConstructor(struct PrimaryConstructorNode * constr)
{
    struct SemanticError * err = NULL; // Считать, что изначально ошибка модификаторов не обнаружена.
    if (constr->mods == NULL)
    {
        constr->mods = createModifierListNode(createPublicModifierNode());
    }
    else if (constr->mods->first == NULL) // Заполнить список модификаторов, если он пустой.
    {
        constr->mods = addModifierToList(constr->mods, createPublicModifierNode());
    }
    else // Иначе.
    {
        struct ModifierHead * head = createEmptyModifierHead();
        err = _fillModifierTableForClass(head, constr->mods); // Заполнить перечень модификаторов.
        if (err != NULL) return err; // Сообщить об ошибке, если она возникла во время проверки (заполнения перечня).
         
        // Заполнить список модфикаторов, если отсутствует какой-либо из модификаторов.
        if (head->isInternal == 0 && head->isPublic == 0 && head->isPrivate == 0 && head->isProtected == 0)
        {
            constr->mods = addModifierToList(constr->mods, createPublicModifierNode());
        }
    }
    return err;
}

/*! Проверить списки модификаторов на наличие взаимоиключающих модификаторов. Проверить применяемые модификаторы и сущности на совместимость.
* \param[in,out] root дерево программы - указатель на узел KotlinFile.
*/
struct SemanticError * checkModifierLists(struct KotlinFileNode * root)
{
    if (root->elemList != NULL)
    {
        return _checkModifierListsInKotlinFileElementList(root->elemList);
    }
    return NULL;
}
