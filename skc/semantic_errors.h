#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

/*! \brief Структура, соотвествующая ошибке семантического анализа. */
struct SemanticError
{
    /// Числовой код ошибки.
    int code;

    /// Сообщение об ошибке.
    char * errMessage;
};

/*! Породить сообщение о семантической ошибке.
* \param[in] code код семантической ошибки.
* \param[in] msg сообщение семантической ошибки.
* \return экземпляр семантической ошибки.
*/
struct SemanticError * createSemanticError(int code, const char * msg);

#ifdef __cplusplus
};
#endif
