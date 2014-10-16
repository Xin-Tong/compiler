rm -rf my_*
lex lex_example.l 
gcc lex.yy.c -o analyse -ll
analyse fibonacci.micro >> my_fibonacci.out
analyse loop.micro >> my_loop.out
analyse loopbreak.micro >> my_loopbreak.out
analyse nested.micro >> my_nested.out
analyse sqrt.micro >> my_sqrt.out

diff -b -B my_fibonacci.out fibonacci.out
diff -b -B my_loop.out loop.out
diff -b -B my_loopbreak.out loopbreak.out
diff -b -B my_nested.out nested.out
diff -b -b my_sqrt.out sqrt.out
