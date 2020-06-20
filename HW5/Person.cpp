#include "Person.h"

Person::Person() {
    id = -1;
    name = "";
    head = NULL;
    size = 0;
}

Person::Person(const int id, const string name, const int* friendsIds, const int numOfFriends) {
    Person::id = id;
    Person::name = name;
    head = NULL;
    if (friendsIds != NULL && numOfFriends != 0)
        for (int i = 0; i < numOfFriends; i++) {
            addFriend(friendsIds[i]);
        }
    size = numOfFriends;
}

int Person::getId() {
    return id;
}

int Person::getSize() {
    return size;
}

string Person::getName() {
    return name;
}

void Person::getFriends() {
    display();
}

void Person::setViewed(const bool view) {
    viewed = view;
}

bool Person::getViewed() {
    return viewed;
}

void Person::addFriend(const int friendId) {
    if (head == NULL) {
        head = new Node;
        head->friendId = friendId;
        head->next = NULL;
        size++;
        return;
    }
    Node* curr = head;
    Node* temp = new Node;
    temp->friendId = friendId;
    temp->next = NULL;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = temp;
    size++;
}

void Person::display() {
    Node* curr = head;
    while (curr != NULL) {
        cout << curr->friendId << " ";
        curr = curr->next;
    }
    cout << endl;
}

void Person::operator=(const Person& right) {
    if (&right != this) {
        id = right.id;
        name = right.name;
        size = right.size;
        if (right.head == NULL) {
            head = NULL;
        }
        else {
            if (head != NULL) {
                Node* current = head;
                Node* next;
                while (current != NULL) {
                    next = current->next;
                    delete current;
                    current = next;
                }
            }

            head = new Node;
            head->friendId = right.head->friendId;
            Node *newPtr = head;
            for (Node *origPtr = right.head->next; origPtr != NULL; origPtr = origPtr->next) {
                // Node* temp = origPtr;
                newPtr->next = new Node;
                newPtr = newPtr->next;
                newPtr->friendId = origPtr->friendId;
                
                newPtr->next = NULL;
            }
            newPtr->next = NULL;
        }
    }
}


int& Person::operator[](int index) { 
    if (index >= size) { 
        cout << "Array index out of bound, exiting"; 
        exit (EXIT_FAILURE);
    } 

    Node* curr = head;
    while ( index != 0 && curr != NULL) {
        curr = curr->next;
        index--;
    }
    return curr->friendId; 
} 

bool Person::hasFriend(const int id) {
    Node* curr = head;
    while (curr != NULL) {
        if (curr->friendId == id)
            return true;
        curr = curr->next;
    }
    return false;
}

Person::Node* Person::getList() {
    return head;
}

void Person::removeFriends() {
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