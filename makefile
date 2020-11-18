main: upsampling.o
	g++ -o main upsampling.cpp
upsampling.o: upsampling.cpp
	g++ -c upsampling.cpp functions.cpp

test:
	g++ -std=c++11 -I ~/COP4531/proj2/googletest/googletest/include/ -L ~/COP4531/proj2/googletest/build/lib UnitTest.cpp -lgtest -lpthread
	a.out

coverage:
	g++ -std=c++11 -o main_test -fprofile-arcs -ftest-coverage -fPIC  UnitTest.cpp -L ./googletest/build/lib -I ./googletest/googletest/include/ -lgtest -lpthread
	main_test
	gcov UnitTest.cpp
	~/.local/bin/gcovr -r . -e ".*\.h" 

metric:
	g++ -o l1 L1metric.cpp

clean:
	rm main
	rm *.o

cleanmet:
	rm l1

cleantest:
	rm a.out

cleancov:
	rm *.gcov
	rm *.gcda
	rm *.gcno
	rm main_test