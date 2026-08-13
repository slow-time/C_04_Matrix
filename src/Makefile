CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11

all: s21_matrix.a

clean:
	rm -rf *.a *.o
	rm -rf s21_test
	rm -rf logs

s21_matrix.a:
	$(CC) $(FLAGS) -c for_tests.c function/s21_create_matrix.c function/s21_remove_matrix.c function/s21_eq_matrix.c function/s21_sum_matrix.c function/s21_sub_matrix.c function/s21_mult_matrix.c function/s21_mult_number.c function/s21_transpose.c function/s21_determinant.c function/s21_calc_complements.c function/s21_inverse_matrix.c
	ar rcs s21_matrix.a *.o
	ranlib s21_matrix.a
	rm *.o

test: s21_matrix.a
	$(CC) $(FLAGS) test_unit.c -L. s21_matrix.a -lcheck -lm -lpthread -lsubunit -o s21_test
	./s21_test

gcov_report: s21_matrix.a
	mkdir logs
	$(CC) $(FLAGS) -fprofile-arcs -ftest-coverage test_unit.c for_tests.c function/s21_create_matrix.c function/s21_remove_matrix.c function/s21_eq_matrix.c function/s21_sum_matrix.c function/s21_sub_matrix.c function/s21_mult_matrix.c function/s21_mult_number.c function/s21_transpose.c function/s21_determinant.c function/s21_calc_complements.c function/s21_inverse_matrix.c -o logs/gcov -lcheck -lm -lsubunit
	./logs/gcov
	gcovr --html-details -o logs/index.html --exclude test_unit.c
	rm logs/*.gcda logs/*.gcno logs/gcov

rebuild: clean s21_matrix.a

check_style:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h function/*.c

valgr:
	valgrind --tool=memcheck --leak-check=yes ./s21_test 

