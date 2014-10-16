%{
#include "yacc.tab.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
extern char *yytext;
extern "C"
{
    int yylex(void);
}
%}

DIGIT    [0-9]
ID       [a-z][a-z0-9]*

%%

{DIGIT}+  {yylval.number=atoi(yytext); return INT;}

{DIGIT}+"."{DIGIT}*  {yylval.number=atoi(yytext); return FLOAT;}

"+"|"-"|"*"|"/"|"<"|">"|"("|")"|"="|";"|","|"["|"]"|"{"|"}" return *yytext;

":="	return FZ;
">="	return GE;
"<="	return LE;
"=="	return EQ;
"!="	return NE;
BEGIN	return BN;

\"[^\"]*\"      {yylval.string=strdup(yytext);return STRINGLITERAL;}

PROGRAM		return PROGRAM;
END		return END;
FUNCTION	return FUNCTION;
READ		return READ;
WRITE		return WRITE;
IF		return IF;
ELSE		return ELSE;
ENDIF		return ENDIF;
WHILE		return WHILE;
ENDWHILE	return ENDWHILE;
CONTINUE	return CONTINUE;
BREAK		return BREAK;
RETURN		return RETURN;
INT		return INT;
VOID		return VOID;
STRING		return STRING;
FLOAT		return FLOAT;

(_|[a-zA-Z])(_|[a-zA-z]|[0-9])* {yylval.string=strdup(yytext);return IDENTIFIER;}

(-)(-).*        /*printf("byebye!\n");*/

[ \t\n]+          /* eat up whitespace */

.           {printf( "Unrecognized character: %s\n", yytext );	exit(0);}
%%
