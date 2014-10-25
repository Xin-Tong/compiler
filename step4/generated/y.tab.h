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
extern YYSTYPE yylval;
