#ifndef __AST_H_
#define __AST_H_

#include <stdlib.h>
#include <string>
#include <map>
#include <iostream>
#include <list>
#include <vector>
#include <sstream>
using namespace std;

extern int global_temp_reg_count;

class IRNode
{
public:
	string opcode, op1, op2, op3;
	static string get_reg()
	{
		stringstream ss; 
        ss << global_temp_reg_count; 
		global_temp_reg_count ++;
        string str; 
        ss>>str;
		str = "$T" + str;
		return str;
	}
};

class ExpressionNode
{
public:
	float val;
	string type;
	IRNode ir;
	bool isNum;
	
	ExpressionNode()
	{
		isNum = false;
	}
	ExpressionNode(ExpressionNode *_exp)
	{
		val = _exp->val;
		type = _exp->type;
		ir.opcode = _exp->ir.opcode;
		ir.op1 = _exp->ir.op1;
		ir.op2 = _exp->ir.op2;
		ir.op3 = _exp->ir.op3;
		isNum = false;
	}
	ExpressionNode(float _val, string _type)
	{
		val = _val;
		type = _type;
		isNum = true;
	}
	virtual string GenIR()
	{
		if(type == "INT")
		{
			ir.opcode = "STOREI";
		}
		else
		{
			ir.opcode = "STOREF";
		}
		ir.op3 = ir.get_reg();
		return ir.op3;
	}
	virtual void PrintIR()
	{
		cout << ";" << ir.opcode << " " << val << " " << ir.op3 << endl;		
	}
	virtual void PrintTiny()
	{
		string str(ir.op3);
		std::size_t pos = str.find_first_of("1234567890");
		str.replace(0, pos, "r");
//		printf("move %f %s\n", val, str.c_str());
		cout << "move " << val << " " << str << endl;
	}
	virtual float calculate()
	{
		return val;
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

class OperatorNode: public ExpressionNode
{
public:
	ExpressionNode *left;
	ExpressionNode *right;

	OperatorNode(ExpressionNode* _left, ExpressionNode* _right) : left(_left), right(_right) 
	{
		type = _left->type;
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

		string s3(ir.op3);
		std::size_t pos = s3.find_first_of("1234567890");
		s3.replace(0, pos, "r");

		string s2(ir.op2);
		pos = s2.find_first_of("$");
		if(pos != string::npos)
		{
			s2.replace(0, 2, "r");  //replace $T with r
		}
    
		string s1(ir.op1);
		pos = s1.find_first_of("$");
		if(pos != string::npos)
		{
			s1.replace(0, 2, "r");	//replace $T with r
		}

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

class AddNode: public OperatorNode
{
public:
	AddNode(ExpressionNode *_left, ExpressionNode *_right) : OperatorNode(_left, _right) {}

	virtual string GenIR()
	{
		if(type == "INT")
		{
			ir.opcode = "ADDI";
		}
		else
		{
			ir.opcode = "ADDF";
		}
		ir.op1 = left->GenIR();
		ir.op2 = right->GenIR();
		ir.op3 = ir.get_reg();
		return ir.op3;
	}
};

class SubNode: public OperatorNode
{
public:
	SubNode(ExpressionNode *_left, ExpressionNode *_right) : OperatorNode(_left, _right) {}

	virtual string GenIR()
	{
		if(type == "INT")
		{
			ir.opcode = "SUBI";
		}
		else
		{
			ir.opcode = "SUBF";
		}
		ir.op1 = left->GenIR();
		ir.op2 = right->GenIR();
		ir.op3 = ir.get_reg();
		return ir.op3;
	}
};

class MultNode: public OperatorNode
{
public:
	MultNode(ExpressionNode *_left, ExpressionNode *_right) : OperatorNode(_left, _right) {}

	virtual string GenIR()
	{
		if(type == "INT")
		{
			ir.opcode = "MULTI";
		}
		else
		{
			ir.opcode = "MULTF";
		}
		ir.op1 = left->GenIR();
		ir.op2 = right->GenIR();
		ir.op3 = ir.get_reg();
		return ir.op3;
	}
};

class DivNode: public OperatorNode
{
public:
	DivNode(ExpressionNode *_left, ExpressionNode *_right) : OperatorNode(_left, _right) {}
	virtual string GenIR()
	{
		if(type == "INT")
		{
			ir.opcode = "DIVI";
		}
		else
		{
			ir.opcode = "DIVF";
		}
		ir.op1 = left->GenIR();
		ir.op2 = right->GenIR();
		ir.op3 = ir.get_reg();
		return ir.op3;
	}
};

class Statement
{
public:
	virtual void GenIR() {}
	virtual void PrintIR() {}
	virtual void PrintTiny() {}
};

class ReturnStatement : public Statement
{
public:
	ExpressionNode *pExpNode;
	ReturnStatement(ExpressionNode *_pExpNode) : pExpNode(_pExpNode) {}
};

class AssignStatement : public Statement
{
public:
	string name;
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
		str.replace(0, pos, "r");
		printf("move %s %s\n", str.c_str(), ir.op3.c_str());
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
		printf("%s %s\n", str.c_str(), ir.op1.c_str());
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
		printf("%s %s\n", str.c_str(), ir.op1.c_str());
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
    list<Statement*> *pStatementsList;
    Function(list<Statement*> *_pStatementList, string _returnType, string _name) : pStatementsList(_pStatementList),returnType(_returnType), name(_name) {}
    virtual void GenIR()
    {
        list<Statement*>::iterator iter;
        for (iter = pStatementsList->begin(); iter != pStatementsList->end(); iter ++)
        {
            (*iter)->GenIR();
        }
    }
    virtual void PrintIR()
    {
        list<Statement*>::iterator iter;
        for (iter = pStatementsList->begin(); iter != pStatementsList->end(); iter ++)
        {
            (*iter)->PrintIR();
        }
    }
    virtual void PrintTiny()
    {
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
    Global(list<Function*> *_pFunctionList): pFunctionList(_pFunctionList) {}
    virtual void GenIR()
    {
        list<Function*>::iterator iter;
        for (iter = pFunctionList->begin(); iter != pFunctionList->end(); iter ++)
        {
            (*iter)->GenIR();
        }
    }
    virtual void PrintIR()
    {
        list<Function*>::iterator iter;
        for (iter = pFunctionList->begin(); iter != pFunctionList->end(); iter ++)
        {
            (*iter)->PrintIR();
        }
    }
    virtual void PrintTiny()
    {
        list<Function*>::iterator iter;
        for (iter = pFunctionList->begin(); iter != pFunctionList->end(); iter ++)
        {
            (*iter)->PrintTiny();
        }
    }
};



#endif
