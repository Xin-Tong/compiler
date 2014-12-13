all: group compiler

group:
	echo "We are Jianqiao Liu (liu1274) and Xin Tong (tong24)"

compiler:
	mkdir build
	mkdir generated
	lex ./src/lex.l
	mv ./lex.yy.c ./generated/
	yacc -d ./src/yacc.y
	mv ./y.tab.c ./generated/
	mv ./y.tab.h ./generated/	
	g++ ./generated/lex.yy.c -g ./generated/y.tab.c ./src/symbol_table.h ./src/symbol_table.c -o ./build/Micro -ll

clean:
	rm -rf build
	rm -rf generated
	rm -rf *~ my* 
	rm -rf *.c *.h
