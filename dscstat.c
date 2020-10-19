/*
Program: dcstat.c
Purpose: Calculate a set of simple destriptive statistics
Author:  Jan Hartstrai
Date:    2020-10-19
*/

#include <stdio.h>

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
   /* Calculate descriptive statistics for the data in data vector */
   /* Print the descriptive statistics to standard out (or file?) */
   return 0;
} 


