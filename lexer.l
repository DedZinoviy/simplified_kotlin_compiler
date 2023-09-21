%option noyywrap
%option never-interactive

%x MULTILINE_COMMENT

DIGIT [0-9]

%{
    #include <stdio.h>
    #include <string.h>
}%

%%

%{
    char bufferString[4096]; // Массив символов - буфер для строковых выражений.
}%

{// Блок ключевых слов.}

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

\/\/[^\n]*\n {bufferString[0] = 0; strcat(bufferString, yytext); printf("(%s) - COMMENT\n", buffer);}

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

([1-9](_*[0-9]*)*)|0

%%
