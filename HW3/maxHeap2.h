#include <iostream>

using namespace std;
#ifndef MH2
#define MH2 1
class Patient {
    public:
        Patient();
        Patient(int patientID, int patientPriority, int patientArrivalTime, int patientServiceTime, 
            int treatmentStartTime = -1, int endTime = -1, int insertTime = -1);
        int getId();
        int getPriorityValue();
        int getArrivalTime();
        int getServiceTime();
        int getEndingTime();
        int getWaitTime();
        
        void setTreatmentStartTime(int startTime);
        void setEndingTime(int freeTime);
        void setInsertTime(int insertTime);

    private:
        int id;
        int priority;
        int arrivalTime;
        int serviceTime; 
        int treatmentStartTime;  
        int timeWhenFree; 
        int insertTime;
};

class MaxHeap {
    public:
        MaxHeap();
        ~MaxHeap();
        bool heapIsEmpty() const;
        void heapInsert(const Patient& newItem);
        void heapDelete(Patient& rootItem);

    protected:
	    void heapRebuild(int root); 
					    
    private:
        Patient *items;
	    int size;    
        int maxCapacity;        	
};
#endif