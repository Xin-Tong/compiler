#ifndef __SYMBOL_TABLE_H_
#define __SYMBOL_TABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <memory.h>

using namespace std;

struct variable
{
    char* name;
    char* type;
    char* value;
};

struct symbol
{
    struct symbol* father;
    char* name;
//    string scope;   // GLOBAL | LOCAL
//    string level;   // PROGRAM | FUNCTION | BLOCK
    vector<struct symbol*> children;
    vector<struct variable*> var;
};

extern bool Find_Variable(string name, struct symbol* psym);
extern struct symbol* Sym_Alloc(string _name, struct symbol* _father, string _scope, string _level);
extern int Variable_Add(struct symbol* _psym, string _name, string _type, string _value);
extern void Print_Symbol(struct symbol* _psym);


#endif
