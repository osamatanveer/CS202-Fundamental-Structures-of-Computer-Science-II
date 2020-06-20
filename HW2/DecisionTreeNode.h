/* *
* Author : Osama Tanveer
* ID : 21801147
* Section : 3
* Assignment : 2
*/
#include <iostream>

using namespace std;

class DecisionTreeNode {
    public:
    DecisionTreeNode();
    bool isLeaf();
    void setFeatureIndexForDecision(const int);
    void setLeftChildPtr(DecisionTreeNode* leftPtr);
    void setRightChildPtr(DecisionTreeNode* rightPtr);
    void setLeafClass(const int);

    int getFeature();
    DecisionTreeNode* getLeftPtr();
    DecisionTreeNode* getRightPtr();
    int getLeafClass();

    private:
    int featureIndexForDecision;
    int leafClass;
    DecisionTreeNode* leftChildPtr;
    DecisionTreeNode* rightChildPtr;
};