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

static int MAX_REGISTER_NUM =   4;
static int R_NUM            =   5;
static int R_NUM_BASE       =   5;
static int L_NUM            =   0;

extern struct symbol* global_symbol;
static int global_ir_reg_count = 1;
static int max_reg_index = 0;
static int global_label_count = 1;
static string whileLabelBegin;
static string whileLabelEnd;
static int assign_id = -1;
static struct symbol* pCurentSym = NULL;
static int nMakeUpForTempIndex = 1;
static string r0 = "";
static string r1 = "";
static string r2 = "";
static string r3 = "";
static bool isdirty0 = false;
static bool isdirty1 = false;
static bool isdirty2 = false;
static bool isdirty3 = false;

class LinkedNode;
static vector<LinkedNode*> *cur_LinkedNodeVec;
static vector<LinkedNode*>::iterator cur_LinkedNode;

static string IR2Tiny(string ir)
{
    size_t found1 = ir.find("$L"); 
	size_t found2 = ir.find("$P"); 
	size_t found3 = ir.find("$T"); 
	if((found1 == string::npos) && (found2 == string::npos) && (found3 == string::npos))
		return ir;
	string secondChar = ir.substr(1, 1);
    string restchars = ir.substr(2, ir.length() - 1);
    string transfered = ir;
    int transfered_id = atoi(restchars.c_str());;
    if (secondChar == "T")
    {
        transfered_id += pCurentSym->num_of_locals;
        stringstream ss;
        ss << transfered_id;
        ss >> transfered;
        transfered = "$-" + transfered;
    }
    else if(secondChar == "P")
    {
        transfered_id = R_NUM + transfered_id;
        stringstream ss;
        ss << transfered_id;
        ss >> transfered;
        transfered = "$" + transfered;
    }
    else if(secondChar == "L")
    {
        transfered_id = transfered_id;
        stringstream ss;
        ss << transfered_id;
        ss >> transfered;
        transfered = "$-" + transfered;
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

class LinkedNode
{
public:
	IRNode node;
	vector<LinkedNode*> preList;
    vector<LinkedNode*> sucList;
    
    vector<string> gen_vec;
    vector<string> kill_vec;
    
    vector<string> live_in_vec;
    vector<string> live_out_vec;
    
    void output()
    {
        if(node.opcode != "")
        {
            cout << node.opcode;
        }
        if(node.op1 != "")
        {
            cout << " " << node.op1;
        }
        if(node.op2 != "")
        {
            cout << " " << node.op2;
        }
        if(node.op3 != "")
        {
            cout << " " << node.op3;
        }

//        cout << endl;
    }
	
	bool isleader()
	{
		if(node.opcode == "LABEL")
        {
			return true;
        }
		vector<LinkedNode*>::iterator it = preList.begin(); 
		vector<LinkedNode*>::iterator it_end = preList.end();
		for(; it != it_end; ++it)
		{
			if( ((*it)->node.opcode == "NEI") || ((*it)->node.opcode == "NEF") || ((*it)->node.opcode == "EQI") || ((*it)->node.opcode == "EQF") || ((*it)->node.opcode == "LEI") || ((*it)->node.opcode == "LEF") || ((*it)->node.opcode == "GEI") || ((*it)->node.opcode == "GEF") || ((*it)->node.opcode == "<") || ((*it)->node.opcode == ">") )
				return true;
		}
		
		return false;
	}
};

    static void markDirty(string rg)
	{
		if("r0" == rg)
			isdirty0 = true;
		if("r1" == rg)
			isdirty1 = true;
		if("r2" == rg)
			isdirty2 = true;
		if("r3" == rg)
			isdirty3 = true;
	}

static void free(string rg)
{
    LinkedNode* p = *cur_LinkedNode;
    if(rg == "r0")
    {
        if(isdirty0)
        {
            cout<<"move r0 "<<IR2Tiny(r0)<<endl;
        }
        r0 = "";
        isdirty0 = false;
    }
    else if(rg == "r1")
    {
        if(isdirty1)
        {
            cout<<"move r1 "<<IR2Tiny(r1)<<endl;
        }
        r1 = "";
        isdirty1 = false;
    }
    else if(rg == "r2")
    {
        if(isdirty2)
        {
            cout<<"move r2 "<<IR2Tiny(r2)<<endl;
        }
        r2 = "";
        isdirty2 = false;
    }
    else if(rg == "r3")
    {
        if(isdirty3)
        {
            cout<<"move r3 "<<IR2Tiny(r3)<<endl;
        }		
        r3 = "";
        isdirty3 = false;
    }
}

static void check(LinkedNode* p)
{
    vector<string>::iterator iter_out_vec;
    for(iter_out_vec = p->live_out_vec.begin(); iter_out_vec != p->live_out_vec.end(); ++ iter_out_vec)
    {
        if(r0 == *iter_out_vec) break;
    }
    if (iter_out_vec == p->live_out_vec.end())
    {
        if(isdirty0)
        {
            cout<<"move r0 " << IR2Tiny(r0)<<endl;
        }
        r0 = "";
        isdirty0 = false;
    }
    
    for(iter_out_vec = p->live_out_vec.begin(); iter_out_vec != p->live_out_vec.end(); ++ iter_out_vec)
    {
        if(r1 == *iter_out_vec) break;
    }
    if (iter_out_vec == p->live_out_vec.end())
    {
        if(isdirty1)
        {
            cout<<"move r1 "<<IR2Tiny(r1)<<endl;
        }
        r1 = "";
        isdirty1 = false;
    }
    
    for(iter_out_vec = p->live_out_vec.begin(); iter_out_vec != p->live_out_vec.end(); ++ iter_out_vec)
    {
        if(r2 == *iter_out_vec) break;
    }
    if (iter_out_vec == p->live_out_vec.end())
    {
        if(isdirty2)
        {
            cout<<"move r2 "<<IR2Tiny(r2)<<endl;
        }
        r2 = "";
        isdirty2 = false;
    }
    
    for(iter_out_vec = p->live_out_vec.begin(); iter_out_vec != p->live_out_vec.end(); ++ iter_out_vec)
    {
        if(r3 == *iter_out_vec) break;
    }
    if (iter_out_vec == p->live_out_vec.end())
    {
        if(isdirty3)
        {
            cout<<"move r3 "<<IR2Tiny(r3)<<endl;
        }
        r3 = "";
        isdirty3 = false;
    }
}

    static void reset()
    {
        free("r0");
        free("r1");
        free("r2");
        free("r3");
    }

	static string allocate(string opr)
	{
		if("" == r0)
		{
			r0 = opr;
			return "r0";
		}
		else if("" == r1)
		{
			r1 = opr;
			return "r1";
		}
		else if("" == r2)
		{
			r2 = opr;
			return "r2";
		}
		else if("" == r3)
		{
			r3 = opr;
			return "r3";
		}
		else
		{
            LinkedNode* p = *cur_LinkedNode;
			string ops[3];
			ops[0] = p->node.op1;
			ops[1] = p->node.op2;
			ops[2] = p->node.op3;
			
			int i;
			for(i=0; i<3; i++)
				if(r0 == ops[i]) break;
			
			if(i == 3)
			{
				free("r0");
				r0 = opr;
				return "r0";
			}
			
			for(i=0; i<3; i++)
				if(r1 == ops[i]) break;
			
			if(i == 3)
			{
				free("r1");
				r1 = opr;
				return "r1";
			}
			
			for(i=0; i<3; i++)
				if(r2 == ops[i]) break;
			
			if(i == 3)
			{
				free("r2");
				r2 = opr;
				return "r2";
			}
			
			for(i=0; i<3; i++)
				if(r3 == ops[i]) break;
			
			if(i == 3)
			{
				free("r3");
				r3 = opr;
				return "r3";
			}
		}
	}
	
	static string ensure(string opr)
	{
        size_t found1 = opr.find("$L");
        size_t found2 = opr.find("$P");
        size_t found3 = opr.find("$T");
        if((found1 == string::npos) && (found2 == string::npos) && (found3 == string::npos))
            return opr;
        
		if(opr == r0)
			return "r0";
		else if(opr == r1)
			return "r1";
		else if(opr == r2)
			return "r2";
		else if(opr == r3)
			return "r3";
		else
		{
			string r = allocate(opr);
			cout<<"move "<<IR2Tiny(opr)<<" "<<r<<endl;
			return r;
		}
	}


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
	LinkedNode *p0, *p2, *finalpop, *pbase;
	list<LinkedNode*> pushList;
	list<LinkedNode*> popList;
	
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
			pbase = new LinkedNode;	
			pbase->node.opcode = ir.opcode;
			pbase->node.op1 = val;
			pbase->node.op3 = ir.op3;
			pbase->kill_vec.push_back(ir.op3);			
            cur_LinkedNodeVec->push_back(pbase);
        }
        else
        {
            list<ExpressionNode*>::iterator iterL;
            for(iterL = pExpList->begin(); iterL != pExpList->end(); ++iterL)
            {
                (*iterL)->PrintIR();
            }
            cout << ";PUSH" << endl;
			p0 = new LinkedNode;	
			p0->node.opcode = "PUSH";		
			cur_LinkedNodeVec->push_back(p0);
			
            for(iterL = pExpList->begin(); iterL != pExpList->end(); ++iterL)
            {
                cout << ";PUSH " << (*iterL)->ir.op3 << endl;
				LinkedNode* p1 = new LinkedNode;	
				p1->node.opcode = "PUSH";
				p1->node.op3 = (*iterL)->ir.op3;
				cur_LinkedNodeVec->push_back(p1);
				p1->gen_vec.push_back((*iterL)->ir.op3);
				pushList.push_back(p1);
            }
            cout << ";JSR " << psym->name << endl;
				p2 = new LinkedNode;	
				p2->node.opcode = "JSR";		
				p2->node.op1 = psym->name;
				cur_LinkedNodeVec->push_back(p2);
				
            for (int i = 0; i < psym->num_of_params; i ++)
            {
                cout << ";POP" << endl;
				LinkedNode* p3 = new LinkedNode;	
				p3->node.opcode = "POP";		
				cur_LinkedNodeVec->push_back(p3);
            }
            cout << ";POP " << ir.op3 << endl;
				finalpop = new LinkedNode;	
				finalpop->node.opcode = "POP";		
				finalpop->node.op3 = ir.op3;
				finalpop->kill_vec.push_back(ir.op3);
				cur_LinkedNodeVec->push_back(finalpop);
        }
	}
	virtual void PrintTiny()
    {
		if (!bFunction)
        {
            string reg = ensure(ir.op3);
            cur_LinkedNode ++;
            cout << "move " << val << " " << reg << endl;
            markDirty(reg);
            if ((*cur_LinkedNode)->isleader())
            {
                reset();
            }
        }
        else
        {
            list<ExpressionNode*>::iterator iterL;
            for(iterL = pExpList->begin(); iterL != pExpList->end(); ++iterL)
            {
                (*iterL)->PrintTiny();
            }
            printf("push\n");
            cur_LinkedNode ++;
            for(iterL = pExpList->begin(); iterL != pExpList->end(); ++iterL)
            {
                string reg = ensure((*iterL)->ir.op3);
                cout << "push " << reg << endl;
                check(*cur_LinkedNode);
                cur_LinkedNode ++;
            }
            for (int i = 0; i < MAX_REGISTER_NUM; i ++)
            {
                printf("push r%d\n", i);
            }
            cout << "jsr " << psym->name << endl;
            cur_LinkedNode ++;
            for (int i = MAX_REGISTER_NUM - 1; i > -1; i --)
            {
                printf("pop r%d\n", i);
            }
            for (int i = 0; i < psym->num_of_params; i ++)
            {
                cout << "pop" << endl;
                cur_LinkedNode ++;
            }
            string reg = ensure(ir.op3);
            cout << "pop " << reg << endl;
            markDirty(reg);
            cur_LinkedNode ++;
            if ((*cur_LinkedNode)->isleader())
            {
                reset();
            }
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
	LinkedNode* pcond;
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
        }
			
        return ir.op3;
    }
    
    virtual void PrintIR()
    {
        left->PrintIR();
        right->PrintIR();
        printf(";%s %s %s %s\n", ir.opcode.c_str(), ir.op1.c_str(), ir.op2.c_str(), ir.op3.c_str());
		pcond = new LinkedNode;	
		pcond->node = ir;
		pcond->gen_vec.push_back(ir.op1);
		pcond->gen_vec.push_back(ir.op2);		
		cur_LinkedNodeVec->push_back(pcond);
    }
    
    virtual void PrintTiny()
    {
		left->PrintTiny();
        right->PrintTiny();
				
//		string s3(IR2Tiny(ir.op3));
		string s1(IR2Tiny(ir.op1));

		string s2(ir.op2);
		std::size_t pos = s2.find_first_of("$");
		if(pos != string::npos)
        {
            string reg1 = ensure(ir.op1);
            string reg2 = ensure(ir.op2);
            if(left->type == "INT")
                cout<<"cmpi "<<reg1<<" "<<reg2<<endl;
            else if(left->type == "FLOAT")
                cout<<"cmpr "<<reg1<<" "<<reg2<<endl;
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
        
        reset();
    
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
        check(*cur_LinkedNode);
        cur_LinkedNode ++;
        if ((*cur_LinkedNode)->isleader())
        {
            reset();
        }
    }
};

class OperatorNode: public ExpressionNode
{
public:
	ExpressionNode *left;
	ExpressionNode *right;
	LinkedNode *pOperator;
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
		pOperator = new LinkedNode;	
		pOperator->node.opcode = ir.opcode;
		pOperator->node.op1 = ir.op1;
		pOperator->node.op2 = ir.op2;
		pOperator->node.op3 = ir.op3;
		pOperator->gen_vec.push_back(ir.op1);
		pOperator->gen_vec.push_back(ir.op2);
		pOperator->kill_vec.push_back(ir.op3);
		cur_LinkedNodeVec->push_back(pOperator);
	}
	virtual void PrintTiny()
	{
		left->PrintTiny();
        right->PrintTiny();
        
		string oprtr;
		if(ir.opcode == "ADDI")			oprtr = "addi";
		else if (ir.opcode == "ADDF")	oprtr = "addr";
		else if (ir.opcode == "SUBI")	oprtr = "subi";
		else if (ir.opcode == "SUBF")	oprtr = "subr";
		else if (ir.opcode == "MULTI")	oprtr = "muli";
		else if (ir.opcode == "MULTF")	oprtr = "mulr";
		else if (ir.opcode == "DIVI")	oprtr = "divi";
        else if (ir.opcode == "DIVF")	oprtr = "divr";
        
        string reg1 = ensure(ir.op1);
        string reg2 = ensure(ir.op2);
        string reg3 = ensure(ir.op3);
        
        printf("move %s %s\n", reg1.c_str(), reg3.c_str());
        printf("%s %s %s\n", oprtr.c_str(), reg2.c_str(), reg3.c_str());
        markDirty(reg3);
        
        check(*cur_LinkedNode);
        cur_LinkedNode ++;
        if ((*cur_LinkedNode)->isleader())
        {
            reset();
        }
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
	LinkedNode *pStore, *pRet;
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
        
        pStore = new LinkedNode;
        pStore->node.opcode = ir.opcode;
        pStore->node.op1 = ir.op1;
        pStore->node.op2 = ir.op3;
		pStore->kill_vec.push_back(ir.op3);
		pStore->gen_vec.push_back(ir.op1);
        cur_LinkedNodeVec->push_back(pStore);
        
        pStore = new LinkedNode;
        pStore->node.opcode = ir.opcode;
        pStore->node.op1 = ir.op3;
        pStore->node.op3 = "$R";
//		pStore->kill_vec.push_back("$R");
		pStore->gen_vec.push_back(pStore->node.op1);
        cur_LinkedNodeVec->push_back(pStore);
        
        pRet = new LinkedNode;
        pRet->node.opcode = "RET";
		//Xin Need to gen?
		//pRet->gen_vec.push_back("$R");
        cur_LinkedNodeVec->push_back(pRet);
        printf(";RET\n");
		
    }
    virtual void PrintTiny()
    {
        pExpNode->PrintTiny();
        string reg1 = ensure(ir.op1);
        string reg2 = ensure(ir.op3);
        printf("move %s %s\n", reg1.c_str(), reg2.c_str());
        printf("move %s $%d\n", reg2.c_str(), (int)R_NUM + pCurentSym->num_of_params + 1);
        cur_LinkedNode++;
        cur_LinkedNode++;
        cur_LinkedNode++;
        reset();
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
	LinkedNode *pBreak, *pContinue, *pElse, *pLabel, *pLabel1, *pLabel2, *pLabel3;
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
				//TODO
				pBreak = new LinkedNode;
				pBreak->node.opcode = "JUMP";
				pBreak->node.op1 = whileLabelEnd;
				cur_LinkedNodeVec->push_back(pBreak);
            }
            else if ((*iter)->name == "CONTINUE")
            {
                printf(";JUMP %s\n", whileLabelEnd.c_str());
				pContinue = new LinkedNode;
				pContinue->node.opcode = "JUMP";
				pContinue->node.op1 = whileLabelEnd;
				cur_LinkedNodeVec->push_back(pContinue);
            }
            
            (*iter)->PrintIR();
        }
        if (pElsePart->size() != 0)
        {
            printf(";JUMP %s\n", jmpLabel.c_str());
			pElse = new LinkedNode;	
			pElse->node.opcode = "JUMP";	
			pElse->node.op1 = jmpLabel;		
			cur_LinkedNodeVec->push_back(pElse);
        }
        printf(";LABEL %s\n", pCmpNode->ir.op3.c_str());
		pLabel = new LinkedNode;	
		pLabel->node.opcode = "LABEL";	
		pLabel->node.op3 = pCmpNode->ir.op3;		
		cur_LinkedNodeVec->push_back(pLabel);
		
        if (pElsePart->size() != 0)
        {
            for (iter = pElsePart->begin(); iter != pElsePart->end(); iter ++)
            {
                if ((*iter)->name == "BREAK")
                {
                    printf(";JUMP %s\n", whileLabelEnd.c_str());
					//TODO name
					pLabel2 = new LinkedNode;	
					pLabel2->node.opcode = "LABEL";
					pLabel2->node.op1 = whileLabelEnd;		
					cur_LinkedNodeVec->push_back(pLabel2);
                }
                else if ((*iter)->name == "CONTINUE")
                {
                    printf(";JUMP %s\n", whileLabelEnd.c_str());
					pLabel3 = new LinkedNode;	
					pLabel3->node.opcode = "LABEL";
					pLabel3->node.op1 = whileLabelEnd;		
					cur_LinkedNodeVec->push_back(pLabel3);
                }
                
                (*iter)->PrintIR();
            }
            printf(";LABEL %s\n", jmpLabel.c_str());
			pLabel1 = new LinkedNode;	
			pLabel1->node.opcode = "LABEL";
			pLabel1->node.op1 = jmpLabel;		
			cur_LinkedNodeVec->push_back(pLabel1);
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
                reset();
                cur_LinkedNode++;
                printf("jmp %s\n", whileLabelEnd.c_str());
            }
            else if ((*iter)->name == "CONTINUE")
            {
                reset();
                cur_LinkedNode++;
                printf("jmp %s\n", whileLabelBegin.c_str());
            }

            (*iter)->PrintTiny();
        }
        if (pElsePart->size() != 0)
        {
            reset();
            cur_LinkedNode++;
            printf("jmp %s\n", jmpLabel.c_str());
        }
        printf("label %s\n", pCmpNode->ir.op3.c_str());
        cur_LinkedNode++;
        if (pElsePart->size() != 0)
        {
            for (iter = pElsePart->begin(); iter != pElsePart->end(); iter ++)
            {
                if ((*iter)->name == "BREAK")
                {
                    reset();
                    cur_LinkedNode++;
                    printf("jmp %s\n", whileLabelEnd.c_str());
                }
                else if ((*iter)->name == "CONTINUE")
                {
                    reset();
                    cur_LinkedNode++;
                    printf("jmp %s\n", whileLabelBegin.c_str());
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
	LinkedNode *pwhile, *pwhile1, *pjump, *pjump1, *pjump2;
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
		pwhile = new LinkedNode;	
		pwhile->node.opcode = "LABEL";
		pwhile->node.op1 = whileLabel;		
		cur_LinkedNodeVec->push_back(pwhile);
		
        pCmpNode->PrintIR();
        list<Statement*>::iterator iter;
        for (iter = pAug->begin(); iter != pAug->end(); iter ++)
        {
            if ((*iter)->name == "BREAK")
            {
                printf(";JUMP %s\n", pCmpNode->ir.op3.c_str());
				pjump = new LinkedNode;	
				pjump->node.opcode = "JUMP";
				pjump->node.op3 = pCmpNode->ir.op3;		
				cur_LinkedNodeVec->push_back(pjump);
            }
            else if ((*iter)->name == "CONTINUE")
            {
                printf(";JUMP %s\n", whileLabel.c_str());
				pjump1 = new LinkedNode;	
				pjump1->node.opcode = "JUMP";
				pjump1->node.op1 = whileLabel;		
				cur_LinkedNodeVec->push_back(pjump1);
            }
            
            (*iter)->PrintIR();
        }
        printf(";JUMP %s\n", whileLabel.c_str());
		pjump2 = new LinkedNode;	
		pjump2->node.opcode = "JUMP";
		pjump2->node.op1 = whileLabel;		
		cur_LinkedNodeVec->push_back(pjump2);
		
        printf(";LABEL %s\n", pCmpNode->ir.op3.c_str());
		pwhile1 = new LinkedNode;	
		pwhile1->node.opcode = "LABEL";
		pwhile1->node.op3 = pCmpNode->ir.op3;		
		cur_LinkedNodeVec->push_back(pwhile1);
    }

    virtual void PrintTiny()
    {
        cur_LinkedNode++;
        printf("label %s\n", whileLabel.c_str());
        pCmpNode->PrintTiny();
        list<Statement*>::iterator iter;
        for (iter = pAug->begin(); iter != pAug->end(); iter ++)
        {
            if ((*iter)->name == "BREAK")
            {
                reset();
                cur_LinkedNode++;
                printf("jump %s\n", pCmpNode->ir.op3.c_str());
            }
            else if ((*iter)->name == "CONTINUE")
            {
                reset();
                cur_LinkedNode++;
                printf("label %s\n", whileLabel.c_str());
            }
            (*iter)->PrintTiny();
        }
        reset();
        cur_LinkedNode++;
        printf("jmp %s\n", whileLabel.c_str());
        cur_LinkedNode++;
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
	LinkedNode* pAssign;
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
		pAssign = new LinkedNode;
		pAssign->node = ir;
		pAssign->gen_vec.push_back(ir.op1);
		pAssign->kill_vec.push_back(ir.op3);
		cur_LinkedNodeVec->push_back(pAssign);
	}
	virtual void PrintTiny()
	{
        pExpNode->PrintTiny();
		string str(ir.op1);
		std::size_t pos = str.find_first_of("1234567890");
        if(pos != string::npos)
        {
            string reg1 = ensure(ir.op1);
            string reg2 = ensure(ir.op3);
            printf("move %s %s\n", reg1.c_str(), reg2.c_str());
            markDirty(reg2);
        }
        else
        {
			string reg1 = ensure(tmp);
            string reg2 = ensure(ir.op3);
		    printf("move %s %s\n", str.c_str(), reg1.c_str());
		    printf("move %s %s\n", reg1.c_str(), reg2.c_str());
    	}
        
        check(*cur_LinkedNode);
        cur_LinkedNode ++;
        if ((*cur_LinkedNode)->isleader())
        {
            reset();
        }
    }
};

class ReadStatement : public Statement
{
public:
	string name;
	string type;
	IRNode ir;
	LinkedNode* pRead;
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
		pRead = new LinkedNode;
		pRead->node = ir;
		pRead->kill_vec.push_back(ir.op1);
		cur_LinkedNodeVec->push_back(pRead);
	}
	virtual void PrintTiny()
	{
		string str;
		if(type == "INT")
		{
            str = "sys readi";
            string reg = ensure(ir.op1);
            printf("%s %s\n", str.c_str(), reg.c_str());
            markDirty(reg);
		}
		else
		{
            str = "sys readr";
            printf("%s %s\n", str.c_str(), IR2Tiny(ir.op1).c_str());
        }
        
        check(*cur_LinkedNode);
        cur_LinkedNode ++;
        if ((*cur_LinkedNode)->isleader())
        {
            reset();
        }
	}
};

class WriteStatement : public Statement
{
public:
	string name;
	string type;
	IRNode ir;
	LinkedNode* pWrite;
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
		pWrite = new LinkedNode;
		pWrite->node = ir;
		pWrite->gen_vec.push_back(ir.op1);
		cur_LinkedNodeVec->push_back(pWrite);
	}
	virtual void PrintTiny()
	{
		string str;
		if(type == "INT")
		{
            str = "sys writei";
            string reg = ensure(ir.op1);
            printf("%s %s\n", str.c_str(), reg.c_str());
		}
		else if(type == "FLOAT")
		{
            str = "sys writer";
            string reg = ensure(ir.op1);
            printf("%s %s\n", str.c_str(), reg.c_str());
		}
		else
		{
            str = "sys writes";
            printf("%s %s\n", str.c_str(), IR2Tiny(ir.op1).c_str());;
		}
        check(*cur_LinkedNode);
        cur_LinkedNode ++;
        if (cur_LinkedNode != (*cur_LinkedNodeVec).end() && (*cur_LinkedNode)->isleader())
        {
            reset();
        }
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
	vector<LinkedNode*> *LinkedNodeVec;
	LinkedNode *p1, *p2;
    Function(list<Statement*> *_pStatementList, string _returnType, string _name, struct symbol* _psym) : pStatementsList(_pStatementList),returnType(_returnType), name(_name), psym(_psym) 
	{
		LinkedNodeVec = new vector<LinkedNode*>();
        cur_LinkedNodeVec = LinkedNodeVec;
	}

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
        cur_LinkedNodeVec = this->LinkedNodeVec;
        printf(";LABEL %s\n", name.c_str());
		p1 = new LinkedNode;	
		p1->node.opcode = "LABEL";
		p1->node.op1 = name;		
		cur_LinkedNodeVec->push_back(p1);
        printf(";LINK\n");
		p2 = new LinkedNode;	
		p2->node.opcode = "LINK";		
		cur_LinkedNodeVec->push_back(p2);
		
        list<Statement*>::iterator iter;
        for (iter = pStatementsList->begin(); iter != pStatementsList->end(); iter ++)
        {
            (*iter)->PrintIR();
        }
		
		vector<LinkedNode*>::iterator iter_rtn = cur_LinkedNodeVec->end();
		iter_rtn --;
		if ((*iter_rtn)->node.opcode != "RET")
		{
			printf(";RET\n");
		}
    }
    virtual void PrintTiny()
    {
        cur_LinkedNodeVec = this->LinkedNodeVec;
        cur_LinkedNode = cur_LinkedNodeVec->begin();
        cur_LinkedNode ++;
        cur_LinkedNode ++;
        printf("label %s\n", name.c_str());
        printf("link %d\n", psym->num_of_locals + this->max_index - 1);
        list<Statement*>::iterator iter;
        for (iter = pStatementsList->begin(); iter != pStatementsList->end(); iter ++)
        {
            (*iter)->PrintTiny();
        }

		vector<LinkedNode*>::iterator iter_rtn = cur_LinkedNodeVec->end();
		iter_rtn --;
		if ((*iter_rtn)->node.opcode != "RET")
		{
			printf("unlnk\n");
			printf("ret\n");
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
        list<Function*>::iterator iterFunc;
        vector<LinkedNode*>::iterator iterNode;
        for (iterFunc = pFunctionList->begin(); iterFunc != pFunctionList->end(); iterFunc ++)
        {
            pCurentSym = (*iterFunc)->psym;
            (*iterFunc)->PrintIR();
        }
        
		for (iterFunc = pFunctionList->begin(); iterFunc != pFunctionList->end(); iterFunc ++)
        {
            vector<LinkedNode*>::iterator iterAllNodesInThisFunc;
            LinkedNode* pCurNode;
            LinkedNode* pNextNode;
			
			for(iterNode = (*iterFunc)->LinkedNodeVec->begin(); iterNode != (*iterFunc)->LinkedNodeVec->end()-1; iterNode ++)
			{
				pCurNode = *iterNode;
				pNextNode = *(iterNode + 1);
                
//                if(p1->node.opcode != "RET" && p1->node.opcode != "JUMP")
//                printf("%s\n", pCurNode->node.opcode.c_str());
                if(pNextNode->node.opcode != "LABEL")
                {
                    pNextNode->preList.push_back(pCurNode);
                }
                pCurNode->sucList.push_back(pNextNode);
				
				if(pCurNode->node.opcode == "JUMP")
				{
					for(iterAllNodesInThisFunc = (*iterFunc)->LinkedNodeVec->begin();
                        iterAllNodesInThisFunc != (*iterFunc)->LinkedNodeVec->end();
                        iterAllNodesInThisFunc ++)
					{
						if(pCurNode->node.op1 == (*iterAllNodesInThisFunc)->node.op1
                           && (*iterAllNodesInThisFunc)->node.opcode == "LABEL")
						{
                            pCurNode->sucList.clear();
							pCurNode->sucList.push_back(*iterAllNodesInThisFunc);
							(*iterAllNodesInThisFunc)->preList.push_back(pCurNode);
							break;
						}	
					}
				}
				
				if(pCurNode->node.opcode == "NEI" || pCurNode->node.opcode == "NEF" ||
                   pCurNode->node.opcode == "EQI" || pCurNode->node.opcode == "EQF" ||
                   pCurNode->node.opcode == "GEI" || pCurNode->node.opcode == "GEF" ||
                   pCurNode->node.opcode == "LEI" || pCurNode->node.opcode == "LEF" ||
                   pCurNode->node.opcode == "GTI" || pCurNode->node.opcode == "GTF" ||
                   pCurNode->node.opcode == "LTI" || pCurNode->node.opcode == "LTF" )
                {
                    for(iterAllNodesInThisFunc = (*iterFunc)->LinkedNodeVec->begin();
                        iterAllNodesInThisFunc != (*iterFunc)->LinkedNodeVec->end();
                        iterAllNodesInThisFunc ++)
					{
						if(pCurNode->node.op3 == (*iterAllNodesInThisFunc)->node.op3 &&
                           (*iterAllNodesInThisFunc)->node.opcode == "LABEL")
						{	
							pCurNode->sucList.push_back(*iterAllNodesInThisFunc);
							(*iterAllNodesInThisFunc)->preList.push_back(pCurNode);
							break;
						}
					}
				}
			}
        }
        
        for(iterFunc = pFunctionList->begin(); iterFunc != pFunctionList->end(); ++iterFunc)
		{	
			while(1)
			{
				bool unchanged = true;
				vector<LinkedNode*>::iterator iter_beg = (*iterFunc)->LinkedNodeVec->begin(); 
				vector<LinkedNode*>::iterator iter = (*iterFunc)->LinkedNodeVec->end();
				iter--;
				iter_beg--;
				for(; iter != iter_beg; --iter)
				{
					if((*iter)->node.opcode == "RET")
					{
						vector<struct variable*>::iterator iter1 = psym->var.begin(); 
						vector<struct variable*>::iterator iter_end1 = psym->var.end();
						for(; iter1 != iter_end1; ++iter1)
						{	
							string s_type = (*iter1)->type;
							if(s_type != "STRING")
							{
								vector<string>::iterator it1 = (*iter)->live_out_vec.begin();
								vector<string>::iterator it1_end = (*iter)->live_out_vec.end();
								for(; it1 != it1_end; ++it1) 
								{
									if(*it1 == string((*iter1)->irname))
										break;
								}
								if(it1 == it1_end)
								{	
									unchanged = false;
									(*iter)->live_out_vec.push_back(string((*iter1)->irname));
									(*iter)->live_in_vec.push_back(string((*iter1)->irname));
								}
							}
						}
						
						vector<string>::iterator iteruse = (*iter)->gen_vec.begin();
						vector<string>::iterator iteruse_end = (*iter)->gen_vec.end();
						for(; iteruse != iteruse_end; ++iteruse)
						{
							vector<string>::iterator it1 = (*iter)->live_in_vec.begin();
							vector<string>::iterator it1_end = (*iter)->live_in_vec.end();
							for(; it1 != it1_end; ++it1) 
							{
								if(*it1 == *iteruse)
									break;
							}
							
							if(it1 == it1_end)
								(*iter)->live_in_vec.push_back(*iteruse);
						}	
					}
					else
					{
						vector<LinkedNode*>::iterator iter2 = (*iter)->sucList.begin();
						vector<LinkedNode*>::iterator iter2_end = (*iter)->sucList.end();
						for(; iter2 != iter2_end; ++iter2) 
						{//	
							vector<string>::iterator it = (*iter2)->live_in_vec.begin();
							vector<string>::iterator it_end = (*iter2)->live_in_vec.end();
							for(; it != it_end; ++it) 
							{
								vector<string>::iterator it1 = (*iter)->live_out_vec.begin();
								vector<string>::iterator it1_end = (*iter)->live_out_vec.end();
								for(; it1 != it1_end; ++it1) 
								{
									if(*it1 == *it)
										break;
								}
								
								if(it1 == it1_end)
								{	
									unchanged = false;
									(*iter)->live_out_vec.push_back(*it);
									(*iter)->live_in_vec.push_back(*it);
								}
							}
						}//
						
						vector<string>::iterator it = (*iter)->kill_vec.begin();
						vector<string>::iterator it_end = (*iter)->kill_vec.end();
						for(; it != it_end; ++it) 
						{
							vector<string>::iterator it1 = (*iter)->live_in_vec.begin();
							vector<string>::iterator it1_end = (*iter)->live_in_vec.end();
							for(; it1 != it1_end;) 
							{
								if(*it1 == *it)
								{
									it1 = (*iter)->live_in_vec.erase(it1);
									break;
								}
								else
									it1++;
							}
						}
						
						it = (*iter)->gen_vec.begin();
						it_end = (*iter)->gen_vec.end();
						for(; it != it_end; ++it) 
						{
							vector<string>::iterator it1 = (*iter)->live_in_vec.begin();
							vector<string>::iterator it1_end = (*iter)->live_in_vec.end();
							for(; it1 != it1_end; ++it1) 
							{
								if(*it1 == *it)
									break;
							}
							
							if(it1 == it1_end)
								(*iter)->live_in_vec.push_back(*it);
						}
						
					}
				}
				
				if(unchanged) break;
			}
		}
		
         printf(";Second Verify**********************************\n");
        for (iterFunc = pFunctionList->begin(); iterFunc != pFunctionList->end(); iterFunc ++)
        {
            for (iterNode = (*iterFunc)->LinkedNodeVec->begin(); iterNode != (*iterFunc)->LinkedNodeVec->end(); iterNode ++)
            {
				cout<<";";
                (*iterNode)->output();
                
/*                vector<LinkedNode*>::iterator iter;
                cout << " {PRED nodes:";
                for(iter = (*iterNode)->preList.begin(); iter != (*iterNode)->preList.end(); iter++)
                {
                    cout<<" ";
                    (*iter)->output();
                }
                cout<<"} {SUCC nodes:";
                for(iter = (*iterNode)->sucList.begin(); iter != (*iterNode)->sucList.end(); iter++)
                {
                    cout<<" ";
                    (*iter)->output();
                }
                cout << "}";*/
				
				vector<string>::iterator Iter2;
				cout<<"     {GEN:";
				for(Iter2 = (*iterNode)->gen_vec.begin(); Iter2 != (*iterNode)->gen_vec.end(); Iter2++)
				{
					cout<<" "<<*Iter2;
				}
				cout<<"}    {KILL:";
				for(Iter2 = (*iterNode)->kill_vec.begin(); Iter2 != (*iterNode)->kill_vec.end(); Iter2++)
				{
					cout<<" "<<*Iter2;
                }
                cout<<"}";
                cout<<"    {OUT:";
                for(Iter2 = (*iterNode)->live_out_vec.begin(); Iter2 != (*iterNode)->live_out_vec.end(); Iter2++)
                {
                    cout<<" "<<*Iter2;
                }
				cout<<"}";
				
                cout << endl;
            }
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
        list<Function*>::iterator iterFunc;
        for (iterFunc = pFunctionList->begin(); iterFunc != pFunctionList->end(); iterFunc ++)
        {
            pCurentSym = (*iterFunc)->psym;
/*            if ((*iterFunc)->name != "main")
            {
                R_NUM = R_NUM_BASE + psym->children.size() - 1;
            }
            else
            {
                R_NUM = R_NUM_BASE;
            }*/
            max_reg_index = (*iterFunc)->max_index;
            (*iterFunc)->PrintTiny();
        }
        printf("end\n");
    }
};



#endif
