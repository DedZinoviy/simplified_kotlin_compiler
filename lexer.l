%option noyywrap
%option never-interactive

%x MULTILINE_COMMENT
%x COMMENT

DIGIT [0-9]


%{
    #include <stdio.h>
}%

%%

%%