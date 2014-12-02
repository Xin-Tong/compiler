make clean
make

./build/Micro ~/ECE573_git/compiler/step6/input/fma.micro > our_fma.out
diff our_fma.out ./output/fma.out
