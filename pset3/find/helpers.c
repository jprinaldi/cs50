/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
   
#include <cs50.h>

#include "helpers.h"

void swap(int values[], int i, int j);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int low = 0;
    int high = n - 1;
    int mid;

    do {
        mid = low + (high - low)/2;
        if (value > values[mid])
            low = mid + 1;
        else if (value < values[mid])
            high = mid - 1;
        else
            return true;
    } while (low <= high);

    return false;
}

/**
 * Sorts array of n values.
 *
 * Intentional implementation of an inefficient sorting algorithm (Bubble Sort).
 */
void sort(int values[], int n)
{
    int swaps;

    do {
        swaps = 0;
        for (int i = 1; i < n; i++)
            if (values[i-1] > values[i]) {
                swap(values, i-1, i);
                swaps++;
            }
    } while (swaps > 0);
}

void swap(int values[], int i, int j)
{
    int temp = values[i];
    values[i] = values[j];
    values[j] = temp;
}
