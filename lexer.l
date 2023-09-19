%option noyywrap
%option never-interactive

%x MULTILINE_COMMENT

DIGIT [0-9]

%{
    #include <stdio.h>
}%

%%

%{
    char bufferString[4096]; // Массив символов - буфер для строковых выражений.
}%

{// Блок ключевых слов.}

as
as\?
break
class
continue
do
else
for
fun
if
in
!in
interface
is
\!is
null
object
package
return
super
this
throw
try
typealias
val
var
when
while

true
false

\/\* {BEGIN(MULTILINE_COMMENT);}
<MULTILINE_COMMENT>[^*]+
<MULTILINE_COMMENT>"*"+[^*/] 
<MULTILINE_COMMENT>"*"+"/" {BEGIN(INITIAL);}

\/\/[^\n]*\n

\+ {printf("(%s) - OPERATOR\n", yytext);}
\- {printf("(%s) - OPERATOR\n", yytext);}
\* {printf("(%s) - OPERATOR\n", yytext);}
\/ {printf("(%s) - OPERATOR\n", yytext);}
= {printf("(%s) - OPERATOR\n", yytext);}
\% {printf("(%s) - OPERATOR\n", yytext);}
\/= {printf("(%s) - OPERATOR\n", yytext);}
\+= {printf("(%s) - OPERATOR\n", yytext);}
\*= {printf("(%s) - OPERATOR\n", yytext);}
\-= {printf("(%s) - OPERATOR\n", yytext);}
\%= {printf("(%s) - OPERATOR\n", yytext);}

%%