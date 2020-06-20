#include "FriendNet.h"
#include <iostream>
#include <fstream>
#include <sstream>

FriendNet::FriendNet(const string fileName) {
    ifstream inFile;
    // inFile.open()
    if (inFile) {
        inFile.open(fileName.c_str(), ifstream::out);
        string line;
        
        // Getting number of people
        getline(inFile, line);
        istringstream is(line);
        is >> numOfPeople;
        // numOfPeople = stoi(line);
        people = new Person[numOfPeople];

        for (int i = 0; i < numOfPeople; i++) {
            // Getting person info
            getline(inFile, line);
            istringstream iss(line);

            int id;
            iss >> id;

            string name;
            iss >> name;

            int degree;
            iss >> degree;

            int* friendsIds = new int[degree];
            for (int j = 0; j < degree; j++) {
                int friendId;
                iss >> friendId;
                friendsIds[j] = friendId;
            }
            Person person(id, name, friendsIds, degree);
            delete [] friendsIds;
            people[i] = person;
            person.removeFriends();
        }
    } 
    else {
        // Empty friendship network
        people = NULL;
        numOfPeople = 0;
    }
}

FriendNet::FriendNet(const FriendNet& aNet) {
    if (&aNet != this) {
        numOfPeople = aNet.numOfPeople;
        people = new Person[numOfPeople];
        for (int i = 0; i < numOfPeople; i++) {
            people[i] = aNet.people[i];
        }
    }
}
FriendNet::~FriendNet() {
    if (people != NULL) {
        for (int i = 0; i < numOfPeople; i++) {
            Person::Node* head = people[i].getList();
            if (head != NULL) {
                Person::Node* current = head;
                Person::Node* next;
                while (current != NULL) {
                    next = current->next;
                    delete current;
                    current = next;
                }
            }
        }
        delete [] people;
    }
}

void FriendNet::listFriends(const string personName, const int hopNo) {
    bool personInNetwork = false;
    int count = -1;
    for (int i = 0; i < numOfPeople; i++) {
        if (people[i].getName() == personName) {
            personInNetwork = true;
            count = i;
            break;
        }
    }

    if (personInNetwork) {
      
        // Make Array for checking what is already viewed
        int *viewed;
        viewed = new int[numOfPeople];
        int index = 0;

        // Call helper function
        if (hopNo >= 0)
            _list(people[count].getId() , hopNo , &viewed , &index);

        // Printing content of array 
        cout << "People accessible from " << people[count].getName() <<  " within " 
            << hopNo << " hops: " ; 
        for (int i = 0 ; i < index ; i++) { 
            cout << people[viewed[i]].getName() << ", "; 
        } 

        if (index == 0) {
            cout << "NOBODY";
        }
        cout << endl;

        for (int i = 0 ; i < numOfPeople ; i++)
            people[i].setViewed(false);
        delete [] viewed;
    }
    else {
        cout << personName << " does not exist in the network." << endl;
    }

}

void FriendNet::_list(const int currId , const int depthNo , int** viewed , int* index) {
    
    // When depth is 0 , no need to look forward
    // Just add to viwed Array
    if (depthNo <= 0) {
        return;
    }

    // Check bfs of currentId
    // Check if it is already viewed , if not add to view Array
    // repeat until depth is 0

    // Add to view Array
    Person* currPerson = &people[currId];
    (*currPerson).setViewed(true);

    for (int i = 0 ; i < (*currPerson).getSize() ; i++) {
        Person* currFriend = &(people[(*currPerson)[i]]);

        // Check if they are already viewed
        if (!(*currFriend).getViewed()) {
            (*currFriend).setViewed(true);
            // add to Array
            (*viewed)[*index] = ((*currFriend).getId());
            (*index)++;
        }

        // Search a level down by recurssion
        _list((*currFriend).getId() , depthNo - 1 ,  viewed , index); 
    }
}

void FriendNet::displayAverageDegrees() {
    double componentsArray[numOfPeople];
    int componentsIndex = 0;

    for (int i = 0 ; i < numOfPeople ; i++) {

        if (people[i].getViewed())
            continue;

        // Make Array for checking what is already viewed
        int *viewed;
        viewed = new int[numOfPeople];
        int index = 0;

        // Check all the people that are connected
        _getComponents(i , &viewed , &index);

        double total = people[i].getSize();
        double double_index = (double)(index) + 1;
        for (int j = 0 ; j < index ; j++) { 
            total += people[viewed[j]].getSize();
        }

        delete [] viewed; 
        
        componentsArray[componentsIndex++] = ( total / double_index);
    }

    cout << "There are " << componentsIndex << " connected components. The average degrees are:" << endl;
    for (int i = 0 ; i < componentsIndex ; i++) {
        cout << "For component " << i << ": ";
        printf("%4.2f\n", componentsArray[i]);        
    }

    for (int i = 0 ; i < numOfPeople ; i++)
        people[i].setViewed(false);
}

void FriendNet::displayDiameters() {
    int componentsArray[numOfPeople];
    int componentsIndex = 0;

    // Get Components
    for (int i = 0 ; i < numOfPeople ; i++) {
        if (people[i].getViewed())
            continue;

        // Make Array for checking what is already viewed
        int *viewed;
        viewed = new int[numOfPeople];
        int index = 0;

        // Check all the people that are connected
        _getComponents(i , &viewed , &index);

        // Add the current person to viewed as well
        viewed[index++] = i;

        // Viewed Array has the graph of the connected sub graph
        // Make an array that depicts the distances of the sub graph
        int** graph;
        graph = new int*[index];
        for (int i = 0 ; i < index ; i++) {
            graph[i] = new int[index];
            for (int j = 0 ; j < index ; j++)
                graph[i][j] = INF; // initialize empty array with INF distance
        }
        _convertToDoubleArray(viewed , &graph , index);

        // Calculate all possible shortest paths
        parseGraph(&graph , index); 

        // Find the longest path of the shortest path
        int answer = 0;
        _longestShortestPath(graph , index , &answer);

        componentsArray[componentsIndex++] = answer;

        delete [] viewed; 
        for (int j = 0 ; j < index ; j++) {
            delete [] graph[j];
        }
        delete [] graph;
    }

    cout << "There are " << componentsIndex << " connected components. The diameters are:" << endl;
    for (int i = 0 ; i < componentsIndex ; i++) {
        cout << "For component " << i << ": " << componentsArray[i] << endl;        
    }

    for (int i = 0 ; i < numOfPeople ; i++)
        people[i].setViewed(false);

}

void FriendNet::parseGraph (int*** graph , int graphLength)  {
    for (int k = 0; k < graphLength; k++)  {  
        // Pick all vertices as source one by one  
        for (int i = 0; i < graphLength; i++)  {  
            // Pick all vertices as destination for the  
            // above picked source  
            for (int j = 0; j < graphLength; j++) {  
                // If vertex k is on the shortest path from  
                // i to j, then update the value of dist[i][j]  
                if ((*graph)[i][k] + (*graph)[k][j] < (*graph)[i][j])  
                    (*graph)[i][j] = (*graph)[i][k] + (*graph)[k][j];  
            }  
        }  
    } 
}

void FriendNet::_convertToDoubleArray(const int* viewed , int*** graph , const int index)  {
    for (int i = 0 ; i < index ; i++) {
        for (int j = 0 ; j < index ; j++) {
            // The i == j diagnol is 0
            if (i == j)
                (*graph)[i][j] = 0;
            else if ((*graph)[i][j] == INF) {
                // Check if the person at viewed index i has a friend at viewed index j
                Person personI = people[viewed[i]];
                Person personJ = people[viewed[j]];

                if (personI.hasFriend(personJ.getId())) {
                    (*graph)[i][j] = 1;
                    (*graph)[j][i] = 1;
                }
            }
        }
    }
}  

void FriendNet::_longestShortestPath(int** graph , int size , int* answer) {
    for (int i = 0 ; i < size ; i++) {
        for (int j = 0 ; j < size ; j++) {
            if (graph[i][j] > *answer) {
                *answer = graph[i][j];
            }
        }
    }
}

void FriendNet::_getComponents(const int currId , int** viewed, int* index) {
    // When depth is 0 , no need to look forward
    // Just add to viwed Array
    if (people[currId].getViewed()) {
        return;
    }

    // Check friends of currentId
    // Check if it is already viewed , if not add to view Array
    // repeat until depth is 0

    // Add to view Array
    Person* currPerson = &people[currId];
    (*currPerson).setViewed(true);

    for (int i = 0 ; i < (*currPerson).getSize() ; i++) {
        Person* currFriend = &(people[(*currPerson)[i]]);

        // Check if they are already viewed
        if (!(*currFriend).getViewed()) {
            // add to Array
            (*viewed)[*index] = ((*currFriend).getId());
            (*index)++;
        }

        // Search a level down by recurssion
        _getComponents((*currFriend).getId() ,  viewed , index); 
    }
}