/*
Program: dcstat.c
Purpose: Calculate a set of simple destriptive statistics
Author:  Jan Hartstra
Date:    2020-10-19
Compile: gcc -c cdist.c
         gcc -c dscstat.c 
         gcc -o dscstat dscstat.o cdist.o -lm
*/

#include <stdio.h>
#include "cdist.h"

#define MAX_VECTOR_SIZE 100

typedef struct vector {
   double data[MAX_VECTOR_SIZE];
   int n;
} Vector;

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

void print_vector (Vector x)
{
   int i;
   for (i = 0; i < x.n; i++)
   {
      printf("Element %d : %9.3f\n", i, x.data[i]);
   }
}

double sum (Vector x)
{
   int i;
   double S = 0;
   for (i = 0; i < x.n; i++)
   {
      S += x.data[i];
   }
   return S;
}

double mean (Vector x)
{
   return sum(x)/x.n;
}

int main(int argc, char *argv[])
{
   int i;
   if( argc >= 2 )
   {
      printf("The arguments supplied are:\n");
      for(i = 1; i < argc; i++)
      {
         printf("%s\t", argv[i]);
      }
      /* -f <filename> */
      /* read_vector() */
   }
   else
   {
       printf("argument list is empty.\n");
       /* Allow the user to enter data */ 
   }
   Vector y;
   y = test_vector();
   print_vector(y);
   /* Calculate descriptive statistics for the data in data vector */
   double s = sum(y);
   printf("Sum             = %9.4f\n", s);
   printf("Mean            = %9.4f\n", mean(y));
   printf("erf(2)          = %9.6f\n", erf(2));
   printf("normalCDF(2)    = %9.6f\n", normalCDF(2));
   printf("normalCDF(1.96) = %9.6f\n", normalCDF(1.96));
   printf("R: pnorm(1.96)  = 0.9750021\n");
   printf("zinv(1)         = %9.4f\n", zinv(1));
   printf("zinv(0.95)      = %9.4f\n", zinv(0.95));
   printf("R: qnorm(0.95)  = 1.644854\n");
   printf("zinv(0.975)     = %9.4f\n", zinv(0.975));
   printf("tinv(0.95,8)    = %9.4f\n", tinv(0.95,8));
   /* Print the descriptive statistics to standard out (or file?) */
   return 0;
} 


