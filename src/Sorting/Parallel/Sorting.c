#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
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
void sorting(Vector * vector){
    pid_t proc = getpid();
    size_t chunk_size = 2;
    int pr_id = 0;
    int pr_num = (int)(vector->length+chunk_size-1)/(int)chunk_size;
    if(pr_num<1) {
        pr_num = 1;
    }
    Vector* shared_vector = mmap(NULL, sizeof(Vector), PROT_READ | PROT_WRITE,
                                 MAP_SHARED | MAP_ANONYMOUS, -1,0);
    shared_vector->letters = mmap(NULL, sizeof(Letters)*vector->capacity, PROT_READ | PROT_WRITE,
                                  MAP_SHARED | MAP_ANONYMOUS, -1,0);
    Vector ** Chuncks = mmap(NULL, sizeof(Vector*)*(pr_num*2-1), PROT_READ | PROT_WRITE,
                            MAP_SHARED | MAP_ANONYMOUS, -1,0);
    for(size_t i=0; i<pr_num; i++){
        Chuncks[i] = vector_constructor(0,1);
    }
    shared_vector->length = vector->length;
    shared_vector->capacity = vector->capacity;
    for(size_t i = 0; i < vector->length ; i++){
        shared_vector->letters[i] = vector->letters[vector->length-1-i];
    }
    for(size_t i = 0; i<vector->length; i++){
        add_letter2(Chuncks[i/chunk_size],&vector->letters[i]);
    }
    sem_t* semaphore = (sem_t*)mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE,
                                    MAP_SHARED | MAP_ANONYMOUS, -1,0);;
    sem_init(semaphore, 1, 1);

    while(proc != 0 && pr_id < pr_num - 1){
        proc = fork();
        if(proc < 0){
            printf("Fork error");
            return;
        }
        if(proc != 0)
            pr_id++;
    }
    merge_sort(Chuncks[pr_id]);

   for(size_t i = pr_id*chunk_size; i< (pr_id+1)*chunk_size && i < vector->length ; i++){
        sem_wait(semaphore);
        vector->letters[i] = Chuncks[pr_id]->letters[i-chunk_size*pr_id];
        sem_post(semaphore);
    }

    if(proc == 0)
        exit(0);
    for(size_t i = 0; i<vector->length; i++){
        vector->letters[i] = Chuncks[i/chunk_size]->letters[i%chunk_size];
    }
    munmap(shared_vector->letters,sizeof(Letters)*vector->length);
    munmap(vector, sizeof(Vector));
}