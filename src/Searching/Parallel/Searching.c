#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<unistd.h>
#include"Letters.h"
#include"Vector.h"
#include "Searching.h"
void search(Vector* vector, int left_day, int left_month, int left_year, int right_day, int right_month,
            int right_year, char*name, FILE* f){


    int left_date = left_day + 31 * left_month + 365 * left_year;
    int right_date = right_day + 31 * right_month + 365 * right_year;

    pid_t proc = getpid();
    size_t chunk_size;
    int pr_id = 0;
    int pr_num = (int)log2((double)vector->length);
    printf("%d", pr_num);
    while(proc != 0 && pr_id < pr_num - 1){
        proc = fork();
        if(proc < 0){
            printf("Fork error");
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
    usleep(10000 * pr_id);
    printf("Hello from parallel %d\n", pr_id);
    for (size_t i = chunk_size * pr_id; i < chunk_size * (pr_id + 1) && i < vector->length; i++) {

        if (total_day(&vector->letters[i]) > right_date)
            return;

        if (total_day(&vector->letters[i]) >= left_date) {

            for (int j = 0; j < vector->letters[i].recipients_num; j++) {

                if (strcmp(vector->letters[i].recipients[j], name) == 0)
                    print_letter(&vector->letters[i], f);
            }
        }
    }
    if(proc == 0){
        exit(0);
    }
}