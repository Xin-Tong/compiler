make clean
make
mkdir myout
./build/Micro ../step5/input/test_if.micro > myout/if.out 
./build/Micro ../step5/input/test_while.micro > myout/while.out 
./build/Micro ../step5/input/test_573.micro > myout/573.out 
./build/Micro ../step5/input/test_adv.micro > myout/adv.out
./build/Micro ../step5/input/step4_testcase.micro > myout/step4.out 
./build/Micro ../step5/input/step4_testcase2.micro > myout/step4_2.out 
./build/Micro ../step4/input/test1.micro > myout/1.out
./build/Micro ../step4/input/test2.micro > myout/2.out
./build/Micro ../step4/input/test3.micro > myout/3.out
./build/Micro ../step6/input/factorial2.micro > myout/factorial2.out 
./build/Micro ../step6/input/fibonacci2.micro > myout/fibnacci2.out 
./build/Micro ../step6/input/fma.micro > myout/fma.out
