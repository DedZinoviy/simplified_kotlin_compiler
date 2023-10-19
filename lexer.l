%option noyywrap
%option never-interactive
%option stack

%s INTERPOLATION
%s INBRACE
%x END_OF_LINE_COMMENT
%x MULTILINE_COMMENT
%x STRING
%x MULTILINE_STRING
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
    int multilineBegin;
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

\/\* {bufferString[0] = 0; multilineBegin = line; yy_push_state(MULTILINE_COMMENT);}
<MULTILINE_COMMENT>[^*\n]+ {strcat(bufferString, yytext);}
<MULTILINE_COMMENT>[^*\n]*\n {line += 1; strcat(bufferString, yytext);}
<MULTILINE_COMMENT>"*"+\n {line += 1; strcat(bufferString, yytext);}
<MULTILINE_COMMENT>"*"+[^*/] {strcat(bufferString, yytext);}
<MULTILINE_COMMENT>"*"+"/" {printf("(%s) - MULTILINE_COMMENT\n", bufferString); yy_pop_state();}
<MULTILINE_COMMENT><<EOF>> {printf("ERROR: no closing */ in line %d.\n", multilineBegin); BEGIN(INITIAL);}

\/\/ {bufferString[0] = 0; yy_push_state(END_OF_LINE_COMMENT);}
<END_OF_LINE_COMMENT>[^\n]* {strcat(bufferString, yytext);}
<END_OF_LINE_COMMENT>[\r\n] {printf("(%s) - END_OF_LINE_COMMENT\n", bufferString);  line += 1; yy_pop_state();}
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

<INITIAL>\{ {printf("(%s) - LEFT_BRACE\n", yytext);}
<INITIAL>\} {printf("(%s) - RIGHT_BRACE\n", yytext);}
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

<INTERPOLATION>"{" {
    printf("(%s) - LEFT_BRACE\n", yytext);
    yy_push_state(INBRACE);
}

<INBRACE>"}" {
    printf("(%s) - RIGHT_BRACE\n", yytext);
    yy_pop_state();
}

<INTERPOLATION>"}" {
    printf("(%s) - END_INTERPOLATION\n", yytext);
    bufferString[0] = 0;
    clearStringBuffer(&buff);
    yy_pop_state();
}

<INBRACE><<EOF>> {
    printf("ERROR: expecting \"{\"");
    BEGIN(INITIAL);
}

<INTERPOLATION><<EOF>> {
    printf("ERROR: expecting \"{\"");
    BEGIN(INITIAL);
}

[A-Za-z_][A-Za-z0-9_]* {printf("(%s) - IDENTIFIER\n", yytext);}

{DIGIT}(\_*{DIGIT})* { bufferString[0] = 0;
    strcat(bufferString, yytext);
    int buffLen = strlen(bufferString);
    if (bufferString[0] == '0' && buffLen > 1)
    {
        printf("ERROR: illegal using of zero in INT in line %d.\n", line);
    }
    else 
    {
        removeUnderline(bufferString);
        int res = atoi(bufferString);
        printf("(%d) - DECIMAL_INT\n", res);
    }
}

{DIGIT}(\_*{DIGIT})*\_+ {
    printf("ERROR: illegal underscore in INT in line %d.\n", line);
}

0(x|X)[0-9a-fA-F](_*[0-9a-fA-F]+)* { 
    bufferString[0] = 0;
    strcat(bufferString, yytext);
    removeUnderline(bufferString);
    int result = strtol(bufferString + 2, NULL, 16);
    printf("(%d) - HEX_INT\n", result);
}

0(x|X)\_* {
    printf("ERROR: missing hex int value in line %d.\n", line);
}

0(x|X)[0-9a-fA-F](_*[0-9a-fA-F]+)*\_+ {
    printf("ERROR: illegal underscore in INT in line %d.\n", line);
}

0(x|X)\_+[0-9a-fA-F](_*[0-9a-fA-F]+)* {
    printf("ERROR: illegal underscore in INT in line %d.\n", line);
}

0(b|B)[0-1](_*[0-1]+)* {
    bufferString[0] = 0;
    strcat(bufferString, yytext);
    removeUnderline(bufferString);
    int result = strtol(bufferString + 2, NULL, 2);
    printf("(%d) - BINARY_INT\n", result);
}

0(b|B)\_* {
    printf("ERROR: missing binary int value in line %d.\n", line);
}

0(b|B)[0-1](_*[0-1]+)*\_+ {
    printf("ERROR: illegal underscore in INT in line %d.\n", line);
}

0(b|B)\_+[0-1](_*[0-1]+)* {
    printf("ERROR: illegal underscore in INT in line %d.\n", line);
}

0(b|B)[_0-9]* {
    printf("ERROR: oot of range binary value in line %d.\n", line);
}

({DIGIT}(\_*{DIGIT})*)?\.{DIGIT}(\_*{DIGIT})*((e|E)(\+|\-)?{DIGIT}(\_*{DIGIT})*)? {
    bufferString[0] = 0;
    strcat(bufferString, yytext);
    removeUnderline(bufferString);
    int resLen = strlen(bufferString);
    double result = atof(bufferString);
    printf("(%.*f) - DOUBLE\n", resLen, result);
}

({DIGIT}(\_*{DIGIT})*\_+)\.{DIGIT}(\_*{DIGIT})*((e|E)(\+|\-)?{DIGIT}(\_*{DIGIT})*)? {
    printf("ERROR: illegal underscore in DOUBLE in line %d.\n", line);
}

({DIGIT}(\_*{DIGIT})*)?\.{DIGIT}(\_*{DIGIT})*\_+((e|E)(\+|\-)?{DIGIT}(\_*{DIGIT})*)? {
    printf("ERROR: illegal underscore in DOUBLE in line %d.\n", line);
}

({DIGIT}(\_*{DIGIT})*)?\.{DIGIT}(\_*{DIGIT})*((e|E)(\+|\-)?\_+{DIGIT}(\_*{DIGIT})*) {
    printf("ERROR: illegal underscore in DOUBLE in line %d.\n", line);
}

({DIGIT}(\_*{DIGIT})*)?\.{DIGIT}(\_*{DIGIT})*((e|E)(\+|\-)?{DIGIT}(\_*{DIGIT})*\_+) {
    printf("ERROR: illegal underscore in DOUBLE in line %d.\n", line);
}

({DIGIT}(\_*{DIGIT})*)?\.{DIGIT}(\_*{DIGIT})*((e|E)(\+|\-)?)(\_)* {
    printf("ERROR: the value is out of range in DOUBLE in line %d.\n", line);
}

\"\"\" {
    bufferString[0] = 0;
    multilineBegin = line;
    printf("(%s) - MULTILINE_STRING_BEGIN\n", yytext);
    yy_push_state(MULTILINE_STRING); 
}
<MULTILINE_STRING>[\n\r] {line += 1; strcat(bufferString, yytext);}
<MULTILINE_STRING>[^\$\"\n\r]+ {strcat(bufferString, yytext);}
<MULTILINE_STRING>\$\{ {
    printf("(%s) - MULTILINE_STRING\n", bufferString);
    printf("(%s) - BEGIN_INTERPOLATION\n", yytext);
    bufferString[0] = 0;
    yy_push_state(INTERPOLATION);
}
<MULTILINE_STRING>\$[A-Za-z_][A-Za-z0-9_]* {
    printf("(%s) - MULTILINE_STRING\n", bufferString);
    printf("($) - BEGIN_INTERPOLATION\n");
    printf("(%s) - IDENTIFIER\n", yytext + 1);
    printf("() - END_INTERPOLATION\n");
    bufferString[0] = 0;
}
<MULTILINE_STRING>\"{1,2} {strcat(bufferString, yytext);}
<MULTILINE_STRING>\"\"\" {printf("(%s) - MULTILINE STRING\n", bufferString); 
    printf("(%s) - MULTILINE_STRING_END\n", yytext);
    yy_pop_state();
}
<MULTILINE_STRING><<EOF>> {printf("ERROR: no closing \"\"\" (three double-quotes) in MULTILINE STRING in line %d.\n", multilineBegin); BEGIN(INITIAL);}

\" {
    bufferString[0] = 0;
    multilineBegin = line;
    clearStringBuffer(&buff);
    printf("(%s) - ESCAPED_STRING_BEGIN\n", yytext);
    yy_push_state(STRING);
}
<STRING>(\$\{) {
    printf("(");
    printStringBuffer(&buff);
    printf(") - ESCAPED_STRING\n");
    printf("(%s) - BEGIN_INTERPOLATION\n", yytext);
    clearStringBuffer(&buff);
    yy_push_state(INTERPOLATION);
}
<STRING>[^\\\"\$\n\r] {appendChar(&buff, yytext[0]);}
<STRING>\$[A-Za-z_][A-Za-z0-9_]* {
    printf("(");
    printStringBuffer(&buff);
    printf(") - ESCAPED_STRING\n");
    printf("($) - BEGIN_INTERPOLATION\n");
    printf("(%s) - IDENTIFIER\n", yytext + 1);
    printf("() - END_INTERPOLATION\n");
    clearStringBuffer(&buff);
    bufferString[0] = 0;
}
<STRING>\$[^A-Za-z_\{]* {appendChars(&buff, yytext);}
<STRING>[\n\r] {printf("ERROR: no closing \" (double-quote) in STRING in line %d.\n", multilineBegin); line += 1; yy_pop_state();}
<STRING>\" { 
    printf("(");
    printStringBuffer(&buff);
    printf(") - ESCAPED STRING\n"); 
    printf("(%s) - ESCAPED_STRING_END\n", yytext);
    yy_pop_state();
}
<STRING><<EOF>> {printf("ERROR: no closing \" (double-quote) in STRING in line %d.\n", multilineBegin); BEGIN(INITIAL);}

\' {bufferString[0] = 0; multilineBegin = line; clearStringBuffer(&buff); yy_push_state(CHAR);}
<CHAR>[^\\\'\n\r] {appendChar(&buff, yytext[0]);}
<CHAR>[\n\r] {printf("ERROR: no closing  \' (single-quote) in CHAR in line %d.\n", multilineBegin); line += 1; yy_pop_state();}
<CHAR>\' {
    int buffLen = buff.length;
    if(buffLen > 1)
    {
        printf("ERROR: Too many characters in a character literal in line %d.\n", multilineBegin);
    }
    else if (buffLen <= 0)
    {
        printf("ERROR: empty character literal in line %d.\n", multilineBegin);
    }
    else
    {
        printf("(%c) - CHAR\n", buff.buffer[0]);
    }
    yy_pop_state();
}
<CHAR><<EOF>> {printf("ERROR: no closing \' (single-quote) in CHAR in line %d.\n", multilineBegin); BEGIN(INITIAL);}

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
        printf("ERROR: Illegal escape \'\\u\' in line %d", line);
    }
    int value = strtol(yytext+2,NULL, 16);
    if (value > 127)
    {
        printf("ERROR: non-supported UNICODE character in line %d.", line);
    }
    else
    {
        appendChar(&buff, value);
    }
}

[ \t] {
    // Игнорирование лишних пробелов и табуляций. 
}

[\r\n] {
    line = line + 1;
}

. {
    bufferString[0] = 0;
    strcat(bufferString, yytext);
    printf("%s - UNRECOGNIZED TOKEN.");
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
