
file=car
arg1=champions/$file.s
arg2=champions/$file.cor

rm test1 test2
make && ./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
diff -u test1 test2
