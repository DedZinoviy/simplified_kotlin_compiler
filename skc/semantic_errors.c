#include "semantic_errors.h"

/*! Породить сообщение о семантической ошибке.
* \param[in] code код семантической ошибки.
* \param[in] msg сообщение семантической ошибки.
* \return экземпляр семантической ошибки.
*/
struct SemanticError * createSemanticError(int code, const char * msg)
{
    struct SemanticError * err = (struct SemanticError *)malloc(sizeof(struct SemanticError));
    err->code = code;
    err->errMessage = msg;
    return err;
}
