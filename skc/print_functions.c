#include <stdlib.h>
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
    case IDENTIFIER:
        res = concat(res, "[label=\"");
        res = concat(res, node->identifierString);
        res = concat(res, "\"];\n");
        break;
    case INT_LIT:
        res = concat(res, "[label=\"");
        res = concat(res, itoa(node->intValue, idStr, 10));
        res = concat(res, "\"];\n");
        break;
    case BOOLEAN_LIT:
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
    case DOUBLE_LIT:
        res = concat(res, "[label=\"");
        double d = node->doubleValue;
        char dstr[20];
        sprintf(dstr, "%f", d);
        res = concat(res, dstr);
        res = concat(res, "\"];\n");
        break;
    case PLUS:
        res = concat(res, "[label=\"+\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case MINUS:
        res = concat(res, "[label=\"-\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case MUL:
        res = concat(res, "[label=\"*\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case DIV:
        res = concat(res, "[label=\"/\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case MOD:
        res = concat(res, "[label=\"%\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case LESS:
        res = concat(res, "[label=\"<\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case GREAT:
        res = concat(res, "[label=\">\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case EQUAL:
        res = concat(res, "[label=\"==\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case GREAT_EQUAL:
        res = concat(res, "[label=\">=\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case LESS_EQUAL:
        res = concat(res, "[label=\"<=\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case NOT_EQUAL:
        res = concat(res, "[label=\"!=\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case RANGE:
        res = concat(res, "[label=\"!=\"];\n");
        res = concat(res, generateStrForBinOperation(node));
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
    char* res = concat(res, "[label=\"ExprList\"];\n");
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
    case EXPRESSION:
        res = concat(res, "[label=\"stmt\"];\n");
        res = concat(res, generateDotFromExpression(stmt->expression));
        res = concat(res, itoa(stmt->id, strId, 10));
        res = concat(res, " -> ");
        res = concat(res, itoa(stmt->expression->id, strId, 10));
        res = concat(res, "[label=\"expr\"];\n");
        break;
    case DOWHILE:
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
    case WHILE:
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
    char* res = concat(res, "[label=\"StmtList\"];\n");
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
