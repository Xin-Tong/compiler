%{
#include <math.h>
%}

DIGIT    [0-9]
ID       [a-z][a-z0-9]*

%%

{DIGIT}+    {
            printf("Token Type: INTLITERAL\nValue: %s\n",yytext);
            }

{DIGIT}+"."{DIGIT}*         {
                            printf("Token Type: FLOATLITERAL\nValue: %s\n",yytext);
                            }

":="|"!="|"="|"("|"<="|">="|")"|";"|"," printf("Token Type: OPERATOR\nValue: %s\n",yytext);
"+"|"-"|"*"|"/"|"<"|">"   printf("Token Type: OPERATOR\nValue: %s\n",yytext);

\"[^\"]*\"      {
                printf("Token Type: STRINGLITERAL\nValue: %s\n",yytext);
                }

PROGRAM|BEGIN|END|FUNCTION|READ|WRITE|IF|ELSE|ENDIF|WHILE|ENDWHILE|CONTINUE|BREAK|RETURN|INT|VOID|STRING|FLOAT  {
               printf("Token Type: KEYWORD\nValue: %s\n",yytext);
               }
(_|[a-zA-Z])(_|[a-zA-z]|[0-9])* {
                                printf("Token Type: IDENTIFIER\nValue: %s\n", yytext);
                                }
(-)(-).*        /*printf("byebye!\n");*/

[ \t\n]+          /* eat up whitespace */


.           printf( "Unrecognized character: %s\n", yytext);

%%

int main(int argc, char** argv)
{
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
            yyin = fopen( argv[0], "r" );
    else
            yyin = stdin;

    yylex();
}
