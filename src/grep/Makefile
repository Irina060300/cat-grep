s21_grep: s21_grep.o
	gcc  s21_grep.c -o  s21_grep
s21_grep.o: s21_grep.c s21_grep.h 
	gcc -c  s21_grep.c
clean:
	rm -rf *.o s21_grep
rebuild: clean s21_grep