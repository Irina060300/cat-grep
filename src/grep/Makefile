CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11 -O2 -D_GNU_SOURCE

all: build
build: s21_grep
s21_grep: s21_grep.o
	${CC} ${CFLAGS} s21_grep.o -o s21_grep
s21_grep.o: s21_grep.c s21_grep.h 
	${CC} -c s21_grep.c
clean:
	rm -rf *.o s21_grep
rebuild: clean s21_grep
.PHONY:all clean rebuild
