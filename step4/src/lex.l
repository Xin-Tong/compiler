%{
#include "../src/ast.h"
#include "y.tab.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
extern char *yytext;
%}

DIGIT    [0-9]
ID       [a-z][a-z0-9]*

%%

{DIGIT}+  {yylval.number=atoi(yytext); return INTLITERAL;}

{DIGIT}+"."{DIGIT}*  {yylval.ft=atof(yytext); return FLOATLITERAL;}


":="	{yylval.cstr = yytext; return FZ;}
">="	return GE;
"<="	return LE;
"=="	return EQ;
"!="	return NE;
BEGIN	return BN;

\"[^\"]*\"      {yylval.cstr=strdup(yytext);return STRINGLITERAL;}

"+"|"-"|"*"|"/"|"<"|">"|"("|")"|"="|";"|","|"["|"]"|"{"|"}" return *yytext;

PROGRAM		return PROGRAM;
END			return END;
FUNCTION	return FUNCTION;
READ		return READ;
WRITE		return WRITE;
IF			return IF;
ELSE		return ELSE;
ENDIF		return ENDIF;
WHILE		return WHILE;
ENDWHILE	return ENDWHILE;
CONTINUE	return CONTINUE;
BREAK		return BREAK;
RETURN		return RETURN;
INT			{yylval.cstr = yytext; return INT;}
VOID		{yylval.cstr = yytext; return VOID;}
STRING		{yylval.cstr = yytext; return STRING;}
FLOAT		{yylval.cstr = yytext; return FLOAT;}

(_|[a-zA-Z])(_|[a-zA-z]|[0-9])* {yylval.cstr=yytext;return IDENTIFIER;}

(-)(-).*        /*printf("byebye!\n");*/

[ \t\n]+          /* eat up whitespace */

.           {printf( "Unrecognized character: %s\n", yytext );	exit(0);}
%%
