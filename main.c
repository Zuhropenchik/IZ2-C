#include <stdio.h>
#include "Letters.h"
#include "Vector.h"
#include "Sorting.h"
#include "Searching.h"
#include "interface.h"
#include <string.h>
int main() {
    FILE * rf = fopen("Data/read.txt", "r");
    FILE * wf = fopen("Data/write.txt", "w");
    if(rf==NULL || wf == NULL){
        printf("Error file");
        return 0;
    }
    Vector * vector = vector_constructor(0,1);
    input_vector(vector, rf);
    quick_sort(vector, 0, (vector->length)-1);
    interface(vector, wf);
    free_vector(&vector);
    return 0;
}
