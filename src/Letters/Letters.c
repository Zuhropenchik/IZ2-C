#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Letters.h"
#define MAX_LEN 100
int total_day(const Letters * letter){
    if(letter == NULL)
        return -1;
    return letter->day + letter->month * 31 + letter->year*365;
}
int Compare(const Letters * letter1, const Letters * letter2){
    if(letter1 == NULL || letter2 == NULL)
        return 0;
    return total_day(letter1)-total_day(letter2);
}
char* get_str(FILE* file) {
    char* str;
    int size = sizeof (char)*MAX_LEN;
    str = (char*)malloc(sizeof(char)*MAX_LEN);
    fgets(str, size, file);
    str[strlen(str)-1] = '\0';
    return str;
}

Letters * input_letter(FILE* f){
    if(f == NULL)
        return NULL;
    Letters * letter = (Letters*)malloc(sizeof(Letters));
    if(letter == NULL)
        return NULL;
    char* temp;

    letter->sender =get_str(f);
    if(letter->sender == NULL || feof(f))
        return NULL;

    temp =get_str(f);
    if(feof(f))
        return NULL;
    letter->recipients_num = atoi(temp);

    letter->recipients = (char**)malloc(sizeof(char*)*letter->recipients_num);
    if(letter->recipients == NULL || feof(f))
        return NULL;

    for(int i=0; i<letter->recipients_num; i++){
        letter->recipients[i] =  get_str(f);
        if(letter->recipients[i] == NULL || feof(f))
            return NULL;
    }

    letter->theme =get_str(f);
    if(letter->theme == NULL || feof(f))
        return NULL;

    letter->body =get_str(f);
    if(letter->body == NULL || feof(f))
        return NULL;

    temp = get_str(f);
    if(feof(f))
        return NULL;
    letter->day = atoi(temp);

    temp = get_str(f);
    if(feof(f))
        return NULL;
    letter->month = atoi(temp);

    temp = get_str(f);
    if(feof(f))
        return NULL;
    letter->year = atoi(temp);

    free(temp);
    return letter;
}
void print_letter(Letters * letters, FILE * f){
    if(letters == NULL || f == NULL)
        return;
    fprintf(f,"from: %s\n", letters->sender);
    fprintf(f, "to: ");
    for(int i=0; i<letters->recipients_num; i++) {
        fprintf(f, "%s", letters->recipients[i]);
        if(i!=letters->recipients_num-1)
            fprintf(f,", ");
    }
    fprintf(f,"\nTheme: %s\n", letters->theme);
    fprintf(f,"%s\n", letters->body);
    fprintf(f,"%d.%d.%d\n\n", letters->day, letters->month, letters->year);
}
void Assignment(Letters* letter1, Letters * letter2){
    strcpy(letter1->sender, letter2->sender);
    letter1->recipients_num = letter2->recipients_num;
    for(int i=0; i<letter1->recipients_num;i++)
        strcpy(letter1->recipients[i], letter2->recipients[i]);
    strcpy(letter1->theme, letter2->theme);
    strcpy(letter1->body, letter2->body);
}