CC=gcc
CFLAGS=-Wall -Werror -Wextra
CFLAGSSPECIAL=-shared -o
CFLAGSFORBINARY=-fPIC

all: s21_cat

s21_cat.o: s21_cat.c 
	$(CC) $(CFLAGS) -c s21_cat.c  
test: s21_cat
	./test_cat.sh
memcheck: s21_cat
	@echo "=================================================================================="
	@valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./s21_cat -e 1.txt
	@valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./s21_cat -n 1.txt
	@valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./s21_cat -s 1.txt
	@valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./s21_cat -t 1.txt
	@valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./s21_cat -b 1.txt
	@echo "=================================================================================="

s21_cat: s21_cat.o
	$(CC) $(CFLAGS)  s21_cat.o -o s21_cat

clean:
	rm -rf *.o s21_cat 


rebuild: clean all