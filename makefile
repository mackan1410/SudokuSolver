C_COMPILER     = gcc
C_OPTIONS      = -Wall -pedantic
CUNIT_LINK     = -lcunit

%.o: %.c solver.h
	$(C_COMPILER) -c $(C_FLAGS) $< -o $@

unit_tests: tests/unit_tests.c solver.o
	$(C_COMPILER) $(C_OPTIONS) tests/unit_tests.c solver.o $(CUNIT_LINK) -o unit_tests

test:
	./unit_tests

mem_test:
	valgrind ./unit_tests
	
clean:
	
	