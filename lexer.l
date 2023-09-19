%option noyywrap
%option never-interactive

%x MULTILINE_COMMENT

DIGIT [0-9]

%{
    #include <stdio.h>
}%

%%

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