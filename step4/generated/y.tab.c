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
#include "../src/ast.h"
extern FILE *yyin;
using namespace std;

struct symbol* global_symbol = NULL;
int global_block_num = 1;
struct symbol* current_symbol = NULL;
Global *root = NULL;
int global_temp_reg_count = 1;

void trim(string &_str);
void ProcessVar(string s1, string s2, struct symbol* _psym);
void ProcessString(string s1, string s2, struct symbol* _psym);
struct variable* LookUp_Global(string _name);
void process_read(list<Statement*> *_pStatementList, string _var);
void process_write(list<Statement*> *_pStatementList, string _var);
void process_rw_list(list<Statement*> *rw_stmts, list<Statement*> *stmts);

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

#line 47 "./src/yacc.y"
typedef union
{
    	int number;
	float ft;
    	char * cstr;
	ExpressionNode *pExpNode;
	ExpressionNodeList *pExpNodeList;
	AssignStatement* pAssign;
	Statement *pState;
	ReturnStatement *pRtnState;
	list<Statement*> *pStateList;
	Function *pFunc;
	list<Function*> *pFuncList;
	Global *pGlobal;
} YYSTYPE;
#line 83 "y.tab.c"
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
   23,    0,    1,   22,   22,   22,   22,   24,   24,   24,
   24,   25,    2,   26,    3,    3,    4,    4,    5,   27,
   27,   28,   29,   30,   30,   11,   11,   32,   10,   31,
   31,   12,   12,   12,   12,    9,    9,    9,    9,    9,
    9,   13,   13,   13,   13,   14,   15,   16,   19,    6,
    6,    6,    7,    7,    7,    8,    8,    8,    8,    8,
    8,   17,   18,   18,   33,   20,   36,   35,   35,   34,
   37,   37,   37,   37,   37,   37,   38,   21,   39,   39,
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
    0,    0,    6,    0,    0,    0,    0,   18,   17,    0,
    0,    0,    0,   26,    2,    4,    8,    9,   28,    0,
    0,   19,   14,    0,   13,    0,    0,    0,    0,   12,
   20,   31,    0,    0,    0,    0,   23,   30,    0,   22,
    0,    0,   65,   77,    0,    0,   34,    0,    0,   42,
    0,    0,   43,   44,   45,    0,    0,    0,    0,    0,
    0,   58,   59,    0,    0,    0,    0,   55,    0,   29,
   36,   37,   38,   32,   24,    0,    0,    0,    0,    0,
    0,   49,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   56,   61,    0,    0,    0,    0,   53,   54,
   46,   47,   48,   76,   75,   74,   71,   72,   73,    0,
    0,    0,    0,   62,   60,    0,    0,   82,    0,    0,
    0,   67,    0,    0,   78,   91,    0,    0,   83,   84,
   85,   86,   88,   81,   87,   63,    0,   66,    0,   89,
   90,   68,    0,    0,    0,    0,   93,    0,    0,   92,
    0,   94,
};
short yydgoto[] = {                                       2,
   75,   36,   11,   20,   23,  100,   77,   78,   57,   12,
   13,   58,   59,   60,   61,   62,  106,  124,   63,   64,
   65,   14,    6,   66,   16,   17,   32,   44,   45,   50,
   39,   34,   70,  101,  133,  147,  120,   71,  129,  130,
  144,  145,  149,  158,  159,
};
short yysindex[] = {                                   -257,
 -233,    0,    0, -208,    0,  -64, -141,    0, -233,    0,
 -233, -199,    0, -174, -199, -105, -105,    0,    0, -233,
 -126,  119,  109,    0,    0,    0,    0,    0,    0,  -89,
 -233,    0,    0,  147,    0,  146,  119,  -41,  -61,    0,
    0,    0, -233,  176,  178, -145,    0,    0, -227,    0,
  180,  185,    0,    0,  -37,  -23,    0,  -43, -188,    0,
 -188, -188,    0,    0,    0, -188,  178, -233, -233,  192,
  196,    0,    0,  -37,  198,  -32,   37,    0,  -37,    0,
    0,    0,    0,    0,    0,  202,  211,  -37,  -37,   76,
  -39,    0,  -37,  -37,  -37,  -37,   17,  203,  204,   11,
  220,  223,    0,    0,  213,  224,   37,   37,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -37,
 -145, -105,  -37,    0,    0,   91,  -12,    0,   -8,  -68,
  213,    0,  -10,  -68,    0,    0,  216,  217,    0,    0,
    0,    0,    0,    0,    0,    0, -145,    0,  237,    0,
    0,    0,  -37,  238, -105,    2,    0,   -1, -105,    0,
    2,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    8,    0,    0,    0,    0,
    0,    9,    0,    0,   10, -172, -124,    0,    0,    0,
    0,  -34,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  -34,    0,    0,    0,
    0,    0,    0,    0,  243,   12,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -269,    0,
 -112,  -60,    0,    0,    0,  -24,  243,    0,    0,    0,
    0,    0,    0,    0,  -26,    0,  -21,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  245,    0,  -15,    7,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -185,  -84,    0,    0,    0,  246,   13,    0,    0,  -75,
  245,    0,    0,  -28,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   14,    0,    0,    0,
    0,    0,    0,    0, -106,   15,    0,    0, -106,    0,
   15,    0,
};
short yygindex[] = {                                      0,
   54,    0,   42,    0,  121,    4,  101,  164,   67,    0,
  150, -116,    0, -122,  -77,  -53,    0,  157,  -44,    0,
  -16,    0,    0,   26,    0,    0,  252,    0,  241,  228,
    0,    0,    0,  -83,    0,    0,    0,    0,  -18,  163,
    0,    0,    0,  135,    0,
};
#define YYTABLESIZE 296
short yytable[] = {                                      42,
   74,  104,   74,   39,  127,  102,   21,  139,   39,   39,
   93,  139,   94,    1,   57,   57,   57,   57,   57,   52,
   57,   52,   52,   52,   21,   50,   92,   50,   50,   50,
  152,   15,   57,   57,   57,   57,    3,   52,   52,   52,
   52,   27,   28,   50,   50,   50,   50,   51,   19,   51,
   51,   51,  140,   93,    4,   94,  140,    8,   76,   93,
   10,   94,   21,    5,   22,   51,   51,   51,   51,  154,
  117,  119,  118,   29,    7,  111,  141,   90,   95,   43,
  141,    3,   97,   96,   37,  142,   51,   52,   53,  142,
   43,   54,   35,   35,  105,   55,   47,   11,   25,   56,
   11,   11,   11,   11,   11,   11,   11,   11,   11,   11,
   11,   11,   56,  143,   56,   56,  103,  143,   93,   56,
   94,   22,   22,  126,    3,   81,  131,   82,   83,   51,
   52,   53,   84,   93,   54,   94,  156,   30,   55,    8,
  161,    9,   10,    8,   18,   10,   10,  128,   10,   10,
   10,   10,   10,   10,   10,   10,   10,   10,   10,   10,
   40,   24,   31,   82,   26,   40,   40,   33,   82,   82,
   82,   82,   82,   82,   56,   82,   82,   82,   35,    8,
  128,    9,   10,   56,  128,   82,   38,   56,   86,   87,
   82,   82,   82,  107,  108,   82,   82,   82,   82,   82,
   56,    3,   80,   80,   40,   80,   51,   52,  136,    7,
   46,   54,   41,  137,  138,   55,   48,   41,   41,   68,
    8,   49,    9,   10,   69,   72,   73,   72,   73,   80,
    3,   88,    3,   57,   57,   89,   57,   91,   52,   52,
   79,   52,   98,    8,   50,   50,   10,   50,   33,   79,
   79,   99,   79,   33,   33,   93,  123,   94,  109,  110,
  121,  112,  113,  122,  125,  132,   51,   51,  148,   51,
  114,  115,  135,  116,  150,  151,  153,  160,  155,  157,
    7,   27,    5,   25,   35,   64,   70,  146,   41,   67,
  134,   69,   35,   95,   85,  162,
};
short yycheck[] = {                                      41,
   40,   41,   40,  273,  121,   89,   41,  130,  278,  279,
   43,  134,   45,  271,   41,   42,   43,   44,   45,   41,
   47,   43,   44,   45,   59,   41,   59,   43,   44,   45,
  147,    6,   59,   60,   61,   62,  270,   59,   60,   61,
   62,   16,   17,   59,   60,   61,   62,   41,    7,   43,
   44,   45,  130,   43,    1,   45,  134,  285,   55,   43,
  288,   45,    9,  272,   11,   59,   60,   61,   62,  153,
   60,   61,   62,   20,  274,   59,  130,   74,   42,   38,
  134,  270,   79,   47,   31,  130,  275,  276,  277,  134,
   49,  280,  278,  279,   91,  284,   43,  270,  273,   46,
  273,  274,  275,  276,  277,  278,  279,  280,  281,  282,
  283,  284,   59,  130,   61,   62,   41,  134,   43,   66,
   45,   68,   69,  120,  270,   59,  123,   61,   62,  275,
  276,  277,   66,   43,  280,   45,  155,  264,  284,  285,
  159,  287,  288,  285,  286,  270,  288,  122,  273,  274,
  275,  276,  277,  278,  279,  280,  281,  282,  283,  284,
  273,   12,   44,  270,   15,  278,  279,   59,  275,  276,
  277,  278,  279,  280,  121,  282,  283,  284,  268,  285,
  155,  287,  288,  130,  159,  270,   40,  134,   68,   69,
  275,  276,  277,   93,   94,  280,  281,  282,  283,  284,
  147,  270,  278,  279,   59,  281,  275,  276,  277,  274,
  272,  280,  273,  282,  283,  284,   41,  278,  279,   40,
  285,   44,  287,  288,   40,  265,  266,  265,  266,  273,
  270,   40,  270,  260,  261,   40,  263,   40,  260,  261,
  264,  263,   41,  285,  260,  261,  288,  263,  273,  278,
  279,   41,  281,  278,  279,   43,   44,   45,   95,   96,
   41,   59,   59,   41,   41,  278,  260,  261,  279,  263,
  260,  261,  281,  263,   59,   59,   40,  279,   41,  278,
  273,  273,  273,   41,  273,   41,   41,  131,   37,   49,
  128,  279,  279,  279,   67,  161,
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
#line 367 "./src/yacc.y"

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
	std::size_t pos = s1.find(":=");
	string s1_sub = s1.substr(0, pos);
	trim(s1_sub);
    trim(s2);
    Variable_Add(_psym, s1_sub, "STRING", s2);
}

struct variable* LookUp_Global(string _name)
{
	bool signal = false;
	string str_val;
	vector<struct variable*>::iterator iter;
	for(iter = global_symbol->var.begin(); iter != global_symbol->var.end(); iter ++)
	{
		str_val = (*iter)->name;
		if(_name == str_val)
		{
			signal = true;
			return (*iter);
		}
	}
	return NULL;
}

void process_read(list<Statement*> *_pStatementList, string _var)
{
	std::size_t pos = _var.find(";");
    string s2 = _var.substr(0,pos); //remove the ;
	pos = s2.rfind(")");
	s2.replace(pos, string::npos, ",");
	
	pos = s2.find(",");
	while(pos != string::npos)
	{
		string str = s2.substr(0, pos);
		trim(str);
		
		struct variable* info = LookUp_Global(str);
		if(info == NULL)
		{
			printf("Read Can't find varibale!\n");
			exit(0);
		}
		else
		{
			_pStatementList->push_back(new ReadStatement(info->name, info->type));
		}
		
		s2 = s2.substr(pos+1);
		pos = s2.find(",");
	}
}

void process_write(list<Statement*> *_pStatementList, string _var)
{
	std::size_t pos = _var.find(";");
    string s2 = _var.substr(0,pos); //remove the ;
	pos = s2.rfind(")");
	s2.replace(pos, string::npos, ",");
	
	pos = s2.find(",");
	while(pos != string::npos)
	{
		string str = s2.substr(0, pos);
		trim(str);
		
		struct variable* info = LookUp_Global(str);
		if(info == NULL)
		{
			printf("Write Can't find varibale!  %s\n", str.c_str());
			exit(0);
		}
		else
		{
			_pStatementList->push_back(new WriteStatement(info->name, info->type));
		}
		
		s2 = s2.substr(pos+1);
		pos = s2.find(",");
	}
}

void process_rw_list(list<Statement*> *_pStatementList1, list<Statement*> *_pStatementList2)
{
	list<Statement*>::iterator iter; 
	for(iter = _pStatementList2->begin(); iter != _pStatementList2->end(); ++iter) 
	{
		_pStatementList1->push_back(*iter);
	}
}



#line 555 "y.tab.c"
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
#line 126 "./src/yacc.y"
{
                        string str("GLOBAL"); 
                        global_symbol = Sym_Alloc(str, NULL, "GLOBAL", "GLOBAL"); 
                        current_symbol = global_symbol;
					}
break;
case 2:
#line 131 "./src/yacc.y"
{
						root = new Global(yyvsp[-1].pFuncList);
						root->GenIR();
						printf(";IR code\n");
						printf(";LABEL main\n");
						printf(";LINK\n");
						root->PrintIR();					
						printf(";RET\n");
						printf(";tiny code\n");
						string s_type;
						vector<variable*>::iterator iter;
						for(iter = global_symbol->var.begin(); iter != global_symbol->var.end(); iter ++)
						{
							s_type = (*iter)->type;
							if (s_type == "INT" || s_type == "FLOAT")
							{
								printf("var %s\n", (*iter)->name);
							}
							else
							{
								printf("str %s %s\n", (*iter)->name, (*iter)->value);
							}
						}
						root->PrintTiny();
						printf("sys halt\n");
/*						Print_Symbol(global_symbol);*/
					}
break;
case 4:
#line 160 "./src/yacc.y"
{yyval.pFuncList = yyvsp[0].pFuncList;}
break;
case 5:
#line 161 "./src/yacc.y"
{yyval.pFuncList = new list<Function*>();}
break;
case 6:
#line 162 "./src/yacc.y"
{yyval.pFuncList = yyvsp[0].pFuncList;}
break;
case 7:
#line 163 "./src/yacc.y"
{yyval.pFuncList = new list<Function*>();}
break;
case 12:
#line 170 "./src/yacc.y"
{ProcessString(string(yyvsp[-3].cstr), string(yyvsp[-1].cstr), current_symbol);}
break;
case 14:
#line 174 "./src/yacc.y"
{ProcessVar(string(yyvsp[-2].cstr), current_symbol);}
break;
case 23:
#line 183 "./src/yacc.y"
{
						string stype(yyvsp[-1].cstr); 
						string sid(yyvsp[0].cstr); 
						size_t blank_pos = stype.find(" "); stype.erase(blank_pos); 
						trim(stype); 
						trim(sid); 
						Variable_Add(current_symbol, sid, stype, "NULL"); 
					}
break;
case 26:
#line 194 "./src/yacc.y"
{ yyvsp[0].pFuncList->push_front(yyvsp[-1].pFunc); yyval.pFuncList = yyvsp[0].pFuncList;}
break;
case 27:
#line 195 "./src/yacc.y"
{yyval.pFuncList = new list<Function*>(); yyval.pFuncList->push_back(yyvsp[0].pFunc);}
break;
case 28:
#line 197 "./src/yacc.y"
{
						string str(yyvsp[0].cstr); 
						struct symbol* sym = Sym_Alloc(str, global_symbol, "LOCAL", "FUNCTION"); 
						current_symbol = sym;
					}
break;
case 29:
#line 203 "./src/yacc.y"
{
						current_symbol = current_symbol->father;
						yyval.pFunc = new Function(yyvsp[-1].pStateList, yyvsp[-6].cstr, yyvsp[-5].cstr);
					}
break;
case 32:
#line 210 "./src/yacc.y"
{yyval.pStateList = yyvsp[0].pStateList;}
break;
case 33:
#line 211 "./src/yacc.y"
{yyval.pStateList = new list<Statement*>();}
break;
case 34:
#line 212 "./src/yacc.y"
{yyval.pStateList = yyvsp[0].pStateList;}
break;
case 35:
#line 213 "./src/yacc.y"
{yyval.pStateList = new list<Statement*>();}
break;
case 36:
#line 216 "./src/yacc.y"
{yyvsp[0].pStateList->push_front(yyvsp[-1].pState); yyval.pStateList = yyvsp[0].pStateList;}
break;
case 37:
#line 217 "./src/yacc.y"
{process_rw_list(yyvsp[-1].pStateList, yyvsp[0].pStateList); yyval.pStateList = yyvsp[-1].pStateList;}
break;
case 38:
#line 218 "./src/yacc.y"
{process_rw_list(yyvsp[-1].pStateList, yyvsp[0].pStateList); yyval.pStateList = yyvsp[-1].pStateList;}
break;
case 39:
#line 219 "./src/yacc.y"
{yyval.pStateList = new list<Statement*>(); yyval.pStateList->push_back(yyvsp[0].pState);}
break;
case 40:
#line 220 "./src/yacc.y"
{yyval.pStateList = yyvsp[0].pStateList;}
break;
case 41:
#line 221 "./src/yacc.y"
{yyval.pStateList = yyvsp[0].pStateList;}
break;
case 42:
#line 223 "./src/yacc.y"
{yyval.pState = yyvsp[0].pAssign;}
break;
case 43:
#line 224 "./src/yacc.y"
{yyval.pState = yyvsp[0].pRtnState;}
break;
case 46:
#line 230 "./src/yacc.y"
{
						string str(yyvsp[-3].cstr);
						trim(str); 
						std::size_t pos = str.find(":=");
						string str_sub = str.substr(0, pos);
						trim(str_sub);
						yyval.pAssign = new AssignStatement(str_sub, yyvsp[-1].pExpNode);
					}
break;
case 47:
#line 238 "./src/yacc.y"
{yyval.pStateList = new list<Statement*>(); process_read(yyval.pStateList, yyvsp[-2].cstr);}
break;
case 48:
#line 239 "./src/yacc.y"
{yyval.pStateList = new list<Statement*>(); process_write(yyval.pStateList, yyvsp[-2].cstr);}
break;
case 49:
#line 240 "./src/yacc.y"
{yyval.pRtnState = new ReturnStatement(yyvsp[-1].pExpNode);}
break;
case 50:
#line 257 "./src/yacc.y"
{yyval.pExpNode = new AddNode(yyvsp[-2].pExpNode, yyvsp[0].pExpNode);}
break;
case 51:
#line 258 "./src/yacc.y"
{yyval.pExpNode = new SubNode(yyvsp[-2].pExpNode, yyvsp[0].pExpNode);}
break;
case 52:
#line 259 "./src/yacc.y"
{yyval.pExpNode = yyvsp[0].pExpNode;}
break;
case 53:
#line 260 "./src/yacc.y"
{yyval.pExpNode = new MultNode(yyvsp[-2].pExpNode, yyvsp[0].pExpNode);}
break;
case 54:
#line 261 "./src/yacc.y"
{yyval.pExpNode = new DivNode(yyvsp[-2].pExpNode, yyvsp[0].pExpNode);}
break;
case 55:
#line 262 "./src/yacc.y"
{yyval.pExpNode = yyvsp[0].pExpNode;}
break;
case 56:
#line 263 "./src/yacc.y"
{yyval.pExpNode = yyvsp[-1].pExpNode;}
break;
case 57:
#line 265 "./src/yacc.y"
{
						string str(yyvsp[0].cstr);
						std::size_t pos = str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
						string s2 = str.substr(0,pos);
						struct variable* info = LookUp_Global(s2);
						if(info == NULL)
						{
							printf("PostFix Can't find varibale!\n");
							exit(0);
						}
						else
						{
							string name(info->name);
							string type(info->type);
							yyval.pExpNode = new IDNode(name, type);
						}
					}
break;
case 58:
#line 282 "./src/yacc.y"
{yyval.pExpNode = new ExpressionNode(yyvsp[0].number, "INT");}
break;
case 59:
#line 283 "./src/yacc.y"
{yyval.pExpNode = new ExpressionNode(yyvsp[0].ft, "FLOAT");}
break;
case 60:
#line 284 "./src/yacc.y"
{yyval.pExpNode = new ExpressionNode();}
break;
case 61:
#line 285 "./src/yacc.y"
{yyval.pExpNode = new ExpressionNode();}
break;
case 62:
#line 286 "./src/yacc.y"
{yyvsp[0].pExpNodeList->pExpNodes->push_front(yyvsp[-1].pExpNode);yyval.pExpNodeList = yyvsp[0].pExpNodeList;}
break;
case 63:
#line 287 "./src/yacc.y"
{yyvsp[0].pExpNodeList->pExpNodes->push_front(yyvsp[-1].pExpNode);yyval.pExpNodeList = yyvsp[0].pExpNodeList;}
break;
case 64:
#line 288 "./src/yacc.y"
{yyval.pExpNodeList = new ExpressionNodeList(new list<ExpressionNode*>());}
break;
case 65:
#line 292 "./src/yacc.y"
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
#line 300 "./src/yacc.y"
{current_symbol = current_symbol->father;}
break;
case 67:
#line 302 "./src/yacc.y"
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
#line 318 "./src/yacc.y"
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
#line 327 "./src/yacc.y"
{current_symbol = current_symbol->father;}
break;
case 91:
#line 344 "./src/yacc.y"
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
#line 352 "./src/yacc.y"
{current_symbol = current_symbol->father;}
break;
case 93:
#line 354 "./src/yacc.y"
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
#line 1056 "y.tab.c"
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
