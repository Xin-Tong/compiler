all: group compiler

group:
	echo "We are Jianqiao Liu (liu1274) and Xin Tong (tong24)"

compiler:
	mkdir build
	mkdir generated
	flex ./src/lex.l
	mv ./lex.yy.c ./generated/
#	yacc -d ./src/yacc.y
	bison -d ./src/yacc.y
	mv ./yacc.tab.c ./generated/
	mv ./yacc.tab.h ./generated/	
	g++ ./generated/lex.yy.c ./generated/yacc.tab.c -o ./build/Micro -ll

clean:
	rm -rf build
	rm -rf generated
	rm -rf *~ my* 
	rm -rf *.c *.h
