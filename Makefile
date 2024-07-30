CXXFLAGS = -Wall -Werror -Wextra

all: s21_matrix_oop.a

build: s21_matrix_oop.cc
	g++ -c $(CXXFLAGS) -std=c++17 s21_matrix_oop.cc -o s21_matrix_oop.o

s21_matrix_oop.a: build
	ar rcs s21_matrix_oop.a s21_matrix_oop.o
	ranlib s21_matrix_oop.a
	rm -f *.o

rebuild:
	make clean
	make build

leaks: test
	leaks -atExit -- ./unit_test

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n *.cc *.h
	rm .clang-format

.PHONY: clang
clang-check:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -i *.cc *.h
	rm .clang-format


test: s21_matrix_oop.a
	g++ $(CXXFLAGS) -std=c++17 s21_matrix_tests.cc s21_matrix_oop.a -lgtest -o unit_test
	./unit_test

gcov_report:
	g++ $(CXXFLAGS) --coverage s21_matrix_tests.cc s21_matrix_oop.cc -lgtest -o gcov_report
	./gcov_report
	lcov --no-external -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open ./report/index.html

clean:
	@rm -rf *.o *.out *.a *\unit_test
	@rm -rf *.gcda *.gcno *.info gcov_report
