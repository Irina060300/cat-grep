s21_cat: header.o main.o
	gcc header.o main.o -o s21_cat
header.o: header.c header.h 
	gcc -c header.c 
main.o: main.c header.h 
	gcc -c main.c 