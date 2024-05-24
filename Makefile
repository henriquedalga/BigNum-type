main: BigNum.o main.o
	gcc main.o -o prog

main.o: BigNum.o main.c
	gcc -g -c main.c

BigNum.o: BigNum.h BigNum.c
	gcc -g -c BigNum.c
