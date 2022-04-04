#include <stdio.h>
#include <stdlib.h>
#include "Letters.h"
#include "Vector.h"
Vector* vector_constructor(size_t length, size_t capacity){
    Vector* vector = (Vector*)malloc(sizeof (Vector));

    vector->length = length;
    vector->capacity = capacity;
    if(length != 0 )
        vector->letters = (Letters*) malloc(sizeof(Letters)*vector->capacity);
    return vector;

}

void add_letter(Vector* vector, FILE * f){
    if(vector==NULL || f == NULL){
        return;
    }

    Letters* temp = input_letter(f);
    if(temp == NULL)
        return;

    if(vector->length+1 >= vector->capacity){
        vector->capacity *=2;
        vector->letters = (Letters*) realloc(vector->letters, sizeof(Letters)*vector->capacity);
        if(!vector->letters){
            return;
        }
    }
    vector->letters[vector->length] = *temp;
    ++vector->length;
    free(temp);
}
void add_letter2(Vector * vector, Letters * letter){
    if(vector==NULL || letter == NULL){
        return;
    }


    if(vector->length+1 >= vector->capacity){
        vector->capacity *=2;
        vector->letters = (Letters*) realloc(vector->letters, sizeof(Letters)*vector->capacity);
        if(!vector->letters){
            return;
        }
    }
    vector->letters[vector->length] = *letter;
    ++vector->length;
}
void input_vector(Vector * vector, FILE * f){
    if(f==NULL || vector == NULL)
        return;
    while(!feof(f)){
        add_letter(vector, f);
    }
}
void free_vector(Vector** vector){
    if (*vector == NULL)
        return;
    if((*vector)->letters == NULL){
        free(*vector);
        *vector = NULL;
        return;
    }
    free((*vector)->letters);
    free(*vector);
    *vector = NULL;
}
