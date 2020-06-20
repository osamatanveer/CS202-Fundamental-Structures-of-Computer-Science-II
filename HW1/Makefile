hw1: sorting.o auxArrayFunctions.o main.o
	g++ sorting.o auxArrayFunctions.o main.o -o hw1

sorting.o:
	g++ -std=c++11 -c sorting.cpp

auxArrayFunctions.o:
	g++ -std=c++11 -c auxArrayFunctions.cpp

main.o:
	g++ -std=c++11 -c main.cpp

clean:
	rm *.o
