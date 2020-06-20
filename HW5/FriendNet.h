#include <string>
#include "Person.h"

#define INF 99999  

using namespace std;

class FriendNet {
    public:
        FriendNet(const string fileName);
        FriendNet(const FriendNet& aNet);
        ~FriendNet();

        void listFriends(const string personName, const int hopNo);
        void displayAverageDegrees();
        void displayDiameters();
        
    private:

        // helper method
        void _list(const int currId , const int depthNo , int** viewed , int* index);
        void _getComponents(const int currId , int** viewed, int* index);
        void parseGraph( int*** graphInput , int graphLength);
        void _convertToDoubleArray(const int* viewed , int*** graph , const int index);
        void _longestShortestPath(int** graph , int size , int* answer);
 
        Person* people;
        int numOfPeople;
};