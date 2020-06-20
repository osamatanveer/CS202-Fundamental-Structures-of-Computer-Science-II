/*
* Title: Algorithm Efficiency and Sorting
* Author: Osama Tanveer
* ID: 21801147
* Section: 3
* Assignment: 1
* Description: This the driver main for sorting.cpp. It analyzes the time count, 
* number of comparies and data moves, for different values of N. 
*/
#include <iostream>
#include "sorting.h"
#include "auxArrayFunctions.h"
#include <chrono>

using namespace std;

void performanceAnalysis() {
    int compCount = 0;
    int moveCount = 0;
    int *arr1;
    int *arr2;
    int *arr3;
    
    cout << "RANDOM NUMBER ARRAYS" << endl;
    // Insertion Sort
    cout << "------------------------------------------------------------" << endl;
    cout << "Part c - Time analysis of Insertion Sort" << endl;
    cout << "Array Size\tTime Elapsed\t   compCount\t     moveCount" << endl;
    for (int i = 10000; i <= 30000; i += 5000) {
        compCount = 0;
        moveCount = 0;
        createRandomArrays(arr1, arr2, arr3, i);
        clock_t begin_time = clock();
        insertionSort(arr1, i, compCount, moveCount);
        auto ms = float( clock () - begin_time ) / (double) CLOCKS_PER_SEC;
        ms *= 1000;
        cout << i << "           ";
        cout << ms << " ms             ";
        cout << compCount << "         ";
        cout << moveCount << endl;
    } 
    
    // Merge Sort
    cout << "------------------------------------------------------------" << endl;
    cout << "Part c - Time analysis of Merge Sort" << endl;
    cout << "Array Size\tTime Elapsed\t   compCount\t     moveCount" << endl;
    for (int i = 10000; i <= 30000; i += 5000) {
        compCount = 0;
        moveCount = 0;
        createRandomArrays(arr1, arr2, arr3, i);
        clock_t begin_time = clock();
        mergeSort(arr1, i, compCount, moveCount);
        mergeSort(arr3, i, compCount, moveCount);
        mergeSort(arr2, i, compCount, moveCount);
        double ms = double( clock () - begin_time ) / (double) CLOCKS_PER_SEC;
        ms *= 1000;
        cout << i << "           ";
        cout << ms/3 << " ms                 ";
        cout << compCount << "           ";
        cout << moveCount << endl;
    }
    // Quick Sort
    cout << "------------------------------------------------------------" << endl;
    cout << "Part c - Time analysis of Quick Sort" << endl;
    cout << "Array Size\tTime Elapsed\t   compCount\t     moveCount" << endl;
    for (int i = 10000; i <= 30000; i += 5000) {
        compCount = 0;
        moveCount = 0;
        createRandomArrays(arr1, arr2, arr3, i);
        clock_t begin_time = clock();
        quickSort(arr1, i, compCount, moveCount);
        quickSort(arr3, i, compCount, moveCount);
        quickSort(arr2, i, compCount, moveCount);
        double ms = double( clock () - begin_time ) / (double) CLOCKS_PER_SEC;
        ms *= 1000;
        cout << i << "           ";
        cout << ms/3 << " ms                 ";
        cout << compCount << "           ";
        cout << moveCount << endl;
    }
    cout << endl;
    cout << "ALREADY SORTED ARRAYS" << endl;
    // Insertion Sort
    cout << "------------------------------------------------------------" << endl;
    cout << "Part c - Time analysis of Insertion Sort" << endl;
    cout << "Array Size\tTime Elapsed\t   compCount\t     moveCount" << endl;
    for (int i = 10000; i <= 30000; i += 5000) {
        compCount = 0;
        moveCount = 0;
        createAlreadySortedArrays(arr1, arr2, arr3, i);
        clock_t begin_time = clock();
        for (int j = 0; j < 100; j++) 
            insertionSort(arr1, i, compCount, moveCount);
        double ms = double( clock () - begin_time ) / (double) CLOCKS_PER_SEC;
        ms *= 1000;
        cout << i << "           ";
        cout << ms/100 << " ms            ";
        cout << compCount << "             ";
        cout << moveCount << endl;
    } 
    
    // Merge Sort
    cout << "------------------------------------------------------------" << endl;
    cout << "Part c - Time analysis of Merge Sort" << endl;
    cout << "Array Size\tTime Elapsed\t   compCount\t     moveCount" << endl;
    for (int i = 10000; i <= 30000; i += 5000) {
        compCount = 0;
        moveCount = 0;
        createAlreadySortedArrays(arr1, arr2, arr3, i);
        clock_t begin_time = clock();
        mergeSort(arr1, i, compCount, moveCount);
        mergeSort(arr3, i, compCount, moveCount);
        mergeSort(arr2, i, compCount, moveCount);
        double ms = double( clock () - begin_time ) / (double) CLOCKS_PER_SEC;
        ms *= 1000;
        cout << i << "           ";
        cout << ms/3 << " ms              ";
        cout << compCount << "           ";
        cout << moveCount << endl;
    }
    // Quick Sort
    cout << "------------------------------------------------------------" << endl;
    cout << "Part c - Time analysis of Quick Sort" << endl;
    cout << "Array Size\tTime Elapsed\t   compCount\t     moveCount" << endl;
    for (int i = 10000; i <= 30000; i += 5000) {
        compCount = 0;
        moveCount = 0;
        createAlreadySortedArrays(arr1, arr2, arr3, i);
        clock_t begin_time = clock();
        quickSort(arr1, i, compCount, moveCount);
        auto ms = float( clock () - begin_time ) / (double) CLOCKS_PER_SEC;
        ms *= 1000;
        cout << i << "           ";
        cout << ms << " ms          ";
        cout << compCount << "           ";
        cout << moveCount << endl;
    }
}

int main() {
    // Question 2
    // Part B
    int compCount = 0;
    int moveCount = 0;
    int arr[] = {9, 5, 8, 15, 16, 6, 3, 11, 18, 0, 14, 17, 2, 9, 11, 7};
    int len = 16;

    cout << "Insertion Sort" << endl;
    insertionSort(arr, len, compCount, moveCount);
    displayArray(arr, len);
    cout << "Number of moves: " << moveCount << endl;
    cout << "Number of comparisons: " << compCount << endl;

    cout << "Merge Sort" << endl;
    int arr1[] = {9, 5, 8, 15, 16, 6, 3, 11, 18, 0, 14, 17, 2, 9, 11, 7};
    compCount = 0;
    moveCount = 0;

    mergeSort(arr1, len, compCount, moveCount);
    displayArray(arr1, len);
    cout << "Number of moves: " << moveCount << endl;
    cout << "Number of comparisons: " << compCount << endl;
    
    cout << "Quick Sort" << endl;
    int arr2[] = {9, 5, 8, 15, 16, 6, 3, 11, 18, 0, 14, 17, 2, 9, 11, 7};
    compCount = 0;
    moveCount = 0;
    mergeSort(arr2, len, compCount, moveCount);
    displayArray(arr2, len);
    cout << "Number of moves: " << moveCount << endl;
    cout << "Number of comparisons: " << compCount << endl;
    cout << "-------------------------------------------------------" << endl;
    // Part C
    performanceAnalysis();
    return 0;
}