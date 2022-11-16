s21_cat: header.o main.o
	gcc -fsanitize=address -g -Wall -Wextra -Werror header.o main.o -o  s21_cat
header.o: header.c header.h 
	gcc -c -Wall -Wextra -Werror header.c 
main.o: main.c header.h 
	gcc -c -Wall -Wextra -Werror main.c 
clean:
	rm -rf *.o s21_cat
rebuild: clean s21_cat