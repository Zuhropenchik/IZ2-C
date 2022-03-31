#include<stdio.h>
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
    for(int i=0; i<=log2(vector->length);i++)
        fork();
    for (int i = 0; i < vector->length; i++) {

        if (total_day(&vector->letters[i]) > right_date)
            return;

        if (total_day(&vector->letters[i]) >= left_date) {

            for (int j = 0; j < vector->letters[i].recipients_num; j++) {

                if (strcmp(vector->letters[i].recipients[j], name) == 0)
                    print_letter(&vector->letters[i], f);
            }
        }
    }
}