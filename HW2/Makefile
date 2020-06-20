all: main run

main: main.o DecisionTree.o DecisionTreeNode.o
	g++ main.o DecisionTree.o DecisionTreeNode.o -o main

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

DecisionTree.o: DecisionTree.cpp
	g++ -c -std=c++11 DecisionTree.cpp

DecisionTreeNode.o: DecisionTreeNode.cpp
	g++ -c -std=c++11 DecisionTreeNode.cpp

clean:
	rm *.o main

run:
	./main
