#include <stdlib.h>
#include "nodes.h"

/*! Сгегнерировать строку в DOT-формате для дальнейшей визуализации для узла Expression.
\param[in] node Визуализироваемый узел.
\return Строка кода на языке DOT из узла Expression.
*/
char * generateDotFromExpression(struct ExpressionNode * node)
{
    return NULL;
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
