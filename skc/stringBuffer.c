#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stringBuffer.h"

/*! Добавить символ в конец строкового буфера.
* \param[in,out] buffer обновляемый экземпляр строкового буффера.
* \param[in] character символ для добавления.
*/
void appendChar(struct stringBuffer* buffer, char character)
{
    buffer->length++;
    *(buffer->buffer + buffer->length - 1) = character;
}

/*! Добавить строку в конец строкового буффера.
* \param[in,out] buffer обновляемый экземпляр строкового буффера.
* \param[in] string Си-строка - массив символов для добавления.
*/
void appendChars(struct stringBuffer* buffer, char* string)
{
    for (int i = 0; i < strlen(string); i++) // Для каждого символа добавляемой строки...
    {
        appendChar(buffer, string[i]); // Добавить символ в конец буффера.
    }
}

/*! Распечатать строковый буффер.
* \param[in,out] buffer распечатываемый буффер.
*/
void printStringBuffer(struct stringBuffer* buffer)
{
    for (int i = 0; i < buffer->length; i++) // Для каждого символа строкового буффера...
    {
        printf("%c", buffer->buffer[i]); // Распечатать строковый буффер.
    }
}

/*! Очистить строковый буффер.
* \param[in,out] buffer очищаемый буффер.
*/
void clearStringBuffer(struct stringBuffer* buffer)
{
    buffer->buffer[0] = 0;
    buffer->length = 0;
}
