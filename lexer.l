%option noyywrap
%option never-interactive

%x MULTILINE_COMMENT

DIGIT [0-9]

%{
    #include <stdio.h>
    #include <string.h>
%}

%%

%{
    char bufferString[4096]; // Массив символов - буфер для строковых выражений.
%}

%{
    /*! Удалить символ из строки по его индексу в ней.
    \param[in] str - исходная строка.
    \param[in] index - индекс удаляемого символа.
    \return - 0, если удалено успешно, 1 - если нет.
    */
    int removeCharFromStringByIndex(char * str; int index); 

    /*! Удалить из строки нижние подчеркивания.
    \param[in] str - исходная строка.
    */
    void removeUnderline(char* str);
    // Блок ключевых слов.
%}

as {printf("(%s) - KEY_WORD\n", yytext);}
as\? {printf("(%s) - KEY_WORD\n", yytext);}
break {printf("(%s) - KEY_WORD\n", yytext);}
class {printf("(%s) - KEY_WORD\n", yytext);}
continue {printf("(%s) - KEY_WORD\n", yytext);}
do 
else {printf("(%s) - KEY_WORD\n", yytext);}
for 
fun 
if {printf("(%s) - KEY_WORD\n", yytext);}
in {printf("(%s) - KEY_WORD\n", yytext);}
!in {printf("(%s) - KEY_WORD\n", yytext);}
interface {printf("(%s) - KEY_WORD\n", yytext);}
is {printf("(%s) - KEY_WORD\n", yytext);}
\!is {printf("(%s) - KEY_WORD\n", yytext);}
null {printf("(%s) - KEY_WORD\n", yytext);}
object {printf("(%s) - KEY_WORD\n", yytext);}
package {printf("(%s) - KEY_WORD\n", yytext);}
return
super {printf("(%s) - KEY_WORD\n", yytext);}
this {printf("(%s) - KEY_WORD\n", yytext);}
throw {printf("(%s) - KEY_WORD\n", yytext);}
try {printf("(%s) - KEY_WORD\n", yytext);}
typealias {printf("(%s) - KEY_WORD\n", yytext);}
val {printf("(%s) - KEY_WORD\n", yytext);}
var {printf("(%s) - KEY_WORD\n", yytext);}
when {printf("(%s) - KEY_WORD\n", yytext);}
while

true {printf("(%s) - KEY_WORD\n", yytext);}
false {printf("(%s) - KEY_WORD\n", yytext);}

\/\* {BEGIN(MULTILINE_COMMENT);}
<MULTILINE_COMMENT>[^*]+
<MULTILINE_COMMENT>"*"+[^*/] 
<MULTILINE_COMMENT>"*"+"/" {BEGIN(INITIAL);}

\/\/[^\n]*\n {bufferString[0] = 0; strcat(bufferString, yytext); printf("(%s) - COMMENT\n", bufferString);}

\+ {printf("(%s) - OPERATOR\n", yytext);}
\- {printf("(%s) - OPERATOR\n", yytext);}
\* {printf("(%s) - OPERATOR\n", yytext);}
\/ {printf("(%s) - OPERATOR\n", yytext);}
= {printf("(%s) - OPERATOR\n", yytext);}
>= {printf("(%s) - OPERATOR\n", yytext);}
<= {printf("(%s) - OPERATOR\n", yytext);}
> {printf("(%s) - OPERATOR\n", yytext);}
< {printf("(%s) - OPERATOR\n", yytext);}
!= {printf("(%s) - OPERATOR\n", yytext);}
== {printf("(%s) - OPERATOR\n", yytext);}
\% {printf("(%s) - OPERATOR\n", yytext);}
\/= {printf("(%s) - OPERATOR\n", yytext);}
\+= {printf("(%s) - OPERATOR\n", yytext);}
\*= {printf("(%s) - OPERATOR\n", yytext);}
\-= {printf("(%s) - OPERATOR\n", yytext);}
\%= {printf("(%s) - OPERATOR\n", yytext);}

\{ {printf("(%s) - BRACKET\n", yytext);}
\} {printf("(%s) - BRACKET\n", yytext);}
\[ {printf("(%s) - BRACKET\n", yytext);}
\] {printf("(%s) - BRACKET\n", yytext);}
\( {printf("(%s) - BRACKET\n", yytext);}
\) {printf("(%s) - BRACKET\n", yytext);}
\: {printf("(%s) - COLON\n", yytext);}
\; {printf("(%s) - SEMICOLON\n", yytext);}
\. {printf("(%s) - DOT\n", yytext);}
\, {printf("(%s) - COMMA\n", yytext);}

\+\+ {printf("(%s) - OPERATOR\n", yytext);}
\-\- {printf("(%s) - OPERATOR\n", yytext);}

=== {printf("(%s) - OPERATOR\n", yytext);}
\!== {printf("(%s) - OPERATOR\n", yytext);}

\!
\|\|
\&\&

\.\. {printf("(%s) - OPERATOR\n", yytext);}
\!\! {printf("(%s) - OPERATOR\n", yytext);}
\?\. {printf("(%s) - OPERATOR\n", yytext);}

\?\: {printf("(%s) - OPERATOR\n", yytext);}
\:\: {printf("(%s) - OPERATOR\n", yytext);}
\? {printf("(%s) - OPERATOR\n", yytext);}
\-\> {printf("(%s) - OPERATOR\n", yytext);}
\@ {printf("(%s) - OPERATOR\n", yytext);}

([1-9](_*[0-9]+)*)|0 {
    bufferString[0] = 0;
    strcat(bufferString, yytext);
    removeUnderline(bufferString);
    printf("(%d) - DECIMAL_INTEGER\n", atoi(bufferString));
}

%%

int removeCharFromStringByIndex(char * str; int index) 
{
    int length = strlen(str); // Вычислить длину строки.
    if (index >= length || index < 0) // Удалить символ, если индекс выходит за границу строки. 
    {
        return 1;
    }
    for (int i = index; i < length - 1; i++)
    str[i] = str[i + 1];

    return 0;
}

void removeUnderline(char* str)
{
    char* underline = strchr(str, '_');
    while (underline != NULL){
        underline = strchr(str, '_');
        int position = underline - str;
        removeCharFromStringByIndex(str, position);
    }
}
