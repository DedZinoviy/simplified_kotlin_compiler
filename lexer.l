%option noyywrap
%option never-interactive

%x MULTILINE_COMMENT
%x STRING
%x MULTILINE_STRING
%x HEX_INTEGER
%x CHAR

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

as {printf("(%s) - AS_KEY_WORD\n", yytext);}
as\? {printf("(%s) - AS?_KEY_WORD\n", yytext);}
break {printf("(%s) - BREAK_KEY_WORD\n", yytext);}
class {printf("(%s) - CLASS_KEY_WORD\n", yytext);}
continue {printf("(%s) - CONTINUE_KEY_WORD\n", yytext);}
do 
else {printf("(%s) - ELSE_KEY_WORD\n", yytext);}
for 
fun 
if {printf("(%s) - IF_KEY_WORD\n", yytext);}
in {printf("(%s) - IN_KEY_WORD\n", yytext);}
!in {printf("(%s) - !IN_KEY_WORD\n", yytext);}
interface {printf("(%s) - INTERFACE_KEY_WORD\n", yytext);}
is {printf("(%s) - IS_KEY_WORD\n", yytext);}
\!is {printf("(%s) - !IS_KEY_WORD\n", yytext);}
null {printf("(%s) - NULL_KEY_WORD\n", yytext);}
object {printf("(%s) - OBJECT_KEY_WORD\n", yytext);}
package {printf("(%s) - PACKAGE_KEY_WORD\n", yytext);}
return
super {printf("(%s) - SUPER_KEY_WORD\n", yytext);}
this {printf("(%s) - THIS_KEY_WORD\n", yytext);}
throw {printf("(%s) - THROW_KEY_WORD\n", yytext);}
try {printf("(%s) - TRY_KEY_WORD\n", yytext);}
typealias {printf("(%s) - TYPEALIAS_KEY_WORD\n", yytext);}
val {printf("(%s) - VAL_KEY_WORD\n", yytext);}
var {printf("(%s) - VAR_KEY_WORD\n", yytext);}
when {printf("(%s) - WHEN_KEY_WORD\n", yytext);}
while

true {printf("(%s) - TRUE_KEY_WORD\n", yytext);}
false {printf("(%s) - FALSE_KEY_WORD\n", yytext);}

\/\* {BEGIN(MULTILINE_COMMENT);}
<MULTILINE_COMMENT>[^*]+
<MULTILINE_COMMENT>"*"+[^*/] 
<MULTILINE_COMMENT>"*"+"/" {BEGIN(INITIAL);}

\/\/[^\n]*\n {bufferString[0] = 0; strcat(bufferString, yytext); printf("(%s) - COMMENT\n", bufferString);}

\+ {printf("(%s) - PLUS_OPERATOR\n", yytext);}
\- {printf("(%s) - MINUS_OPERATOR\n", yytext);}
\* {printf("(%s) - MUL_OPERATOR\n", yytext);}
\/ {printf("(%s) - DIV_OPERATOR\n", yytext);}
\= {printf("(%s) - ASSIGNMENT_OPERATOR\n", yytext);}
\>\= {printf("(%s) - GREATER_EQUAL_OPERATOR\n", yytext);}
\<\= {printf("(%s) - LESS_EQUAL_OPERATOR\n", yytext);}
\> {printf("(%s) - GREATER_OPERATOR\n", yytext);}
\< {printf("(%s) - LESS_OPERATOR\n", yytext);}
\!\= {printf("(%s) - NOT_EQUAL_OPERATOR\n", yytext);}
\=\= {printf("(%s) - EQUAL_OPERATOR\n", yytext);}
\% {printf("(%s) - MOD_OPERATOR\n", yytext);}
\/\= {printf("(%s) - DIV_ASSIGNMENT_OPERATOR\n", yytext);}
\+\= {printf("(%s) - PLUS_ASSIGNMENT_OPERATOR\n", yytext);}
\*\= {printf("(%s) - MUL_ASSIGNMENT_OPERATOR\n", yytext);}
\-\= {printf("(%s) - MINUS_ASSIGNMENT_OPERATOR\n", yytext);}
\%\= {printf("(%s) - MOD_ASSIGNMENT_OPERATOR\n", yytext);}

\{ {printf("(%s) - LEFT_BRACE\n", yytext);}
\} {printf("(%s) - RIGHT_BRACE\n", yytext);}
\[ {printf("(%s) - LEFT_SQUARE_BRACKET\n", yytext);}
\] {printf("(%s) - RIGHT_SQUARE_BRACKET\n", yytext);}
\( {printf("(%s) - LEFT_ROUND_BRACKET\n", yytext);}
\) {printf("(%s) - RIGHT_ROUND_BRACKET\n", yytext);}
\: {printf("(%s) - COLON\n", yytext);}
\; {printf("(%s) - SEMICOLON\n", yytext);}
\. {printf("(%s) - DOT\n", yytext);}
\, {printf("(%s) - COMMA\n", yytext);}

\+\+ {printf("(%s) - INCREMENT_OPERATOR\n", yytext);}
\-\- {printf("(%s) - DECREMENT_OPERATOR\n", yytext);}

\=\=\= {printf("(%s) - REF_EQUAL_OPERATOR\n", yytext);}
\!\=\= {printf("(%s) - REF_NOT_EQUAL_OPERATOR\n", yytext);}

\!
\|\|
\&\&

\.\. {printf("(%s) - RANGE_OPERATOR\n", yytext);}
\!\! {printf("(%s) - NOT_NULL_ASSERTION_OPERATOR\n", yytext);}
\?\. {printf("(%s) - SAFE_CALL_OPERATOR\n", yytext);}

\?\: {printf("(%s) - TERNAR_OPERATOR\n", yytext);}
\:\: {printf("(%s) - UNIT_REFERENCE_OPERATOR\n", yytext);}
\? {printf("(%s) - ALLOW_NULL_OPERATOR\n", yytext);}
\-\> {printf("(%s) - LAMBDA_OPERATOR\n", yytext);}
\@ {printf("(%s) - ANNOTATION_OPERATOR\n", yytext);}

[A-Za-z_][A-Za-z0-9_]* {printf("(%s) - IDENTIFIER\n", yytext);}

([1-9](_*[0-9]+)*)|0 {
    bufferString[0] = 0;
    strcat(bufferString, yytext);
    removeUnderline(bufferString);
    printf("(%d) - DECIMAL_INTEGER\n", atoi(bufferString));
}

\" {bufferString[0] = 0; BEGIN(STRING);}
<STRING>[^\\\"\$\n\r]+ {strcat(bufferString, yytext);}
<STRING>\$[A-Za-z_][A-Za-z0-9_]* {
    printf("(%s) - ESCAPED_STRING\n", bufferString);
    printf("(+) - PLUS_OPERATOR\n");
    printf("(%s) - IDENTIFIER\n", yytext + 1);
    printf("(+) - PLUS_OPERATOR\n");
    bufferString[0] = 0;
}
<STRING>\$[^A-Za-z_]* {strcat(bufferString, yytext);}
<STRING>[\n\r] {printf("ERROR: no closing \"\n"); BEGIN(INITIAL);}
<STRING>\" {printf("(%s) - ESCAPED STRING\n", bufferString); BEGIN(INITIAL);}
<STRING><<EOF>> {printf("ERROR: no closing \"\n"); BEGIN(INITIAL);}

\' {bufferString[0] = 0; BEGIN(CHAR);}
<STRING>[^\\\'\n\r] {strcat(bufferString, yytext);}
<STRING>[\n\r] {printf("ERROR: no closing  \'\n"); BEGIN(INITIAL);}
<CHAR>\' {
    int buffLen = strlen(bufferString);
    if(buffLen > 1)
    {
        printf("ERROR: Too many characters in character literal.\n");
    }
    else if (buffLen <= 0)
    {
        printf("ERROR: empty character literal.\n");
    }
    else
    {
        printf("%c - CHAR\n", bufferString[0]);
    }
    BEGIN(INITIAL);
}
<CHAR><<EOF>> {printf("ERROR: no closing \'\n"); BEGIN(INITIAL);}

<STRING,CHAR>\\n {strcat(bufferString, "\n");}
<STRING,CHAR>\\t {strcat(bufferString, "\t");}
<STRING,CHAR>\\b {strcat(bufferString, "\b");}
<STRING,CHAR>\\r {strcat(bufferString, "\r");}
<STRING,CHAR>\\\$ {strcat(bufferString, "$");}
<STRING,CHAR>\\\" {strcat(bufferString, "\"");}
<STRING,CHAR>\\\' {strcat(bufferString, "\'");}
<STRING,CHAR>\\\\ {strcat(bufferString, "\\");}

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
