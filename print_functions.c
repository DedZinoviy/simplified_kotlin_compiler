#include <stdlib.h>
#include "nodes.h"

char* generateStrForBinOperation(struct ExpressionNode* node);
char* concat(char* firstStr, char* secStr);

/*! Сгегнерировать строку в DOT-формате для дальнейшей визуализации для узла Expression.
\param[in] node Визуализироваемый узел.
\return Строка кода на языке DOT из узла Expression.
*/
char * generateDotFromExpression(struct ExpressionNode * node)
{
    char base[] = "";
    char* res = concat(base, itoa(node->id));
    switch (node->type)
    {
    case IDENTIFIER:
        res = concat(res, "[label=\"");
        res = concat(res, node->identifierString);
        res = concat(res, "\"];\n");
        break;
    case INT_LIT:
        res = concat(res, "[label=\"");
        res = concat(res, itoa(node->intValue));
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
    default:
        break;
    }
    return res;
}

/*! Сгегнерировать строку в DOT-формате для дальнейшей визуализации для узла ExpressionList.
\param[in] listNode Визуализироваемый узел.
\return Строка кода на языке DOT из узла ExpressionList.
*/
char * generateDotFromExpressionList(struct ExpressionListNode * listNode)
{
    return NULL;
}


/*! Сгегнерировать строку в DOT-формате для дальнейшей визуализации для узла Statement.
\param[in] stmt Визуализироваемый узел.
\return Строка кода на языке DOT из узла Statement.
*/
char * generateDotFromStatement(struct StatementNode * stmt)
{
    return NULL;
}

/*! Сгегнерировать строку в DOT-формате для дальнейшей визуализации для узла StatementList.
\param[in] stmtList Визуализироваемый узел.
\return Строка кода на языке DOT из узла StatementList.
*/
char * generateDotFromStatementList(struct StatementistNode * stmtList)
{
    return NULL;
}

/*! Динамичски склеить две строки и вернуть ссылку на новую строку.
\param[in] firstStr первая строка для склейки.
\param[in] secStr вторая строка для склейки.
\return Новая склеенная строка.
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
    char res[] = "";
    res = concat(res, generateDotFromExpression(node->left));
    res = concat(res, generateDotFromExpression(node->right));
    res = concat(res, itoa(node->id));
    res = concat(res, " -> ");
    res = concat(res, itoa(node->left->id));
    res = concat(res, "[label=\"left\"];\n");
    res = concat(res, itoa(node->id));
    res = concat(res, " -> ");
    res = concat(res, itoa(node->right->id));
    res = concat(res, "[label=\"right\"];\n");
    return res;
}
