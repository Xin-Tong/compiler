rm lex.yy.c y* analyse;
lex lex_yacc_exp.l
yacc -d lex_yacc_exp.y
gcc lex.yy.c y.tab.c -o analyse -ll
#./analyse < ./input/test1.micro
#./analyse < ./input/test2.micro
#./analyse < ./input/test3.micro
#./analyse < ./input/test4.micro
#./analyse < ./input/test5.micro
./analyse < ./input/test6.micro
./analyse < ./input/test7.micro
#./analyse < ./input/test8.micro
#./analyse < ./input/test9.micro
#./analyse < ./input/test10.micro
#./analyse < ./input/test11.micro
#./analyse < ./input/test12.micro
#./analyse < ./input/test13.micro
#./analyse < ./input/test14.micro
#./analyse < ./input/test15.micro
#./analyse < ./input/test16.micro
#./analyse < ./input/test17.micro
#./analyse < ./input/test18.micro
#./analyse < ./input/test19.micro
./analyse < ./input/test20.micro
#./analyse < ./input/test21.micro
#./analyse < ./input/test22.micro


