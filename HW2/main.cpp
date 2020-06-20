/* *
* Author : Osama Tanveer
* ID : 21801147
* Section : 3
* Assignment : 2
*/
#include <iostream>
#include <math.h>
#include "DecisionTree.h"

using namespace std;

int main() {
    int numSamples = 498;
    int numFeatures = 21;
    int numSamplesTest = 473;

    DecisionTree* tree = new DecisionTree();
    tree->train( (const string) "train_data.txt" , (const int) numSamples , (const int) numFeatures);
    double accuracy = tree->test( (const string) "test_data.txt", numSamplesTest);
    cout << "The accuracy is " << accuracy << endl;
    tree->print();
    tree->~DecisionTree();
    delete tree;
    return 0;
}
