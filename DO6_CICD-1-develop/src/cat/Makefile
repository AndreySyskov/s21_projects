CC = gcc -Wall -Werror -Wextra

all: s21_cat

s21_cat: s21_cat.o s21_cat_module.o
	$(CC)  -o s21_cat s21_cat.o s21_cat_module.o

s21_cat.o:
	$(CC) -c s21_cat.c
	
s21_cat_module.o:
	$(CC) -c s21_cat_module.c

clang:
	cp ../../materials/linters/.clang-format ./.clang-format
	clang-format -n -style=Google *.c *.h


clean:
	rm -rf *.o
	rm -rf s21_cat
	rm -rf *.log
	rm -rf *.txt

