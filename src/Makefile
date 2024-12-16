CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
FLAGS_CHECK = -lcheck -lm -lpthread -pthread 
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
CH_FILES =$(wildcard ./tests/s21_*.c)
C_FILES =$(wildcard *.c)
OS := $(shell uname -s)
TEST_SRC=$(wildcard ./tests/s21_*.c)
OPEN = open report/index.html

# если мы имеем дело с Linux при работе с checkmk добавляем доп флаги к FLAGS_CHECK и меняем OPEN
ifeq ($(shell uname -s),Linux)
  FLAGS_CHECK += -lsubunit -lgcov
  OPEN = xdg-open report/index.html
endif

all: clean s21_decimal.a

s21_decimal.a: 
	$(CC) $(FLAGS) -c $(C_FILES)
	ar rc s21_decimal.a *.o
	ranlib s21_decimal.a
	rm -rf *.o

s21_decimal_gcov:
	$(CC) $(FLAGS) $(GCOV_FLAGS) -c $(C_FILES)
	ar rc s21_decimal.a *.o
	ranlib s21_decimal.a
	rm -rf *.o

test: s21_decimal_gcov
	$(CC) $(FLAGS) $(GCOV_FLAGS) $(TEST_SRC) s21_decimal.a -o unit_test $(FLAGS_CHECK)
	./unit_test 0

gcov_report: test
	lcov -t "s21_decimal" -o s21_decimal.info -c -d . --no-external
	genhtml -o report s21_decimal.info
	$(OPEN)

clang:
	cp ../materials/linters/.clang-format .
	clang-format -i *.c *.h tests/*.

clean: 
	rm -rf *.info
	rm -rf test
	rm -rf report
	rm -rf test.dSYM
	rm -rf *.o
	rm -rf *.a
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf unit_test
