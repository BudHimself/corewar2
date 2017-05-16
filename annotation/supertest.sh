
file=examples/fluttershy
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
make && ./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"

file=examples/helltrain
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm "$arg1" && hexdump "$arg2" > test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null 

file=examples/zork
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm "$arg1" && hexdump "$arg2" > test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null
file=examples/bigzork
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=examples/turtle
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=ex
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=42
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=Backward
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=Car
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=Death
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=Gagnant
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=Octobre_Rouge_V4.2
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=Survivor
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=Torpille
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=barriere
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=jumper
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=lde
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=leeloo
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=mat
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=maxidef
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=mortel
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=new
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=new
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=sebc
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=slider2
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=tdc2
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=tdc3
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=tdc4
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null

file=toto
arg1=champions/$file.s
arg2=champions/$file.cor

rm -rf test1 test2
./asm_proto "$arg1" && hexdump "$arg2" > test1
./asm "$arg1" && hexdump "$arg2" > test2
echo "$arg1 $arg2\n"
diff -u test1 test2 2> /dev/null


