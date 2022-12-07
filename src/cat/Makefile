CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11 -O2

all: build
build: s21_cat
s21_cat: s21_cat.o
	${CC} ${CFLAGS} s21_cat.o -o  s21_cat
s21_cat.o: s21_cat.c s21_cat.h
	${CC} -c s21_cat.c 
clean:
	rm -rf *.o s21_cat
rebuild: clean s21_cat
.PHONY:all clean rebuild