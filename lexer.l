%{
    #include "parser_tab.h"
    #include "parsing_tree.h"
    #include "print_functions.h"
    #include "modifier_head.h"
    extern int yyparse();
%}
%option noyywrap
%option never-interactive
%option stack

%s INTERPOLATION
%s INBRACE
%s INBRACKET
%s FUNCTION
%s FUNC_BODY
%x END_OF_LINE_COMMENT
%x MULTILINE_COMMENT
%x STRING
%x MULTILINE_STRING
%x CHAR
%x MODIFIER
%x OVER

DIGIT [0-9]

%{
    #include <stdio.h>
    #include <string.h>
    #include "stringBuffer.h"
    #include "iohandler.h"
%}

%{
    /*! Удалить символ из строки по его индексу в ней.
    * \param[in] str исходная строка.
    * \param[in] index индекс удаляемого символа.
    * \return 0, если удалено успешно, 1 - если нет.
    */
    int removeCharFromStringByIndex(char * str, int index); 

    /*! Удалить из строки нижние подчеркивания.
    * \param[in] str исходная строка.
    */
    void removeUnderline(char* str);

    /*! Опциональный вывод лексем в зависимости от значения флага.
    * \param[in] str выводимая строка.
    * \param[in] token выводимый токен.
    */
    void printHandler(char* str, char * token);

    int hasClosingBrace = 0;

    int hasPlus = 0;

    int hasOpenBracket = 0;

    int hasCloseBracket = 0;

    int needsTokens = 0;

    char tempIdent[1024];

    struct ModifierHead head = {0,0,0,0,0,0,0};
    
    int line = 1;
    
    int multilineBegin;
%}

%%

%{
    char bufferString[20480]; // Массив символов - буфер для строковых выражений.
    struct stringBuffer buff = {"", 0}; // Дополнительный буффер для строк.
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

<FUNC_BODY>public {printf("ERROR: Modifiers is incompatible with local variables.\n"); return -1;}
<FUNC_BODY>private {printf("ERROR: Modifiers is incompatible with local variables.\n"); return -1;}
<FUNC_BODY>internal {printf("ERROR: Modifiers is incompatible with local variables.\n"); return -1;}
<FUNC_BODY>protected {printf("ERROR: Modifiers is incompatible with local variables.\n"); return -1;}
<FUNC_BODY>open {printf("ERROR: Modifiers is incompatible with local variables.\n"); return -1;}
<FUNC_BODY>override {printf("ERROR: Modifiers is incompatible with local variables.\n"); return -1;}
<FUNC_BODY>final {printf("ERROR: Modifiers is incompatible with local variables.\n"); return -1;}

<MODIFIER>public {
    if (head.isPublic == 0)
    {
        if((head.isInternal != 0) || (head.isProtected != 0) || (head.isPrivate != 0))
        {
            printf("ERROR: Incompatible visibility modifiers in line %d.\n", line);
            BEGIN(INITIAL);
            return -1;    
        }
        else
        {
            printHandler((char*)"PUBLIC_KEY_WORD", yytext);
            head.isPublic = 1;
        }
    }
    else
    {
        printf("ERROR: Repeated \"public\" modifier in line %d.\n", line);
        BEGIN(INITIAL);
        return -1;
    }
}
<MODIFIER>internal {
    if (head.isInternal == 0)
    {
        if((head.isPublic != 0) || (head.isProtected != 0) || (head.isPrivate != 0))
        {
            printf("ERROR: Incompatible visibility modifiers in line %d.\n", line);
            BEGIN(INITIAL);
            return -1;    
        }
        else
        {
            printHandler((char*)"INTERNAL_KEY_WORD", yytext);
            head.isInternal = 1;
        }
    }
    else
    {
        printf("ERROR: Repeated \"internal\" modifier in line %d.\n", line);
        BEGIN(INITIAL);
        return -1;
    }
}
<MODIFIER>protected {
    if (head.isProtected == 0)
    {
        if((head.isPublic != 0) || (head.isInternal != 0) || (head.isPrivate != 0))
        {
            printf("ERROR: Incompatible visibility modifiers in line %d.\n", line);
            BEGIN(INITIAL);
            return -1;    
        }
        else
        {
            printHandler((char*)"PROTECTED_KEY_WORD", yytext);
            head.isProtected = 1;
        }
    }
    else
    {
        printf("ERROR: Repeated \"protected\" modifier in line %d.\n", line);
        BEGIN(INITIAL);
        return -1;
    }
}
<MODIFIER>private {
    if (head.isPrivate == 0)
    {
        if((head.isPublic != 0) || (head.isInternal != 0) || (head.isProtected != 0))
        {
            printf("ERROR: Incompatible visibility modifiers in line %d.\n", line);
            BEGIN(INITIAL);
            return -1;    
        }
        else
        {
            printHandler((char*)"PRIVATE_KEY_WORD", yytext);
            head.isPrivate = 1;
        }
    }
    else
    {
        printf("ERROR: Repeated \"private\" modifier in line %d.\n", line);
        BEGIN(INITIAL);
        return -1;
    }
}
<MODIFIER>open {
    if (head.isOpen == 0)
    {
        if((head.isFinal != 0))
        {
            printf("ERROR: Incompatible modifiers \"open\" and \"final\" in line %d.\n", line);
            BEGIN(INITIAL);
            return -1;    
        }
        else
        {
            printHandler((char*)"OPEN_KEY_WORD", yytext);
            head.isOpen = 1;
        }
    }
    else
    {
        printf("ERROR: Repeated \"open\" modifier in line %d.\n", line);
        BEGIN(INITIAL);
        return -1;
    }
}
<MODIFIER>final {
    if (head.isFinal == 0)
    {
        if((head.isOpen != 0))
        {
            printf("ERROR: Incompatible modifiers \"open\" and \"final\" in line %d.\n", line);
            BEGIN(INITIAL);
            return -1;    
        }
        else
        {
            head.isFinal = 1;
            printHandler((char*)"FINAL_KEY_WORD", yytext);
        }
    }
    else
    {
        printf("ERROR: Repeated \"final\" modifier in line %d.\n", line);
        BEGIN(INITIAL);
        return -1;
    }
}
<MODIFIER>override {
    if (head.isOverride == 0)
    {
        printHandler((char*)"OVERRIDE_KEY_WORD", yytext);
        head.isOverride = 1;
    }
    else
    {
        printf("ERROR: Repeated \"override\" modifier in line %d.\n", line);
        BEGIN(INITIAL);
        return -1;
    }
}

<MODIFIER>fun {
    struct ModifierHead * copy = copyModifierHead(&head);
    yylval.modHead = copy;
    clearModifierHead(&head);
    yy_pop_state();
    yy_push_state(FUNCTION);
    printHandler((char*)"FUN_KEY_WORD", yytext);
    return FUNC;
}
<MODIFIER>class {
    struct ModifierHead * copy = copyModifierHead(&head);
    yylval.modHead = copy;
    clearModifierHead(&head);
    yy_pop_state();
    printHandler((char*)"CLASS_KEY_WORD", yytext);
    return CLASS;
}
<MODIFIER>constructor {
    struct ModifierHead * copy = copyModifierHead(&head);
    yylval.modHead = copy;
    clearModifierHead(&head);
    yy_pop_state();
    printHandler((char*)"CONSTUCTOR_KEY_WORD", yytext);
    return CONSTRUCTOR;
}
<MODIFIER>val {
    struct ModifierHead * copy = copyModifierHead(&head);
    yylval.modHead = copy;
    clearModifierHead(&head);
    yy_pop_state();
    printHandler((char*)"VAL_KEYWORD", yytext);
    return VAL;
}
<MODIFIER>var {
    struct ModifierHead * copy = copyModifierHead(&head);
    yylval.modHead = copy;
    clearModifierHead(&head);
    yy_pop_state();
    printHandler((char*)"VAR_KEYWORD", yytext);
    return VAR;
}

as {printHandler((char*)"AS_KEY_WORD", yytext);}
as\? {printHandler((char * )"AS?_KEY_WORD", yytext);}
break {printHandler((char*)"BREAK_KEY_WORD", yytext);}
class {
    printHandler((char*)"CLASS_KEY_WORD", yytext);
    struct ModifierHead * copy = copyModifierHead(&head);
    yylval.modHead = copy;
    return CLASS;
}
constructor {
    printHandler((char*)"CONSTRUCTOR_KEY_WORD", yytext);
    struct ModifierHead * copy = copyModifierHead(&head);
    yylval.modHead = copy;
    return CONSTRUCTOR;
}
continue {printHandler((char*)"CONTINUE_KEY_WORD", yytext);}
do {
    printHandler((char*)"DO_KEY_WORD", yytext);
    return DO;
}
else {printHandler((char*)"ELSE_KEY_WORD", yytext);}
for {
    printHandler((char*)"FOR_KEY_WORD", yytext);
    return FOR;
}
fun {
    printHandler((char*)"FUN_KEY_WORD", yytext);
    struct ModifierHead * copy = copyModifierHead(&head);
    yylval.modHead = copy;
    yy_push_state(FUNCTION);
    return FUNC;
}
if {printHandler((char*)"IF_KEY_WORD", yytext);}
in {
    printHandler((char*)"IN_KEY_WORD", yytext);
    return IN;
}
\!in {printHandler((char*)"!IN_KEY_WORD", yytext);}
interface {printHandler((char*)"INTERFACE_KEY_WORD", yytext);}
internal {
    multilineBegin = line;
    printHandler((char*)"INTERNAL_KEY_WORD", yytext);
    head.isInternal = 1;
    yy_push_state(MODIFIER);
}
is {printHandler((char*)"IS_KEY_WORD", yytext);}
\!is {printHandler((char*)"!IS_KEY_WORD", yytext);}
null {printHandler((char*)"NULL_KEY_WORD", yytext);}
object {printHandler((char*)"OBJECT_KEY_WORD", yytext);}
final {
    multilineBegin = line;
    printHandler((char*)"FINAL_KEY_WORD", yytext);
    head.isFinal = 1;
    yy_push_state(MODIFIER);
}
override {
    multilineBegin = line;
    printHandler((char*)"OVERRIDE_KEY_WORD", yytext);
    head.isOverride = 1;
    yy_push_state(MODIFIER);
}
open {
    multilineBegin = line;
    printHandler((char*)"OPEN_KEY_WORD", yytext);
    head.isOpen = 1;
    yy_push_state(MODIFIER);
}
private {
    multilineBegin = line;
    printHandler((char*)"PRIVATE_KEY_WORD", yytext);
    head.isPrivate = 1;
    yy_push_state(MODIFIER);
}
protected {
    multilineBegin = line;
    printHandler((char*)"PROTECTED_KEY_WORD", yytext);
    head.isProtected = 1;
    yy_push_state(MODIFIER);
}
public {
    multilineBegin = line;
    printHandler((char*)"PUBLIC_KEY_WORD", yytext);
    head.isPublic = 1;
    yy_push_state(MODIFIER);
}
package {printHandler((char*)"PACKAGE_KEY_WORD", yytext);}
return {printHandler((char*)"RETURN_KEY_WORD", yytext);}
super {
    printHandler((char*)"SUPER_KEY_WORD", yytext);
    return SUPER;
}
this {
    printHandler((char*)"THIS_KEY_WORD", yytext);
    return THIS;
}
throw {printHandler((char*)"THROW_KEY_WORD", yytext);}
try {printHandler((char*)"TRY_KEY_WORD", yytext);}
typealias {printHandler((char*)"TYPEALIAS_KEY_WORD", yytext);}
val {
    printHandler((char*)"VAL_KEY_WORD", yytext);
    struct ModifierHead * copy = copyModifierHead(&head);
    yylval.modHead = copy;
    return VAL;
}
var {
    printHandler((char*)"VAR_KEY_WORD", yytext);
    struct ModifierHead * copy = copyModifierHead(&head);
    yylval.modHead = copy;
    return VAR;
}
when {printHandler((char*)"WHEN_KEY_WORD", yytext);}
while {
    printHandler((char*)"WHILE_KEY_WORD", yytext);
    return WHILE;
}

true {
    printHandler((char*)"TRUE_KEY_WORD", yytext);
    return TRUE_LITERAL;
}
false {
    printHandler((char*)"FALSE_KEY_WORD", yytext);
    return FALSE_LITERAL;
}

\/\* {bufferString[0] = 0; multilineBegin = line; yy_push_state(MULTILINE_COMMENT);}
<MULTILINE_COMMENT>[^*\n]+ {strcat(bufferString, yytext);}
<MULTILINE_COMMENT>[^*\n]*\n {line += 1; strcat(bufferString, yytext);}
<MULTILINE_COMMENT>"*"+\n {line += 1; strcat(bufferString, yytext);}
<MULTILINE_COMMENT>"*"+[^*/] {strcat(bufferString, yytext);}
<MULTILINE_COMMENT>"*"+"/" {printHandler((char*)"MULTILINE_COMMENT", bufferString); yy_pop_state();}
<MULTILINE_COMMENT><<EOF>> {printf("ERROR: no closing */ in line %d.\n", multilineBegin); BEGIN(INITIAL); return -1;}

\/\/ {bufferString[0] = 0; yy_push_state(END_OF_LINE_COMMENT);}
<END_OF_LINE_COMMENT>[^\n]* {strcat(bufferString, yytext);}
<END_OF_LINE_COMMENT>[\r\n] {printHandler((char*)"END_OF_LINE_COMMENT", bufferString);  line += 1; yy_pop_state();
return ENDL; }
<END_OF_LINE_COMMENT><<EOF>> {printHandler((char*)"END_OF_LINE_COMMENT", bufferString); BEGIN(INITIAL);}

\+ {
    printHandler((char*)"PLUS_OPERATOR", yytext);
    return '+';
}
\- {
    printHandler((char*)"MINUS_OPERATOR", yytext);
    return '-';
}
\* {
    printHandler((char*)"MUL_OPERATOR", yytext);
    return '*';
}
\/ {
    printHandler((char*)"DIV_OPERATOR", yytext);
    return '/';
}
<FUNCTION>\= {
    printHandler((char*)"ASSIGNMENT_OPERATOR", yytext);
    yy_pop_state();
    return '=';
}
\= {
    printHandler((char*)"ASSIGNMENT_OPERATOR", yytext);
    return '=';
}
\>\= {
    printHandler((char*)"GREATER_EQUAL_OPERATOR", yytext);
    return GREATER_EQUAL;
}
\<\= {
    printHandler((char*)"LESS_EQUAL_OPERATOR", yytext);
    return LESS_EQUAL;
}
\> {
    printHandler((char*)"GREATER_OPERATOR", yytext);
    return '>';
}
\< {
    printHandler((char*)"LESS_OPERATOR", yytext);
    return '<';
}
\!\= {
    printHandler((char*)"NOT_EQUAL_OPERATOR", yytext);
    return NOT_EQUAL;
}
\=\= {
    printHandler((char*)"EQUAL_OPERATOR", yytext);
    return EQUAL;
}
\% {
    printHandler((char*)"MOD_OPERATOR", yytext);
    return '%';
}
\/\= {
    printHandler((char*)"DIV_ASSIGNMENT_OPERATOR", yytext);
    return DIV_ASSIGNMENT;
}
\+\= {
    printHandler((char*)"PLUS_ASSIGNMENT_OPERATOR", yytext);
    return PLUS_ASSIGNMENT;
}
\*\= {
    printHandler((char*)"MUL_ASSIGNMENT_OPERATOR", yytext);
    return MUL_ASSIGNMENT;
}
\-\= {
    printHandler((char*)"MINUS_ASSIGNMENT_OPERATOR", yytext);
    return MINUS_ASSIGNMENT;
}
\%\= {
    printHandler((char*)"MOD_ASSIGNMENT_OPERATOR", yytext);
    return MOD_ASSIGNMENT;
}

<INITIAL>"{" {
    printHandler((char*)"LEFT_BRACE", yytext);
    return '{';
}
<FUNCTION>"{" {
    printHandler((char*)"LEFT_BRACE", yytext);
    yy_push_state(FUNC_BODY);
    return '{';
}
<INITIAL>\} {
    printHandler((char*)"RIGHT_BRACE", yytext);
    hasClosingBrace = 1;
    return ';';
}
\[ {printHandler((char*)"LEFT_SQUARE_BRACKET", yytext);}
\] {printHandler((char*)"RIGHT_SQUARE_BRACKET", yytext);}
\( {
    printHandler((char*)"LEFT_ROUND_BRACKET", yytext);
    yy_push_state(INBRACKET);
    return '(';
}
\) {
    printHandler((char*)"RIGHT_ROUND_BRACKET", yytext);
    yy_pop_state();
    return ')';
}
\: {
    printHandler((char*)"COLON", yytext);
    return ':';
}
\; {
    printHandler((char*)"SEMICOLON", yytext);
    return ';';
}
\. {
    printHandler((char*)"DOT", yytext);
    return '.';
}
\, {
    printHandler((char*)"COMMA", yytext);
    return ',';
}

\+\+ {
    printHandler((char*)"INCREMENT_OPERATOR", yytext);
    return INCREMENT;
}
\-\- {
    printHandler((char*)"DECREMENT_OPERATOR", yytext);
    return DECREMENT;
}

\=\=\= {printHandler((char*)"REF_EQUAL_OPERATOR", yytext);}
\!\=\= {printHandler((char*)"REF_NOT_EQUAL_OPERATOR", yytext);}

\! {
    printHandler((char*)"NOT_OPERATOR", yytext);
    return '!';
}
\|\| {
    printHandler((char*)"OR_OPERATOR", yytext);
    return DISJ;
} 
\&\& {
    printHandler((char*)"AND_OPERATOR", yytext);
    return CONJ;
}

\.\. {
    printHandler((char*)"RANGE_OPERATOR", yytext);
    return RANGE;
}
\!\! {printHandler((char*)"NOT_NULL_ASSERTION_OPERATOR", yytext);}
\?\. {printHandler((char*)"SAFE_CALL_OPERATOR", yytext);}

\?\: {printHandler((char*)"ELVIS_OPERATOR", yytext);}
\:\: {printHandler((char*)"UNIT_REFERENCE_OPERATOR", yytext);}
\? {printHandler((char*)"ALLOW_NULL_OPERATOR", yytext);}
\-\> {printHandler((char*)"LAMBDA_OPERATOR", yytext);}
\@ {printHandler((char*)"ANNOTATION_OPERATOR", yytext);}

<INTERPOLATION>"{" {
    printHandler((char*)"LEFT_BRACE", yytext);
    yy_push_state(INBRACE);
    return '{';
}

<FUNC_BODY>"{" {
    printHandler((char*)"LEFT_BRACE", yytext);
    yy_push_state(INBRACE);
    return '{';
}

<INBRACE>"}" {
    printHandler((char*)"RIGHT_BRACE", yytext);
    hasClosingBrace = 1;
    yy_pop_state();
    return ';';
}

<INBRACE>"{" {
    printHandler((char*)"LEFT_BRACE", yytext);
    yy_push_state(INBRACE);
    return '{';
}

<INTERPOLATION>"}" {
    printHandler((char*)"END_INTERPOLATION", yytext);
    bufferString[0] = 0;
    clearStringBuffer(&buff);
    hasPlus = 1;
    yy_pop_state();
    return ')';
}

<FUNC_BODY>"}" {
    printHandler((char*)"RIGHT_BRACE", yytext);
    hasClosingBrace = 1;
    yy_pop_state();
    if (YYSTATE == FUNCTION)
    {
        yy_pop_state();
    }
    return ';';
}

<INBRACE><<EOF>> {
    printf("ERROR: expecting \"}\".\n");
    BEGIN(INITIAL);
    return -1;
}

<INTERPOLATION><<EOF>> {
    printf("ERROR: expecting \"}\".\n");
    BEGIN(INITIAL);
    return -1;
}

<FUNC_BODY><<EOF>> {
    printf("ERROR: expecting \"}\".\n");
    BEGIN(INITIAL);
    return -1;
}

[A-Za-z_][A-Za-z0-9_]* {
    printHandler((char*)"IDENTIFIER", yytext);
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
        if(needsTokens) printf("(%d) - DECIMAL_INT\n", res);
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
    if(needsTokens) printf("(%d) - HEX_INT\n", result);
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
    if(needsTokens) printf("(%d) - BINARY_INT\n", result);
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
    if(needsTokens) printf("(%.*f) - DOUBLE\n", resLen, result);
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
    printHandler((char*)"MULTILINE_STRING_BEGIN", yytext);
    yy_push_state(MULTILINE_STRING); 
}
<MULTILINE_STRING>[\n\r] {line += 1; strcat(bufferString, yytext);}
<MULTILINE_STRING>[^\$\"\n\r]+ {strcat(bufferString, yytext);}
<MULTILINE_STRING>\$\{ {
    printHandler((char*)"MULTILINE_STRING", bufferString);
    struct stringBuffer * ns = (struct stringBuffer*)malloc(sizeof(struct stringBuffer));
    strcpy(ns->buffer, bufferString);
    ns->length = strlen(bufferString);
    yylval.stringLit = ns;
    hasPlus = 1;
    hasOpenBracket = 1;
    printHandler((char*)"BEGIN_INTERPOLATION", yytext);
    bufferString[0] = 0;
    yy_push_state(INTERPOLATION);
    return STRING_LITERAL;
}
<MULTILINE_STRING>\$[A-Za-z_][A-Za-z0-9_]* {
    printHandler((char*)"MULTILINE_STRING", bufferString);
    struct stringBuffer * ns = (struct stringBuffer*)malloc(sizeof(struct stringBuffer));
    strcpy(ns->buffer, bufferString);
    ns->length = strlen(bufferString);
    yylval.stringLit = ns;
    hasPlus = 1;
    hasOpenBracket = 1;
    strcpy(tempIdent, yytext + 1);
    hasCloseBracket = 1;
    printHandler((char*)"BEGIN_INTERPOLATION", (char*)"$");
    printHandler((char*)"IDENTIFIER", yytext + 1);
    printHandler((char*)"END_INTERPOLATION", (char*)" ");
    bufferString[0] = 0;
    return STRING_LITERAL;
}
<MULTILINE_STRING>\"{1,2} {strcat(bufferString, yytext);}
<MULTILINE_STRING>\"{3,} {
    for (int i = 0; i < yyleng - 3; i++)
    {
        strcat(bufferString, "\"");        
    }
    printHandler((char*)"MULTILINE STRING", bufferString);
    struct stringBuffer * ns = (struct stringBuffer*)malloc(sizeof(struct stringBuffer));
    strcpy(ns->buffer, bufferString);
    ns->length = strlen(bufferString);
    yylval.stringLit = ns;
    printHandler((char*)"MULTILINE_STRING_END", (char*)"\"\"\"");
    yy_pop_state();
    return STRING_LITERAL;
}
<MULTILINE_STRING><<EOF>> {printf("ERROR: no closing \"\"\" (three double-quotes) in MULTILINE STRING in line %d.\n", multilineBegin); BEGIN(INITIAL); return -1;}

\" {
    bufferString[0] = 0;
    multilineBegin = line;
    clearStringBuffer(&buff);
    printHandler((char*)"ESCAPED_STRING_BEGIN", yytext);
    yy_push_state(STRING);
}
<STRING>(\$\{) {
    printHandler((char*)"ESCAPED_STRING", getSafeCString(&buff));

    struct stringBuffer * ns = (struct stringBuffer*)malloc(sizeof(struct stringBuffer));
    memcpy(ns->buffer, buff.buffer, buff.length);
    ns->length = buff.length;
    yylval.stringLit = ns;
    hasPlus = 1;
    hasOpenBracket = 1;

    printHandler((char*)"BEGIN_INTERPOLATION", yytext);
    clearStringBuffer(&buff);
    yy_push_state(INTERPOLATION);
    return STRING_LITERAL;
}
<STRING>[^\\\"\$\n\r] {appendChar(&buff, yytext[0]);}
<STRING>\$[A-Za-z_][A-Za-z0-9_]* {
    struct stringBuffer * ns = (struct stringBuffer*)malloc(sizeof(struct stringBuffer));
    memcpy(ns->buffer, buff.buffer, buff.length);
    ns->length = buff.length;
    yylval.stringLit = ns;
    hasPlus = 1;
    hasOpenBracket = 1;
    strcpy(tempIdent, yytext + 1);
    hasCloseBracket = 1;
    printHandler((char*)"ESCAPED_STRING", getSafeCString(&buff));
    printHandler((char*)"BEGIN_INTERPOLATION", (char*)"$");
    printHandler((char*)"IDENTIFIER", yytext + 1);
    printHandler((char*)"END_INTERPOLATION", (char*)" ");
    clearStringBuffer(&buff);
    bufferString[0] = 0;
    return STRING_LITERAL;
}
<STRING>\$[^A-Za-z_\{\"]* {appendChars(&buff, yytext);}
<STRING>[\n\r] {printf("ERROR: no closing \" (double-quote) in STRING in line %d.\n", multilineBegin); line += 1; yy_pop_state(); return -1;}
<STRING>\" { 
    printHandler((char*)"ESCAPED STRING", getSafeCString(&buff)); 
    printHandler((char*)"ESCAPED_STRING_END", yytext);
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
        if (needsTokens) printf("(%c) - CHAR\n", buff.buffer[0]);
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
        printf("ERROR: Illegal escape \'\\u\' in line %d\n", line);
        return -1;
    }
    int value = strtol(yytext+2,NULL, 16);
    if (value > 127)
    {
        printf("ERROR: non-supported UNICODE character in line %d.\n", line);
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

<MODIFIER>[\r\n] {
    line = line + 1;
}

[\r\n] {
    line = line + 1;
    return ENDL;
}

. {
    bufferString[0] = 0;
    strcat(bufferString, yytext);
    printf("%s - UNRECOGNIZED TOKEN.\n", bufferString);
    return -1;
}

<MODIFIER><<EOF>> {
    BEGIN(OVER);
    printf("ERROR: Exprecting top level declaration in line %d.\n", multilineBegin);
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
		printf("The path to the input file is missing; use -h to get help using the utility.\n");
		return -1;
	}

    int needsDotCon = 0;
    int needsDotFile = 0;
	int needsHelp = 0;
    int opt = 0;

    while((opt = t_getopt(argc, argv, "cfht")) != -1)
    {
        switch(opt) 
        {
            case 'h':
                printf("%s", getHelp());
				needsHelp = 1;
                return 0;
                break;
            case 't':
                needsTokens = 1;
                break;
            case 'c':
                needsDotCon = 1;
                break;
            case 'f':
                needsDotFile = 1;
                break;
            case '?':
                printf("%c : unrecognized option; use -h to get help using the utility.\n", opt);
                return -1;
                break;
        }   
    }
	if (!needsHelp && argv[argc - 1][0] == '-')
	{
		printf("The path to the input file is missing; use -h to get help using the utility.\n");
		return -1;
	}

	yyin = fopen(argv[argc - 1], "r");

    printf("The parsing process has started.\n");

	yyparse();

    printf("The parsing process is completed.\n");

    if (needsDotCon || needsDotFile) 
    {   
        char * res = generateDotFromKotlinFile(root);
        if (needsDotFile)
        {
            FILE *f = fopen("result.gv", "w");
            fprintf(f, "%s", res);
            fclose(f);
        }
        if (needsDotCon)
        {
            printf("%s\n", res);
        }
    
    }

	return 0;
}

void printHandler(char* str, char * token)
{
    if(needsTokens != 0)
    {
        printf("(%s) - %s\n", token, str);
    }
}
