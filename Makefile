OS=$(shell uname)
INSTALL_DIR=SMART_CALC2_0/
CC=g++ -std=c++17
FLAGS=-Wall -Werror -Wextra
OPEN=
ifeq ($(OS), Linux)
	QMAKE=qmake
	OPT=-spec linux-g++ CONFIG+=qtquickcompiler
	BUILD_DIR=build-smart_calc-Desktop_Qt_6_4_0_GCC_64bit-Release
	LIBS=-lgtest -lpthread
	OPEN=xdg-open
else
	QMAKE=qmake
	OPT=CONFIG+=qtquickcompiler
	BUILD_DIR=build-smart_calc-Desktop_Qt_6_4_0_GCC_64bit-Release/smart_calc.app/Contents/MacOS
	LIBS=-lgtest
	OPEN=open
endif

all:
	make create_make
	make -C build-smart_calc-Desktop_Qt_6_4_0_GCC_64bit-Release/ first

rebuild:
	make clean
	make remove
	make all

install:
	@mkdir SMART_CALC2_0
	@cp $(BUILD_DIR)/smart_calc $(INSTALL_DIR)smart_calc
	@make dvi

uninstall:
	@rm -rf $(INSTALL_DIR)

dist:
	@make install
	@tar -zcf calc.tar.gz $(INSTALL_DIR)
	@make uninstall

dvi:
	@cp materials/manual.pdf $(INSTALL_DIR)manual.pdf

tests:
	$(CC) $(FLAGS) src/test/test.cpp src/controller.cpp src/model.cpp src/token.cpp -o src/test/test $(LIBS)
	./src/test/test

gcov_report:
	$(CC) $(CFLAGS) src/test/test.cpp src/controller.cpp src/model.cpp src/token.cpp -o src/test/test --coverage $(LIBS)
	./src/test/test
	lcov -t "test" -o test.info -c -d .
	lcov -q --remove test.info "/usr/include/*" -o test.info --rc lcov_function_coverage=0
	lcov -q --remove test.info "/usr/local/*" -o test.info --rc lcov_function_coverage=0
	genhtml -o report test.info
	$(OPEN) report/index.html

create_make:

	$(QMAKE) -o build-smart_calc-Desktop_Qt_6_4_0_GCC_64bit-Release/Makefile src/smart_calc.pro

run:
	./$(BUILD_DIR)/smart_calc

clean:
	rm -rf $(BUILD_DIR) *.o *.a *.out *.gcda *.gcno *.info *.dSYM *.info report

code_check: check style

check:
	cppcheck --quiet --enable=all --language=c++ --suppress=unusedFunction \
	--suppress=unknownMacro --suppress=missingInclude src/*.cpp src/*.h src/test/*.cpp

style:
	cp materials/linters/.clang-format src/
	cp materials/linters/.clang-format src/test/
	clang-format -n src/*.cpp src/*.h src/test/*.cpp

leaks:
	make tests
	valgrind ./src/test/test
