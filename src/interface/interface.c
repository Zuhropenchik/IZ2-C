#include <stdio.h>
#include <stdlib.h>
#include "Letters.h"
#include "Vector.h"
#include "Searching.h"
#include "interface.h"
void interface(Vector * vector, FILE * f){
    if(vector == NULL || f == NULL)
        return;

    char *name = (char*)malloc(sizeof(char)*100);
    int day1, month1, year1, day2, month2, year2;
    printf("Input first date: ");
    scanf("%d %d %d", &day1, &month1, &year1);
    printf("Input second date: ");
    scanf("%d %d %d", &day2, &month2, &year2);

    if(day1 <= 0 || month1 <=0 || year1<=0 || day2 <= 0 || month2 <=0 || year2<=0) {
        printf("Try again:\n");
    } else {
        printf("Input name of recipient: ");
        scanf("%s", name);
        search(vector, day1, month1, year1, day2, month2, year2, name, f);
    }
    free(name);
}