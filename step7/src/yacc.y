%{
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

void trim(string &_str);
void ProcessVar(string s1, string s2, struct symbol* _psym);
void ProcessString(string s1, string s2, struct symbol* _psym);
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

%}

%union
{
    int number;
	float ft;
    char * cstr;
	ExpressionNode *pExpNode;
	ExpressionNodeList *pExpNodeList;
	AssignStatement* pAssign;
	IfStatement* pIf;
	Statement *pState;
	ReturnStatement *pRtnState;
	list<Statement*> *pStateList;
	Function *pFunc;
	list<Function*> *pFuncList;
	Global *pGlobal;
}

%token <number> STATE
%token <number> NUMBER
%token <string> WORD

%token <cstr> GE
%token <cstr> LE
%token <cstr> EQ
%token <cstr> NE
%token FZ

%token <cstr> INTLITERAL
%token <cstr> FLOATLITERAL 
%token OPERATOR 
%token <cstr>STRINGLITERAL 
%token KEYWORD 
%token <cstr>IDENTIFIER
%token PROGRAM 
%token BN 
%token END 
%token FUNCTION 
%token READ 
%token WRITE 
%token IF 
%token ELSE 
%token ENDIF 
%token WHILE 
%token ENDWHILE 
%token CONTINUE 
%token BREAK 
%token RETURN 
%token <cstr> INT 
%token <cstr> VOID 
%token <cstr> STRING 
%token <cstr> FLOAT

%type <cstr> id
%type <cstr> str
%type <cstr> var_type
%type <cstr> any_type
%type <cstr> id_list
%type <pExpNode> expr
%type <pExpNode> factor
%type <pExpNode> postfix_expr
%type <pExpNode> cond
%type <cstr> compop
%type <pStateList> stmt_list
%type <pFunc> func_decl
%type <pFuncList> func_declarations 
%type <pStateList> func_body
%type <pStateList> else_part
%type <pState> stmt
%type <pAssign> assign_stmt
%type <pStateList> read_stmt
%type <pStateList> write_stmt
%type <pExpNodeList> expr_list
%type <pExpNodeList> expr_list_tail
%type <pRtnState> return_stmt
%type <pState> if_stmt
%type <pStateList> else_part
%type <pStateList> aug 
%type <pState> aug_stmt
%type <pState> aug_if_stmt
%type <pStateList> aug_else_part
%type <pStateList> aug_stmt_list
%type <pState> while_stmt
%type <pGlobal> program
%type <pFuncList> pgm_body

%%
/* Program */
program				: PROGRAM id BN 
					{
                        string str("GLOBAL"); 
                        global_symbol = Sym_Alloc(str, NULL, "GLOBAL", "GLOBAL"); 
						global_symbol->num_of_locals = 0;
						global_symbol->num_of_params = 0;
                        current_symbol = global_symbol;
					} 
					pgm_body END 
					{
						root = new Global($5, global_symbol);
						root->GenIR();
						printf(";IR code\n");
						root->PrintIR();	
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
					};
id					: IDENTIFIER;
pgm_body			: decl func_declarations {$$ = $2;}
					| decl {$$ = new list<Function*>();}
					| func_declarations {$$ = $1;}
					| {$$ = new list<Function*>();};
decl				: string_decl decl 
					| var_decl decl 
					| var_decl
					| string_decl;

/* Global String Declaration */
string_decl         : STRING id FZ str ";" {ProcessString(string($2), string($4), current_symbol);};
str					: STRINGLITERAL;

/* Variable Declaration */
var_decl			: var_type id_list ";" {ProcessVar(string($1), current_symbol);};
var_type			: FLOAT | INT;
any_type			: var_type | VOID; 
id_list				: id id_tail;
id_tail				: "," id id_tail | ;

/* Function Paramater List */
param_decl_list		: param_decl param_decl_tail ;
param_decl			: var_type id 
					{
						string stype($1); 
						string sid($2); 
						size_t blank_pos = stype.find(" "); 
						stype.erase(blank_pos); 
						trim(stype); 
						trim(sid); 
						Variable_Add(current_symbol, sid, stype, "NULL", "param");
					};
param_decl_tail		: "," param_decl param_decl_tail | ;

/* Function Declarations */
func_declarations	: func_decl func_declarations { $2->push_front($1); $$ = $2;}
					| func_decl {$$ = new list<Function*>(); $$->push_back($1);};
func_decl			: FUNCTION any_type id 
					{
						string str($3); 
						struct symbol* sym = Sym_Alloc(str, global_symbol, "LOCAL", "FUNCTION");
						sym->num_of_locals = 0;
						sym->num_of_params = 0;
						current_symbol = sym;
					} 
					func_para BN func_body END 
					{
						string str($3); 
						size_t pos = str.find(" "); 
						str.erase(pos); 
						pos = str.find("("); 
						str = str.substr(0, pos);
						$$ = new Function($7, $2, str, current_symbol);
						current_symbol = current_symbol->father;
					};
func_para : "(" param_decl_list ")" | "(" ")" ;

func_body			: decl stmt_list {$$ = $2;}
					| decl {$$ = new list<Statement*>();}
					| stmt_list {$$ = $1;}
					| {$$ = new list<Statement*>();};

/* Statement List */
stmt_list			: stmt stmt_list {$2->push_front($1); $$ = $2;}
                    | read_stmt stmt_list {process_rw_list($1, $2); $$ = $1;}
                    | write_stmt stmt_list {process_rw_list($1, $2); $$ = $1;}
                    | stmt {$$ = new list<Statement*>(); $$->push_back($1);}
                    | read_stmt {$$ = $1;}
                    | write_stmt {$$ = $1;};

stmt				: assign_stmt {$$ = $1;}
                    | return_stmt {$$ = $1;}
                    | if_stmt {$$ = $1;} 
                    | while_stmt {$$ = $1;};

/* Basic Statements */
assign_stmt			: id FZ expr ";" 
					{
						string str($1);
						trim(str); 
						std::size_t pos = str.find(":=");
						string str_sub = str.substr(0, pos);
						trim(str_sub);
                        pos = str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
                        str_sub = str_sub.substr(0,pos);
						struct variable* info = Find_Variable(str_sub, current_symbol, false);
                        $$ = new AssignStatement(info->irname, $3);
					};
read_stmt			: READ "(" id_list ")" ";" {$$ = new list<Statement*>(); process_read($$, $3);};
write_stmt			: WRITE "(" id_list ")" ";" {$$ = new list<Statement*>(); process_write($$, $3);};
return_stmt			: RETURN expr ";"
                    {
                        $$ = new ReturnStatement($2);
                    };

expr				: expr '+' factor {$$ = new OperatorNode($1, $3, "ADD");}
					| expr '-' factor {$$ = new OperatorNode($1, $3, "SUB");}
					| factor {$$ = $1;};
factor				: factor '*' postfix_expr {$$ = new OperatorNode($1, $3, "MULT");}
					| factor '/' postfix_expr {$$ = new OperatorNode($1, $3, "DIV");}
					| postfix_expr {$$ = $1;};
postfix_expr		: '(' expr ')' {$$ = $2;}
					| id 
					{
						string str($1);
						std::size_t pos = str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
						string s2 = str.substr(0,pos);
						struct variable* info = Find_Variable(s2, current_symbol, false);
						if(info == NULL)
						{
							printf("PostFix Can't find varibale!\n");
							exit(0);
						}
						else
						{
							string name(info->irname);
							string type(info->type);
							$$ = new IDNode(name, type);
						}
					}
					| INTLITERAL  {$$ = new ExpressionNode($1, "INT");}
					| FLOATLITERAL {$$ = new ExpressionNode($1, "FLOAT");}
					| id '(' expr_list ')' 
					{
						string str($1); 
						size_t pos = str.find("("); 
						str.erase(pos); 
						vector<struct symbol*>::iterator iter;
						for(iter = global_symbol->children.begin(); iter != global_symbol->children.end(); ++iter)
						{
							if((*iter)->name == str)
							{
								break;
							}
						}
						if (iter == global_symbol->children.end())
						{
							printf("Can\'t find certain function!\n");
							exit(0);
						}
/*						vector<string> var_name;
						list<ExpressionNode*> *pExpList = $3->pExpNodes;
						list<ExpressionNode*>::iterator iterL;
						vector<variable*>::iterator iterV;
						for(iterL = pExpList->begin(); iterL != pExpList->end(); ++iterL)
						{
							for(iterV = current_symbol->var.begin(); iterV != current_symbol->var.end(); ++iterV)
							{
								if((*iterV)->irname == (*iterL)->ir.op3)
								{
									string name((*iterV)->irname);
									var_name.push_back(name);
									break;
								}
							}
						}
						$$ = new ExpressionNode((*iter), current_symbol, var_name);*/
						$$ = new ExpressionNode((*iter), current_symbol, $3->pExpNodes);
					}
					| id '(' ')' 
					{
						string str($1); 
						size_t pos = str.find("("); 
						str.erase(pos); 
						vector<struct symbol*>::iterator iter;
						for(iter = global_symbol->children.begin(); iter != global_symbol->children.end(); ++iter)
						{
							if((*iter)->name == str)
							{
								break;
							}
						}
						if (iter == global_symbol->children.end())
						{
							printf("Can\'t find certain function!\n");
							exit(0);
						}

						$$ = new ExpressionNode((*iter), current_symbol, NULL);
					};
expr_list			: expr expr_list_tail {$2->pExpNodes->push_front($1);$$ = $2;};
expr_list_tail		: ',' expr expr_list_tail {$3->pExpNodes->push_front($2);$$ = $3;}
					| {$$ = new ExpressionNodeList(new list<ExpressionNode*>());};
			   
/* Complex Statements and Condition */ 
if_stmt				: IF 
					{
						stringstream ss; 
						ss << global_block_num; global_block_num++; 
						string str; 
						ss>>str; 
						str = "BLOCK " + str; 
						struct symbol* sym = Sym_Alloc(str, current_symbol, "LOCAL", "BLOCK"); 
						current_symbol = sym;
					} "(" cond ")" func_body else_part ENDIF 
					{
						$$ = new IfStatement($4, $6, $7);
						current_symbol = current_symbol->father;
					};
else_part			: ELSE 
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
					} func_body {$$ = $3;}
					| {$$ = new list<Statement*>();};
cond				: expr compop expr {$$ = new CompareNode($1, $2, $3);};
compop				: "<" {char str[] = "<"; $$ = str;} 
					| ">" {char str[] = ">"; $$ = str;}
					| "=" {char str[] = "=="; $$ = str;}
					| NE  {char str[] = "!="; $$ = str;}
					| LE  {char str[] = "<="; $$ = str;}
					| GE  {char str[] = ">="; $$ = str;};

/* ECE 573 students use this version of do_while_stmt */
while_stmt			: WHILE 
					{
						stringstream ss; 
						ss << global_block_num; 
						global_block_num++; 
						string str; 
						ss>>str; 
						str = "BLOCK " + str; 
						struct symbol* sym = Sym_Alloc(str, current_symbol, "LOCAL", "BLOCK"); 
						current_symbol = sym;
					} "(" cond ")" aug ENDWHILE 
					{
						$$ = new WhileStatement($4, $6);
						current_symbol = current_symbol->father;
					};
aug					: decl aug_stmt_list {$$ = $2;}
					| aug_stmt_list {$$ = $1;};
aug_stmt_list		: aug_stmt_list aug_stmt {$1->push_back($2); $$ = $1;}
					| aug_stmt_list write_stmt {process_rw_list($1, $2); $$ = $1;}
					| aug_stmt_list read_stmt {process_rw_list($1, $2); $$ = $1;}
					| {$$ = new list<Statement*>();};
/* CONTINUE and BREAK statements. ECE 573 students only */
aug_stmt			: assign_stmt {$$ = $1;}
					| return_stmt {$$ = $1;}
					| aug_if_stmt {$$ = $1;}
					| while_stmt  {$$ = $1;}
					| CONTINUE ";" {$$ = new ContinueStatement();}
					| BREAK ";" {$$ = new BreakStatement();};

/* Augmented IF statements for ECE 573 students */ 
aug_if_stmt			: IF 
					{
						stringstream ss; 
						ss << global_block_num; 
						global_block_num++; 
						string str; 
						ss>>str; 
						str = "BLOCK " + str; 
						struct symbol* sym = Sym_Alloc(str, current_symbol, "LOCAL", "BLOCK"); 
						current_symbol = sym;
					} "(" cond ")" aug aug_else_part ENDIF 
					{
						$$ = new IfStatement($4, $6, $7);
						current_symbol = current_symbol->father;
					};
aug_else_part		: ELSE 
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
					} aug aug_else_part { $$ = $3;}
					| {$$ = new list<Statement*>();};

%%

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
        Variable_Add(_psym, str_temp, str_type, "NULL", "local");
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
    Variable_Add(_psym, s1_sub, "STRING", s2, "local");
}

void process_read(list<Statement*> *_pStatementList, string _var)
{
	std::size_t pos = _var.find(";");
    string s2 = _var.substr(0,pos); 
	pos = s2.rfind(")");
	s2.replace(pos, string::npos, ",");
	
	pos = s2.find(",");
	while(pos != string::npos)
	{
		string str = s2.substr(0, pos);
		trim(str);
		
		struct variable* info = Find_Variable(str, current_symbol, false);
		if(info == NULL)
		{
			printf("Read Can't find varibale!\n");
			exit(0);
		}
		else
		{
			_pStatementList->push_back(new ReadStatement(info->irname, info->type));
		}
		
		s2 = s2.substr(pos+1);
		pos = s2.find(",");
	}
}

void process_write(list<Statement*> *_pStatementList, string _var)
{
	std::size_t pos = _var.find(";");
    string s2 = _var.substr(0,pos); 
	pos = s2.rfind(")");
	s2.replace(pos, string::npos, ",");
	
	pos = s2.find(",");
	while(pos != string::npos)
	{
		string str = s2.substr(0, pos);
		trim(str);
		
		struct variable* info = Find_Variable(str, current_symbol, false);
		if(info == NULL)
		{
			printf("Write Can't find varibale!  %s\n", str.c_str());
			exit(0);
		}
		else
		{
			_pStatementList->push_back(new WriteStatement(info->irname, info->type));
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



