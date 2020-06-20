/* *
* Author : Osama Tanveer
* ID : 21801147
* Section : 3
* Assignment : 2
*/
#include "DecisionTreeNode.h"
#include <math.h>
#include <iostream>

using namespace std;

class DecisionTree {
    public:
    ~DecisionTree();
    void destroy(DecisionTreeNode* root);
    double calculateEntropy(const int* classCounts, const int numClasses);
    double calculateInformationGain(const bool** data, const int* labels, 
                                const int numSamples, const int numFeatures, const bool* usedSamples,
                                const int featureId);
    void train(const bool**, const int*, const int, const int);
    void train(const string, const int, const int);
    DecisionTreeNode* trainHelper(const bool** data, const int* labels, const int numSamples, const int numFeatures, bool* usedSamples ,bool* featuresUsedSoFar) ;
    int predict(const bool*);
    double test(const bool**, const int*, const int);
    double test(const string, const int);
    void print();
    void printHelper(DecisionTreeNode* node, int tabs);

    private:
    DecisionTreeNode *root;
    int numberOfFeatures;
};