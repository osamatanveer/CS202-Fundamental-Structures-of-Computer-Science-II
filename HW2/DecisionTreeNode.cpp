/* *
* Author : Osama Tanveer
* ID : 21801147
* Section : 3
* Assignment : 2
*/
#include "DecisionTreeNode.h"

DecisionTreeNode::DecisionTreeNode() {
    featureIndexForDecision = -1;
    leafClass = -1;
    leftChildPtr = NULL;
    rightChildPtr = NULL;
}

bool DecisionTreeNode::isLeaf() {
    if ((leftChildPtr == NULL) && (rightChildPtr == NULL))
        return true;
    return false;    
}

void DecisionTreeNode::setFeatureIndexForDecision(const int featureIndex) {
    featureIndexForDecision = featureIndex;
}

void DecisionTreeNode::setLeftChildPtr(DecisionTreeNode* leftPtr) {
    leftChildPtr = leftPtr;
}

void DecisionTreeNode::setRightChildPtr(DecisionTreeNode* rightPtr) {
    rightChildPtr = rightPtr;
}

void DecisionTreeNode::setLeafClass(const int _class) {
    leafClass = _class;
}

int DecisionTreeNode::getFeature() {
    return featureIndexForDecision;
}

DecisionTreeNode* DecisionTreeNode::getLeftPtr() {
    return leftChildPtr;
}

DecisionTreeNode* DecisionTreeNode::getRightPtr() {
    return rightChildPtr;
}

int DecisionTreeNode::getLeafClass() {
    return leafClass;
}