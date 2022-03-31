#include<stdio.h>
#include "Letters.h"
#include "Vector.h"
#include "Sorting.h"
void swap(Vector * vector, int index1, int index2)
{
    Letters temp = vector->letters[index1];
    vector->letters[index1] = vector->letters[index2];
    vector->letters[index2] = temp;
}
void quick_sort(Vector * vector, const int low, const int high) {
if (low >= high) {
return;
}

int leftPtr = low, rightPtr = high;
while (leftPtr < rightPtr) {


while (leftPtr < rightPtr && Compare(&vector->letters[leftPtr], &vector->letters[high]) <=0)
    leftPtr++;


while (leftPtr < rightPtr && Compare(&vector->letters[rightPtr], &vector->letters[high]) >=0)
    rightPtr--;

swap(vector, leftPtr, rightPtr);
}

swap(vector, leftPtr, high);
quick_sort(vector, low, leftPtr - 1);
quick_sort(vector, leftPtr + 1, high);


}