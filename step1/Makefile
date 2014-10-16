all: compiler group

group:
	echo "Jianqiao Liu--liu1274;Xin Tong--tong24"	

compiler: 
	mkdir generated
	mkdir build
	lex src/lex_example.l
	gcc lex.yy.c -o Micro -ll
	mv Micro build/
	mv lex.yy.c generated/
	
clean:
	rm -rf generated/
	rm -rf build/ 
