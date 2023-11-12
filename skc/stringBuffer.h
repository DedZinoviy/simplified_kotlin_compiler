#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*! ��������� ��� ������� ������, ����������� ������� ������ � \0. */
struct stringBuffer
{
    char buffer[10240]; // ������ �������� �������.
    int length; // ����� �������.
};

/*! �������� ������ � ����� ���������� ������.
\param[in,out] buffer - ����������� ��������� ���������� �������.
\param[in] character - ������ ��� ����������
*/
void appendChar(struct stringBuffer* buffer, char character);

/*! �������� ������ � ����� ���������� �������.
\param[in,out] buffer - ����������� ��������� ���������� �������.
\param[in] string - ������ ��� ����������
*/
void appendChars(struct stringBuffer* buffer, char* string);

/*! ����������� ��������� ������.
\param[in,out] buffer - ��������������� ������.
*/
void printStringBuffer(struct stringBuffer* buffer);

/*! �������� ��������� ������.
\param[in,out] buffer - ��������� ������.
*/
void clearStringBuffer(struct stringBuffer* buffer);
