CC=gcc
CFLAGS=-Wall -Werror -Wextra
CFLAGSSPECIAL=-shared -o
CFLAGSFORBINARY=-fPIC

all: s21_grep 

s21_grep.o: s21_grep.c 
	$(CC) $(CFLAGS) -c s21_grep.c  
test: s21_grep
	./test_grep.sh

memcheck: s21_grep
	@echo "=================================================================================="
	@valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./s21_grep -e and 1.txt
	@valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./s21_grep -n and 1.txt
	@valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./s21_grep -s and 1.txt
	@valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./s21_grep -v and 1.txt
	@echo "=================================================================================="


s21_grep: s21_grep.o
	$(CC) $(CFLAGS)  s21_grep.o -o s21_grep

clean:
	rm -rf *.o s21_grep 


rebuild: clean all