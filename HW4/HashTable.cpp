/* *
* Author : Osama Tanveer
* ID : 21801147
* Section : 3
* Assignment : 4
*/
#include "HashTable.h"

HashTable::HashTable(const int tableSize, const CollisionStrategy option) {
    HashTable::tableSize = tableSize;
    HashTable::table = new int[tableSize];
    HashTable::tableStatus = new int[tableSize]; // -1 - unused, 0 - removed, 1 - occupied 
    HashTable::collisionStrategy = option;
    HashTable::itemsInTable = 0;
    for (int i = 0; i < tableSize; i++) {
        table[i] = 0;
        tableStatus[i] = -1;
    }
}

HashTable::~HashTable() {
    if (table) {
        delete [] table;
        delete [] tableStatus;
    }
}

bool HashTable::insert(const int item) {
    // Checking if table full or not
    if (itemsInTable == tableSize) {
        return false;
    }
    
    // Inserting into table using first hash function
    int hash1_key = item % tableSize;
    if ((tableStatus[hash1_key] != 1) || (table[hash1_key] == item))  {
        if (table[hash1_key] == item) {
            return false;
        }
        table[hash1_key] = item;
        tableStatus[hash1_key] = 1;
        itemsInTable++;
        return true;
    }
    
    // If at this point, collision occured and thus resolving
    bool inserted = false;
    // Linear probing
    if (collisionStrategy == LINEAR) {
        int counter = (hash1_key + 1) % tableSize;
        while (counter != hash1_key) {
            if (table[counter] == item) {
                return false;
            }
            if (tableStatus[counter] != 1) {
                table[counter] = item;
                tableStatus[counter] = 1;
                inserted = true;
                itemsInTable++;
                break;
            } else {
                inserted = false;
            }
            counter++;
            counter %= tableSize; // wrap around the table
        }    
    }
    // Quadratic probing
    if (collisionStrategy == QUADRATIC) {
        int power = 1;
        int counter = (hash1_key + 1) % tableSize;
        while (counter != hash1_key) {
            if (table[counter] == item) {
                return false;
            }
            if (tableStatus[counter] != 1) {
                table[counter] = item;
                tableStatus[counter] = 1;
                inserted = true;
                itemsInTable++;
                break;
            } else {
                inserted = false;
            }
            counter = (hash1_key + (int)pow(power, 2)) % tableSize;
            power++;
            
        }    
    }
    
    // Double Hashing resolution of collision
    if (collisionStrategy == DOUBLE) {
        int counter = tableSize * 2;
        int i = 1;
        int reversedKey = hashUsingSecondFunction(item);
        int position = (hash1_key + (i * reversedKey)) % tableSize;
        while (counter >= 0) {
            if (table[position] == item) {
                return false;
            }
            if (tableStatus[position] != 1) {
                table[position] = item;
                tableStatus[position] = 1;
                inserted = true;
                itemsInTable++;
                break;
            } else {
                inserted = false;
            }
            i++;
            position = (hash1_key + (i * reversedKey)) % tableSize;
            counter--;
        }
    }
    return inserted;
}

bool HashTable::remove(const int item) {
    if ((tableSize == 0) || (itemsInTable == 0)) {
        return false;
    }

    // Checking at position according to 1st hash function    
    int hash1_key = item % tableSize;
    if (table[hash1_key] == item) {
        tableStatus[hash1_key] = 0;
        itemsInTable--;
        return true;
    }

    // If here, means collision occured during insertion

    if (collisionStrategy == LINEAR) {
        // Next position never used, not found
        if (tableStatus[hash1_key] == -1) {
            return false;
        }        
        // If not at position, linear probe
        int counter = (hash1_key + 1) % tableSize;
        while (counter != hash1_key) {
            // Wrap around
            if (counter >= tableSize) {
                counter %= tableSize;
            }
            // Checking next occupied place
            if (tableStatus[counter] == 1 && (table[counter] == item)) {
                    tableStatus[counter] = 0;
                    itemsInTable--;
                    return true;
            }
            // If place not used, means linear probe did not reach here when inserting
            else if (tableStatus[counter] == -1) {
                return false;
            }
            counter++;
        }
    }

    if (collisionStrategy == QUADRATIC) {
        int power = 1;
        int counter = (hash1_key + 1) % tableSize;
        while (counter != hash1_key) {
            if (tableStatus[counter] == 1 && table[counter] == item) {
                tableStatus[counter] = 0;
                itemsInTable--;
                return true;
            }
            counter = (hash1_key + (int)pow(power, 2)) % tableSize;
            power++;
        }
    }

    if (collisionStrategy == DOUBLE) {
        int i = 1;
        int reversedKey = hashUsingSecondFunction(item);
        int position = (hash1_key + (i * reversedKey)) % tableSize;
        int counter = tableSize * 2;
        while (counter >= 0) {
            if (tableStatus[position] == 1 && table[position] == item) {
                tableStatus[position] = 0;
                itemsInTable--;
                return true;
            }
            i++;
            position = (hash1_key + (i * reversedKey)) % tableSize;
            counter--;
        }
    }
    return false;
}

bool HashTable::search(const int item, int& numProbes) {
    numProbes = 0;
    // Item at 1st function hash position
    int hash1_key = item % tableSize;
    if (table[hash1_key] == item) {
        numProbes = 1;
        return true;
    }

    if (collisionStrategy == LINEAR) {
        // If not at position, linear probe
        int counter = (hash1_key + 1) % tableSize;
        numProbes++;
        while (counter != hash1_key) {
            // Checking next occupied place
            if ((tableStatus[counter] == 1) && (table[counter] == item)) {
                numProbes++;
                return true;
            }
            // if place not used, means linear probe did not reach here
            if (tableStatus[counter] == -1) {
                numProbes++;
                return false;
            }
            counter++;
            counter %= tableSize;
            numProbes++;
        }
    }

    if (collisionStrategy == QUADRATIC) {
        numProbes++; // comparison with first hash key
        bool found = false;
        int position = (hash1_key + 1) % tableSize;
        
        int power = 2;
        while (position != hash1_key) {
            if (tableStatus[position] == -1) {
                return false;
            }

            if (table[position] == item && tableStatus[position] == 1) {
                found = true;
            } 
            numProbes++;
            position = (hash1_key + (int)pow(power, 2)) % tableSize;
            power++;
            if (found) return true;
        }
    }

    if (collisionStrategy == DOUBLE) {
        int i = 0;
        int reversedKey = hashUsingSecondFunction(item);
        int position = (hash1_key + (i * reversedKey)) % tableSize;
        numProbes++;
        bool found = false;
        int counter = tableSize * 2;
        while (counter >= 0) {
            // numProbes++;
            if (tableStatus[position] == -1) {
                return false; // item not found
            }

            if (tableStatus[position] == 1 && table[position] == item) {
                found = true;
            }
            // Updating position
            i++;
            position = (hash1_key + (i * reversedKey)) % tableSize;
            if (found) {
                return true;
            }    
            numProbes++;
            counter--;       
        }
    }
    return false;
}

void HashTable::display() {
    for (int i = 0; i < tableSize; i++) {
        if (tableStatus[i] == 1) {
            cout << i << ": " << table[i] << endl;
        }
        else {
            cout << i << ": " << endl;
        }     
    }
}

void HashTable::analyze(int& numSuccProbes, int& numUnsuccProbes) {
    numSuccProbes = 0;
    numUnsuccProbes = 0;

    if (itemsInTable == 0) {
        return;
    }

    // Copying items in table to a temporary array to search for
    int* tempItems = new int[itemsInTable];
    int i = 0, j = 0;
    while (i < itemsInTable) {
        if (tableStatus[j] == 1) {
            tempItems[i] = table[j];
            i++;
            j++;
        }
        else {
            j++;
        }
    }

    if (collisionStrategy == LINEAR) {
        // Analyzing successful search
        int numberOfProbes = 0;
        int totalSuccProbes = 0;
        for (int i = 0; i < itemsInTable; i++) {
            search(tempItems[i], numberOfProbes);
            totalSuccProbes += numberOfProbes;
        }
        numSuccProbes = totalSuccProbes / itemsInTable;

        //Analyzing unsuccessful search
        numberOfProbes = 0;
        int totalUnSuccProbs = 0;
        for (int i = 0; i < tableSize; i++) {
            int counter = i;
            bool backToStartPos = false;
            while (tableStatus[counter] != -1 && !backToStartPos) {
                numberOfProbes++;
                counter++;
                counter %= tableSize;
                if (counter == i) backToStartPos = true;
            }
            numberOfProbes++;
            totalUnSuccProbs += numberOfProbes;
            numberOfProbes = 0;
        }
        numUnsuccProbes = totalUnSuccProbs / tableSize;
    }
    
    if (collisionStrategy == QUADRATIC) {
        // Analyzing successful search
        int numberOfProbes = 0;
        int totalSuccProbes = 0;
        for (int i = 0; i < itemsInTable; i++) {
            search(tempItems[i], numberOfProbes);
            totalSuccProbes += numberOfProbes;
        }
        numSuccProbes = totalSuccProbes / itemsInTable;

        //Analyzing unsuccessful search
        numberOfProbes = 0;
        int totalUnSuccProbs = 0;
        for (int i = 0; i < tableSize; i++) {
            int counter = i;
            bool backToStartPos = false;
            while (tableStatus[counter] != -1 && !backToStartPos) {
                numberOfProbes++;
                counter++;
                counter %= tableSize;
                if (counter == i) backToStartPos = true;
            }
            numberOfProbes++;
            totalUnSuccProbs += numberOfProbes;
            numberOfProbes = 0;
        }
        numUnsuccProbes = totalUnSuccProbs / itemsInTable;
    }


    if (collisionStrategy == DOUBLE) {
        // Analyzing successful search
        int numberOfProbes = 0;
        int totalSuccProbes = 0;
        for (int i = 0; i < itemsInTable; i++) {
            search(tempItems[i], numberOfProbes);
            totalSuccProbes += numberOfProbes;
        }
        numSuccProbes = totalSuccProbes / itemsInTable;
        numUnsuccProbes = -1;
    }
    
    delete [] tempItems;
}

int HashTable::hashUsingSecondFunction(int key) {
    int reverse = 0;
    int temp;
    while (key != 0) {
        temp = key % 10;
        reverse = reverse*10 + temp;
        key /= 10;
    }
    return reverse;
}