#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<unistd.h>
#include<sys/mman.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include"Letters.h"
#include"Vector.h"
#include "Sorting.h"
#include "Searching.h"
void search(Vector* vector, int left_day, int left_month, int left_year, int right_day, int right_month,
            int right_year, char*name, FILE* f){


    int left_date = left_day + 31 * left_month + 365 * left_year;
    int right_date = right_day + 31 * right_month + 365 * right_year;

    Vector* shared_vector = mmap(NULL, sizeof(Vector), PROT_READ | PROT_WRITE,
                                 MAP_SHARED | MAP_ANONYMOUS, -1,0);
    shared_vector->letters = mmap(NULL, sizeof(Letters)*vector->capacity, PROT_READ | PROT_WRITE,
                                    MAP_SHARED | MAP_ANONYMOUS, -1,0);
    shared_vector->length = 0;
    shared_vector->capacity = vector->capacity;

    sem_t* semaphore = (sem_t*)mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE,
                                    MAP_SHARED | MAP_ANONYMOUS, -1,0);;
    sem_init(semaphore, 1, 1);

    pid_t proc = getpid();
    size_t chunk_size;
    int pr_id = 0;
    int pr_num = (int)log2((double)vector->length);
    while(proc != 0 && pr_id < pr_num - 1){
        proc = fork();
        if(proc < 0){
            printf("Fork error!\n");
            return;
        }
        if(proc != 0)
            pr_id++;
    }
    if(pr_num>1) {
        chunk_size = (vector->length + pr_num - 1) / (pr_num);
    }
    else {
        chunk_size = vector->length;
    }
    for (size_t i = chunk_size * pr_id; i < chunk_size * (pr_id + 1) && i < vector->length; i++) {

        if (total_day(&vector->letters[i]) > right_date)
            return;

        if (total_day(&vector->letters[i]) >= left_date) {

            for (int j = 0; j < vector->letters[i].recipients_num; j++) {

                if (strcmp(vector->letters[i].recipients[j], name) == 0) {
                    for(int i=0; i<pr_num; i++) {
                        if(i == pr_id) {
                            sem_wait(semaphore);
                            shared_vector->length++;
                            shared_vector->letters[shared_vector->length - 1] = vector->letters[i];
                            sem_post(semaphore);
                        }
                    }


                }
            }
        }
    }
    if(proc != 0) {
        merge_sort(shared_vector);
    }
    for(size_t i = chunk_size * pr_id; i < chunk_size * (pr_id + 1) && i < shared_vector->length; i++){
        print_letter(&shared_vector->letters[i], f);
    }
    if(proc == 0){
        exit(0);
    }


    printf("\n%zu\n",shared_vector->length);
}