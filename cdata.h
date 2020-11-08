/*
Program: cdata.h
Purpose: Provide functions for a simple data structure value
Author:  Jan Hartstra
Date:    2020-10-24
*/

#define MAX_DATALINE_LENGTH 100

/* Define the data vector structure */
/* Should this be in header file? */
#define MAX_VECTOR_SIZE 100
typedef struct vector {
   double data[MAX_VECTOR_SIZE];
   int n;
} Vector;


/* Function providing a data vector with test data */
Vector test_vector(void);
/* Function to load dat =a from a simple text file */
Vector load_vector(void);
/* Function to print out the data vector */
void print_vector(Vector x);

Vector rand_vector (int n);

void sort_vector(Vector *x);
Vector vector_sort(Vector x);

