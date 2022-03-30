#ifndef IZ2_VECTOR_H
#define IZ2_VECTOR_H

#endif //IZ2_VECTOR_H
typedef struct{
Letters * letters;
size_t length;
size_t capacity;
}Vector;
Vector* vector_constructor(size_t length, size_t capacity);
void add_letter(Vector* vector, FILE* f);
void input_vector(Vector * vector, FILE * f);
void free_vector(Vector** vector);
