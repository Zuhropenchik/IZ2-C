#include<stdio.h>
#include "Letters.h"
#include "Vector.h"
#include "Sorting.h"
void merge(Vector * vector, Vector * left, Vector * right) {
    int m=0;
    int i = 0, j = 0;
    if(vector == NULL || left == NULL || right == NULL || left->length + right->length != vector->length){
        return;
    }
    while(i < left->length && j < right->length) {
        if (Compare(&left->letters[i], &right->letters[j]) < 0) {
            vector->letters[m] = left->letters[i];
            i++;
            m++;
        }

        else {
            vector->letters[m] = right->letters[j];
            j++;
            m++;
        }
    }

    for (; i < left->length; ++i) {
        vector->letters[m] = left->letters[i];
        m++;
    }
    for (; j < right->length; ++j) {
        vector->letters[m] = right->letters[j];
        m++;
    }

}

void merge_sort(Vector * vector) {
    if (vector->length <= 1) {
        return;
    }

    Vector * left = vector_constructor(0,1);
    Vector * right = vector_constructor(0,1);

    int i = 0;
    for (; i < vector->length / 2; ++i)
        add_letter2(left, &vector->letters[i]);

    for (; i < vector->length; ++i)
        add_letter2(right, &vector->letters[i]);

    merge_sort(left);
    merge_sort(right);
    merge(vector, left, right);
}