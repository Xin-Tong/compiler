#! /bin/bash

i=1
while [ $i -le 22 ]
do
    echo "testcase: $i"
    inputfilename="/home/min/a/tong24/Desktop/compiler/step2/liu1274/input/test$i.micro"
    if [ -f $inputfilename ]; then
        outputfilename="/home/min/a/tong24/Desktop/compiler/step2/liu1274/ouroutput/myout$i.out"
        standardout="/home/min/a/tong24/Desktop/compiler/step2/liu1274/output/test$i.out"
        ./build/Micro $inputfilename > $outputfilename
        diff -b -B $outputfilename $standardout
    fi
    echo
    ((i++))
done
