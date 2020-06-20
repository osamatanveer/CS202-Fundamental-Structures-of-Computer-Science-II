
#include "maxHeap1.h"
MaxHeap::MaxHeap() {
    size = 0;
}

bool MaxHeap::heapIsEmpty() const {
    return (size == 0);
}

void MaxHeap::heapInsert(const Patient& newItem) {
    if (size <= MAX_HEAP) {
        items[size] = newItem;

        int place = size;
        int parent = (place - 1) / 2;
        while ((place > 0) && (items[place].getPriorityValue() >= items[parent].getPriorityValue())) {
            if (items[place].getPriorityValue() == items[parent].getPriorityValue()) {
                if (items[place].getArrivalTime() < items[parent].getArrivalTime()) {
                    Patient temp = items[parent];
                    items[parent] = items[place];
                    items[place] = temp;
                }
            }
            else {
                Patient temp = items[parent];
                items[parent] = items[place];
                items[place] = temp;

            }
            
            place = parent;
            parent = (place - 1)/2;
	    }
        size++;
    }
}

void MaxHeap::heapDelete(Patient& rootItem) {
    if (!heapIsEmpty()) {
		rootItem = items[0];
		items[0] = items[size - 1];
		heapRebuild(0);
        size--;
	}
}

void MaxHeap::heapRebuild(int root) {
    int child = 2 * root + 1;
	if (child < size) {		
		int rightChild = child + 1;
		if ((rightChild < size) && (items[rightChild].getPriorityValue() > items[child].getPriorityValue()))
			child = rightChild; 	

		if (items[root].getPriorityValue() <= items[child].getPriorityValue()) {
            if (items[root].getPriorityValue() == items[child].getPriorityValue()) {
                if (items[root].getArrivalTime() > items[child].getArrivalTime()) {
                    Patient temp = items[root];
                    items[root] = items[child];
                    items[child] = temp;
                    heapRebuild(child);
                }
            }
            else {
                Patient temp = items[root];
                items[root] = items[child];
                items[child] = temp;
                heapRebuild(child);
            }
			
		}
    }
}

Patient::Patient() {
    id = -1;
    priority = -1;
    arrivalTime = -1;
    serviceTime = -1;
    treatmentStartTime = -1;
    timeWhenFree = -1;
}

Patient::Patient(int patientID, int patientPriority, int patientArrivalTime, 
                int patientServiceTime, int treatmentStartTime, int endingTime, int insertTime) {
    Patient::id = patientID;
    Patient::priority = patientPriority;
    Patient::arrivalTime = patientArrivalTime;
    Patient::serviceTime = patientServiceTime;
    Patient::treatmentStartTime = treatmentStartTime;
    Patient::timeWhenFree = endingTime;
    Patient::insertTime = insertTime;
}

int Patient::getId() {
    return id;
}

int Patient::getPriorityValue() {
    return priority;
}

int Patient::getArrivalTime() {
    return arrivalTime;
}

int Patient::getServiceTime() {
    return serviceTime;
}    

int Patient::getEndingTime() {
    return timeWhenFree;
}

int Patient::getWaitTime() {
    return treatmentStartTime - insertTime;
}
        

void Patient::setTreatmentStartTime(int startTime) {
    treatmentStartTime = startTime;
}

void Patient::setEndingTime(int freeTime) {
    timeWhenFree = freeTime;
}

void Patient::setInsertTime(int insertTime) {
    Patient::insertTime = insertTime;
}
