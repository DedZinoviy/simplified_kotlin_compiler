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

/*! Получить строку в стиле Си (массив Char), окончанием которой будет является терминальный 0. Промежуточные терминальные 0 будут заменены на пробелы.
* \param[in] buffer Строковый буффер, который требуется перевести в Си-строку.
* \return Массив char - строка в Си-стиле.
*/
char * getSafeCString(struct stringBuffer* buffer)
{
    char * res = (char*)malloc((buffer->length + 1) * sizeof(char)); // Выделить память под создаваемую строку.
    for(int i = 0; i < buffer->length; i++) // Для каждого символа строкового буффера...
    {
        if (buffer->buffer[i] != 0) // Если символ не является терминальным нулем, добавить символ в результат.
        {
            res[i] = buffer->buffer[i];
        }
        else // Иначе заменить его на пробел.
        {
            res[i] = 32;
        }
    }
    res[buffer->length] = 0; // Завершить строку терминальным нулем.
    return res;
}
