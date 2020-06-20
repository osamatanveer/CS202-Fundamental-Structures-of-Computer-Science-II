/* *
* Author : Osama Tanveer
* ID : 21801147
* Section : 3
* Assignment : 4
*/
#include "HashTable.h"

int main() {
    // Constants
    const int tableSize = 11;
    const CollisionStrategy collisionStrategy = DOUBLE;
    const string fileName = "test.txt";
    
    // Creating HashTable
    HashTable table(tableSize, collisionStrategy);
    
    // Parsing file and performing operations
    ifstream inFile(fileName);
    string opType;
    string tempItem;
    int item;
    int counter = 0;
    while (inFile >> opType >> tempItem) {
        item = stoi(tempItem);
        if (opType == "I" || opType == "i") {
            if (table.insert(item)) {
                cout << item << " inserted" << endl;
            } else {
                cout << item << " not inserted" << endl;
            }
        } 
        else if (opType == "R" || opType == "r") {
            if (table.remove(item)) {
                cout << item << " removed" << endl;
            } else {
                cout << item << " not removed" << endl;
            }
        }
        else if (opType == "S" || opType == "s") {
            int numberOfProbes;
            if (table.search(item, numberOfProbes)) {
                cout << item << " found after " << numberOfProbes << " probes" << endl;
            } else {
                cout << item << " not found after " << numberOfProbes << " probes" << endl;
            }
        }
    }
    
    table.display();
    int numberOfSuccProbes, numberOfUnsuccProbes;
    table.analyze(numberOfSuccProbes, numberOfUnsuccProbes);
    cout << "Average number of successful probes: " << numberOfSuccProbes << endl;
    cout << "Average number of unsuccessful probes: " << numberOfUnsuccProbes << endl;
    table.~HashTable();
    return 0;
}