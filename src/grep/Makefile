s21_grep: s21_grep.o
	gcc -fsanitize=address -g s21_grep.o -o s21_grep
s21_grep.o: s21_grep.c s21_grep.h 
	gcc -c s21_grep.c
clean:
	rm -rf *.o s21_grep
rebuild: clean s21_grep
