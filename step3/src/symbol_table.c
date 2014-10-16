#include "symbol_table.h"

bool Find_Variable(string _name, struct symbol* _psym)
{
	if(_psym == NULL)
	{
		return false;
	}
	bool signal = false;
	if(_psym->father != NULL)
	{
		signal = Find_Variable(_name, _psym->father);
	}
    if(signal)
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
			signal = true;
            printf("SHADOW WARNING %s\n", _name.c_str());
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

int Variable_Add(struct symbol* _psym, string _name, string _type, string _value)
{
    if(_psym == NULL)
    {
        return -1;
    }
    bool signal = false;
	vector<struct variable*>::iterator iter;
	string str_val;
	for(iter = _psym->var.begin(); iter != _psym->var.end(); iter ++)
	{
		str_val = (*iter)->name;
		if(_name == str_val)
		{
			signal = true;
            printf("DECLARATION ERROR %s\n", _name.c_str());
			exit(0);
		}
	}
    if(_psym->father != NULL)
    {
        signal = Find_Variable(_name, _psym->father);
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







