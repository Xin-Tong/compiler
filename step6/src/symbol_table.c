#include "symbol_table.h"

struct variable* Find_Variable(string _name, struct symbol* _psym, bool _print)
{
	if(_psym == NULL)
	{
		return false;
	}
	struct variable* signal = NULL;
	if(_psym->father != NULL)
	{
		signal = Find_Variable(_name, _psym->father, _print);
	}
    if(signal != NULL)
    {
        return signal;    
    }
	string str_val;
	vector<struct variable*>::iterator iter;
	for(iter = _psym->var.begin(); iter != _psym->var.end(); iter ++)
	{
		str_val = (*iter)->name;
		if(_name == (*iter)->name)
		{
			signal = *iter;
			if (_print)
			{
				printf("SHADOW WARNING %s\n", _name.c_str());
			}
		}
	}
	
	return signal;
}

struct symbol* Sym_Alloc(string _name, struct symbol* _father, string _scope, string _level)
{
    struct symbol* s_root = ( struct symbol*)malloc(sizeof(struct symbol));
    if (s_root)
    {
        memset(s_root, 0, sizeof(struct symbol));
        int len = _name.length();
		s_root->name = (char*)malloc((len+1)*sizeof(char));
		_name.copy(s_root->name, len, 0);
		s_root->name[len] = 0;
//        s_root->scope = _scope;
//        s_root->level = _level;
        s_root->children.clear();
        s_root->var.clear();
		s_root->father = _father;
		if(_father != NULL)
		{
			_father->children.push_back(s_root);
		}
		return s_root;
	}
	else
	{
		return NULL;
	}
}

int Variable_Add(struct symbol* _psym, string _name, string _type, string _value, string _opt)
{
    if(_psym == NULL)
    {
        return -1;
    }
    struct variable* signal = NULL;
	vector<struct variable*>::iterator iter;
	string str_val;
	for(iter = _psym->var.begin(); iter != _psym->var.end(); iter ++)
	{
		str_val = (*iter)->name;
		if(_name == str_val)
		{
			signal = *iter;
            printf("DECLARATION ERROR %s\n", _name.c_str());
			exit(0);
		}
	}
    if(_psym->father != NULL)
    {
        signal = Find_Variable(_name, _psym->father, true);
    }

    struct variable *var = (struct variable *) malloc(sizeof(struct variable));
    memset(var, 0, sizeof(struct variable));
	int len = _name.length();
	var->name = (char*)malloc((len+1)*sizeof(char));
	_name.copy(var->name, len, 0);
	var->name[len] = 0;

	len = _type.length();
	var->type = (char*)malloc((len+1)*sizeof(char));
	_type.copy(var->type, len, 0);
	var->type[len] = 0;

	len = _value.length();
	var->value = (char*)malloc((len+1)*sizeof(char));
	_value.copy(var->value, len, 0);
	var->value[len] = 0;

	stringstream ss;
	string irname;
	if(_psym->father != NULL)
	{
		if (_opt == "param")
		{
			_psym->num_of_params ++;
			ss << _psym->num_of_params;
			ss >> irname;
			irname = "$P" + irname;
//			printf("Now we have a new param named as %s\n", tinyname.c_str());
		}
		else if (_opt == "local")
		{
			_psym->num_of_locals ++;
			ss << _psym->num_of_locals;
			ss >> irname;
			irname = "$L" + irname;
//			printf("Now we have a new local named as %s\n", tinyname.c_str());
		}
	}
	// global variable should not have tiny name
	else
	{
		irname = _name;
	}
	len = irname.length();
	var->irname = (char*)malloc((len+1)*sizeof(char));
	irname.copy(var->irname, len, 0);
	var->irname[len] = 0;

    _psym->var.push_back(var);
}

void Print_Symbol(struct symbol* _psym)
{
    if(_psym == NULL)
    {
        return;
    }

    printf("Symbol table %s\n", _psym->name);

    vector<variable*>::iterator iter;
	string s_type;
	for(iter = _psym->var.begin(); iter != _psym->var.end(); iter ++)
	{
		s_type = (*iter)->type;
        if (s_type == "INT" || s_type == "FLOAT")
        {
	        printf("name %s type %s\n", (*iter)->name, (*iter)->type);
        }
        else
        {
            printf("name %s type %s value %s\n", (*iter)->name, (*iter)->type, (*iter)->value);
        }
	}
    if(_psym->children.size() != 0)
    {
        vector<struct symbol*>::iterator iter_sym;
        for(iter_sym = _psym->children.begin(); iter_sym != _psym->children.end(); iter_sym ++)
        {
            if ((*iter_sym) != NULL)
            {
                printf("\n");
                Print_Symbol(*iter_sym);
            }
        }
    }   
}

void str2pchar(string _str, char* _pchar)
{
	int len = _str.length();
	_pchar = (char*)malloc((len+1)*sizeof(char));
	_str.copy(_pchar, len, 0);
	_pchar[len] = 0;
}

void IRCode_Add(string _str, struct ircode* _ir)
{
	struct ircode* temp_ir = (struct ircode*) malloc(sizeof(struct ircode));
	str2pchar(_str, temp_ir->content);
	temp_ir->next = NULL;
	if(_ir != NULL)
	{
		_ir->next = temp_ir;
	}
	_ir = temp_ir;
}

void Print_Code(struct ircode* _root, struct ircode* _tinyroot, struct symbol* _psym)
{
	printf(";IR code\n");
	printf(";LABEL main\n");
	printf(";LINK\n");
	struct ircode* temp_ir = _root;
	while(temp_ir != NULL)
	{
		printf(";%s\n", temp_ir->content);
		temp_ir = temp_ir->next;
	}
	printf(";RET\n");
	printf(";tiny code\n");
	string s_type;
	vector<variable*>::iterator iter;
	for(iter = _psym->var.begin(); iter != _psym->var.end(); iter ++)
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
	temp_ir = _tinyroot;
	while(temp_ir != NULL)
	{
		printf(";%s\n", temp_ir->content);
		temp_ir = temp_ir->next;
	}
}




