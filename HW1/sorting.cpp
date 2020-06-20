/*
* Title: Algorithm Efficiency and Sorting
* Author: Osama Tanveer
* ID: 21801147
* Section: 3
* Assignment: 1
* Description: This cpp file contains implementations of insertion sort, merge sort, and 
* quick sort that also counts the number of key comparisons and data moves. 
*/

#include <iostream>
// #include "sorting.h"
using namespace std;

void insertionSort(int *arr, int size, int &compCount, int &moveCount);
void quickSort(int *arr, int size, int &compCount, int &moveCount);
void mergeSort(int *arr, int size, int &compCount, int &moveCount);

// INSERTION SORT
void insertionSort(int *arr, int size, int &compCount, int &moveCount) {
    compCount = 0;
    moveCount = 0;
    int key;
    int i;
    int count = 0; // counter to prevent double counting of 1 comparison

    for (int j = 1; j < size; j++) {
        count = 0;
        key = arr[j]; // First possible data move position
        moveCount++; 

        i = j-1;
        compCount++;
        while (i >= 0 && arr[i] > key) {
            if (count > 0) { // checking if a comparison has been counted or not
                compCount++;
            }     
            arr[i+1] = arr[i]; // Second possible data move position
            moveCount++; 
            i -= 1;
            count++;
        }
        arr[i+1] = key; // Third possible data move position
        moveCount++;
    }
}

// QUICK SORT
void partition(int *theArray, int first, int last, int &pivotIndex, int &compCount, int &moveCount) {
    moveCount++;
    int pivot = theArray[first]; // first data move
    int lastS1 = first;         
    int firstUnknown = first + 1;
    for (  ; firstUnknown <= last; ++firstUnknown) {
        compCount++; // comparison
        if (theArray[firstUnknown] < pivot) {  	
      	    ++lastS1;
            int temp = theArray[firstUnknown]; // second data mvoe
            theArray[firstUnknown] = theArray[lastS1]; // third data move
            theArray[lastS1] = temp; // fourth data move
            moveCount += 3;
        }
    }
    int temp = theArray[first]; // fifth data move
    theArray[first] = theArray[lastS1]; // sixth data move
    theArray[lastS1] = temp; // seventh data move
    moveCount += 3; 
    pivotIndex = lastS1;
}

void helperQuickSort(int *arr, int first, int last, int &compCount, int &moveCount) {
    int pivotIndex;

   if (first < last) {

    partition(arr, first, last, pivotIndex, compCount, moveCount);
    helperQuickSort(arr, first, pivotIndex-1, compCount, moveCount);
    helperQuickSort(arr, pivotIndex+1, last, compCount, moveCount);
   }
}

void quickSort(int *arr, int size, int &compCount, int &moveCount) {
    int first = 0;
    int last = size - 1;
    helperQuickSort(arr, first, last, compCount, moveCount);
}

// MERGE SORT
void merge(int *theArray, int first, int mid, int last, int &compCount, int &moveCount) {
   
	int tempArray[last+1]; 
   
    int first1 = first; 	
    int last1 = mid; 		
    int first2 = mid + 1;	
    int last2 = last;	
    int index = first1; 

    for ( ; (first1 <= last1) && (first2 <= last2); ++index) {
        compCount++;
        if (theArray[first1] < theArray[first2]) {  
            tempArray[index] = theArray[first1];
            ++first1;
            moveCount++;
        }
        else {  
            tempArray[index] = theArray[first2];
            ++first2;
            moveCount++;
        }
    }

    for (; first1 <= last1; ++first1, ++index) {
        moveCount++;
        tempArray[index] = theArray[first1];
    }
        

    for (; first2 <= last2; ++first2, ++index) {
        moveCount++;
        tempArray[index] = theArray[first2];
    }

    for (index = first; index <= last; ++index) {
        moveCount++;
        theArray[index] = tempArray[index];
    }
}

void helperMergeSort(int *arr, int first, int last, int &compCount, int &moveCount) {
	if (first < last) {
      int mid = (first + last)/2; 	
      helperMergeSort(arr, first, mid, compCount, moveCount);
      helperMergeSort(arr, mid+1, last, compCount, moveCount);
      merge(arr, first, mid, last, compCount, moveCount);
   }
} 

void mergeSort(int *arr, int size, int &compCount, int &moveCount) {
    int first = 0;
    int last = size - 1;
    helperMergeSort(arr, first, last, compCount, moveCount);
}

