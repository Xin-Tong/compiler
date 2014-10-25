#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>
#include <string.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20070509

#define YYEMPTY (-1)
#define yyclearin    (yychar = YYEMPTY)
#define yyerrok      (yyerrflag = 0)
#define YYRECOVERING (yyerrflag != 0)

extern int yyparse(void);

static int yygrowstack(void);
#define YYPREFIX "yy"
#line 2 "./src/yacc.y"
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <sstream>
#include <iostream>
#include "../src/symbol_table.h"
extern FILE *yyin;
using namespace std;

struct symbol* global_symbol = NULL;
int global_block_num = 1;
struct symbol* current_symbol = NULL;

void trim(string &_str);
void ProcessVar(string s1, string s2, struct symbol* _psym);
void ProcessString(string s1, string s2, struct symbol* _psym);

int yylex();

void yyerror(const char *str)
{
    fprintf(stderr,"Not accepted\n");
}

int yywrap()
{
    return 1;
}

main(int argc, char *argv[])
{
    FILE *fp=fopen(argv[1], "r");
    yyin = fp;
    yyparse();
}

#line 40 "./src/yacc.y"
typedef union
{
    int number;
	float ft;
    char * cstr;
} YYSTYPE;
#line 67 "y.tab.c"
#define STATE 257
#define NUMBER 258
#define WORD 259
#define GE 260
#define LE 261
#define EQ 262
#define NE 263
#define FZ 264
#define INTLITERAL 265
#define FLOATLITERAL 266
#define OPERATOR 267
#define STRINGLITERAL 268
#define KEYWORD 269
#define IDENTIFIER 270
#define PROGRAM 271
#define BN 272
#define END 273
#define FUNCTION 274
#define READ 275
#define WRITE 276
#define IF 277
#define ELSE 278
#define ENDIF 279
#define WHILE 280
#define ENDWHILE 281
#define CONTINUE 282
#define BREAK 283
#define RETURN 284
#define INT 285
#define VOID 286
#define STRING 287
#define FLOAT 288
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    6,    0,    1,    5,    5,    5,    5,    7,    7,    7,
    7,    9,    2,   10,    3,    3,   11,   11,    4,   12,
   12,   13,   14,   15,   15,    8,    8,   18,   16,   17,
   17,   19,   19,   19,   19,   20,   20,   20,   20,   20,
   20,   21,   21,   21,   21,   24,   22,   23,   25,   28,
   28,   28,   29,   29,   29,   30,   30,   30,   30,   30,
   30,   31,   32,   32,   33,   26,   36,   35,   35,   34,
   37,   37,   37,   37,   37,   37,   38,   27,   39,   39,
   40,   40,   41,   41,   41,   41,   41,   41,   41,   41,
   43,   42,   45,   44,   44,
};
short yylen[] = {                                         2,
    0,    6,    1,    2,    1,    1,    0,    2,    2,    1,
    1,    5,    1,    3,    1,    1,    1,    1,    2,    3,
    0,    2,    2,    3,    0,    2,    1,    0,    8,    3,
    2,    2,    1,    1,    0,    2,    2,    2,    1,    1,
    1,    1,    1,    1,    1,    4,    5,    5,    3,    3,
    3,    1,    3,    3,    1,    3,    1,    1,    1,    4,
    3,    2,    3,    0,    0,    8,    0,    3,    0,    3,
    1,    1,    1,    1,    1,    1,    0,    7,    2,    1,
    2,    0,    1,    1,    1,    1,    1,    1,    2,    2,
    0,    8,    0,    4,    0,
};
short yydefred[] = {                                      0,
    0,    0,    3,    0,    1,    0,    0,   16,    0,   15,
    0,    0,    0,    6,    0,    0,    0,   18,   17,    0,
    0,    0,    0,    2,    4,    8,    9,   26,   28,    0,
    0,   19,   14,    0,   13,    0,    0,    0,    0,   12,
   20,   31,    0,    0,    0,    0,   23,   30,    0,   22,
    0,    0,   65,   77,    0,    0,    0,    0,   34,    0,
    0,    0,   42,   43,   44,   45,    0,    0,    0,    0,
    0,   58,   59,    0,    0,    0,    0,   55,    0,   32,
   29,   36,   37,   38,   24,    0,    0,    0,    0,    0,
    0,   49,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   56,   61,    0,    0,    0,    0,   53,   54,
   46,   47,   48,   76,   75,   74,   71,   72,   73,    0,
    0,    0,    0,   62,   60,    0,    0,   82,    0,    0,
    0,   67,    0,    0,   78,   91,    0,    0,   84,   85,
   83,   86,   88,   81,   87,   63,    0,   66,    0,   89,
   90,   68,    0,    0,    0,    0,   93,    0,    0,   92,
    0,   94,
};
short yydgoto[] = {                                       2,
   75,   36,   11,   23,   12,    6,   57,   14,   15,   16,
   20,   32,   44,   45,   50,   17,   39,   34,   58,   59,
   60,   61,   62,   63,   64,   65,   66,  100,   77,   78,
  106,  124,   70,  101,  133,  147,  120,   71,  129,  130,
  144,  145,  149,  158,  159,
};
short yysindex[] = {                                   -262,
 -259,    0,    0, -245,    0, -199,  -82,    0, -259,    0,
 -259, -241, -221,    0, -159, -159, -221,    0,    0, -259,
 -206,   20,   33,    0,    0,    0,    0,    0,    0, -134,
 -259,    0,    0,  105,    0,   92,   20,  -41,  -92,    0,
    0,    0, -259,  141,  143, -145,    0,    0, -204,    0,
  165,  178,    0,    0,  -37,  -32,  -99,  -43,    0,  -99,
  -99,  -99,    0,    0,    0,    0,  143, -259, -259,  196,
  198,    0,    0,  -37,  201,   17,   40,    0,  -37,    0,
    0,    0,    0,    0,    0,  202,  208,  -37,  -37,  -33,
  -39,    0,  -37,  -37,  -37,  -37,   34,  194,  199,   11,
  218,  220,    0,    0,  180,  224,   40,   40,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -37,
 -145, -159,  -37,    0,    0,  111,  -12,    0,   -8,  -20,
  180,    0,  -10,  -20,    0,    0,  216,  217,    0,    0,
    0,    0,    0,    0,    0,    0, -145,    0,  237,    0,
    0,    0,  -37,  238, -159,    2,    0,   -1, -159,    0,
    2,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    8,    0,    0,    0,    0,
    0,    0,    9,    0, -115,  -84,   10,    0,    0,    0,
    0,  -34,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  -34,    0,    0,    0,
    0,    0,    0,    0,  243,   12,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -236,    0,    0, -166,
 -132, -129,    0,    0,    0,    0,  243,    0,    0,    0,
    0,    0,    0,    0,  -26,    0,  -21,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  245,    0,  -15,    7,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -180,  -68,    0,    0,    0,  246,   13,    0,    0,  -59,
  245,    0,    0,  -27,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   14,    0,    0,    0,
    0,    0,    0,    0, -174,   16,    0,    0, -174,    0,
   16,    0,
};
short yygindex[] = {                                      0,
   54,    0,   42,   50,    0,    0,   -2,   44,    0,    0,
    0,  251,    0,  240,  223,    0,    0,    0, -116,   76,
    0,  -40,  -13,   18,   49,    0,   87,    4,   79,  115,
    0,  160,    0,  -83,    0,    0,    0,    0,   15,  166,
    0,    0,    0,  135,    0,
};
#define YYTABLESIZE 296
short yytable[] = {                                      42,
   74,  104,   74,   13,  127,  102,   21,  103,    1,   93,
    3,   94,   26,   27,   57,   57,   57,   57,   57,   52,
   57,   52,   52,   52,   21,   50,    5,   50,   50,   50,
  152,   24,   57,   57,   57,   57,   33,   52,   52,   52,
   52,   33,   33,   50,   50,   50,   50,   51,   19,   51,
   51,   51,    7,   93,    4,   94,   25,   30,   76,   93,
   28,   94,   21,   31,   22,   51,   51,   51,   51,  154,
  117,  119,  118,   29,    7,   92,   93,   90,   94,   43,
    8,   95,   97,   10,   37,    8,   96,    9,   10,  139,
   43,   33,  111,  139,  105,   82,   47,   35,   35,   56,
   82,   82,   82,   82,   82,   82,   39,   82,   82,   82,
   56,   39,   39,   56,   56,   56,  140,   86,   87,  128,
  140,   22,   22,  126,    3,    8,  131,    9,   10,   51,
   52,   53,   80,   35,   54,   82,   83,   84,   55,    8,
   40,    9,   10,   41,   38,   40,   40,  141,   41,   41,
   40,  141,  128,   93,   11,   94,  128,   11,   11,   11,
   11,   11,   11,   11,   11,   11,   11,   11,   11,  156,
    3,  107,  108,  161,   56,   51,   52,   53,  142,   46,
   54,   48,  142,   56,   55,   10,   49,   56,   10,   10,
   10,   10,   10,   10,   10,   10,   10,   10,   10,   10,
   56,   82,    8,   18,   68,   10,   82,   82,   82,  109,
  110,   82,   82,   82,   82,   82,  143,   69,   80,   80,
  143,   80,   93,  123,   94,   72,   73,   72,   73,   81,
    3,   79,    3,   57,   57,   88,   57,   89,   52,   52,
   91,   52,   98,    8,   50,   50,   10,   50,   99,    3,
   79,   79,  112,   79,   51,   52,  136,  113,  121,   54,
  122,  137,  138,   55,  125,  132,   51,   51,  148,   51,
  114,  115,  135,  116,  150,  151,  153,  160,  155,  157,
    7,    5,   27,   25,   35,   64,   70,   41,   67,   85,
  146,   69,   35,  134,   95,  162,
};
short yycheck[] = {                                      41,
   40,   41,   40,    6,  121,   89,   41,   41,  271,   43,
  270,   45,   15,   16,   41,   42,   43,   44,   45,   41,
   47,   43,   44,   45,   59,   41,  272,   43,   44,   45,
  147,  273,   59,   60,   61,   62,  273,   59,   60,   61,
   62,  278,  279,   59,   60,   61,   62,   41,    7,   43,
   44,   45,  274,   43,    1,   45,   13,  264,   55,   43,
   17,   45,    9,   44,   11,   59,   60,   61,   62,  153,
   60,   61,   62,   20,  274,   59,   43,   74,   45,   38,
  285,   42,   79,  288,   31,  285,   47,  287,  288,  130,
   49,   59,   59,  134,   91,  270,   43,  278,  279,   46,
  275,  276,  277,  278,  279,  280,  273,  282,  283,  284,
   57,  278,  279,   60,   61,   62,  130,   68,   69,  122,
  134,   68,   69,  120,  270,  285,  123,  287,  288,  275,
  276,  277,   57,  268,  280,   60,   61,   62,  284,  285,
  273,  287,  288,  273,   40,  278,  279,  130,  278,  279,
   59,  134,  155,   43,  270,   45,  159,  273,  274,  275,
  276,  277,  278,  279,  280,  281,  282,  283,  284,  155,
  270,   93,   94,  159,  121,  275,  276,  277,  130,  272,
  280,   41,  134,  130,  284,  270,   44,  134,  273,  274,
  275,  276,  277,  278,  279,  280,  281,  282,  283,  284,
  147,  270,  285,  286,   40,  288,  275,  276,  277,   95,
   96,  280,  281,  282,  283,  284,  130,   40,  278,  279,
  134,  281,   43,   44,   45,  265,  266,  265,  266,  273,
  270,  264,  270,  260,  261,   40,  263,   40,  260,  261,
   40,  263,   41,  285,  260,  261,  288,  263,   41,  270,
  278,  279,   59,  281,  275,  276,  277,   59,   41,  280,
   41,  282,  283,  284,   41,  278,  260,  261,  279,  263,
  260,  261,  281,  263,   59,   59,   40,  279,   41,  278,
  273,  273,  273,   41,  273,   41,   41,   37,   49,   67,
  131,  279,  279,  128,  279,  161,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 288
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,
"';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"STATE","NUMBER","WORD","GE","LE","EQ","NE","FZ","INTLITERAL",
"FLOATLITERAL","OPERATOR","STRINGLITERAL","KEYWORD","IDENTIFIER","PROGRAM","BN",
"END","FUNCTION","READ","WRITE","IF","ELSE","ENDIF","WHILE","ENDWHILE",
"CONTINUE","BREAK","RETURN","INT","VOID","STRING","FLOAT",
};
char *yyrule[] = {
"$accept : program",
"$$1 :",
"program : PROGRAM id BN $$1 pgm_body END",
"id : IDENTIFIER",
"pgm_body : decl func_declarations",
"pgm_body : decl",
"pgm_body : func_declarations",
"pgm_body :",
"decl : string_decl decl",
"decl : var_decl decl",
"decl : var_decl",
"decl : string_decl",
"string_decl : STRING id FZ str ';'",
"str : STRINGLITERAL",
"var_decl : var_type id_list ';'",
"var_type : FLOAT",
"var_type : INT",
"any_type : var_type",
"any_type : VOID",
"id_list : id id_tail",
"id_tail : ',' id id_tail",
"id_tail :",
"param_decl_list : param_decl param_decl_tail",
"param_decl : var_type id",
"param_decl_tail : ',' param_decl param_decl_tail",
"param_decl_tail :",
"func_declarations : func_decl func_declarations",
"func_declarations : func_decl",
"$$2 :",
"func_decl : FUNCTION any_type id $$2 func_para BN func_body END",
"func_para : '(' param_decl_list ')'",
"func_para : '(' ')'",
"func_body : decl stmt_list",
"func_body : decl",
"func_body : stmt_list",
"func_body :",
"stmt_list : stmt stmt_list",
"stmt_list : read_stmt stmt_list",
"stmt_list : write_stmt stmt_list",
"stmt_list : stmt",
"stmt_list : read_stmt",
"stmt_list : write_stmt",
"stmt : assign_stmt",
"stmt : return_stmt",
"stmt : if_stmt",
"stmt : while_stmt",
"assign_stmt : id FZ expr ';'",
"read_stmt : READ '(' id_list ')' ';'",
"write_stmt : WRITE '(' id_list ')' ';'",
"return_stmt : RETURN expr ';'",
"expr : expr '+' factor",
"expr : expr '-' factor",
"expr : factor",
"factor : factor '*' postfix_expr",
"factor : factor '/' postfix_expr",
"factor : postfix_expr",
"postfix_expr : '(' expr ')'",
"postfix_expr : id",
"postfix_expr : INTLITERAL",
"postfix_expr : FLOATLITERAL",
"postfix_expr : id '(' expr_list ')'",
"postfix_expr : id '(' ')'",
"expr_list : expr expr_list_tail",
"expr_list_tail : ',' expr expr_list_tail",
"expr_list_tail :",
"$$3 :",
"if_stmt : IF $$3 '(' cond ')' func_body else_part ENDIF",
"$$4 :",
"else_part : ELSE $$4 func_body",
"else_part :",
"cond : expr compop expr",
"compop : '<'",
"compop : '>'",
"compop : '='",
"compop : NE",
"compop : LE",
"compop : GE",
"$$5 :",
"while_stmt : WHILE $$5 '(' cond ')' aug ENDWHILE",
"aug : decl aug_stmt_list",
"aug : aug_stmt_list",
"aug_stmt_list : aug_stmt_list aug_stmt",
"aug_stmt_list :",
"aug_stmt : assign_stmt",
"aug_stmt : read_stmt",
"aug_stmt : write_stmt",
"aug_stmt : return_stmt",
"aug_stmt : aug_if_stmt",
"aug_stmt : while_stmt",
"aug_stmt : CONTINUE ';'",
"aug_stmt : BREAK ';'",
"$$6 :",
"aug_if_stmt : IF $$6 '(' cond ')' aug aug_else_part ENDIF",
"$$7 :",
"aug_else_part : ELSE $$7 aug aug_else_part",
"aug_else_part :",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;
int      yyerrflag;
int      yychar;
short   *yyssp;
YYSTYPE *yyvsp;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static short   *yyss;
static short   *yysslim;
static YYSTYPE *yyvs;
static int      yystacksize;
#line 276 "./src/yacc.y"

void trim(string &_str)
{
    if (!_str.empty())
    {
        _str.erase(0, _str.find_first_not_of(" "));
        _str.erase(_str.find_last_not_of(" ") + 1);
    }
}

void ProcessVar(string s1, struct symbol* _psym)
{  
    std::size_t found_first_whitespace = s1.find(" ");
    string str_type = s1.substr(0, found_first_whitespace);
    std::size_t found = s1.rfind(";");
    s1.replace(found, 2, ",,"); 
    string s2 = s1.substr(found_first_whitespace+1, s1.length());
    std::size_t found_col = s2.find(",");
    do
	{       
		string str_temp = s2.substr(0,found_col);
        trim(str_temp);  //remove the whitespace
//		cout<<str_temp<<"  "<<str_type<<endl;
        Variable_Add(_psym, str_temp, str_type, "NULL");
        s2 = s2.substr(found_col+1);
        found_col = s2.find(",");
	}
    while(found_col != s2.rfind(","));
}

void ProcessString(string s1, string s2, struct symbol* _psym)
{
    trim(s1);
    trim(s2);
    Variable_Add(_psym, s1, "STRING", s2);
}

#line 450 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = yyssp - yyss;
    newss = (yyss != 0)
          ? (short *)realloc(yyss, newsize * sizeof(*newss))
          : (short *)malloc(newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    yyss  = newss;
    yyssp = newss + i;
    newvs = (yyvs != 0)
          ? (YYSTYPE *)realloc(yyvs, newsize * sizeof(*newvs))
          : (YYSTYPE *)malloc(newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse(void)
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

#ifdef lint
    goto yyerrlab;
#endif

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 91 "./src/yacc.y"
{
                        string str("GLOBAL"); 
                        global_symbol = Sym_Alloc(str, NULL, "GLOBAL", "GLOBAL"); 
                        current_symbol = global_symbol;
					}
break;
case 2:
#line 95 "./src/yacc.y"
{Print_Symbol(global_symbol);}
break;
case 12:
#line 108 "./src/yacc.y"
{ProcessString(string(yyvsp[-3].cstr), string(yyvsp[-1].cstr), current_symbol);}
break;
case 14:
#line 112 "./src/yacc.y"
{ProcessVar(string(yyvsp[-2].cstr), current_symbol);}
break;
case 23:
#line 121 "./src/yacc.y"
{
						string stype(yyvsp[-1].cstr); 
						string sid(yyvsp[0].cstr); 
						size_t blank_pos = stype.find(" "); stype.erase(blank_pos); 
						trim(stype); 
						trim(sid); 
						Variable_Add(current_symbol, sid, stype, "NULL"); 
					}
break;
case 28:
#line 134 "./src/yacc.y"
{
						string str(yyvsp[0].cstr); 
						struct symbol* sym = Sym_Alloc(str, global_symbol, "LOCAL", "FUNCTION"); 
						current_symbol = sym;
					}
break;
case 29:
#line 138 "./src/yacc.y"
{current_symbol = current_symbol->father;}
break;
case 65:
#line 201 "./src/yacc.y"
{
						stringstream ss; 
						ss << global_block_num; global_block_num++; 
						string str; 
						ss>>str; 
						str = "BLOCK " + str; 
						struct symbol* sym = Sym_Alloc(str, current_symbol, "LOCAL", "BLOCK"); 
						current_symbol = sym;
					}
break;
case 66:
#line 209 "./src/yacc.y"
{current_symbol = current_symbol->father;}
break;
case 67:
#line 211 "./src/yacc.y"
{
						current_symbol = current_symbol->father; 
						stringstream ss; 
						ss << global_block_num; 
						global_block_num++; 
						string str; 
						ss>>str; 
						str = "BLOCK " + str; 
						struct symbol* sym = Sym_Alloc(str, current_symbol, "LOCAL", "BLOCK"); 
						current_symbol = sym;
					}
break;
case 77:
#line 227 "./src/yacc.y"
{
						stringstream ss; 
						ss << global_block_num; 
						global_block_num++; 
						string str; 
						ss>>str; 
						str = "BLOCK " + str; 
						struct symbol* sym = Sym_Alloc(str, current_symbol, "LOCAL", "BLOCK"); 
						current_symbol = sym;
					}
break;
case 78:
#line 236 "./src/yacc.y"
{current_symbol = current_symbol->father;}
break;
case 91:
#line 253 "./src/yacc.y"
{
						stringstream ss; 
						ss << global_block_num; global_block_num++; 
						string str; 
						ss>>str; 
						str = "BLOCK " + str; 
						struct symbol* sym = Sym_Alloc(str, current_symbol, "LOCAL", "BLOCK"); 
						current_symbol = sym;
					}
break;
case 92:
#line 261 "./src/yacc.y"
{current_symbol = current_symbol->father;}
break;
case 93:
#line 263 "./src/yacc.y"
{
						current_symbol = current_symbol->father; 
						stringstream ss; 
						ss << global_block_num; 
						global_block_num++; 
						string str; 
						ss>>str; 
						str = "BLOCK " + str; 
						struct symbol* sym = Sym_Alloc(str, current_symbol, "LOCAL", "BLOCK"); 
						current_symbol = sym;
					}
break;
#line 751 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    return (1);

yyaccept:
    return (0);
}
