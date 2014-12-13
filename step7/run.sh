rm *.out
make clean
make
mkdir myout

i=0;
for file in input/*.micro
do  
    ./build/Micro $file -> myout/$i.out
    echo $file
    let ++i
done
