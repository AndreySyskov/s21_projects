CC = gcc -Wall -Werror -Wextra

all: s21_grep

s21_grep.o: s21_grep.c	
	$(CC) -c s21_grep.c
	
s21_grep: s21_grep.o 
	$(CC) -o s21_grep s21_grep.o 

clean:
	rm -rf *.o
	rm -rf s21_grep

clang:
	cp ../../materials/linters/.clang-format ./.clang-format
	clang-format -n -style=Google *.c *.h