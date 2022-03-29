#ifndef IZ2_LETTERS_H
#define IZ2_LETTERS_H

#endif //IZ2_LETTERS_H
typedef struct {
    char* sender;
    char** recipients;
    int recipients_num;
    char* theme;
    char* body;
    int day;
    int month;
    int year;
}Letters;
int total_day(const Letters * letter);
int Compare(const Letters * letter1, const Letters * letter2);
char* get_str(FILE* file);
Letters * input_letter(FILE* f);
void print_letter(Letters * letters1, FILE * f);