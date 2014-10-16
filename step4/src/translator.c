#include <iostream>
#include "translator.h"

node *left;
node *right;

void printIR(){
    left -> printIR();
    right -> printIR();
    cout<<"; "<<ir.opcode;
    cout<<" "<<ir.op1;
    cout<<" "<<ir.op2;
    cout<<" "<<ir.op3;
    cout<<endl;
}
   
void printTiny(){
    left -> printTiny();
    right -> printTiny();
    
    string s3(ir.op3);
    std::size_t found = s3.find_first_of("1234567890");
    s3.replace(0, found, "r");

    string s2(ir.op2);
    found = s2.find_first_of("$");
    if(found != string::npos)
        s1.replace(0, 2, "r");  //replace $T with r
    
    string s1(ir.op1);
    found = s1.find_first_of("$");
    if(found != string::npos)
        s1.replace(0, 2, "r");

    string str_op;

    if(ir.opcode == "ADDI") str_op = "addi";
    else if (ir.opcode == "ADDF") str_op = "addr";
    else if (ir.opcode == "SUBI") str_op = "subi";
    else if (ir.opcode == "SUBF") str_op = "subr";
    else if (ir.opcode == "MULTI") str_op = "muli";
    else if (ir.opcode == "MULTF") str_op = "mulr";
    else if (ir.opcode == "DIVI") str_op = "divi";
    else if (ir.opcode == "DIVF") str_op = "divr";

    cout<<"move "<<s1<<" "<<s3<<endl;
    cout<<str_op<<" "<<s2<<" "<<s3<<endl;
}



