#ifndef __AST_H_
#define __AST_H_

#include <stdlib.h>
#include <string>
#include <map>
#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include "symbol_table.h"
using namespace std;

static int MAX_REGISTER_NUM =   15;
static int R_NUM            =   17;
static int R_NUM_BASE       =   17;
static int L_NUM            =   0;

static int global_ir_reg_count = 1;
static int max_reg_index = 0;
static int global_label_count = 1;
static string whileLabelBegin;
static string whileLabelEnd;
static int assign_id = -1;
static struct symbol* pCurentSym = NULL;
static int nMakeUpForTempIndex = 1;

static string IR2Tiny(string ir)
{
    size_t found1 = ir.find("$L"); 
	size_t found2 = ir.find("$P"); 
	size_t found3 = ir.find("$T"); 
	if((found1 == string::npos) && (found2 == string::npos) && (found3 == string::npos))
		return ir;
	string secondChar = ir.substr(1, 1);
    string restchars = ir.substr(2);
    string transfered = ir;
    int transfered_id = atoi(restchars.c_str());;
    if (secondChar == "T")
    {
        transfered_id -= nMakeUpForTempIndex;
        stringstream ss;
        ss << transfered_id;
        ss >> transfered;
        transfered = "r" + transfered;
    }
    else if(secondChar == "P")
    {
        transfered_id = R_NUM - transfered_id;
        stringstream ss;
        ss << transfered_id;
        ss >> transfered;
        transfered = "$" + transfered;
    }
    else if(secondChar == "L")
    {
        transfered_id = L_NUM - transfered_id;
        stringstream ss;
        ss << transfered_id;
        ss >> transfered;
        transfered = "$" + transfered;
    }
    
    return transfered;
}

class IRNode
{
public:
	string opcode, op1, op2, op3;
	static string get_ir_reg()
	{
		stringstream ss; 
        ss << global_ir_reg_count; 
		global_ir_reg_count ++;
        string str; 
        ss>>str;
		str = "$T" + str;
		return str;
    }
	static string get_label()
	{
		stringstream ss;
		ss << global_label_count;
		global_label_count ++;
		string str;
		ss >> str;
		str = "label" + str;
		return str;
	}
};

class ExpressionNode
{
public:
	string val;
	string type;
	IRNode ir;
    bool bFunction;
    struct symbol* psym;
    struct symbol* pCurrentSymp;
    list<ExpressionNode*> *pExpList;
    vector<string> params;
	
	ExpressionNode()
	{
        bFunction = false;
        psym = NULL;
	}
	ExpressionNode(ExpressionNode *_exp)
	{
		val = _exp->val;
		type = _exp->type;
		ir.opcode = _exp->ir.opcode;
		ir.op1 = _exp->ir.op1;
		ir.op2 = _exp->ir.op2;
		ir.op3 = _exp->ir.op3;
        bFunction = _exp->bFunction;
        psym = _exp->psym;
	}
	ExpressionNode(string _val, string _type)
	{
		val = _val;
		type = _type;
        bFunction = false;
        psym = NULL;
	}
    ExpressionNode(struct symbol* _psym, struct symbol* _pCurrentSymp, list<ExpressionNode*> *_pExpList)
    {
        bFunction = true;
        psym = _psym;
        pCurrentSymp = _pCurrentSymp;
        pExpList = _pExpList;
    }
	virtual string GenIR()
	{
        if (!bFunction)
        {
            if(type == "INT")
            {
                ir.opcode = "STOREI";
            }
            else
            {
                ir.opcode = "STOREF";
            }
        }
        else
        {
            list<ExpressionNode*>::iterator iterL;
            for(iterL = pExpList->begin(); iterL != pExpList->end(); ++iterL)
            {
                string tmp = (*iterL)->GenIR();
                params.push_back(tmp);
            }
        }
        ir.op3 = ir.get_ir_reg();
        return ir.op3;
	}
	virtual void PrintIR()
	{
        if (!bFunction)
        {
            cout << ";" << ir.opcode << " " << val << " " << ir.op3 << endl;
        }
        else
        {
            list<ExpressionNode*>::iterator iterL;
            for(iterL = pExpList->begin(); iterL != pExpList->end(); ++iterL)
            {
                (*iterL)->PrintIR();
            }
            cout << ";PUSH" << endl;
            for(iterL = pExpList->begin(); iterL != pExpList->end(); ++iterL)
            {
                cout << ";PUSH " << (*iterL)->ir.op3 << endl;
            }
            cout << ";JSR " << psym->name << endl;
            for (int i = 0; i < psym->num_of_params; i ++)
            {
                cout << ";POP" << endl;
            }
            cout << ";POP " << ir.op3 << endl;
        }
	}
	virtual void PrintTiny()
	{
        if (!bFunction)
        {
            cout << "move " << val << " " << IR2Tiny(ir.op3) << endl;;
        }
        else
        {
            list<ExpressionNode*>::iterator iterL;
            for(iterL = pExpList->begin(); iterL != pExpList->end(); ++iterL)
            {
                (*iterL)->PrintTiny();
            }
            printf("push\n");
            for(iterL = pExpList->begin(); iterL != pExpList->end(); ++iterL)
            {
                cout << "push " << IR2Tiny((*iterL)->ir.op3) << endl;
            }
            for (int i = 0; i < MAX_REGISTER_NUM; i ++)
            {
                printf("push r%d\n", i);
            }
            cout << "jsr " << psym->name << endl;
            for (int i = MAX_REGISTER_NUM - 1; i > -1; i --)
            {
                printf("pop r%d\n", i);
            }
            for (int i = 0; i < psym->num_of_params; i ++)
            {
                cout << "pop" << endl;
            }
            cout << "pop " << IR2Tiny(ir.op3) << endl;
        }
	}
};

class IDNode: public ExpressionNode
{
public:
	string name;
	IDNode(string _name, string _type)
	{
		name = _name;
		type = _type;
        ir.op3 = _name;
	}
	
	virtual void PrintIR() {}
	virtual void PrintTiny() {}
	virtual string GenIR()
	{
		return name;
	}
};

class ExpressionNodeList
{
public:
	list<ExpressionNode*> *pExpNodes;
	ExpressionNodeList(list<ExpressionNode*> *_pExpNodeList) : pExpNodes(_pExpNodeList) {}
};

class CompareNode: public ExpressionNode
{
public:
    ExpressionNode *left;
    ExpressionNode *right;
    string cmptr, tmp;
    CompareNode(ExpressionNode* _left, string _cmptr, ExpressionNode* _right) : left(_left), cmptr(_cmptr), right(_right)
    {
        type = left->type;
    }
    
    virtual string GenIR()
    {
        if (type == "INT")
        {
            if (cmptr == ">")
            {
                ir.opcode = "LEI";
            }
            else if (cmptr == ">=")
            {
                ir.opcode = "LTI";
            }
            else if (cmptr == "<")
            {
                ir.opcode = "GEI";
            }
            else if (cmptr == "<=")
            {
                ir.opcode = "GTI";
            }
            else if (cmptr == "==")
            {
                ir.opcode = "NEI";
            }
            else if (cmptr == "!=")
            {
                ir.opcode = "EQI";
            }
        }
        else if (type == "FLOAT")
        {
            if (cmptr == ">")
            {
                ir.opcode = "LEF";
            }
            else if (cmptr == ">=")
            {
                ir.opcode = "LTF";
            }
            else if (cmptr == "<")
            {
                ir.opcode = "GEF";
            }
            else if (cmptr == "<=")
            {
                ir.opcode = "GTF";
            }
            else if (cmptr == "==")
            {
                ir.opcode = "NEF";
            }
            else if (cmptr == "!=")
            {
                ir.opcode = "EQF";
            }
        }
        
        ir.op1 = left->GenIR();
        ir.op2 = right->GenIR();
        ir.op3 = ir.get_label();
        
		std::size_t pos = ir.op2.find_first_of("$");
		if(pos == string::npos)
        {
			tmp = ir.get_ir_reg();
            nMakeUpForTempIndex --;
        }
			
        return ir.op3;
    }
    
    virtual void PrintIR()
    {
        left->PrintIR();
        right->PrintIR();
        printf(";%s %s %s %s\n", ir.opcode.c_str(), ir.op1.c_str(), ir.op2.c_str(), ir.op3.c_str());
    }
    
    virtual void PrintTiny()
    {
		left->PrintTiny();
		right->PrintTiny();
				
		string s3(IR2Tiny(ir.op3));
		string s1(IR2Tiny(ir.op1));

		string s2(ir.op2);
		std::size_t pos = s2.find_first_of("$");
		if(pos != string::npos)
        {
            stringstream ss;
            ss << max_reg_index;
            ss >> tmp;
            tmp = "$T" + tmp;
            tmp = IR2Tiny(tmp);
            s2 = IR2Tiny(ir.op2);
            cout<<"move "<<s2<<" "<<tmp<<endl;
			if(left->type == "INT")
				cout<<"cmpi "<<s1<<" "<<tmp<<endl;
			else if(left->type == "FLOAT")	
				cout<<"cmpr "<<s1<<" "<<tmp<<endl;
		}
		else
        {
            tmp = IR2Tiny(tmp);
			cout<<"move "<<s2<<" "<<tmp<<endl;
			if(left->type == "INT")
				cout<<"cmpi "<<s1<<" "<<tmp<<endl;
			else if(left->type == "FLOAT")	
				cout<<"cmpr "<<s1<<" "<<tmp<<endl;
		}
    
		string oprtr;
		if(ir.opcode == "LEI")		oprtr = "jle";
		else if (ir.opcode == "LTI")	oprtr = "jlt";
		else if (ir.opcode == "GEI")	oprtr = "jge";
		else if (ir.opcode == "GTI")	oprtr = "jgt";
		else if (ir.opcode == "NEI")	oprtr = "jne";
		else if (ir.opcode == "EQI")	oprtr = "jeq";
		
		else if (ir.opcode == "LEF")	oprtr = "jle";
		else if (ir.opcode == "LTF")	oprtr = "jlt";
		else if (ir.opcode == "GEF")	oprtr = "jge";
		else if (ir.opcode == "GTF")	oprtr = "jgt";
		else if (ir.opcode == "NEF")	oprtr = "jne";
		else if (ir.opcode == "EQF")	oprtr = "jeq";
		
		cout << oprtr << " "<< ir.op3 << endl; // op3 could be label name
    }
};

class OperatorNode: public ExpressionNode
{
public:
	ExpressionNode *left;
	ExpressionNode *right;
    string optr;

	OperatorNode(ExpressionNode* _left, ExpressionNode* _right, string _optr) : left(_left), right(_right), optr(_optr)
	{
		type = _left->type;
	}
    
    virtual string GenIR()
    {
        if (optr == "ADD")
        {
            if(type == "INT")
            {
                ir.opcode = "ADDI";
            }
            else
            {
                ir.opcode = "ADDF";
            }
        }
        else if (optr == "SUB")
        {
            if(type == "INT")
            {
                ir.opcode = "SUBI";
            }
            else
            {
                ir.opcode = "SUBF";
            }
        }
        else if (optr == "MULT")
        {
            if(type == "INT")
            {
                ir.opcode = "MULTI";
            }
            else
            {
                ir.opcode = "MULTF";
            }
        }
        else if (optr == "DIV")
        {
            if(type == "INT")
            {
                ir.opcode = "DIVI";
            }
            else
            {
                ir.opcode = "DIVF";
            }
        }
        
        ir.op1 = left->GenIR();
        ir.op2 = right->GenIR();
        ir.op3 = ir.get_ir_reg();
        return ir.op3;
    }
	virtual void PrintIR()
	{
		left->PrintIR();
		right->PrintIR();
		printf(";%s %s %s %s\n", ir.opcode.c_str(), ir.op1.c_str(), ir.op2.c_str(), ir.op3.c_str());
	}
	virtual void PrintTiny()
	{
		left->PrintTiny();
		right->PrintTiny();

		string s3(IR2Tiny(ir.op3));
		string s2(IR2Tiny(ir.op2));
		string s1(IR2Tiny(ir.op1));

		string oprtr;
		if(ir.opcode == "ADDI")			oprtr = "addi";
		else if (ir.opcode == "ADDF")	oprtr = "addr";
		else if (ir.opcode == "SUBI")	oprtr = "subi";
		else if (ir.opcode == "SUBF")	oprtr = "subr";
		else if (ir.opcode == "MULTI")	oprtr = "muli";
		else if (ir.opcode == "MULTF")	oprtr = "mulr";
		else if (ir.opcode == "DIVI")	oprtr = "divi";
		else if (ir.opcode == "DIVF")	oprtr = "divr";

		printf("move %s %s\n", s1.c_str(), s3.c_str());
		printf("%s %s %s\n", oprtr.c_str(), s2.c_str(), s3.c_str());
	}
};

class Statement
{
public:
    string name;
	virtual void GenIR() {}
	virtual void PrintIR() {}
	virtual void PrintTiny() {}
};

class ReturnStatement : public Statement
{
public:
	ExpressionNode *pExpNode;
    string result;
    IRNode ir;
    string temp;
	ReturnStatement(ExpressionNode *_pExpNode) : pExpNode(_pExpNode) {}
    
    virtual void GenIR()
    {
        if(pExpNode->type == "INT")
        {
            ir.opcode = "STOREI";
        }
        else
        {
            ir.opcode = "STOREF";
        }
        ir.op1 = pExpNode->GenIR();
        ir.op3 = IRNode::get_ir_reg();
    }
    virtual void PrintIR()
    {
        pExpNode->PrintIR();
        printf(";%s %s %s\n", ir.opcode.c_str(), ir.op1.c_str(), ir.op3.c_str());
        printf(";%s %s $R\n", ir.opcode.c_str(), ir.op3.c_str());
        printf(";RET\n");
    }
    virtual void PrintTiny()
    {
        pExpNode->PrintTiny();
        printf("move %s %s\n", IR2Tiny(ir.op1).c_str(), IR2Tiny(ir.op3).c_str());
        printf("move %s $%d\n", IR2Tiny(ir.op3).c_str(), (int)R_NUM);
        printf("unlnk\n");
        printf("ret\n");
    }
};

class IfStatement : public Statement
{
public:
	ExpressionNode *pCmpNode;
    list<Statement*> *pFuncBody;
    list<Statement*> *pElsePart; 
    string jmpLabel;
    IfStatement() {}
    IfStatement(ExpressionNode *_pCmpNode, list<Statement*>* _pFuncBody, list<Statement*>* _pElsePart) : pCmpNode(_pCmpNode), pFuncBody(_pFuncBody), pElsePart(_pElsePart) {}
     virtual void GenIR()
    {
        pCmpNode->GenIR();
        
        list<Statement*>::iterator iter;
        for (iter = pFuncBody->begin(); iter != pFuncBody->end(); iter ++)
        {
            (*iter)->GenIR();
        }
        
        if (pElsePart->size() != 0)
        {
            jmpLabel = IRNode::get_label();
            
            for (iter = pElsePart->begin(); iter != pElsePart->end(); iter ++)
            {
                (*iter)->GenIR();
            }
        }
    }
    virtual void PrintIR()
    {
        pCmpNode->PrintIR();
        
        list<Statement*>::iterator iter;
        for (iter = pFuncBody->begin(); iter != pFuncBody->end(); iter ++)
        {
            if ((*iter)->name == "BREAK")
            {
                printf(";JUMP %s\n", whileLabelEnd.c_str());
            }
            else if ((*iter)->name == "CONTINUE")
            {
                printf(";JUMP %s\n", whileLabelEnd.c_str());
            }
            
            (*iter)->PrintIR();
        }
        if (pElsePart->size() != 0)
        {
            printf(";JUMP %s\n", jmpLabel.c_str());
        }
        printf(";LABEL %s\n", pCmpNode->ir.op3.c_str());
        if (pElsePart->size() != 0)
        {
            for (iter = pElsePart->begin(); iter != pElsePart->end(); iter ++)
            {
                if ((*iter)->name == "BREAK")
                {
                    printf(";JUMP %s\n", whileLabelEnd.c_str());
                }
                else if ((*iter)->name == "CONTINUE")
                {
                    printf(";JUMP %s\n", whileLabelEnd.c_str());
                }
                
                (*iter)->PrintIR();
            }
            printf(";LABEL %s\n", jmpLabel.c_str());
        }
    }
    virtual void PrintTiny()
    {
        pCmpNode->PrintTiny();
		list<Statement*>::iterator iter;
        for (iter = pFuncBody->begin(); iter != pFuncBody->end(); iter ++)
        {
            if ((*iter)->name == "BREAK")
            {
                printf("jmp %s\n", whileLabelEnd.c_str());
            }
            else if ((*iter)->name == "CONTINUE")
            {
                printf("jmp %s\n", whileLabelEnd.c_str());
            }

            (*iter)->PrintTiny();
        }
        if (pElsePart->size() != 0)
        {
            printf("jmp %s\n", jmpLabel.c_str());
        }
        printf("label %s\n", pCmpNode->ir.op3.c_str());
        if (pElsePart->size() != 0)
        {
            for (iter = pElsePart->begin(); iter != pElsePart->end(); iter ++)
            {
                if ((*iter)->name == "BREAK")
                {
                    printf("jmp %s\n", whileLabelEnd.c_str());
                }
                else if ((*iter)->name == "CONTINUE")
                {
                    printf("jmp %s\n", whileLabelEnd.c_str());
                }

                (*iter)->PrintTiny();
            }
            printf("label %s\n", jmpLabel.c_str());
        }
    }

};

class WhileStatement : public Statement
{
public:
    ExpressionNode *pCmpNode;
    list<Statement*> *pAug;
    string whileLabel;
    WhileStatement() {}
    WhileStatement(ExpressionNode* _pCmpNode, list<Statement*> *_pAug) : pCmpNode(_pCmpNode), pAug(_pAug) {}
    
    virtual void GenIR()
    {
        whileLabel = IRNode::get_label();
        whileLabelBegin = whileLabel;
        pCmpNode->GenIR();
        whileLabelEnd = pCmpNode->ir.op3;
        list<Statement*>::iterator iter;
        for (iter = pAug->begin(); iter != pAug->end(); iter ++)
        {
            (*iter)->GenIR();
        }
    }
    
    virtual void PrintIR()
    {
        printf(";LABEL %s\n", whileLabel.c_str());
        pCmpNode->PrintIR();
        list<Statement*>::iterator iter;
        for (iter = pAug->begin(); iter != pAug->end(); iter ++)
        {
            if ((*iter)->name == "BREAK")
            {
                printf(";JUMP %s\n", pCmpNode->ir.op3.c_str());
            }
            else if ((*iter)->name == "CONTINUE")
            {
                printf(";JUMP %s\n", whileLabel.c_str());
            }
            
            (*iter)->PrintIR();
        }
        printf(";JUMP %s\n", whileLabel.c_str());
        printf(";LABEL %s\n", pCmpNode->ir.op3.c_str());
    }

    virtual void PrintTiny(){
        printf("label %s\n", whileLabel.c_str());
        pCmpNode->PrintTiny();
        list<Statement*>::iterator iter;
        for (iter = pAug->begin(); iter != pAug->end(); iter ++)
        {
            if ((*iter)->name == "BREAK")
            {
                printf("jump %s\n", pCmpNode->ir.op3.c_str());
            }
            else if ((*iter)->name == "CONTINUE")
            {
                printf("label %s\n", whileLabel.c_str());
            }
            (*iter)->PrintTiny();
        }
        printf("jmp %s\n", whileLabel.c_str());
        printf("label %s\n", pCmpNode->ir.op3.c_str());
    }
};

class ContinueStatement : public Statement
{
public:
    ContinueStatement()
    {
        name = "CONTINUE";
    }
};

class BreakStatement : public Statement
{
public:
    BreakStatement()
    {
        name = "BREAK";
    }
};

class AssignStatement : public Statement
{
public:
	string name, tmp;
	ExpressionNode *pExpNode;
	IRNode ir;
	AssignStatement(string _name, ExpressionNode *_pExpNode): name(_name), pExpNode(_pExpNode) {}	
	
	virtual void GenIR() 
	{
		if(pExpNode->type == "INT")
		{
			ir.opcode = "STOREI";
		}
		else
		{
			ir.opcode = "STOREF";
		}
        ir.op1 = pExpNode->GenIR();
        std::size_t pos = ir.op1.find_first_of("1234567890");
        if(pos == string::npos)
        {
            tmp = IRNode::get_ir_reg();
        }
		ir.op3 = name;
	}
	virtual void PrintIR()
	{
		pExpNode->PrintIR();
		printf(";%s %s %s\n", ir.opcode.c_str(), ir.op1.c_str(), ir.op3.c_str());
	}
	virtual void PrintTiny()
	{
		pExpNode->PrintTiny();
		string str(ir.op1);
		std::size_t pos = str.find_first_of("1234567890");
        if(pos != string::npos)
        {
            str = IR2Tiny(ir.op1);
            printf("move %s %s\n", str.c_str(), IR2Tiny(ir.op3).c_str());
        }
        else
        {
            tmp = IR2Tiny(tmp);
		    printf("move %s r%d\n", str.c_str(), tmp.c_str());
		    printf("move %s %s\n", tmp.c_str(), IR2Tiny(ir.op3).c_str());
    	}
    }
};

class ReadStatement : public Statement
{
public:
	string name;
	string type;
	IRNode ir;
	ReadStatement(string _name, string _type): name(_name), type(_type) {}	
	
	virtual void GenIR()
	{
		if(type == "INT")
		{
			ir.opcode = "READI";
		}
		else
		{
			ir.opcode = "READF";
		}
		ir.op1 = name;
	}
	virtual void PrintIR()
	{
		printf(";%s %s\n", ir.opcode.c_str(), ir.op1.c_str());
	}
	virtual void PrintTiny()
	{
		string str;
		if(type == "INT")
		{
			str = "sys readi";
		}
		else
		{
			str = "sys readr";
		}
		printf("%s %s\n", str.c_str(), IR2Tiny(ir.op1).c_str());
	}
};

class WriteStatement : public Statement
{
public:
	string name;
	string type;
	IRNode ir;
	WriteStatement(string _name, string _type): name(_name), type(_type) {}	
	
	virtual void GenIR()
	{
		if(type == "INT")
		{
			ir.opcode = "WRITEI";
		}
		else if(type == "FLOAT")
		{
			ir.opcode = "WRITEF";
		}
		else
		{
			ir.opcode = "WRITES";
		}
		ir.op1 = name;
	}
	virtual void PrintIR()
	{
		printf(";%s %s\n", ir.opcode.c_str(), ir.op1.c_str());
	}
	virtual void PrintTiny()
	{
		string str;
		if(type == "INT")
		{
			str = "sys writei";
		}
		else if(type == "FLOAT")
		{
			str = "sys writer";
		}
		else
		{
			str = "sys writes";
		}
		printf("%s %s\n", str.c_str(), IR2Tiny(ir.op1).c_str());
	}
};

class Grammar
{
    
};

class Function
{
public:
    string returnType;
    string name;
    int max_index;
    struct symbol* psym;
    list<Statement*> *pStatementsList;
    Function(list<Statement*> *_pStatementList, string _returnType, string _name, struct symbol* _psym) : pStatementsList(_pStatementList),returnType(_returnType), name(_name), psym(_psym) {}
    
    virtual void GenIR()
    {
        list<Statement*>::iterator iter;
        for (iter = pStatementsList->begin(); iter != pStatementsList->end(); iter ++)
        {
            (*iter)->GenIR();
        }
        max_index = global_ir_reg_count;
    }
    virtual void PrintIR()
    {
        printf(";LABEL %s\n", name.c_str());
        printf(";LINK\n");
        list<Statement*>::iterator iter;
        for (iter = pStatementsList->begin(); iter != pStatementsList->end(); iter ++)
        {
            (*iter)->PrintIR();
        }
    }
    virtual void PrintTiny()
    {
        printf("label %s\n", name.c_str());
        printf("link %d\n", psym->num_of_locals);
        list<Statement*>::iterator iter;
        for (iter = pStatementsList->begin(); iter != pStatementsList->end(); iter ++)
        {
            (*iter)->PrintTiny();
        }
    }
};

class Global
{
public:
    list<Function*> *pFunctionList;
    struct symbol* psym;
    Global(list<Function*> *_pFunctionList, struct symbol* _psym): pFunctionList(_pFunctionList), psym(_psym) {}
    virtual void GenIR()
    {
        list<Function*>::iterator iter;
        for (iter = pFunctionList->begin(); iter != pFunctionList->end(); iter ++)
        {
            pCurentSym = (*iter)->psym;
            global_ir_reg_count = 1;
            (*iter)->GenIR();
        }
    }
    virtual void PrintIR()
    {
        list<Function*>::iterator iter;
        for (iter = pFunctionList->begin(); iter != pFunctionList->end(); iter ++)
        {
            pCurentSym = (*iter)->psym;
            (*iter)->PrintIR();
        }
    }
    virtual void PrintTiny()
    {
        printf("push\n");
        for (int i = 0; i < MAX_REGISTER_NUM; i ++)
        {
            printf("push r%d\n", i);
        }
        printf("jsr main\n");
        printf("sys halt\n");
        list<Function*>::iterator iter;
        for (iter = pFunctionList->begin(); iter != pFunctionList->end(); iter ++)
        {
            pCurentSym = (*iter)->psym;
            if ((*iter)->name != "main")
            {
                R_NUM = R_NUM_BASE + psym->children.size() - 1;
            }
            else
            {
                R_NUM = R_NUM_BASE;
            }
            max_reg_index = (*iter)->max_index;
            (*iter)->PrintTiny();
        }
        printf("end\n");
    }
};



#endif
