%option noyywrap
%option never-interactive

%x END_OF_LINE_COMMENT
%x MULTILINE_COMMENT
%x STRING
%x MULTILINE_STRING
%x HEX_INTEGER
%x DECIMAL_INTEGER
%x CHAR

DIGIT [0-9]

%{
    #include <stdio.h>
    #include <string.h>
    #include "stringBuffer.c"
%}

%{
    /*! Удалить символ из строки по его индексу в ней.
    \param[in] str - исходная строка.
    \param[in] index - индекс удаляемого символа.
    \return - 0, если удалено успешно, 1 - если нет.
    */
    int removeCharFromStringByIndex(char * str, int index); 

    /*! Удалить из строки нижние подчеркивания.
    \param[in] str - исходная строка.
    */
    void removeUnderline(char* str);
    // Блок ключевых слов.
%}

%%

%{
    char bufferString[20480]; // Массив символов - буфер для строковых выражений.
    struct stringBuffer buff = {"", 0}; // Дополнительный буффер для строк.
    int line = 1;
%}

as {printf("(%s) - AS_KEY_WORD\n", yytext);}
as\? {printf("(%s) - AS?_KEY_WORD\n", yytext);}
break {printf("(%s) - BREAK_KEY_WORD\n", yytext);}
class {printf("(%s) - CLASS_KEY_WORD\n", yytext);}
continue {printf("(%s) - CONTINUE_KEY_WORD\n", yytext);}
do {printf("(%s) - DO_KEY_WORD\n", yytext);}
else {printf("(%s) - ELSE_KEY_WORD\n", yytext);}
for {printf("(%s) - FOR_KEY_WORD\n", yytext);}
fun {printf("(%s) - FUN_KEY_WORD\n", yytext);}
if {printf("(%s) - IF_KEY_WORD\n", yytext);}
in {printf("(%s) - IN_KEY_WORD\n", yytext);}
\!in {printf("(%s) - !IN_KEY_WORD\n", yytext);}
interface {printf("(%s) - INTERFACE_KEY_WORD\n", yytext);}
is {printf("(%s) - IS_KEY_WORD\n", yytext);}
\!is {printf("(%s) - !IS_KEY_WORD\n", yytext);}
null {printf("(%s) - NULL_KEY_WORD\n", yytext);}
object {printf("(%s) - OBJECT_KEY_WORD\n", yytext);}
package {printf("(%s) - PACKAGE_KEY_WORD\n", yytext);}
return {printf("(%s) - RETURN_KEY_WORD\n", yytext);}
super {printf("(%s) - SUPER_KEY_WORD\n", yytext);}
this {printf("(%s) - THIS_KEY_WORD\n", yytext);}
throw {printf("(%s) - THROW_KEY_WORD\n", yytext);}
try {printf("(%s) - TRY_KEY_WORD\n", yytext);}
typealias {printf("(%s) - TYPEALIAS_KEY_WORD\n", yytext);}
val {printf("(%s) - VAL_KEY_WORD\n", yytext);}
var {printf("(%s) - VAR_KEY_WORD\n", yytext);}
when {printf("(%s) - WHEN_KEY_WORD\n", yytext);}
while {printf("(%s) - WHILE_KEY_WORD\n", yytext);}

true {printf("(%s) - TRUE_KEY_WORD\n", yytext);}
false {printf("(%s) - FALSE_KEY_WORD\n", yytext);}

\/\* {bufferString[0] = 0; BEGIN(MULTILINE_COMMENT);}
<MULTILINE_COMMENT>[^*\n]+ {strcat(bufferString, yytext);}
<MULTILINE_COMMENT>[^*\n]*\n {line += 1; strcat(bufferString, yytext);}
<MULTILINE_COMMENT>"*"+\n {line += 1; strcat(bufferString, yytext);}
<MULTILINE_COMMENT>"*"+[^*/] {strcat(bufferString, yytext);}
<MULTILINE_COMMENT>"*"+"/" {printf("(%s) - MULTILINE_COMMENT\n", bufferString); BEGIN(INITIAL);}
<MULTILINE_COMMENT><<EOF>> {printf("ERROR: no closing */\n"); BEGIN(INITIAL);}

\/\/ {bufferString[0] = 0; BEGIN(END_OF_LINE_COMMENT);}
<END_OF_LINE_COMMENT>[^\n]* {strcat(bufferString, yytext);}
<END_OF_LINE_COMMENT>[\r\n] {printf("(%s) - END_OF_LINE_COMMENT\n", bufferString);  line += 1; BEGIN(INITIAL);}
<END_OF_LINE_COMMENT><<EOF>> {printf("(%s) - END_OF_LINE_COMMENT\n", bufferString); BEGIN(INITIAL);}

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

\! {printf("(%s) - NOT_OPERATOR\n", yytext);}
\|\| {printf("(%s) - OR_OPERATOR\n", yytext);} 
\&\& {printf("(%s) - AND_OPERATOR\n", yytext);}

\.\. {printf("(%s) - RANGE_OPERATOR\n", yytext);}
\!\! {printf("(%s) - NOT_NULL_ASSERTION_OPERATOR\n", yytext);}
\?\. {printf("(%s) - SAFE_CALL_OPERATOR\n", yytext);}

\?\: {printf("(%s) - ELVIS_OPERATOR\n", yytext);}
\:\: {printf("(%s) - UNIT_REFERENCE_OPERATOR\n", yytext);}
\? {printf("(%s) - ALLOW_NULL_OPERATOR\n", yytext);}
\-\> {printf("(%s) - LAMBDA_OPERATOR\n", yytext);}
\@ {printf("(%s) - ANNOTATION_OPERATOR\n", yytext);}

[A-Za-z_][A-Za-z0-9_]* {printf("(%s) - IDENTIFIER\n", yytext);}

[0-9]([_0-9])* { bufferString[0] = 0;
    BEGIN(DECIMAL_INTEGER);
    strcat(bufferString, yytext);
    int buffLen = strlen(bufferString);
    char lastChar = bufferString[buffLen - 1];
    if (lastChar == '_')
    {
        printf("ERROR: illegal using \"_\" in INT.\n");
    }
    else if (bufferString[0] == '0' && buffLen > 1)
    {
        printf("ERROR: illegal using zero in INT.\n");
    }
    else 
    {
        removeUnderline(bufferString);
        int res = atoi(bufferString);
        printf("(%d) - DECIMAL_INT\n", res);
    }
    BEGIN(INITIAL);
}

0x[_0-9a-fA-F]* { bufferString[0] = 0;
    BEGIN(HEX_INTEGER);
    strcat(bufferString, yytext);
    int buffLen = strlen(bufferString);
    char lastChar = bufferString[buffLen - 1];
    if (buffLen == 2) {
        printf("ERROR: missing hex int value.\n");
    }
    else if (lastChar == '_' || (buffLen > 2 && bufferString[2] == '_'))
    {
        printf("ERROR: illegal using \"_\" in INT.\n");
    }
    else
    {
        removeUnderline(bufferString);
        int result = strtol(bufferString + 2, NULL, 16);
        printf("(%d) - HEX_INT\n", result);
    }
    BEGIN(INITIAL);
}

0b[_0-1]* { bufferString[0] = 0;
    strcat(bufferString, yytext);
    int buffLen = strlen(bufferString);
    char lastChar = bufferString[buffLen - 1];
    if (buffLen == 2) {
        printf("ERROR: missing binary int value.\n");
    }
    else if (lastChar == '_' || (buffLen > 2 && bufferString[2] == '_'))
    {
        printf("ERROR: illegal using \"_\" in INT.\n");
    }
    else
    {
        removeUnderline(bufferString);
        int result = strtol(bufferString + 2, NULL, 2);
        printf("(%d) - BINARY_INT\n", result);
    }
}

({DIGIT}[_0-9]*)*\.({DIGIT}[_0-9]*)+ {
    bufferString[0] = 0;
    strcat(bufferString, yytext);
    int buffLen = strlen(bufferString);
    char * dot = strchr(bufferString, '.');
    char lastChar = bufferString[buffLen - 1];
    int position = dot - bufferString;
    if ((lastChar == '_') || (position != 0 && bufferString[position - 1] == '_')) 
    {
        printf("ERROR: illegal using \"_\" in DOUBLE.\n");
    }
    else
    {
        removeUnderline(bufferString);
        int resLen = strlen(bufferString);
        double result = atof(bufferString);
        printf("(%.*f) - DOUBLE", resLen, result);
    }
}

({DIGIT}[_0-9]*)*\.({DIGIT}[_0-9]*)+e[\+\-]?{DIGIT}+ {
    bufferString[0] = 0;
    strcat(bufferString, yytext);
    char* dot = strchr(bufferString, '.');
    char* e = strchr(bufferString, 'e');
    int positionDot = dot - bufferString;
    int positionE = e - bufferString;
    if ((positionDot != 0 && bufferString[positionDot - 1] == '_') || (bufferString[positionE - 1] == '_')) 
    {
        printf("ERROR: illegal using \"_\" in DOUBLE.\n");
    }
    else
    {
        removeUnderline(bufferString);
        double result = atof(bufferString);
        printf("(%e) - DOUBLE", result);
    }
}

\"\"\" {bufferString[0] = 0; BEGIN(MULTILINE_STRING);}
<MULTILINE_STRING>[^\$\"]+ {strcat(bufferString, yytext);}
<MULTILINE_STRING>\$[A-Za-z_][A-Za-z0-9_]* {
    printf("(%s) - MULTILINE_STRING\n", bufferString);
    printf("(+) - PLUS_OPERATOR\n");
    printf("(%s) - IDENTIFIER\n", yytext + 1);
    printf("(+) - PLUS_OPERATOR\n");
    bufferString[0] = 0;
}
<MULTILINE_STRING>\"{1,2} {strcat(bufferString, yytext);}
<MULTILINE_STRING>\"\"\" {printf("(%s) - MULTILINE STRING\n", bufferString); BEGIN(INITIAL);}
<MULTILINE_STRING><<EOF>> {printf("ERROR: no closing \"\"\"\n"); BEGIN(INITIAL);}

\" {bufferString[0] = 0; clearStringBuffer(&buff); BEGIN(STRING);}
<STRING>[^\\\"\$\n\r] {appendChar(&buff, yytext[0]);}
<STRING>\$[A-Za-z_][A-Za-z0-9_]* {
    printf("(");
    printBufferString(&buff);
    printf(") - ESCAPED_STRING\n");
    printf("(+) - PLUS_OPERATOR\n");
    printf("(%s) - IDENTIFIER\n", yytext + 1);
    printf("(+) - PLUS_OPERATOR\n");
    clearStringBuffer(&buff);
    bufferString[0] = 0;
}
<STRING>\$[^A-Za-z_]* {appendChars(&buff, yytext);}
<STRING>[\n\r] {printf("ERROR: no closing \"\n"); BEGIN(INITIAL);}
<STRING>\" { 
    printf("(");
    printBufferString(&buff);
    printf(") - ESCAPED STRING\n"); 
    BEGIN(INITIAL);
}
<STRING><<EOF>> {printf("ERROR: no closing \"\n"); BEGIN(INITIAL);}

\' {bufferString[0] = 0; clearStringBuffer(&buff); BEGIN(CHAR);}
<CHAR>[^\\\'\n\r] {appendChar(&buff, yytext[0]);}
<CHAR>[\n\r] {printf("ERROR: no closing  \'\n"); BEGIN(INITIAL);}
<CHAR>\' {
    int buffLen = buff.length;
    if(buffLen > 1)
    {
        printf("ERROR: Too many characters in a character literal.\n");
    }
    else if (buffLen <= 0)
    {
        printf("ERROR: empty character literal.\n");
    }
    else
    {
        printf("(%c) - CHAR\n", buff.buffer[0]);
    }
    BEGIN(INITIAL);
}
<CHAR><<EOF>> {printf("ERROR: no closing \'\n"); BEGIN(INITIAL);}

<STRING,CHAR>\\n {appendChar(&buff, '\n');}
<STRING,CHAR>\\t {appendChar(&buff, '\t');}
<STRING,CHAR>\\b {appendChar(&buff, '\b');}
<STRING,CHAR>\\r {appendChar(&buff, '\r');}
<STRING,CHAR>\\\$ {appendChar(&buff, '$');}
<STRING,CHAR>\\\" {appendChar(&buff, '\"');}
<STRING,CHAR>\\\' {appendChar(&buff, '\'');}
<STRING,CHAR>\\\\ {appendChar(&buff, '\\');}
<STRING,CHAR>\\u[0-9A-Fa-f]{0,4} {
    if (strlen(yytext) < 4)
    {
        printf("Illegal escape: \'\\u\'");
    }
    int value = strtol(yytext+2,NULL, 16);
    if (value > 127)
    {
        printf("ERROR: non-supported UNICODE char.");
    }
    else
    {
        appendChar(&buff, strtol(yytext+2,NULL, 16));
    }
}

[ \t] {
    // Игнорирование лишних пробелов и табуляций. 
}

%%

int removeCharFromStringByIndex(char * str, int index) 
{
    int length = strlen(str); // Вычислить длину строки.
    if (index >= length || index < 0) // Удалить символ, если индекс выходит за границу строки. 
    {
        return 1;
    }
    for (int i = index; i < length; i++)
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
