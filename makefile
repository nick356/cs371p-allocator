all:

Allocator.log:
	git log > Allocator.log

Doxyfile:
	doxygen -g

html: Doxyfile Allocator.h TestAllocator.c++
	doxygen Doxyfile

TestAllocator: Allocator.h TestAllocator.c++
	g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall TestAllocator.c++ -o TestAllocator -lgtest -lgtest_main -lpthread

TestAllocator.out: TestAllocator
	valgrind TestAllocator        >  TestAllocator.out 2>&1
	gcov-4.7 -b TestAllocator.c++ >> TestAllocator.out

TestAllocator2: Allocator.h kk23537-TestAllocator.c++
	g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall kk23537-TestAllocator.c++ -o TestAllocator2 -lgtest -lgtest_main -lpthread

kk23537-TestAllocator.out: TestAllocator2
	valgrind TestAllocator2        >  kk23537-TestAllocator.out 2>&1
	gcov-4.7 -b kk23537-TestAllocator.c++ >> kk23537-TestAllocator.out

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f TestAllocator
	rm -f TestAllocator.out

