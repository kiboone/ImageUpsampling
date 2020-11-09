main: upsampling.o
	g++ -o main upsampling.cpp
upsampling.o: upsampling.cpp
	g++ -c upsampling.cpp
clean:
		rm main
		rm *.o
