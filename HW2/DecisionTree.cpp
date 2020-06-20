/* *
* Author : Osama Tanveer
* ID : 21801147
* Section : 3
* Assignment : 2
*/
#include "DecisionTree.h"
#include <fstream>
#include <sstream>

DecisionTree::~DecisionTree() {
    destroy(root);
}

void DecisionTree::destroy(DecisionTreeNode* root) {
    if (root) {
        destroy(root->getLeftPtr());
        destroy(root->getRightPtr());
        delete root;
    }
}

// Part A
double DecisionTree::calculateEntropy(const int* classCounts, const int numClasses) {
    int sumOfClassCounts = 0;
    for (int i = 0; i < numClasses; i++) {
        sumOfClassCounts += classCounts[i];
    }

    double h_n = 0;
    double fraction = 0;
    for (int i = 0; i < numClasses; i++) {
        fraction = (double) classCounts[i] / sumOfClassCounts;
        if (fraction != 0)
            h_n -= fraction * log2(fraction);
    }

    return h_n;
}

// Part B
double DecisionTree::calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId) {

    // Assuming that the classes are numbered in order
    // That is the classes are named 1,2,3,4 and so on

    // Find the max of the labels which would be the total number of classes
    int numClasses = 0;
    for (int i = 0 ; i < numSamples ; i++) {
        if (numClasses < labels[i])
            numClasses = labels[i];
    }

    // Find the classCounts for H(P), H(left), H(right)
    int *classCounts = new int[numClasses];
    int *leftClassCounts = new int[numClasses];
    int *rightClassCounts = new int[numClasses];

    // Find the samples in left and right
    int leftSampleSize = 0;
    int rightSampleSize = 0;

    // Initialize the values to 0
    for (int i = 0 ; i < numClasses ; i++){
        classCounts[i] = 0;
        leftClassCounts[i] = 0;
        rightClassCounts[i] = 0;
    }

    for (int i = 0 ; i < numSamples ; i++) {
        // Check if this sample should be considered
        if (usedSamples[i]) {
            // Count according to class number
            classCounts[labels[i] - 1] += 1;

            // If data[i][featureId] == 0 , the tree will go left
            // Else it will go right

            if (data[i][featureId] == 0) {
                leftClassCounts[labels[i] - 1] += 1;
                leftSampleSize++;
            } else {
                rightClassCounts[labels[i] - 1] += 1;
                rightSampleSize++;
            }

        }
    }

    // Calulate the H(P) , H(left) , H(right)
    double h_p = calculateEntropy(classCounts , numClasses);
    double h_left = calculateEntropy(leftClassCounts , numClasses);
    double h_right = calculateEntropy(rightClassCounts , numClasses);

    // cout << h_left << "\n";

    // Calculate P left and P right
    double p_left = (double) leftSampleSize / (leftSampleSize + rightSampleSize);
    double p_right = (double) rightSampleSize / (leftSampleSize + rightSampleSize);

    delete [] classCounts;
    delete [] leftClassCounts;
    delete [] rightClassCounts;
    // Calculate the Information Gain
    return h_p - ((p_left * h_left) + (p_right * h_right));
}


// Part D
void DecisionTree::train(const bool** data, const int* labels, const int numSamples, const int numFeatures) {
    
    // Assign numFeatures to the global variable
    numberOfFeatures = numFeatures;

    // Used samples initialize
    bool usedSamples[numSamples];
    for (int i = 0; i < numSamples; i++) {
        usedSamples[i] = true;
    }

    // Calculating information gain for all features
    // Get Information Gain for all valid features
    double maxIg = 0;
    int maxIgIndex= -1;
    for (int i = 0 ; i < numFeatures ; i++){
        double temp = calculateInformationGain(data, labels, numSamples, numFeatures, usedSamples, i);
        if (maxIg < temp) {
            maxIg = temp;
            maxIgIndex = i;
        }
    }

    // Creating node
    root = new DecisionTreeNode();
    root->setFeatureIndexForDecision(maxIgIndex);

    // Create an array for features used so far
    bool* featuresUsedSoFar = new bool[numFeatures];
    for (int i = 0 ; i < numFeatures ; i++) {
        if (i == maxIgIndex)
            featuresUsedSoFar[i] = true;
        else
            featuresUsedSoFar[i] = false;

    }

    // Create two arrays for left and right child used samples
    bool* leftUsedSample = new bool[numSamples];
    bool* rightUsedSample = new bool[numSamples];

    // Check for purity of the samples
    bool leftSampleIsPure = true;
    bool rightSampleIsPure = true;

    int leftLabelCheck = -1;
    int rightLabelCheck = -1;


    for (int i = 0; i < numSamples; i++) {

        if (data[i][maxIgIndex] == 0) {
            leftUsedSample[i] = true;
            rightUsedSample[i] = false;
            
            // Update the value of the label the first time
            // If at any point the labels are not the same then the sample is not pure
            if (leftLabelCheck == -1)
                leftLabelCheck = labels[i];
            else if (leftLabelCheck != labels[i])
                leftSampleIsPure = false;

        } else {
            leftUsedSample[i] = false;
            rightUsedSample[i] = true;

            // Same Concept as above
            if (rightLabelCheck == -1)
                rightLabelCheck = labels[i];
            else if (rightLabelCheck != labels[i])
                rightSampleIsPure = false;

        }
    }

    // If right or left side is not pure, divide the node to that side
    if (!leftSampleIsPure)
        root->setLeftChildPtr(trainHelper(data, labels, numSamples, numFeatures, leftUsedSample, featuresUsedSoFar));
    if (!rightSampleIsPure)
        root->setRightChildPtr(trainHelper(data, labels, numSamples, numFeatures, rightUsedSample, featuresUsedSoFar));

    // Delete Arrays that are not needed later
    delete[] leftUsedSample;
    delete[] rightUsedSample;
    delete[] featuresUsedSoFar;


    if (leftSampleIsPure) {
        root->setLeftChildPtr(new DecisionTreeNode());
        root->getLeftPtr()->setLeafClass(leftLabelCheck);
    }
    if (rightSampleIsPure){
        root->setRightChildPtr(new DecisionTreeNode());
        root->getRightPtr()->setLeafClass(rightLabelCheck);
    }
}

void DecisionTree::train(const string fileName, const int numSamples, const int numFeatures) {
    ifstream infile(fileName);

    // Store the data into a double array
    bool** data = new bool*[numSamples];
    for (int i = 0 ; i < numSamples ; i++)
        data[i] = new bool[numFeatures];

    // Store the labels in a single array
    int* labels = new int[numSamples];

    // Run till the number of Samples provided or if end of file reached
    for (int i = 0 ; i < numSamples && !infile.eof() ; i++ ) {

        string line;
        getline(infile , line);

        // Parse the line
        istringstream iss(line);
        for (int j = 0 ; j < numFeatures ; j++) {
            int value;
            iss >> value;
            data[i][j] = value;
        }

        // Add the label into the array
        int label;
        iss >> label;
        labels[i] = label;
    }

    // Call the other implementation of the train method
    train((const bool**) data , (const int*) labels, numSamples , numFeatures);
    for (int i = 0; i < numSamples; i++) {
        delete [] data[i];
    }
    delete [] data;
    delete [] labels;
}

DecisionTreeNode* DecisionTree::trainHelper(const bool** data, const int* labels, const int numSamples, const int numFeatures, bool* usedSamples ,bool* featuresUsedSoFar) {
    
    // Get Information Gain for all valid features
    double maxIg = 0;
    int maxIgIndex= -1;
    for (int i = 0 ; i < numFeatures ; i++){
        
        //Check if the feature is not already used
        if (featuresUsedSoFar[i] != 1) {

            double temp = calculateInformationGain(data, labels, numSamples, numFeatures, usedSamples, i);
            if (maxIg < temp) {
                maxIg = temp;
                maxIgIndex = i;
            }

        }
    }

    // Make the node for the child and the feature index
    DecisionTreeNode* childNode = new DecisionTreeNode();
    childNode->setFeatureIndexForDecision(maxIgIndex);

    // Update the array of features used so far and check if all features have been used
    bool allFeaturesUsed = true;
    featuresUsedSoFar[maxIgIndex] = true;
    for (int i = 0 ; i < numFeatures ; i++) {
        if (featuresUsedSoFar[i] == false) {
            allFeaturesUsed = false;
            break;
        }
    }
    
    // Create two arrays for left and right child used samples
    bool* leftUsedSample = new bool[numSamples];
    bool* rightUsedSample = new bool[numSamples];

    // Check for purity of the samples
    bool leftSampleIsPure = true;
    bool rightSampleIsPure = true;

    int leftLabelCheck = -1;
    int rightLabelCheck = -1;


    for (int i = 0; i < numSamples; i++) {

        // If the used samples are true, then divide , otherwise do not divide
        if (usedSamples[i] == true) {

            if (data[i][maxIgIndex] == 0) {
                leftUsedSample[i] = true;
                rightUsedSample[i] = false;
                
                // Update the value of the label the first time
                // If at any point the labels are not the same then the sample is not pure
                if (leftLabelCheck == -1)
                    leftLabelCheck = labels[i];
                else if (leftLabelCheck != labels[i])
                    leftSampleIsPure = false;

            } else {
                leftUsedSample[i] = false;
                rightUsedSample[i] = true;

                // Same Concept as above
                if (rightLabelCheck == -1)
                    rightLabelCheck = labels[i];
                else if (rightLabelCheck != labels[i])
                    rightSampleIsPure = false;
            }
 
        } 
        // These samples have not reached the parent split and therefore cannot go further in the child splits
        else {
            leftUsedSample[i] = false;
            rightUsedSample[i] = false;
        }
    }

    // If all features have been used, return and exit
    if (allFeaturesUsed){

        // Set the leaf nodes
        childNode->setLeftChildPtr(new DecisionTreeNode);
        childNode->setRightChildPtr(new DecisionTreeNode);

        childNode->getLeftPtr()->setLeafClass(leftLabelCheck);
        childNode->getRightPtr()->setLeafClass(rightLabelCheck);

        return childNode;
    }


    // If right or left side is not pure, divide the node to that side
    // Return the node afterwards
    if (!leftSampleIsPure)
        childNode->setLeftChildPtr(trainHelper(data, labels, numSamples, numFeatures, leftUsedSample, featuresUsedSoFar));
    if (!rightSampleIsPure)
        childNode->setRightChildPtr(trainHelper(data, labels, numSamples, numFeatures, rightUsedSample, featuresUsedSoFar));
    
    // Remove the arrays when not needed
    delete[] leftUsedSample;
    delete[] rightUsedSample;

    if (leftSampleIsPure){
        childNode->setLeftChildPtr(new DecisionTreeNode);
        childNode->getLeftPtr()->setLeafClass(leftLabelCheck);
    }    
    if (rightSampleIsPure){
        childNode->setRightChildPtr(new DecisionTreeNode);
        childNode->getRightPtr()->setLeafClass(rightLabelCheck);
    }

    return childNode;
}

// Part E
int DecisionTree::predict(const bool* data) {

    // Go through the tree to find the leaf node which will be the predicted class
    DecisionTreeNode* traversalNode = root;
    while(!traversalNode->isLeaf()) {
        int currentFeature = traversalNode->getFeature();
        // If the value of the data at this feature is 0 we go left 
        // Else we go right
        if (data[currentFeature] == 0)
            traversalNode = traversalNode->getLeftPtr();
        else
            traversalNode = traversalNode->getRightPtr();
    }

    return traversalNode->getLeafClass();
}

// Part F
double DecisionTree::test(const bool** data, const int* labels, const int numSamples) {

    // Predict the values of the data using our training data
    int truePred = 0;
    for (int i = 0 ; i < numSamples ; i++) {
        int prediction = predict(data[i]);
        if (prediction == labels[i])
            truePred++;
    }
    return (double) truePred / numSamples;
}

double DecisionTree::test(const string fileName, const int numSamples) {
    ifstream infile(fileName);

    // Store the data into a double array
    bool** data = new bool*[numSamples];
    for (int i = 0 ; i < numSamples ; i++)
        data[i] = new bool[numberOfFeatures];
    
    // Store the labels in a single array
    int* labels = new int[numSamples];

    // Run till the number of Samples provided or if end of file reached
    for (int i = 0 ; i < numSamples && !infile.eof() ; i++ ) {

        string line;
        getline(infile , line);

        // Parse the line
        istringstream iss(line);
        for (int j = 0 ; j < numberOfFeatures ; j++) {
            int value;
            iss >> value;
            data[i][j] = value;
        }

        // Add the label into the array
        int label;
        iss >> label;
        labels[i] = label;
    }

    test((const bool**) data , (const int*) labels, numSamples);
    delete [] labels;
    for (int i = 0; i < numSamples; i++) 
        delete [] data[i];
    delete [] data;
}

// Part G
void DecisionTree::print() {
    // Print the tree using preorder method
    printHelper(root, 0);
}

void DecisionTree::printHelper(DecisionTreeNode* node, int tabs) {
    
    if (node == NULL) 
        return; 

    // Print tabs for the level
    for (int i = 0 ; i < tabs ; i++) {
        cout << "\t";
    }
    
    // Check if the node is a leaf node
    if (node->isLeaf()){
        cout << "Class=" << node->getLeafClass() << endl;
    } else {
        cout << node->getFeature() << endl;; 
    }
  
    /* then recur on left sutree */
    printHelper(node->getLeftPtr(), (tabs + 1 ) );  
  
    /* now recur on right subtree */
    printHelper(node->getRightPtr(), (tabs + 1 ) );  
}