# this makefile runs all the tests
# each test numbe is the same example, with one version failing, and one with the fix
# *a* suffix is *without* the required fix, so gcc should return *1*
# *b* suffix is *with* the fix, so gcc should return *0*

# Stop make outputing the rules as it executes
.SILENT:

CC = gcc
#CC = clang

CXX = g++
#CXX = clang++

INC_DIRS := -I..
#INC_DIRS :=

FLAGS := $(INC_DIRS) -D__ENABLE_COMPILE_ASSERT__ -O2

# Stop compiler outputting text, then only the return code is checked
LOG := > /dev/null 2>&1
#LOG :=
#LOG := >> testsuite.log 2>&1


all: start main1_a main1_b main2_a main2_b main3_a main3_b main4_a main4_b main5_a main5_b main6_a main6_b main17_a main17_b test_20_a main24_a main24_b main25_a main25_b main28_a main28_b main29_a main29_b

start:
	echo "compile_assert() testsuite"
	@echo "C Compiler  :" $(CC)
	@echo "C++ Compiler:" $(CXX)
	rm -f testsuite.log

# should *not* compile
main1_a:
	$(CC) $(INC_DIRS) $(FLAGS) -Wno-nonnull -o main1_a.bin main1_a.c $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main1_a: *FAIL*"; \
	else \
		echo "main1_a: PASS"; \
	fi

# should compile
main1_b:
	$(CC) $(INC_DIRS) $(FLAGS) -Wno-nonnull -o main1_b.bin main1_b.c $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main1_b: PASS"; \
	else \
		echo "main1_b: *FAIL*"; \
	fi


# should *not* compile
main2_a:
	$(CC) $(INC_DIRS) $(FLAGS) -Wno-nonnull -o main2_a.bin main2_a.c $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main1_a: *FAIL*"; \
	else \
		echo "main1_a: PASS"; \
	fi

# should compile
main2_b:
	$(CC) $(INC_DIRS) $(FLAGS) -Wno-nonnull -o main3_b.bin main2_b.c $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main2_b: PASS"; \
	else \
		echo "main2_b: *FAIL*"; \
	fi

# should *not* compile
main3_a:
	$(CC) $(INC_DIRS) $(FLAGS) -o main3_a.bin main3_a.c $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main3_a: *FAIL*"; \
	else \
		echo "main3_a: PASS"; \
	fi

# should compile
main3_b:
	$(CC) $(INC_DIRS) $(FLAGS) -o main3_b.bin main3_b.c $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main3_b: PASS"; \
	else \
		echo "main3_b: *FAIL*"; \
	fi


# should *not* compile
main4_a:
	$(CC) $(INC_DIRS) $(FLAGS) -o main4_a.bin main4_a.c $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main4_a: *FAIL*"; \
	else \
		echo "main4_a: PASS"; \
	fi

# should compile
main4_b:
	$(CC) $(INC_DIRS) $(FLAGS) -o main4_b.bin main4_b.c $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main4_b: PASS"; \
	else \
		echo "main4_b: *FAIL*"; \
	fi


# should *not* compile
main5_a:
	$(CC) $(INC_DIRS) $(FLAGS) -o main5_a.bin main5_a.c $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main5_a: *FAIL*"; \
	else \
		echo "main5_a: PASS"; \
	fi

# should compile
main5_b:
	$(CC) $(INC_DIRS) $(FLAGS) -o main5_b.bin main5_b.c $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main5_b: PASS"; \
	else \
		echo "main5_b: *FAIL*"; \
	fi

# should *not* compile
main6_a:
	$(CC) $(INC_DIRS) $(FLAGS) -o main5_a.bin main6_a.c $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main6_a: *FAIL*"; \
	else \
		echo "main6_a: PASS"; \
	fi

# should compile
main6_b:
	$(CC) $(INC_DIRS) $(FLAGS) -o main6_b.bin main6_b.c $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main6_b: PASS"; \
	else \
		echo "main6_b: *FAIL*"; \
	fi

# should fail
main17_a:
	$(CXX) $(INC_DIRS) $(FLAGS) -o main17_a.bin main17_a.cpp $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main17_a: *FAIL*"; \
	else \
		echo "main17_a: PASS"; \
	fi

# should fail
test_20_a:
	$(CXX) $(INC_DIRS) $(FLAGS) -o test_20_a.bin test_20_a.cpp $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "test_20_a: *FAIL*"; \
	else \
		echo "test_20_a: PASS"; \
	fi

# should compile
main17_b:
	$(CXX) $(INC_DIRS) $(FLAGS) -o main17_b.bin main17_b.cpp $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main17_b: PASS"; \
	else \
		echo "main17_b: *FAIL*"; \
	fi

# should fail
main24_a:
	$(CXX) $(INC_DIRS) $(FLAGS) -o main24_a.bin main24_a.cpp $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main25_a: *FAIL*"; \
	else \
		echo "main25_a: PASS"; \
	fi

# should compile
main24_b:
	$(CXX) $(INC_DIRS) $(FLAGS) -o main24_b.bin main24_b.cpp $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main24_b: PASS"; \
	else \
		echo "main24_b: *FAIL*"; \
	fi

# should fail
main25_a:
	$(CXX) $(INC_DIRS) $(FLAGS) -o main25_a.bin main25_a.cpp $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main25_a: *FAIL*"; \
	else \
		echo "main25_a: PASS"; \
	fi


# should compile
main25_b:
	$(CXX) $(INC_DIRS) $(FLAGS) -o main25_b.bin main25_b.cpp $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main25_b: PASS"; \
	else \
		echo "main25_b: *FAIL*"; \
	fi


# should fail
main26_a:
	$(CXX) $(INC_DIRS) $(FLAGS) -o main26_a.bin main26_a.cpp $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main26_a: *FAIL*"; \
	else \
		echo "main26_a: PASS"; \
	fi


# should compile
main26_b:
	$(CXX) $(INC_DIRS) $(FLAGS) -o main26_b.bin main26_b.cpp $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main26_b: PASS"; \
	else \
		echo "main26_b: *FAIL*"; \
	fi

# should fail
main27_a:
	$(CXX) $(INC_DIRS) $(FLAGS) -o main27_a.bin main27_a.cpp $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main27_a: *FAIL*"; \
	else \
		echo "main27_a: PASS"; \
	fi


# should compile
main27_b:
	$(CXX) $(INC_DIRS) $(FLAGS) -o main27_b.bin main27_b.cpp $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main27_b: PASS"; \
	else \
		echo "main27_b: *FAIL*"; \
	fi

# should fail
main28_a:
	$(CXX) $(INC_DIRS) $(FLAGS) -std=c++23 -o main28_a.bin main28_a.cpp $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main28_a: *FAIL*"; \
	else \
		echo "main28_a: PASS"; \
	fi


# should compile
main28_b:
	$(CXX) $(INC_DIRS) $(FLAGS) -std=c++23 -o main28_b.bin main28_b.cpp $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main28_b: PASS"; \
	else \
		echo "main28_b: *FAIL*"; \
	fi

# should fail
main29_a:
	$(CC) $(INC_DIRS) $(FLAGS) -flto -c -o test_29_lto1_a.o test_29_lto1_a.c $(LOG)
	$(CC) $(INC_DIRS) $(FLAGS) -flto -c -o test_29_lto2_a.o test_29_lto2_a.c $(LOG)
	$(CC) -DLINKMSG $(INC_DIRS) $(FLAGS) -flto -o test_29_lto_a.bin test_29_lto1_a.o test_29_lto2_a.o $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main29_a: *FAIL*"; \
	else \
		echo "main29_a: PASS"; \
	fi


# should compile
main29_b:
	$(CC) $(INC_DIRS) $(FLAGS) -flto -c -o test_29_lto1_b.o test_29_lto1_b.c $(LOG)
	$(CC) $(INC_DIRS) $(FLAGS) -flto -c -o test_29_lto2_b.o test_29_lto2_b.c $(LOG)
	$(CC) -DLINKMSG $(INC_DIRS) $(FLAGS) -flto -o test_29_lto_b.bin test_29_lto1_b.o test_29_lto2_b.o $(LOG); \
	if [ $$? -eq 0 ]; then \
		echo "main29_b: PASS"; \
	else \
		echo "main29_b: *FAIL*"; \
	fi


clean:
	rm -f *.bin
	rm -f *.o
