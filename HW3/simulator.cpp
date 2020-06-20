#include <iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include "maxHeap1.h"
#include "maxHeap2.h"

using namespace std;

double simulatorHelper(int numberOfDoctors, string filename, double avgwaitingtime, string &simulationDetails) {
    simulationDetails = "";
    // Initializing priority queue based on priority of patients
    MaxHeap priorityQueue;

    // Getting patients
    ifstream inFile(filename);
    string line;
    getline(inFile, line);
    int numberOfPatients = stoi(line); // number of patients always on first line
    int patientDetails[4]; // for patient details temporarily

    // Creating an array to store patients from file
    Patient patients[numberOfPatients];
    for (int i = 0; i < numberOfPatients; i++) {
        getline(inFile, line);
        // Parsing line and storing in patientDetails array
        istringstream iss(line);
        for (int j = 0; j < 4; j++) {
            int value;
            iss >> value;
            patientDetails[j] = value;
        }
        Patient patient(patientDetails[0], patientDetails[1], patientDetails[2], patientDetails[3]);
        patients[i] = patient;
    }

    int numberOfDocs = numberOfDoctors;

    // Patients currently being served
    Patient serving[numberOfDocs];
    for (int i = 0 ; i < numberOfDocs; i++) {
        Patient temp;
        serving[i] = temp;
    }

    // All docs free intially
    bool docsFree[numberOfDocs];
    for (int i = 0; i < numberOfDocs; i++) {
        docsFree[i] = true;
    }

    // Time since 12:00 pm
    int currentTime = 0; 
    
    bool patientsArrayEmpty = false;
    bool currentlyServing = false;

    int indexOfPatientToAddress = 0;
    int sumOfWaitTime = 0;

    while (1) {
        // Inserting into heap
        bool test = false;
        if (indexOfPatientToAddress < numberOfPatients) {
            Patient currentPatient = patients[indexOfPatientToAddress];
            if (indexOfPatientToAddress < numberOfPatients - 1){
                Patient nextPat = patients[indexOfPatientToAddress + 1];
                if(currentPatient.getArrivalTime() == nextPat.getArrivalTime()){
                    test = true;
                }
            }
            if (currentPatient.getArrivalTime() <= currentTime) {
                indexOfPatientToAddress++;
                currentPatient.setInsertTime(currentTime); // inserted at current time
                priorityQueue.heapInsert(currentPatient);  
            }
        }
        else {
            patientsArrayEmpty = true;
        }

        // Removing patients if treatment over
        for (int i = 0; i < numberOfDocs; i++) {
            if (!docsFree[i]) {
                if (serving[i].getEndingTime() == currentTime) {
                    docsFree[i] = true;
                    serving[i].setEndingTime(-1);
                }
            }
        }

        // Checking which doc is free
        int indexOfFreeDoc = -1;

        for (int i = 0; i < numberOfDocs; i++) {
            if (docsFree[i]) {
                indexOfFreeDoc = i;
                break;
            }
        }

        // Assigning patient to doctor from heap
        if (indexOfFreeDoc != -1 && !priorityQueue.heapIsEmpty() && !test) {
            Patient nextPatientInLine;
            priorityQueue.heapDelete(nextPatientInLine);
            nextPatientInLine.setTreatmentStartTime(currentTime);
            nextPatientInLine.setEndingTime(currentTime + nextPatientInLine.getServiceTime());
            int waitTime = nextPatientInLine.getWaitTime();
            sumOfWaitTime += waitTime;
            serving[indexOfFreeDoc] = nextPatientInLine;
            docsFree[indexOfFreeDoc]= false;
            simulationDetails += "Doctor " + to_string(indexOfFreeDoc) + " takes patient " + to_string(nextPatientInLine.getId()) 
                + " at minute " + to_string(currentTime) + "  (wait: " + to_string(waitTime) + " mins)\n";
        }

        // Setting current time
        int indexOfMinTime = 0;
        int minTime = INT_MAX;
        bool isAnyDoctorFree = false;
        bool allFree = true;
        bool temp = indexOfPatientToAddress >= numberOfPatients;
        for (int i = 0; i < numberOfDocs; i++) {
            if (minTime > serving[i].getEndingTime() && serving[i].getEndingTime() >= 0) {
                minTime = serving[i].getEndingTime();
            }
            if (docsFree[i]) {
                isAnyDoctorFree = true;
            }
            else {
                allFree = false;
            }
        }

        // Checking condition to terminate the loop
        if (allFree && temp && priorityQueue.heapIsEmpty())
            break;

        // Updating current time based on possible cases
        if (minTime <= patients[indexOfPatientToAddress].getArrivalTime()) {
            currentTime = minTime;
        }
        else if(isAnyDoctorFree && !priorityQueue.heapIsEmpty()) {
            currentTime = currentTime;
        }
        else if ((temp && !allFree) || (temp && priorityQueue.heapIsEmpty())) {
            currentTime = minTime;
        }
        else if (priorityQueue.heapIsEmpty() && allFree && !temp){
            currentTime = patients[indexOfPatientToAddress].getArrivalTime();
        }
        else if (minTime > patients[indexOfPatientToAddress].getArrivalTime()) {
            currentTime = patients[indexOfPatientToAddress].getArrivalTime();
        }
    }
    double avg = (double)sumOfWaitTime / numberOfPatients;
    return avg; 
}

void simulator(string filename, double avgwaitingtime) {
    string simulationDetails = "";
    int currNumOfDocs = 1;
    double temp = simulatorHelper(1, filename, avgwaitingtime, simulationDetails);
    double minAvgTime = temp;
    int numOfDocsWithMinAvgTime = 0;
    
    while (temp > avgwaitingtime) {
        currNumOfDocs++;
        temp = simulatorHelper(currNumOfDocs, filename, avgwaitingtime, simulationDetails);
        if (minAvgTime > temp) {
            minAvgTime = temp;
            numOfDocsWithMinAvgTime = currNumOfDocs;
        } 
    }
    cout << "Minimum number of doctors required: " << currNumOfDocs << endl;
    cout << endl; 
    cout << "Simultation with " << currNumOfDocs << " doctors:"<< endl;
    cout << simulationDetails << endl;
    cout.precision(3);
    printf("Average waiting time: %.2f minutes", minAvgTime);
    cout << endl;
}

int main(int argc, char** argv) {
    // Parsing command line arguments
    string fname = argv[1];
    double waitingtime = atof(argv[2]);

    // Passing arguments to simulator
    simulator(fname, waitingtime);

    return 0;
}