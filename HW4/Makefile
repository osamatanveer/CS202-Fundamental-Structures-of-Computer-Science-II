all: main run

main: main.o HashTable.o
	g++ main.o HashTable.o -o main

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

HashTable.o: HashTable.cpp
	g++ -c -std=c++11 HashTable.cpp

clean:
	rm *.o main

run:
	./main
	


