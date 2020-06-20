/* *
* Author : Osama Tanveer
* ID : 21801147
* Section : 3
* Assignment : 4
*/
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string.h>

using namespace std;

enum CollisionStrategy {LINEAR, QUADRATIC, DOUBLE};

class HashTable {    
    public:
        HashTable(const int tableSize, const CollisionStrategy option);
        ~HashTable();
        bool insert(const int item);
        bool remove(const int item);
        bool search(const int item, int& numProbes);
        void display();
        void analyze(int& numSuccProbes, int& numUnsuccProbes);

    private:
        int itemsInTable;
        int tableSize;
        int* table;
        int* tableStatus;
        CollisionStrategy collisionStrategy;

        int hashUsingSecondFunction(int key);
};