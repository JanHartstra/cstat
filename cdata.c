/*
Program: cdata.c
Purpose: Provide functions for a simple data structure value
Author:  Jan Hartstra
Date:    2020-10-24
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "cdata.h"
#include "clogs.h"

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
   char data_file_name[] = "test.dat";
   FILE *fp;
   // char temp[MAX_DATALINE_LENGTH];
   char dataline[100];

   fp = fopen(data_file_name, "r");

   Vector x;
   int i = 0;
   while (fgets(dataline, 100, fp)!=NULL) {
      // puts(dateline);
      x.data[i] = atof(dataline);
      i++;
   }
   fclose(fp);
   x.n = i;

   char* m;
   int e;
   /*if(0 > asprintf(&m, "%d lines read from %s\n", i, data_file_name)) return error;*/
   e = asprintf(&m, "%d lines read from %s\n", i, data_file_name);
   log_note(m);
   free(m); 

   return x;
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

Vector rand_vector (int n)
{
   Vector x;
   x.n = n;
   int i;
   for (i = 0; i < n; i++)
   {
      x.data[i] = rand() % 100;
   }
   return x;
}

void sort_vector(Vector *x)
{
   int i, j;
   double tmp;
   for (i = 0; i < x.n; i++)
   {
      for (j = 0; j < x.n; j++)
      {
         if (x.data[i] < x.data[j])
         {
            temp = x.data[i];
            x.data[i] = x.data[j];
            x.data[j] = temp;
         }
      }
   }
}

/*
int main()
{
    int a[10], n, i, j, temp;
    float mean, median;

    printf("Enter no. for Random Numbers :");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        a[i] = rand() % 100;
    }
    printf("Random Numbers Generated are :\n");
    for (i = 0; i < n; i++)
    {
        printf("\n%d", a[i]);
    }
    printf("\n");
    printf("\nSorted Data:");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (a[i] < a[j])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        printf("\n%d", a[i]);
    }

    if (n % 2 == 0)
    {
        median = (a[n / 2] + a[(n / 2) - 1]) / 2;
    }
    else
    {
        median = a[n / 2];
    }
    printf("\nMedian is : %f", median);

    return 0;
}
*/
