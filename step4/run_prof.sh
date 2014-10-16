#! /bin/bash

i=1
while [ $i -le 22 ]
do
    echo "testcase: $i"
    inputfilename="/home/min/a/liu1274/Documents/input/test$i.micro"
    if [ -f $inputfilename ]; then
        outputfilename="/home/min/a/liu1274/Documents/ouroutput/myout$i.out"
        standardout="/home/min/a/liu1274/Documents/output/573/test$i.out"
        ./build/Micro $inputfilename > $outputfilename
        diff -b -B $outputfilename $standardout
    fi
    echo
    ((i++))
done
