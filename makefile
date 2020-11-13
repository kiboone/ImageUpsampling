main: upsampling.o
	g++ -o main upsampling.cpp
upsampling.o: upsampling.cpp
	g++ -c upsampling.cpp functions.cpp

test:
	g++ -std=c++11 -I ~/COP4531/proj2/googletest/googletest/include/ -L ~/COP4531/proj2/googletest/build/lib UnitTest.cpp -lgtest -lpthread
	a.out

coverage:
	echo "code coverage"

metric:
	g++ -o l1 L1metric.cpp

clean:
	rm main
	rm *.o

cleantest:
	rm a.out