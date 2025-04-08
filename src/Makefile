CC = gcc
OS = $(shell uname)
ifeq ($(OS), Linux)
	LIBS = -lcheck -pthread -lrt -lm -lsubunit
else
	LIBS = -lcheck
endif

CFLAGS = -c -Wall -Werror -Wextra -std=c11 $(LIBS)

all: s21_matrix.a

test: gcov_s21_matrix.a
	$(CC) $(CFLAGS) test.c
	$(CC) --coverage *.o s21_matrix.a $(LIBS) -o s21_matrix_test
	./s21_matrix_test

clean:
	rm -rf *.o *.info s21_*_test *.gcda *.gcno *.css *.html *.gcov *.a report

s21_matrix.a:
	$(CC) $(CFLAGS) s21_*.c
	ar rc s21_matrix.a s21_*.o
	ranlib s21_matrix.a

leaks: test
	valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=no ./s21_matrix_test

gcov_s21_matrix.a:
	rm -f s21_matrix.a
	$(CC) --coverage $(CFLAGS) s21_*.c
	ar rc s21_matrix.a s21_*.o
	ranlib s21_matrix.a

gcov_report: test
	lcov -c -d ./ -o s21_test.info --rc lcov_branch_coverage=1    
	genhtml -o ./report s21_test.info --rc lcov_branch_coverage=1

rebuild: clean all

style_fix:
	clang-format -i *.c *.h --style=Google

style:
	clang-format -n *.c *.h --style=Google

.PHONY: all test clean gcov_report rebuild style style_fix
