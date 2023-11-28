#include <stdlib.h>
#pragma warning(disable : 4996)
#include "print_functions.h"

/*! Сгегнерировать строку в DOT-формате для дальнейшей визуализации для узла Expression.
* \param[in] node Визуализироваемый узел.
* \return Строка кода на языке DOT из узла Expression.
*/
char * generateDotFromExpression(struct ExpressionNode * node)
{
    char base[] = "";
    char idStr[10];
    char* res = concat(base, itoa(node->id, idStr, 10));
    switch (node->type)
    {
    case _IDENTIFIER:
        res = concat(res, "[label=\"");
        res = concat(res, node->identifierString);
        res = concat(res, "\"];\n");
        break;
    case _INT_LIT:
        res = concat(res, "[label=\"");
        res = concat(res, itoa(node->intValue, idStr, 10));
        res = concat(res, "\"];\n");
        break;
    case _BOOLEAN_LIT:
        res = concat(res, "[label=\"");
        if (node->boolValue == 0) 
        {
            res = concat(res, "true");
        }
        else
        {
            res = concat(res, "false");
        }
        res = concat(res, "\"];\n");
        break;
    case _DOUBLE_LIT:
        res = concat(res, "[label=\"");
        double d = node->doubleValue;
        char dstr[20];
        sprintf(dstr, "%f", d);
        res = concat(res, dstr);
        res = concat(res, "\"];\n");
        break;
    case _PLUS:
        res = concat(res, "[label=\"+\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _MINUS:
        res = concat(res, "[label=\"-\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _MUL:
        res = concat(res, "[label=\"*\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _DIV:
        res = concat(res, "[label=\"/\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _MOD:
        res = concat(res, "[label=\"%\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _LESS:
        res = concat(res, "[label=\"<\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _GREAT:
        res = concat(res, "[label=\">\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _EQUAL:
        res = concat(res, "[label=\"==\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _GREAT_EQUAL:
        res = concat(res, "[label=\">=\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _LESS_EQUAL:
        res = concat(res, "[label=\"<=\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _NOT_EQUAL:
        res = concat(res, "[label=\"!=\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _RANGE:
        res = concat(res, "[label=\"..\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _UNARY_PLUS:
        res = concat(res, "[label=\"U_+\"];\n");
        res = concat(res, generateDotFromExpression(node->right));
        res = concat(res, itoa(node->id, idStr, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(node->right->id, idStr, 10));
        res = concat(res, ";\n");
        break;
    case _UNARY_MINUS:
        res = concat(res, "[label=\"U_-\"];\n");
        res = concat(res, generateDotFromExpression(node->right));
        res = concat(res, itoa(node->id, idStr, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(node->right->id, idStr, 10));
        res = concat(res, ";\n");
        break;
    case _PREF_INCREMENT:
        res = concat(res, "[label=\"PREF_++\"];\n");
        res = concat(res, generateDotFromExpression(node->right));
        res = concat(res, itoa(node->id, idStr, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(node->right->id, idStr, 10));
        res = concat(res, ";\n");
        break;
    case _PREF_DECREMENT:
        res = concat(res, "[label=\"PREF_--\"];\n");
        res = concat(res, generateDotFromExpression(node->right));
        res = concat(res, itoa(node->id, idStr, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(node->right->id, idStr, 10));
        res = concat(res, ";\n");
        break;
    case _POST_INCREMENT:
        res = concat(res, "[label=\"POST_++\"];\n");
        res = concat(res, generateDotFromExpression(node->right));
        res = concat(res, itoa(node->id, idStr, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(node->right->id, idStr, 10));
        res = concat(res, ";\n");
        break;
    case _POST_DECREMENT:
        res = concat(res, "[label=\"POST_--\"];\n");
        res = concat(res, generateDotFromExpression(node->right));
        res = concat(res, itoa(node->id, idStr, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(node->right->id, idStr, 10));
        res = concat(res, ";\n");
        break;
    default:
        break;
    }
    if(node->next != NULL)
    {
        res = concat(res, generateDotFromExpression(node->next));
        res = concat(res, itoa(node->id, idStr, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(node->next->id, idStr, 10));
        res = concat(res, "[label=\"next\"];\n");
    }
    return res;
}

/*! Сгегнерировать строку в DOT-формате для дальнейшей визуализации для узла ExpressionList.
* \param[in] listNode Визуализироваемый узел.
* \return Строка кода на языке DOT из узла ExpressionList.
*/
char * generateDotFromExpressionList(struct ExpressionListNode * listNode)
{
    char base[] = "";
    char strId[10];
    char* res = concat(base, itoa(listNode->id, strId, 10));
    res = concat(res, "[label=\"ExprList\"];\n");
    if (listNode->first != NULL)
    {
        res = concat(res, generateDotFromExpression(listNode->first));
        res = concat(res, itoa(listNode->id, strId, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(listNode->first->id, strId, 10));
        res = concat(res, "[label=\"first\"];\n");
    }
    return res;
}

/*! Сгегнерировать строку в DOT-формате для дальнейшей визуализации для узла Statement.
* \param[in] stmt Визуализироваемый узел.
* \return Строка кода на языке DOT из узла Statement.
*/
char * generateDotFromStatement(struct StatementNode * stmt)
{
    char base[] = "";
    char strId[10];
    char* res = concat(base, itoa(stmt->id, strId, 10));
    switch (stmt->type) {
    case _EXPRESSION:
        res = concat(res, "[label=\"stmt\"];\n");
        res = concat(res, generateDotFromExpression(stmt->expression));
        res = concat(res, itoa(stmt->id, strId, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(stmt->expression->id, strId, 10));
        res = concat(res, "[label=\"expr\"];\n");
        break;
    case _DOWHILE:
        res = concat(res, "[label=\"DO_WHILE\"];\n");
        res = concat(res, generateDotFromExpression(stmt->condition));
        res = concat(res, itoa(stmt->id, strId, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(stmt->condition->id, strId, 10));
        res = concat(res, "[label = \"condition\"];\n");
        if (stmt->complexBody != NULL) 
        {
            res = concat(res, generateDotFromStatementList(stmt->complexBody));
            res = concat(res, itoa(stmt->id, strId, 10));
            res = concat(res, " -> ");
            res = concat(res, itoa(stmt->complexBody->id, strId, 10));
            res = concat(res, "[label = \"control_body\"];\n");
        }
        else if (stmt->singleBody != NULL)
        {
            res = concat(res, generateDotFromStatement(stmt->singleBody));
            res = concat(res, itoa(stmt->id, strId, 10));
            res = concat(res, " -> ");
            res = concat(res, itoa(stmt->singleBody->id, strId, 10));
            res = concat(res, "[label = \"control_body\"];\n");
        }
        break;
    case _WHILE:
        res = concat(res, "[label=\"WHILE\"];\n");
        res = concat(res, generateDotFromExpression(stmt->condition));
        res = concat(res, itoa(stmt->id, strId, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(stmt->condition->id, strId, 10));
        res = concat(res, "[label = \"condition\"];\n");
        if (stmt->complexBody != NULL) 
        {
            res = concat(res, generateDotFromStatementList(stmt->complexBody));
            res = concat(res, itoa(stmt->id, strId, 10));
            res = concat(res, " -> ");
            res = concat(res, itoa(stmt->complexBody->id, strId, 10));
            res = concat(res, "[label = \"control_body\"];\n");
        }
        else if (stmt->singleBody != NULL)
        {
            res = concat(res, generateDotFromStatement(stmt->singleBody));
            res = concat(res, itoa(stmt->id, strId, 10));
            res = concat(res, " -> ");
            res = concat(res, itoa(stmt->singleBody->id, strId, 10));
            res = concat(res, "[label = \"control_body\"];\n");
        }
        break;
    case _FOR:
        res = concat(res, "[label=\"FOR\"];\n");
        res = concat(res, generateDotFromVarDeclarationList(stmt->varDeclList));
        res = concat(res, itoa(stmt->id, strId, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(stmt->varDeclList->id, strId, 10));
        res = concat(res, "[label = \"vars\"];\n");

        res = concat(res, generateDotFromExpression(stmt->condition));
        res = concat(res, itoa(stmt->id, strId, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(stmt->condition->id, strId, 10));
        res = concat(res, "[label = \"condition\"];\n");

        if (stmt->complexBody != NULL) 
        {
            res = concat(res, generateDotFromStatementList(stmt->complexBody));
            res = concat(res, itoa(stmt->id, strId, 10));
            res = concat(res, " -> ");
            res = concat(res, itoa(stmt->complexBody->id, strId, 10));
            res = concat(res, "[label = \"control_body\"];\n");
        }
        else if (stmt->singleBody != NULL)
        {
            res = concat(res, generateDotFromStatement(stmt->singleBody));
            res = concat(res, itoa(stmt->id, strId, 10));
            res = concat(res, " -> ");
            res = concat(res, itoa(stmt->singleBody->id, strId, 10));
            res = concat(res, "[label = \"control_body\"];\n");
        }
        break;
    case _EMPTY:
        res = concat(res, "[label=\"empty_stmt\"];\n");
        break;
    case _VAL:
        break;
    case _VAR:
        break;
    case _MULTI_VAL:
        break;
    case _MULTI_VAR:
        break;
    }
    if(stmt->next != NULL)
    {
        res = concat(res, generateDotFromStatement(stmt->next));
        res = concat(res, itoa(stmt->id, strId, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(stmt->next->id, strId, 10));
        res = concat(res, "[label = \"next\"];\n");
    }
    return res;
}

/*! Сгегнерировать строку в DOT-формате для дальнейшей визуализации для узла StatementList.
* \param[in] stmtList Визуализироваемый узел.
* \return Строка кода на языке DOT из узла StatementList.
*/
char * generateDotFromStatementList(struct StatementListNode * stmtList)
{  
    char base[] = "";
    char strId[10];
    char* res = concat(base, itoa(stmtList->id, strId, 10));
    res = concat(res, "[label=\"StmtList\"];\n");
    if (stmtList->first != NULL)
    {
        res = concat(res, generateDotFromStatement(stmtList->first));
        res = concat(res, itoa(stmtList->id, strId, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(stmtList->first->id, strId, 10));
        res = concat(res, "[label=\"first\"];\n");
    }
    return res;
}

/*! Динамичски склеить две строки и вернуть ссылку на новую строку.
* \param[in] firstStr первая строка для склейки.
* \param[in] secStr вторая строка для склейки.
* \return Новая склеенная строка.
*/
char * concat(char * firstStr, char * secStr)
{
    char * result = malloc((strlen(firstStr)  + strlen(secStr) + 1) * sizeof(char));
    strcpy(result, firstStr);
    strcat(result, secStr);
}

/*! Сгенерировать DOT-строку для дочерних узллов Expression бинарной операции.
* \param[in] node узел, для дочерних узлов которого формируется DOT-строка.
* \return DOT-строка с дочерними узлами.
*/
char* generateStrForBinOperation(struct ExpressionNode* node)
{
    char base[] = "";
    char strId[10];
    char * res = concat(base, generateDotFromExpression(node->left));
    res = concat(res, generateDotFromExpression(node->right));
    res = concat(res, itoa(node->id, strId, 10));
    res = concat(res, " -> ");
    res = concat(res, itoa(node->left->id, strId, 10));
    res = concat(res, "[label=\"left\"];\n");
    res = concat(res, itoa(node->id, strId, 10));
    res = concat(res, " -> ");
    res = concat(res, itoa(node->right->id, strId, 10));
    res = concat(res, "[label=\"right\"];\n");
    return res;
}

/*! Сгенерировать DOT-строку для файла Kotlin. трока будет содержать корневую структуру направленного графа digraph prg.
* \param[in] node Визуализироваемый узел.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromKotlinFile(struct KotlinFileNode * node)
{
    char base[] = "digraph prg {\n";
    char strId[10];
    char * res = concat(base, itoa(node->id, strId, 10));
    res = concat(res, "[label=\"KotlinFile\"];\n");

    res = concat(res, generateDotFromKotlinFileElementList(node->elemList));

    res = concat(res, itoa(node->id, strId, 10));
    res = concat(res, " -> ");
    res = concat(res, itoa(node->elemList->id, strId, 10));
    res = concat(res, ";\n");
    res = concat(res, '}');
    return res;
}

/*! Сгенерировать DOT-строку для списка элементов файла Kotlin.
* \param[in] node Узел списка элементов файла Kotlin.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromKotlinFileElementList(struct KotlinFileElementListNode * node)
{
    char base[] = "";
    char strId[10];
    char * res = concat(base, itoa(node->id, strId, 10));
    res = concat(res, "[label=\"KotlinFileElementList\"];\n");
    if (node->first != NULL)
    {
        res = concat(res, generateDotFromKotlinFileElement(node->first));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(node->first->id, strId, 10));
        res = concat(res, "[label=\"first\"];\n");
    }
    return res;
}

/*! Сгенерировать DOT-строку для элемена файла Kotlin.
* \param[in] node Узел элемента файла Kotlin.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromKotlinFileElement(struct KotlinFileElementNode * node)
{
    char base[] = "";
    char strId[10];
    char * res  = concat(base, itoa(node->id, strId, 10));
    if(node->modifiers != NULL)
    {
        res = concat(res, generateDotFromModifierList(node->modifiers));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(node->modifiers->id, strId, 10));
        res = concat(res, "[label=\"modifiers\"];\n");
    }
    switch (node->type)
    {
    case _FUNCTION:
        res = concat(res, generateDotFromFunction(node->func));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(node->func->id, strId, 10));
        res = concat(res, "[label=\"function\"];\n");
        break;
    case _CLASS:
        break;
    default:
        break;
    }
    
    if (node->next != NULL)
    {
        res = concat(res, generateDotFromKotlinFileElement(node->next));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(node->next->id, strId, 10));
        res = concat(res, "[label=\"next\"];\n");
    }
    return res;
}

/*! Сгенерировать DOT-строку для узла модификатора.
* \param[in] node Узел модификатора.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromModifier(struct ModifierNode * node)
{
    char base[] = "";
    char strId[10];
    char * res = concat(base, itoa(node->id, strId, 10));
    switch (node->type)
    {
        case _PUBLIC:
            res = concat(res, "[label=\"PUBLIC\"];\n");
            break;
        case _PRIVATE:
            res = concat(res, "[label=\"PRIVATE\"];\n");
            break;
        case _PROTECTED:
            res = concat(res, "[label=\"PROTECTED\"];\n");
            break;
        case _INTERNAL:
            res = concat(res, "[label=\"INTERNAL\"];\n");
            break;
        case _OPEN:
            res = concat(res, "[label=\"OPEN\"];\n");
            break;
        case _OVERRIDE:
            res = concat(res, "[label=\"OVERRIDE\"];\n");
            break;
        default:
            break;
    }

    if (node->next != NULL)
    {
        res = concat(res, generateDotFromModifier(node->next));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(node->next->id, strId, 10));
        res = concat(res, "[label=\"next\"];\n");
    }

    return res;
}

/*! Сгенерировать DOT-строку для узла списка модификаторов.
* \param[in] node Узел списка модификаторов.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromModifierList(struct ModifierListNode * node)
{
    char base[] = "";
    char strId[10];
    char * res = concat(base, itoa(node->id, strId, 10));
    res = concat(res, "[label=\"ModifierList\"];\n");
    if (node->first != NULL)
    {
        res = concat(res, generateDotFromModifier(node->first));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(node->first->id, strId, 10));
        res = concat(res, "[label=\"first\"];\n");
    }
    return res;
}

/*! Сгенерировать DOT-строку для узла функции.
* \param[in] node Узел функции.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromFunction(struct FunctionNode * node)
{
    char base[] = "";
    char strId[10];
    char * res = concat(base, itoa(node->id, strId, 10));
    res = concat(res, "[label=\"Function <ident=");
    res = concat(res, node->identifier);
    res = concat(res, "> <return ");
    res = concat(res, node->returnValue);
    res = concat(res, ">\"];\n");
    if (node->params != NULL) /*Список параметров.*/
    {
        res = concat(res, generateDotFromVarDeclarationList(node->params));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(node->params->id, strId, 10));
        res = concat(res, "[label=\"params\"];\n");
    }
    res = concat(res, generateDotFromStatementList(node->body));
    res = concat(res, itoa(node->id, strId, 10));
    res = concat(res, " -> ");
    res = concat(res, itoa(node->body->id, strId, 10));
    res = concat(res, "[label=\"body\"];\n");
    return res;
}

/*! Сгенерировать DOT-строку для узла объявления переменной.
* \param[in] node Узел объявления переменной.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromVarDeclaration(struct VarDeclarationNode * node)
{
    char base[] = "";
    char strId[10];
    char * res = concat(base, itoa(node->id, strId, 10));
    res = concat(res, "[label=\"VarDecl <ident=");
    res = concat(res, node->identifier);
    if (node->type != NULL)
    {
        res = concat(res, "> <type=");
        res = concat(res, node->type);
    }
    res = concat(res, ">];\n");
    if(node->next != NULL)
    {
        res = concat(res, generateDotFromVarDeclaration(node->next));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(node->next->id, strId, 10));
        res = concat(res, "[label=\"next\"];\n");
    }
    return res;
}

/*! Сгенерировать DOT-строку для узла списка объявлений переменной.
* \param[in] node Узел списка объявлений переменной.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromVarDeclarationList(struct VarDeclarationListNode * node)
{
    char base[] = "";
    char strId[10];
    char * res = concat(base, itoa(node->id, strId, 10));
    res = concat(res, "[label=\"VarDeclList\"];\n");
    if(node->first != NULL)
    {
        res = concat(res, generateDotFromVarDeclaration(node->first));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(node->first->id, strId, 10));
        res = concat(res, "[label=\"first\"];\n");
    }
    return res;
}
