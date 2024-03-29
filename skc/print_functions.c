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
        res = concat(res, (char *)"[label=\"");
        res = concat(res, node->identifierString);
        res = concat(res, (char *)"\"];\n");
        break;
    case _INT_LIT:
        res = concat(res, (char *)"[label=\"");
        res = concat(res, itoa(node->intValue, idStr, 10));
        res = concat(res, (char *)"\"];\n");
        break;
    case _BOOLEAN_LIT:
        res = concat(res, (char *)"[label=\"");
        if (node->boolValue == 1) 
        {
            res = concat(res, (char *)"true");
        }
        else
        {
            res = concat(res, (char *)"false");
        }
        res = concat(res, (char *)"\"];\n");
        break;
    case _DOUBLE_LIT:
        res = concat(res, (char *)"[label=\"");
        double d = node->doubleValue;
        char dstr[20];
        sprintf(dstr, "%f", d);
        res = concat(res, dstr);
        res = concat(res, (char *)"\"];\n");
        break;
    case _STRING_LIT:
        res = concat(res, (char*)"[label=\"");
        res = concat(res, getSafeCString(node->stringValue->buffer));
        res = concat(res, (char *)"\"];\n");
        break;
    case _CHAR_LIT:
        res = concat(res, (char*)"[label=\"");
        char tmp[2];
        tmp[1] = 0;
        if (node->charValue != 0) tmp[0] = node->charValue;
        else tmp[0] = 32;
        res = concat(res, tmp);
        res = concat(res, (char *)"\"];\n");
        break;
    case _THIS:
        res = concat(res, (char *)"[label=\"THIS\"];\n");
        break;
    case _SUPER:
        res = concat(res, (char *)"[label=\"SUPER\"];\n");
        break;
    case _PLUS:
        res = concat(res, (char *)"[label=\"+\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _MINUS:
        res = concat(res, (char *)"[label=\"-\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _MUL:
        res = concat(res, (char *)"[label=\"*\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _DIV:
        res = concat(res, (char *)"[label=\"/\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _MOD:
        res = concat(res, (char *)"[label=\"%\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _LESS:
        res = concat(res, (char *)"[label=\"<\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _GREAT:
        res = concat(res, (char *)"[label=\">\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _EQUAL:
        res = concat(res, (char *)"[label=\"==\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _GREAT_EQUAL:
        res = concat(res, (char *)"[label=\">=\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _LESS_EQUAL:
        res = concat(res, (char *)"[label=\"<=\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _NOT_EQUAL:
        res = concat(res, (char *)"[label=\"!=\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _RANGE:
        res = concat(res, (char *)"[label=\"..\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _CONJUNCTION:
        res = concat(res, (char *)"[label=\"&&\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _DISJUNCTION:
        res = concat(res, (char *)"[label=\"||\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _ASSIGNMENT:
        res = concat(res, (char *)"[label=\"=\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _PLUS_ASSIGNMENT:
        res = concat(res, (char *)"[label=\"+=\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _MINUS_ASSIGNMENT:
        res = concat(res, (char *)"[label=\"-=\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _MUL_ASSIGNMENT:
        res = concat(res, (char *)"[label=\"*=\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _DIV_ASSIGNMENT:
        res = concat(res, (char *)"[label=\"/=\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _MOD_ASSIGNMENT:
        res = concat(res, (char *)"[label=\"%=\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _UNARY_PLUS:
        res = concat(res, (char *)"[label=\"U_+\"];\n");
        res = concat(res, generateDotFromExpression(node->right));
        res = concat(res, itoa(node->id, idStr, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->right->id, idStr, 10));
        res = concat(res, (char *)";\n");
        break;
    case _UNARY_MINUS:
        res = concat(res, (char *)"[label=\"U_-\"];\n");
        res = concat(res, generateDotFromExpression(node->right));
        res = concat(res, itoa(node->id, idStr, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->right->id, idStr, 10));
        res = concat(res, (char *)";\n");
        break;
    case _PREF_INCREMENT:
        res = concat(res, (char *)"[label=\"PREF_++\"];\n");
        res = concat(res, generateDotFromExpression(node->right));
        res = concat(res, itoa(node->id, idStr, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->right->id, idStr, 10));
        res = concat(res, (char *)";\n");
        break;
    case _PREF_DECREMENT:
        res = concat(res, (char *)"[label=\"PREF_--\"];\n");
        res = concat(res, generateDotFromExpression(node->right));
        res = concat(res, itoa(node->id, idStr, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->right->id, idStr, 10));
        res = concat(res, (char *)";\n");
        break;
    case _NOT:
        res = concat(res, (char *)"[label=\"!\"];\n");
        res = concat(res, generateDotFromExpression(node->right));
        res = concat(res, itoa(node->id, idStr, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->right->id, idStr, 10));
        res = concat(res, (char *)";\n");
        break;
    case _POST_INCREMENT:
        res = concat(res, (char *)"[label=\"POST_++\"];\n");
        res = concat(res, generateDotFromExpression(node->left));
        res = concat(res, itoa(node->id, idStr, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->left->id, idStr, 10));
        res = concat(res, (char *)";\n");
        break;
    case _POST_DECREMENT:
        res = concat(res, (char *)"[label=\"POST_--\"];\n");
        res = concat(res, generateDotFromExpression(node->left));
        res = concat(res, itoa(node->id, idStr, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->left->id, idStr, 10));
        res = concat(res, (char *)";\n");
        break;
    case _BRACKETS:
        res = concat(res, (char*)"[label=\"()\"];\n");
        res = concat(res, generateDotFromExpression(node->left));
        res = concat(res, itoa(node->id, idStr, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->left->id, idStr, 10));
        res = concat(res, (char *)"[label=\"inner\"];\n");
        break;
    case _FUNC_CALL:
        res = concat(res, (char*)"[label=\"invoke <name=");
        res = concat(res, node->identifierString);
        if (node->fromLit != _FROM_NONE)
        {
            double d;
            char tmp[2];
            res = concat(res, (char*)"> java_plain = ");
            switch (node->fromLit)
            {
                case _FROM_INT:
                    res = concat(res, itoa(node->intValue, idStr, 10));
                    break;
                case _FROM_DOUBLE:
                    d = node->doubleValue;
                    char dstr[20];
                    sprintf(dstr, "%f", d);
                    res = concat(res, dstr);
                    break;
                case _FROM_STRING:
                    res = concat(res, getSafeCString(node->stringValue->buffer));
                    break;
                case _FROM_BOOLEAN:
                    if (node->boolValue == 1) res = concat(res, (char*)"true");
                    else res = concat(res, (char*)"false");
                    break;
                case _FROM_CHAR:
                    tmp[1] = 0;
                    if (node->charValue != 0) tmp[0] = node->charValue;
                    else tmp[0] = 32;
                    res = concat(res, tmp);
                    break;
            }
        }
        res = concat(res, (char*)">\"];\n");
        if(node->params != NULL)
        {
            res = concat(res, generateDotFromExpressionList(node->params));
            res = concat(res, itoa(node->id, idStr, 10));
            res = concat(res, (char *)" -> ");
            res = concat(res, itoa(node->params->id, idStr, 10));
            res = concat(res, (char *)"[label=\"params\"];\n");
        }
        break;
    case _FIELD_ACCESS:
        res = concat(res, (char*)"[label=\"field_access <name=");
        res = concat(res, node->identifierString);
        res = concat(res, (char*)">\"];\n");
        res = concat(res, generateDotFromExpression(node->left));
        res = concat(res, itoa(node->id, idStr, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->left->id, idStr, 10));
        res = concat(res, (char *)"[label=\"object\"];\n");
        break;
    case _METHOD_ACCESS:
        res = concat(res, (char*)"[label=\"method_invoke <name=");
        res = concat(res, node->identifierString);
        res = concat(res, (char*)">\"];\n");
        res = concat(res, generateDotFromExpression(node->left));
        res = concat(res, itoa(node->id, idStr, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->left->id, idStr, 10));
        res = concat(res, (char *)"[label=\"object\"];\n");
        if(node->params != NULL)
        {
            res = concat(res, generateDotFromExpressionList(node->params));
            res = concat(res, itoa(node->id, idStr, 10));
            res = concat(res, (char *)" -> ");
            res = concat(res, itoa(node->params->id, idStr, 10));
            res = concat(res, (char *)"[label=\"params\"];\n");
        }
        break;
    case _ARRAY_ACCESS:
        res = concat(res, (char *)"[label=\"array_access\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    case _ARRAY_CREATION:
        res = concat(res, (char *)"[label=\"array_creation\"];\n");
        res = concat(res, generateStrForBinOperation(node));
        break;
    default:
        break;
    }
    if(node->next != NULL)
    {
        res = concat(res, generateDotFromExpression(node->next));
        res = concat(res, itoa(node->id, idStr, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->next->id, idStr, 10));
        res = concat(res, (char *)"[label=\"next\"];\n");
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
    res = concat(res, (char *)"[label=\"ExprList\"];\n");
    if (listNode->first != NULL)
    {
        res = concat(res, generateDotFromExpression(listNode->first));
        res = concat(res, itoa(listNode->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(listNode->first->id, strId, 10));
        res = concat(res, (char *)"[label=\"first\"];\n");
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
        res = concat(res, (char *)"[label=\"stmt\"];\n");
        res = concat(res, generateDotFromExpression(stmt->expression));
        res = concat(res, itoa(stmt->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(stmt->expression->id, strId, 10));
        res = concat(res, (char *)"[label=\"expr\"];\n");
        break;
    case _DOWHILE:
        res = concat(res, (char *)"[label=\"DO_WHILE\"];\n");
        res = concat(res, generateDotFromExpression(stmt->condition));
        res = concat(res, itoa(stmt->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(stmt->condition->id, strId, 10));
        res = concat(res, (char *)"[label = \"condition\"];\n");
        if (stmt->complexBody != NULL) 
        {
            res = concat(res, generateDotFromStatementList(stmt->complexBody));
            res = concat(res, itoa(stmt->id, strId, 10));
            res = concat(res, (char *)" -> ");
            res = concat(res, itoa(stmt->complexBody->id, strId, 10));
            res = concat(res, (char *)"[label = \"control_body\"];\n");
        }
        else if (stmt->singleBody != NULL)
        {
            res = concat(res, generateDotFromStatement(stmt->singleBody));
            res = concat(res, itoa(stmt->id, strId, 10));
            res = concat(res, (char *)" -> ");
            res = concat(res, itoa(stmt->singleBody->id, strId, 10));
            res = concat(res, (char *)"[label = \"control_body\"];\n");
        }
        break;
    case _WHILE:
        res = concat(res, (char *)"[label=\"WHILE\"];\n");
        res = concat(res, generateDotFromExpression(stmt->condition));
        res = concat(res, itoa(stmt->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(stmt->condition->id, strId, 10));
        res = concat(res, (char *)"[label = \"condition\"];\n");
        if (stmt->complexBody != NULL) 
        {
            res = concat(res, generateDotFromStatementList(stmt->complexBody));
            res = concat(res, itoa(stmt->id, strId, 10));
            res = concat(res, (char *)" -> ");
            res = concat(res, itoa(stmt->complexBody->id, strId, 10));
            res = concat(res, (char *)"[label = \"control_body\"];\n");
        }
        else if (stmt->singleBody != NULL)
        {
            res = concat(res, generateDotFromStatement(stmt->singleBody));
            res = concat(res, itoa(stmt->id, strId, 10));
            res = concat(res, (char *)" -> ");
            res = concat(res, itoa(stmt->singleBody->id, strId, 10));
            res = concat(res, (char *)"[label = \"control_body\"];\n");
        }
        break;
    case _FOR:
        res = concat(res, (char *)"[label=\"FOR\"];\n");
        res = concat(res, generateDotFromVarDeclarationList(stmt->varDeclList));
        res = concat(res, itoa(stmt->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(stmt->varDeclList->id, strId, 10));
        res = concat(res, (char *)"[label = \"vars\"];\n");

        res = concat(res, generateDotFromExpression(stmt->condition));
        res = concat(res, itoa(stmt->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(stmt->condition->id, strId, 10));
        res = concat(res, (char *)"[label = \"condition\"];\n");

        if (stmt->complexBody != NULL) 
        {
            res = concat(res, generateDotFromStatementList(stmt->complexBody));
            res = concat(res, itoa(stmt->id, strId, 10));
            res = concat(res, (char*)" -> ");
            res = concat(res, itoa(stmt->complexBody->id, strId, 10));
            res = concat(res, (char*)"[label = \"control_body\"];\n");
        }
        else if (stmt->singleBody != NULL)
        {
            res = concat(res, generateDotFromStatement(stmt->singleBody));
            res = concat(res, itoa(stmt->id, strId, 10));
            res = concat(res, (char *)" -> ");
            res = concat(res, itoa(stmt->singleBody->id, strId, 10));
            res = concat(res, (char *)"[label = \"control_body\"];\n");
        }
        break;
    case _EMPTY:
        res = concat(res, (char *)"[label=\"empty_stmt\"];\n");
        break;
    case _VAL:
        res = concat(res, (char *)"[label=\"VAL <ident=");
        res = concat(res, stmt->varValId);
        res = concat(res, (char *)">\"];\n");
        if (stmt->varValType != NULL)
        {
            res = concat(res, generateDotFromType(stmt->varValType));
            res = concat(res, itoa(stmt->id, strId, 10));
            res = concat(res, (char *)" -> ");
            res = concat(res, itoa(stmt->varValType->id, strId, 10));
            res = concat(res, (char *)"[label = \"type\"];\n");
        }
        if (stmt->expression != NULL)
        {
            res = concat(res, generateDotFromExpression(stmt->expression));
            res = concat(res, itoa(stmt->id, strId, 10));
            res = concat(res, (char *)" -> ");
            res = concat(res, itoa(stmt->expression->id, strId, 10));
            res = concat(res, (char *)"[label = \"expr\"];\n");
        }
        break;
    case _VAR:
        res = concat(res, (char *)"[label=\"VAR <ident=");
        res = concat(res, stmt->varValId);
        res = concat(res, (char *)">\"];\n");
        if (stmt->varValType != NULL)
        {
            res = concat(res, generateDotFromType(stmt->varValType));
            res = concat(res, itoa(stmt->id, strId, 10));
            res = concat(res, (char *)" -> ");
            res = concat(res, itoa(stmt->varValType->id, strId, 10));
            res = concat(res, (char *)"[label = \"type\"];\n");
        }
        if (stmt->expression != NULL)
        {
            res = concat(res, generateDotFromExpression(stmt->expression));
            res = concat(res, itoa(stmt->id, strId, 10));
            res = concat(res, (char *)" -> ");
            res = concat(res, itoa(stmt->expression->id, strId, 10));
            res = concat(res, (char *)"[label = \"expr\"];\n");
        }
        break;
    case _MULTI_VAL:
        res = concat(res, (char *)"[label=\"MULTI_VAL\"];\n");
        if (stmt->varDeclList != NULL)
        {
            res = concat(res, generateDotFromVarDeclarationList(stmt->varDeclList));
            res = concat(res, itoa(stmt->id, strId, 10));
            res = concat(res, (char *)" -> ");
            res = concat(res, itoa(stmt->varDeclList->id, strId, 10));
            res = concat(res, (char *)"[label = \"vals\"];\n");
        }
        if (stmt->expression != NULL)
        {
            res = concat(res, generateDotFromExpression(stmt->expression));
            res = concat(res, itoa(stmt->id, strId, 10));
            res = concat(res, (char *)" -> ");
            res = concat(res, itoa(stmt->expression->id, strId, 10));
            res = concat(res, (char *)"[label = \"expr\"];\n");
        }
        break;
    case _MULTI_VAR:
        res = concat(res, (char *)"[label=\"MULTI_VAR\"];\n");
                if (stmt->varDeclList != NULL)
        {
            res = concat(res, generateDotFromVarDeclarationList(stmt->varDeclList));
            res = concat(res, itoa(stmt->id, strId, 10));
            res = concat(res, (char *)" -> ");
            res = concat(res, itoa(stmt->varDeclList->id, strId, 10));
            res = concat(res, (char *)"[label = \"vars\"];\n");
        }
        if (stmt->expression != NULL)
        {
            res = concat(res, generateDotFromExpression(stmt->expression));
            res = concat(res, itoa(stmt->id, strId, 10));
            res = concat(res, (char *)" -> ");
            res = concat(res, itoa(stmt->expression->id, strId, 10));
            res = concat(res, (char *)"[label = \"expr\"];\n");
        }
        break;
    case _RETURN:
        res = concat(res, (char *)"[label=\"RETURN\"];\n");
        if (stmt->expression != NULL) 
        {
            res = concat(res, generateDotFromExpression(stmt->expression));
            res = concat(res, itoa(stmt->id, strId, 10));
            res = concat(res, (char *)" -> ");
            res = concat(res, itoa(stmt->expression->id, strId, 10));
            res = concat(res, (char *)"[label = \"expr\"];\n");
        }
        break;
    }
    if(stmt->next != NULL)
    {
        res = concat(res, generateDotFromStatement(stmt->next));
        res = concat(res, itoa(stmt->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(stmt->next->id, strId, 10));
        res = concat(res, (char *)"[label = \"next\"];\n");
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
    res = concat(res, (char *)"[label=\"StmtList\"];\n");
    if (stmtList->first != NULL)
    {
        res = concat(res, generateDotFromStatement(stmtList->first));
        res = concat(res, itoa(stmtList->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(stmtList->first->id, strId, 10));
        res = concat(res, (char *)"[label=\"first\"];\n");
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
    char * result = (char *)malloc((strlen(firstStr)  + strlen(secStr) + 1) * sizeof(char));
    result[0] = 0;
    strcpy(result, firstStr);
    strcat(result, secStr);
    return result;
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
    res = concat(res, (char *)" -> ");
    res = concat(res, itoa(node->left->id, strId, 10));
    res = concat(res, (char *)"[label=\"left\"];\n");
    res = concat(res, itoa(node->id, strId, 10));
    res = concat(res, (char *)" -> ");
    res = concat(res, itoa(node->right->id, strId, 10));
    res = concat(res, (char *)"[label=\"right\"];\n");
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
    res = concat(res, (char *)"[label=\"KotlinFile\"];\n");

    res = concat(res, generateDotFromKotlinFileElementList(node->elemList));

    res = concat(res, itoa(node->id, strId, 10));
    res = concat(res, (char *)" -> ");
    res = concat(res, itoa(node->elemList->id, strId, 10));
    res = concat(res, (char *)";\n");
    res = concat(res, (char *)"}");
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
    res = concat(res, (char *)"[label=\"KotlinFileElementList\"];\n");
    if (node->first != NULL)
    {
        res = concat(res, generateDotFromKotlinFileElement(node->first));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->first->id, strId, 10));
        res = concat(res, (char *)"[label=\"first\"];\n");
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
    if (node->type != _EMPT) res = concat(res, (char*)"[label=\"KotlinFileElement\"];\n");
    else res = concat(res, (char*)"[label=\"EmptyElement\"];\n");
    if(node->modifiers != NULL)
    {
        res = concat(res, generateDotFromModifierList(node->modifiers));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->modifiers->id, strId, 10));
        res = concat(res, (char *)"[label=\"modifiers\"];\n");
    }
    switch (node->type)
    {
    case _FUNCTION:
        res = concat(res, generateDotFromFunction(node->func));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->func->id, strId, 10));
        res = concat(res, (char *)"[label=\"function\"];\n");
        break;
    case _CLASS:
        res = concat(res, generateDotFromClass(node->clas));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->clas->id, strId, 10));
        res = concat(res, (char *)"[label=\"class\"];\n");
        break;
    case _EMPT:
        break;
    default:
        break;
    }
    
    if (node->next != NULL)
    {
        res = concat(res, generateDotFromKotlinFileElement(node->next));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->next->id, strId, 10));
        res = concat(res, (char *)"[label=\"next\"];\n");
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
            res = concat(res, (char *)"[label=\"PUBLIC\"];\n");
            break;
        case _PRIVATE:
            res = concat(res, (char *)"[label=\"PRIVATE\"];\n");
            break;
        case _PROTECTED:
            res = concat(res, (char *)"[label=\"PROTECTED\"];\n");
            break;
        case _INTERNAL:
            res = concat(res, (char *)"[label=\"INTERNAL\"];\n");
            break;
        case _OPEN:
            res = concat(res, (char *)"[label=\"OPEN\"];\n");
            break;
        case _OVERRIDE:
            res = concat(res, (char *)"[label=\"OVERRIDE\"];\n");
            break;
        case _FINAL:
            res = concat(res, (char *)"[label=\"FINAL\"];\n");
            break;
        default:
            break;
    }

    if (node->next != NULL)
    {
        res = concat(res, generateDotFromModifier(node->next));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->next->id, strId, 10));
        res = concat(res, (char *)"[label=\"next\"];\n");
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
    res = concat(res, (char *)"[label=\"ModifierList\"];\n");
    if (node->first != NULL)
    {
        res = concat(res, generateDotFromModifier(node->first));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->first->id, strId, 10));
        res = concat(res, (char *)"[label=\"first\"];\n");
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
    res = concat(res, (char *)"[label=\"Function <ident=");
    res = concat(res, node->identifier);
    res = concat(res, (char *)">\"];\n");
    if (node->returnValue != NULL) 
    {
        res = concat(res, generateDotFromType(node->returnValue));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->returnValue->id, strId, 10));
        res = concat(res, (char *)"[label=\"type\"];\n");
    }
    if (node->params != NULL) /*Список параметров.*/
    {
        res = concat(res, generateDotFromVarDeclarationList(node->params));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->params->id, strId, 10));
        res = concat(res, (char *)"[label=\"params\"];\n");
    }
    res = concat(res, generateDotFromStatementList(node->body));
    res = concat(res, itoa(node->id, strId, 10));
    res = concat(res, (char *)" -> ");
    res = concat(res, itoa(node->body->id, strId, 10));
    res = concat(res, (char *)"[label=\"body\"];\n");
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
    res = concat(res, (char *)"[label=\"VarDecl <ident=");
    res = concat(res, node->identifier);
    res = concat(res, (char *)">\"];\n");
    if (node->type != NULL)
    {
        res = concat(res, generateDotFromType(node->type));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->type->id, strId, 10));
        res = concat(res, (char *)"[label=\"type\"];\n");
    }
    if(node->next != NULL)
    {
        res = concat(res, generateDotFromVarDeclaration(node->next));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->next->id, strId, 10));
        res = concat(res, (char *)"[label=\"next\"];\n");
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
    res = concat(res, (char *)"[label=\"VarDeclList\"];\n");
    if(node->first != NULL)
    {
        res = concat(res, generateDotFromVarDeclaration(node->first));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->first->id, strId, 10));
        res = concat(res, (char *)"[label=\"first\"];\n");
    }
    return res;
}

/*! Сгенерировать DOT-строку для узла класса.
* \param[in] node Узел класса.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromClass(struct ClassNode * node)
{
    char base[] = "";
    char strId[10];
    char * res = concat(base, itoa(node->id, strId, 10));
    res = concat(res, (char *)"[label=\"Class <ident=");
    res = concat(res, node->identifier);
    res = concat(res, (char *)">\"];\n");

    if (node->base != NULL)
    {
        res = concat(res, generateDotFromExpression(node->base));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->base->id, strId, 10));
        res = concat(res, (char *)"[label=\"parent\"];\n");
    }

    if (node->members != NULL)
    {
        res = concat(res, generateDotFromClassMemberList(node->members));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->members->id, strId, 10));
        res = concat(res, (char *)"[label=\"members\"];\n");
    }
    
    if (node->constr != NULL)
    {
        res = concat(res, generateDotFromPrimaryConstructor(node->constr));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->constr->id, strId, 10));
        res = concat(res, (char *)"[label=\"prim constructor\"];\n");
    }

    return res;
}

/*! Сгенерировать DOT-строку для узла первичного конструктора.
* \param[in] node Узел первичного конструктора.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromPrimaryConstructor(struct PrimaryConstructorNode * node)
{
    char base[] = "";
    char strId[10];
    char * res = concat(base, itoa(node->id, strId, 10));
    res = concat(res, (char *)"[label=\"Primary Constructor\"];\n");
    
    if(node->mods != NULL)
    {
        res = concat(res, generateDotFromModifierList(node->mods));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->mods->id, strId, 10));
        res = concat(res, (char *)"[label=\"modifiers\"];\n");
    }

    if(node->params != NULL)
    {
        res = concat(res, generateDotFromClassParamList(node->params));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->params->id, strId, 10));
        res = concat(res, (char *)"[label=\"class parameters\"];\n");
    }

    return res;
}

/*! Сгенерировать DOT-строку для узла члена класса.
* \param[in] node Узел члена класса.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromClassMember(struct ClassMemberNode * node)
{
    char base[] = "";
    char strId[10];
    char * res = concat(base, itoa(node->id, strId, 10));
    
    switch (node->type)
    {
        case _C_EMPTY:
            res = concat(res, (char *)"[label=\"Empty Class Member\"];\n");
            break;
        case _FIELD:
            res = concat(res, (char *)"[label=\"Class Field Member\"];\n");
            res = concat(res, generateDotFromStatement(node->stmt));
            res = concat(res, itoa(node->id, strId, 10));
            res = concat(res, (char *)" -> ");
            res = concat(res, itoa(node->stmt->id, strId, 10));
            res = concat(res, (char *)"[label=\"field\"];\n");
            break;
        case _METHOD:
            res = concat(res, (char *)"[label=\"Class Method Member\"];\n");
            res = concat(res, generateDotFromFunction(node->method));
            res = concat(res, itoa(node->id, strId, 10));
            res = concat(res, (char *)" -> ");
            res = concat(res, itoa(node->method->id, strId, 10));
            res = concat(res, (char *)"[label=\"method\"];\n");
            break;
        default:
            break;
    }

    if(node->mods != NULL)
    {
        res = concat(res, generateDotFromModifierList(node->mods));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->mods->id, strId, 10));
        res = concat(res, (char *)"[label=\"modifiers\"];\n");
    }

    if(node->next != NULL)
    {
        res = concat(res, generateDotFromClassMember(node->next));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->next->id, strId, 10));
        res = concat(res, (char *)"[label=\"next\"];\n");
    }

    return res;
}

/*! Сгенерировать DOT-строку для узла списка членов класса.
* \param[in] node Узел списка членов класса.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromClassMemberList(struct ClassMemberListNode * node)
{
    char base[] = "";
    char strId[10];
    char * res = concat(base, itoa(node->id, strId, 10));
    res = concat(res, (char *)"[label=\"ClassMemberList\"];\n");
    if(node->first != NULL)
    {
        res = concat(res, generateDotFromClassMember(node->first));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->first->id, strId, 10));
        res = concat(res, (char *)"[label=\"first\"];\n");
    }
    return res;
}

/*! Сгенерировать DOT-строку для узла списка параметров класса.
* \param[in] node Узел списка параметров класса.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromClassParamList(struct ClassParamListNode * node)
{
    char base[] = "";
    char strId[10];
    char * res = concat(base, itoa(node->id, strId, 10));
    res = concat(res, (char *)"[label=\"ClassParamList\"];\n");
    if(node->first != NULL)
    {
        res = concat(res, generateDotFromClassParam(node->first));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->first->id, strId, 10));
        res = concat(res, (char *)"[label=\"first\"];\n");
    }
    return res;
}

/*! Сгенерировать DOT-строку для узла параметра класса.
* \param[in] node Узел параметра класса.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromClassParam(struct ClassParamNode * node)
{
    char base[] = "";
    char strId[10];
    char * res = concat(base, itoa(node->id, strId, 10));
    res = concat(res, (char *)"[label=\"ClassParam\"];\n");
    if(node->varDecl != NULL)
    {
        res = concat(res, generateDotFromVarDeclaration(node->varDecl));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->varDecl->id, strId, 10));
        res = concat(res, (char *)"[label=\"varDecl\"];\n");
        if(node->expr != NULL)
        {
            res = concat(res, generateDotFromExpression(node->expr));
            res = concat(res, itoa(node->id, strId, 10));
            res = concat(res, (char *)" -> ");
            res = concat(res, itoa(node->expr->id, strId, 10));
            res = concat(res, (char *)"[label=\"expression\"];\n");
        }
    }
    else if (node->valVar != NULL)
    {
        res = concat(res, generateDotFromStatement(node->valVar));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->valVar->id, strId, 10));
        res = concat(res, (char *)"[label=\"val|var\"];\n");
    }
    if(node->next != NULL)
    {
        res = concat(res, generateDotFromClassParam(node->next));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->next->id, strId, 10));
        res = concat(res, (char *)"[label=\"next\"];\n");
    }
    if (node->mods != NULL)
    {
        res = concat(res, generateDotFromModifierList(node->mods));
        res = concat(res, itoa(node->id, strId, 10));
        res = concat(res, (char *)" -> ");
        res = concat(res, itoa(node->mods->id, strId, 10));
        res = concat(res, (char *)"[label=\"modifiers\"];\n");
    }
    return res;
}

/*! Сгенерировать DOT-строку для узла типа данных.
* \param[in] node Узел типа данных.
* \return DOT-строка с дочерними узлами.
*/
char * generateDotFromType(struct TypeNode * node)
{
    char base[] = "";
    char strId[10];
    char * res = concat(base, itoa(node->id, strId, 10));
    switch (node->type)
    {
        case _CLS:
            if(node->ident != NULL) 
            {
                res = concat(res, (char *)"[label=\"Class_Type <ident = ");
                res = concat(res, node->ident);
                res = concat(res, ">\"];\n");
            }
            break;
        case _ARRAY:
            res = concat(res, (char *)"[label=\"Array_Type\"];\n");
            if (node->complexType != NULL)
            {
                res = concat(res, generateDotFromType(node->complexType));
                res = concat(res, itoa(node->id, strId, 10));
                res = concat(res, (char *)" -> ");
                res = concat(res, itoa(node->complexType->id, strId, 10));
                res = concat(res, (char *)"[label=\"nested_type\"];\n");
            }
            break;
    }

    return res;
}
