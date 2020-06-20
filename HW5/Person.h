#include <iostream>
#include <stdlib.h>

using namespace std;

class Person {
    public:
        Person();    
        Person(const int id, const string name, const int* friendsIds, const int numOfFriends);
    
        int getId();
        string getName();
        int getSize();
        void getFriends();
        void addFriend(const int id);
        void display();
        void setViewed(const bool viewed);
        bool getViewed();
        bool hasFriend(const int id);

        void removeFriends();

        void operator=(const Person& right);
        int& operator[](int);
        
        struct Node {
            int friendId;
            Node* next;
        };

        Node* getList();

    private:
        
        int id;
        string name;
        Node *head;
        int size;
        bool viewed;
};