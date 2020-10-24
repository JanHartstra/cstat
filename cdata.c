/*
Program: cdata.c
Purpose: Provide functions for a simple data structure value
Author:  Jan Hartstra
Date:    2020-10-24
*/

#include <stdio.h>
#include "cdata.h"

/* Define the data vector structure */
/* Should this be in header file? */
/*
#define MAX_VECTOR_SIZE 100
typedef struct vector {
   double data[MAX_VECTOR_SIZE];
   int n;
} Vector;
*/

/* Function providing a data vector with test data */
Vector test_vector(void) 
{
   Vector test;
   test.n = 5;
   test.data[0] = 11;
   test.data[1] = 12;
   test.data[2] = 13;
   test.data[3] = 14;
   test.data[4] = 15;   
   return test;
}

/* Function to load data from a simple text file */
Vector load_vector(void) 
{
   /* TO DO */
   Vector test;
   test.n = 5;
   test.data[0] = 11;
   test.data[1] = 12;
   test.data[2] = 13;
   test.data[3] = 14;
   test.data[4] = 15;   
   return test;
}

/* Function to print out the data vector */
void print_vector(Vector x)
{
   int i;
   for (i = 0; i < x.n; i++)
   {
      printf("Element %d : %9.3f\n", i, x.data[i]);
   }
}

