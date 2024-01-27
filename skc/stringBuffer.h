#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief Структура для буффера строки, позволяющая хранить строки с \0. */
struct stringBuffer
{
    /// Массив символов буффера.
    char buffer[10240];
    
    /// Длина буффера.
    int length;
};

/*! Добавить символ в конец строкового буфера.
* \param[in,out] buffer обновляемый экземпляр строкового буффера.
* \param[in] character символ для добавления.
*/
void appendChar(struct stringBuffer* buffer, char character);

/*! Добавить строку в конец строкового буффера.
* \param[in,out] buffer обновляемый экземпляр строкового буффера.
* \param[in] string Си-строка - массив символов для добавления.
*/
void appendChars(struct stringBuffer* buffer, char* string);

/*! Распечатать строковый буффер.
* \param[in,out] buffer распечатываемый буффер.
*/
void printStringBuffer(struct stringBuffer* buffer);

/*! Очистить строковый буффер.
* \param[in,out] buffer очищаемый буффер.
*/
void clearStringBuffer(struct stringBuffer* buffer);

/*! Получить строку в стиле Си (массив Char), окончанием которой будет является терминальный 0. Промежуточные терминальные 0 будут заменены на пробелы.
* \param[in] buffer Строковый буффер, который требуется перевести в Си-строку.
* \return Массив char - строка в Си-стиле.
*/
char * getSafeCString(struct stringBuffer* buffer);

#ifdef __cplusplus
};
#endif
