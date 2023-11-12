#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*! Структура для буффера строки, позволяющая хранить строки с \0. */
struct stringBuffer
{
    char buffer[10240]; // Массив символов буффера.
    int length; // Длина буффера.
};

/*! Добавить символ в конец строкового буфера.
\param[in,out] buffer - обновляемый экземпляр строкового буффера.
\param[in] character - символ для добавления
*/
void appendChar(struct stringBuffer* buffer, char character);

/*! Добавить строку в конец строкового буффера.
\param[in,out] buffer - обновляемый экземпляр строкового буффера.
\param[in] string - символ для добавления
*/
void appendChars(struct stringBuffer* buffer, char* string);

/*! Распечатать строковый буффер.
\param[in,out] buffer - распечатываемый буффер.
*/
void printStringBuffer(struct stringBuffer* buffer);

/*! Очистить строковый буффер.
\param[in,out] buffer - очищаемый буффер.
*/
void clearStringBuffer(struct stringBuffer* buffer);
