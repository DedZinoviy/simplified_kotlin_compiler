%{
    #include "grammar_tab.h"
    #include "parsing_tree.h"
    #include "print_functions.h"
    extern int yyparse();
%}
%option noyywrap
%option never-interactive
%option stack

%s INTERPOLATION
%s INBRACE
%s INBRACKET
%x END_OF_LINE_COMMENT
%x MULTILINE_COMMENT
%x STRING
%x MULTILINE_STRING
%x CHAR
%x OVER

DIGIT [0-9]

%{
    #include <stdio.h>
    #include <string.h>
    #include "stringBuffer.h"
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

    int hasClosingBrace = 0;

    int hasPlus = 0;

    int hasOpenBracket = 0;

    int hasCloseBracket = 0;

    char tempIdent[1024];
    // Блок ключевых слов.
%}

%%

%{
    char bufferString[20480]; // Массив символов - буфер для строковых выражений.
    struct stringBuffer buff = {"", 0}; // Дополнительный буффер для строк.
    int line = 1;
    int multilineBegin;
%}

%{
    if(hasClosingBrace != 0)
    {
        hasClosingBrace = 0;
        return '}';
    }
    if(hasPlus != 0)
    {
        hasPlus = 0;
        return '+';
    }
    if(hasOpenBracket != 0)
    {
        hasOpenBracket = 0;
        return '(';
    }
    if(strlen(tempIdent) != 0)
    {
        char * t = (char*)malloc(strlen(tempIdent) + 1);
        strcpy(t, tempIdent);
        yylval.ident = t;
        tempIdent[0] = 0;
        return ID;
    }
    if(hasCloseBracket != 0)
    {
        hasCloseBracket = 0;
        hasPlus = 1;
        return ')';
    }
%}

as {printf("(%s) - AS_KEY_WORD\n", yytext);}
as\? {printf("(%s) - AS?_KEY_WORD\n", yytext);}
break {printf("(%s) - BREAK_KEY_WORD\n", yytext);}
class {printf("(%s) - CLASS_KEY_WORD\n", yytext);}
continue {printf("(%s) - CONTINUE_KEY_WORD\n", yytext);}
do {
    printf("(%s) - DO_KEY_WORD\n", yytext);
    return DO;
}
else {printf("(%s) - ELSE_KEY_WORD\n", yytext);}
for {
    printf("(%s) - FOR_KEY_WORD\n", yytext);
    return FOR;
}
fun {
    printf("(%s) - FUN_KEY_WORD\n", yytext);
    return FUNC;
}
if {printf("(%s) - IF_KEY_WORD\n", yytext);}
in {
    printf("(%s) - IN_KEY_WORD\n", yytext);
    return IN;
}
\!in {printf("(%s) - !IN_KEY_WORD\n", yytext);}
interface {printf("(%s) - INTERFACE_KEY_WORD\n", yytext);}
internal {
    printf("(%s) - INTERNAL_KEY_WORD\n", yytext);
    return INTERNAL;
}
is {printf("(%s) - IS_KEY_WORD\n", yytext);}
\!is {printf("(%s) - !IS_KEY_WORD\n", yytext);}
null {printf("(%s) - NULL_KEY_WORD\n", yytext);}
object {printf("(%s) - OBJECT_KEY_WORD\n", yytext);}
open {
    printf("(%s) - OPEN_KEY_WORD\n", yytext);
    return OPEN;
}
private {
    printf("(%s) - PRIVATE_KEY_WORD\n", yytext);
    return PRIVATE;
}
protected {
    printf("(%s) - PROTECTED_KEY_WORD\n", yytext);
    return PROTECTED;
}
public {
    printf("(%s) - PUBLIC_KEY_WORD\n", yytext);
    return PUBLIC;
}
package {printf("(%s) - PACKAGE_KEY_WORD\n", yytext);}
return {printf("(%s) - RETURN_KEY_WORD\n", yytext);}
super {
    printf("(%s) - SUPER_KEY_WORD\n", yytext);
    return SUPER;
}
this {
    printf("(%s) - THIS_KEY_WORD\n", yytext);
    return THIS;
}
throw {printf("(%s) - THROW_KEY_WORD\n", yytext);}
try {printf("(%s) - TRY_KEY_WORD\n", yytext);}
typealias {printf("(%s) - TYPEALIAS_KEY_WORD\n", yytext);}
val {
    printf("(%s) - VAL_KEY_WORD\n", yytext);
    return VAL;
}
var {
    printf("(%s) - VAR_KEY_WORD\n", yytext);
    return VAR;
}
when {printf("(%s) - WHEN_KEY_WORD\n", yytext);}
while {
    printf("(%s) - WHILE_KEY_WORD\n", yytext);
    return WHILE;
}

true {
    printf("(%s) - TRUE_KEY_WORD\n", yytext);
    return TRUE_LITERAL;
}
false {
    printf("(%s) - FALSE_KEY_WORD\n", yytext);
    return FALSE_LITERAL;
}

\/\* {bufferString[0] = 0; multilineBegin = line; yy_push_state(MULTILINE_COMMENT);}
<MULTILINE_COMMENT>[^*\n]+ {strcat(bufferString, yytext);}
<MULTILINE_COMMENT>[^*\n]*\n {line += 1; strcat(bufferString, yytext);}
<MULTILINE_COMMENT>"*"+\n {line += 1; strcat(bufferString, yytext);}
<MULTILINE_COMMENT>"*"+[^*/] {strcat(bufferString, yytext);}
<MULTILINE_COMMENT>"*"+"/" {printf("(%s) - MULTILINE_COMMENT\n", bufferString); yy_pop_state();}
<MULTILINE_COMMENT><<EOF>> {printf("ERROR: no closing */ in line %d.\n", multilineBegin); BEGIN(INITIAL); return -1;}

\/\/ {bufferString[0] = 0; yy_push_state(END_OF_LINE_COMMENT);}
<END_OF_LINE_COMMENT>[^\n]* {strcat(bufferString, yytext);}
<END_OF_LINE_COMMENT>[\r\n] {printf("(%s) - END_OF_LINE_COMMENT\n", bufferString);  line += 1; yy_pop_state();}
<END_OF_LINE_COMMENT><<EOF>> {printf("(%s) - END_OF_LINE_COMMENT\n", bufferString); BEGIN(INITIAL);}

\+ {
    printf("(%s) - PLUS_OPERATOR\n", yytext);
    return '+';
}
\- {
    printf("(%s) - MINUS_OPERATOR\n", yytext);
    return '-';
}
\* {
    printf("(%s) - MUL_OPERATOR\n", yytext);
    return '*';
}
\/ {
    printf("(%s) - DIV_OPERATOR\n", yytext);
    return '/';
}
\= {
    printf("(%s) - ASSIGNMENT_OPERATOR\n", yytext);
    return '=';
}
\>\= {
    printf("(%s) - GREATER_EQUAL_OPERATOR\n", yytext);
    return GREATER_EQUAL;
}
\<\= {
    printf("(%s) - LESS_EQUAL_OPERATOR\n", yytext);
    return LESS_EQUAL;
}
\> {
    printf("(%s) - GREATER_OPERATOR\n", yytext);
    return '>';
}
\< {
    printf("(%s) - LESS_OPERATOR\n", yytext);
    return '<';
}
\!\= {
    printf("(%s) - NOT_EQUAL_OPERATOR\n", yytext);
    return NOT_EQUAL;
}
\=\= {
    printf("(%s) - EQUAL_OPERATOR\n", yytext);
    return EQUAL;
}
\% {
    printf("(%s) - MOD_OPERATOR\n", yytext);
    return '%';
}
\/\= {
    printf("(%s) - DIV_ASSIGNMENT_OPERATOR\n", yytext);
    return DIV_ASSIGNMENT;
}
\+\= {
    printf("(%s) - PLUS_ASSIGNMENT_OPERATOR\n", yytext);
    return PLUS_ASSIGNMENT;
}
\*\= {
    printf("(%s) - MUL_ASSIGNMENT_OPERATOR\n", yytext);
    return MUL_ASSIGNMENT;
}
\-\= {
    printf("(%s) - MINUS_ASSIGNMENT_OPERATOR\n", yytext);
    return MINUS_ASSIGNMENT;
}
\%\= {
    printf("(%s) - MOD_ASSIGNMENT_OPERATOR\n", yytext);
    return MOD_ASSIGNMENT;
}

<INITIAL>\{ {
    printf("(%s) - LEFT_BRACE\n", yytext);
    return '{';
}
<INITIAL>\} {
    printf("(%s) - RIGHT_BRACE\n", yytext);
    hasClosingBrace = 1;
    return ';';
}
\[ {printf("(%s) - LEFT_SQUARE_BRACKET\n", yytext);}
\] {printf("(%s) - RIGHT_SQUARE_BRACKET\n", yytext);}
\( {
    printf("(%s) - LEFT_ROUND_BRACKET\n", yytext);
    yy_push_state(INBRACKET);
    return '(';
}
\) {
    printf("(%s) - RIGHT_ROUND_BRACKET\n", yytext);
    yy_pop_state();
    return ')';
}
\: {
    printf("(%s) - COLON\n", yytext);
    return ':';
}
\; {
    printf("(%s) - SEMICOLON\n", yytext);
    return ';';
}
\. {
    printf("(%s) - DOT\n", yytext);
    return '.';
}
\, {
    printf("(%s) - COMMA\n", yytext);
    return ',';
}

\+\+ {
    printf("(%s) - INCREMENT_OPERATOR\n", yytext);
    return INCREMENT;
}
\-\- {
    printf("(%s) - DECREMENT_OPERATOR\n", yytext);
    return DECREMENT;
}

\=\=\= {printf("(%s) - REF_EQUAL_OPERATOR\n", yytext);}
\!\=\= {printf("(%s) - REF_NOT_EQUAL_OPERATOR\n", yytext);}

\! {
    printf("(%s) - NOT_OPERATOR\n", yytext);
    return '!';
}
\|\| {
    printf("(%s) - OR_OPERATOR\n", yytext);
    return DISJ;
} 
\&\& {
    printf("(%s) - AND_OPERATOR\n", yytext);
    return CONJ;
}

\.\. {
    printf("(%s) - RANGE_OPERATOR\n", yytext);
    return RANGE;
}
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
    return '{';
}

<INBRACE>"}" {
    printf("(%s) - RIGHT_BRACE\n", yytext);
    hasClosingBrace = 1;
    yy_pop_state();
    return ';';
}

<INBRACE>"{" {
    printf("(%s) - LEFT_BRACE\n", yytext);
    yy_push_state(INBRACE);
    return '{';
}

<INTERPOLATION>"}" {
    printf("(%s) - END_INTERPOLATION\n", yytext);
    bufferString[0] = 0;
    clearStringBuffer(&buff);
    hasPlus = 1;
    yy_pop_state();
    return ')';
}

<INBRACE><<EOF>> {
    printf("ERROR: expecting \"{\"");
    BEGIN(INITIAL);
    return -1;
}

<INTERPOLATION><<EOF>> {
    printf("ERROR: expecting \"{\"");
    BEGIN(INITIAL);
    return -1;
}

[A-Za-z_][A-Za-z0-9_]* {
    printf("(%s) - IDENTIFIER\n", yytext);
    char * t = (char*)malloc(strlen(yytext) + 1);
    strcpy(t, yytext);
    yylval.ident = t;
    return ID;
}

{DIGIT}(\_*{DIGIT})* { bufferString[0] = 0;
    strcat(bufferString, yytext);
    int buffLen = strlen(bufferString);
    if (bufferString[0] == '0' && buffLen > 1)
    {
        printf("ERROR: illegal using of zero in INT in line %d.\n", line);
        return -1;
    }
    else 
    {
        removeUnderline(bufferString);
        int res = atoi(bufferString);
        printf("(%d) - DECIMAL_INT\n", res);
        yylval.intLit = res;
        return INT_LITERAL;
    }
}

{DIGIT}(\_*{DIGIT})*\_+ {
    printf("ERROR: illegal underscore in INT in line %d.\n", line);
    return -1;
}

0(x|X)[0-9a-fA-F](_*[0-9a-fA-F]+)* { 
    bufferString[0] = 0;
    strcat(bufferString, yytext);
    removeUnderline(bufferString);
    int result = strtol(bufferString + 2, NULL, 16);
    printf("(%d) - HEX_INT\n", result);
    yylval.intLit = result;
    return INT_LITERAL;
}

0(x|X)\_* {
    printf("ERROR: missing hex int value in line %d.\n", line);
    return -1;
}

0(x|X)[0-9a-fA-F](_*[0-9a-fA-F]+)*\_+ {
    printf("ERROR: illegal underscore in INT in line %d.\n", line);
    return -1;
}

0(x|X)\_+[0-9a-fA-F](_*[0-9a-fA-F]+)* {
    printf("ERROR: illegal underscore in INT in line %d.\n", line);
    return -1;
}

0(b|B)[0-1](_*[0-1]+)* {
    bufferString[0] = 0;
    strcat(bufferString, yytext);
    removeUnderline(bufferString);
    int result = strtol(bufferString + 2, NULL, 2);
    printf("(%d) - BINARY_INT\n", result);
    yylval.intLit = result;
    return INT_LITERAL;
}

0(b|B)\_* {
    printf("ERROR: missing binary int value in line %d.\n", line);
    return -1;
}

0(b|B)[0-1](_*[0-1]+)*\_+ {
    printf("ERROR: illegal underscore in INT in line %d.\n", line);
    return -1;
}

0(b|B)\_+[0-1](_*[0-1]+)* {
    printf("ERROR: illegal underscore in INT in line %d.\n", line);
    return -1;
}

0(b|B)[_0-9]* {
    printf("ERROR: oot of range binary value in line %d.\n", line);
    return -1;
}

(({DIGIT}(\_*{DIGIT})*)?\.)?{DIGIT}(\_*{DIGIT})*((e|E)(\+|\-)?{DIGIT}(\_*{DIGIT})*)? {
    bufferString[0] = 0;
    strcat(bufferString, yytext);
    removeUnderline(bufferString);
    int resLen = strlen(bufferString);
    double result = atof(bufferString);
    printf("(%.*f) - DOUBLE\n", resLen, result);
    yylval.doubleLit = result;
    return DOUBLE_LITERAL;
}

({DIGIT}(\_*{DIGIT})*\_+)\.{DIGIT}(\_*{DIGIT})*((e|E)(\+|\-)?{DIGIT}(\_*{DIGIT})*)? {
    printf("ERROR: illegal underscore in DOUBLE in line %d.\n", line);
    return -1;
}

({DIGIT}(\_*{DIGIT})*)?\.{DIGIT}(\_*{DIGIT})*\_+((e|E)(\+|\-)?{DIGIT}(\_*{DIGIT})*)? {
    printf("ERROR: illegal underscore in DOUBLE in line %d.\n", line);
    return -1;
}

(({DIGIT}(\_*{DIGIT})*)?\.)?{DIGIT}(\_*{DIGIT})*((e|E)(\+|\-)?\_+{DIGIT}(\_*{DIGIT})*) {
    printf("ERROR: illegal underscore in DOUBLE in line %d.\n", line);
    return -1;
}

(({DIGIT}(\_*{DIGIT})*)?\.)?{DIGIT}(\_*{DIGIT})*((e|E)(\+|\-)?{DIGIT}(\_*{DIGIT})*\_+) {
    printf("ERROR: illegal underscore in DOUBLE in line %d.\n", line);
    return -1;
}

(({DIGIT}(\_*{DIGIT})*)?\.)?{DIGIT}(\_*{DIGIT})*((e|E)(\+|\-)?)(\_)* {
    printf("ERROR: the value is out of range in DOUBLE in line %d.\n", line);
    return -1;
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
    struct stringBuffer * ns = (struct stringBuffer*)malloc(sizeof(struct stringBuffer));
    strcpy(ns->buffer, bufferString);
    ns->length = strlen(bufferString);
    yylval.stringLit = ns;
    hasPlus = 1;
    hasOpenBracket = 1;
    printf("(%s) - BEGIN_INTERPOLATION\n", yytext);
    bufferString[0] = 0;
    yy_push_state(INTERPOLATION);
    return STRING_LITERAL;
}
<MULTILINE_STRING>\$[A-Za-z_][A-Za-z0-9_]* {
    printf("(%s) - MULTILINE_STRING\n", bufferString);
    struct stringBuffer * ns = (struct stringBuffer*)malloc(sizeof(struct stringBuffer));
    strcpy(ns->buffer, bufferString);
    ns->length = strlen(bufferString);
    yylval.stringLit = ns;
    hasPlus = 1;
    hasOpenBracket = 1;
    strcpy(tempIdent, yytext + 1);
    hasCloseBracket = 1;
    printf("($) - BEGIN_INTERPOLATION\n");
    printf("(%s) - IDENTIFIER\n", yytext + 1);
    printf("() - END_INTERPOLATION\n");
    bufferString[0] = 0;
    return STRING_LITERAL;
}
<MULTILINE_STRING>\"{1,2} {strcat(bufferString, yytext);}
<MULTILINE_STRING>\"{3,} {
    for (int i = 0; i < yyleng - 3; i++)
    {
        strcat(bufferString, "\"");        
    }
    printf("(%s) - MULTILINE STRING\n", bufferString);
    struct stringBuffer * ns = (struct stringBuffer*)malloc(sizeof(struct stringBuffer));
    strcpy(ns->buffer, bufferString);
    ns->length = strlen(bufferString);
    yylval.stringLit = ns;
    printf("(\"\"\") - MULTILINE_STRING_END\n", yytext);
    yy_pop_state();
    return STRING_LITERAL;
}
<MULTILINE_STRING><<EOF>> {printf("ERROR: no closing \"\"\" (three double-quotes) in MULTILINE STRING in line %d.\n", multilineBegin); BEGIN(INITIAL); return -1;}

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

    struct stringBuffer * ns = (struct stringBuffer*)malloc(sizeof(struct stringBuffer));
    memcpy(ns->buffer, buff.buffer, buff.length);
    ns->length = buff.length;
    yylval.stringLit = ns;
    hasPlus = 1;
    hasOpenBracket = 1;

    printf("(%s) - BEGIN_INTERPOLATION\n", yytext);
    clearStringBuffer(&buff);
    yy_push_state(INTERPOLATION);
    return STRING_LITERAL;
}
<STRING>[^\\\"\$\n\r] {appendChar(&buff, yytext[0]);}
<STRING>\$[A-Za-z_][A-Za-z0-9_]* {
    printf("(");
    printStringBuffer(&buff);
    
    struct stringBuffer * ns = (struct stringBuffer*)malloc(sizeof(struct stringBuffer));
    memcpy(ns->buffer, buff.buffer, buff.length);
    ns->length = buff.length;
    yylval.stringLit = ns;
    hasPlus = 1;
    hasOpenBracket = 1;
    strcpy(tempIdent, yytext + 1);
    hasCloseBracket = 1;
    printf(") - ESCAPED_STRING\n");
    printf("($) - BEGIN_INTERPOLATION\n");
    printf("(%s) - IDENTIFIER\n", yytext + 1);
    printf("() - END_INTERPOLATION\n");
    clearStringBuffer(&buff);
    bufferString[0] = 0;
    return STRING_LITERAL;
}
<STRING>\$[^A-Za-z_\{\"]* {appendChars(&buff, yytext);}
<STRING>[\n\r] {printf("ERROR: no closing \" (double-quote) in STRING in line %d.\n", multilineBegin); line += 1; yy_pop_state(); return -1;}
<STRING>\" { 
    printf("(");
    printStringBuffer(&buff);
    printf(") - ESCAPED STRING\n"); 
    printf("(%s) - ESCAPED_STRING_END\n", yytext);
    yy_pop_state();
    struct stringBuffer * ns = (struct stringBuffer*)malloc(sizeof(struct stringBuffer));
    memcpy(ns->buffer, buff.buffer, buff.length);
    ns->length = buff.length;
    yylval.stringLit = ns;
    return STRING_LITERAL;
}
<STRING><<EOF>> {printf("ERROR: no closing \" (double-quote) in STRING in line %d.\n", multilineBegin); BEGIN(INITIAL); return -1;}

\' {bufferString[0] = 0; multilineBegin = line; clearStringBuffer(&buff); yy_push_state(CHAR);}
<CHAR>[^\\\'\n\r] {appendChar(&buff, yytext[0]);}
<CHAR>[\n\r] {printf("ERROR: no closing  \' (single-quote) in CHAR in line %d.\n", multilineBegin); line += 1; yy_pop_state(); return -1;}
<CHAR>\' {
    int buffLen = buff.length;
    int isOk = 0;
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
        isOk = 1;
    }
    yy_pop_state();
    if(isOk) 
    {        
        yylval.charLit = buff.buffer[0];
        return CHAR_LITERAL;
    }
    else
    {
        return -1;
    }
}
<CHAR><<EOF>> {printf("ERROR: no closing \' (single-quote) in CHAR in line %d.\n", multilineBegin); BEGIN(INITIAL); return -1;}

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
        return -1;
    }
    int value = strtol(yytext+2,NULL, 16);
    if (value > 127)
    {
        printf("ERROR: non-supported UNICODE character in line %d.", line);
        return -1;
    }
    else
    {
        appendChar(&buff, value);
    }
}

[ \t] {
    // Игнорирование лишних пробелов и табуляций. 
}

<INBRACKET>[\r\n] {
    line = line + 1;
}

[\r\n] {
    line = line + 1;
    return ENDL;
}

. {
    bufferString[0] = 0;
    strcat(bufferString, yytext);
    printf("%s - UNRECOGNIZED TOKEN.", bufferString);
    return -1;
}

<INITIAL><<EOF>> { 
    BEGIN(OVER);
    return ';';
}

<OVER><<EOF>> {
    yyterminate();
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

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("The path to the input file is missing.\n");
		return -1;
	}

	yyin = fopen(argv[1], "r");

    printf("The parsing process has started.");

	yyparse();

    printf("The parsing process is completed.");

    FILE *f = fopen("result.gv", "w");

    char * res = generateDotFromKotlinFile(root);

    fprintf(f, "%s", res);

    fclose(f);

	return 0;
}
