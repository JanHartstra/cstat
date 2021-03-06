/*-----------------------------------------------------------------------------
Program name : dscstat.c
Description  : Command line program to calculate and report univariate 
Repository   : https://github.com/JanHartstra/cstat.git (git@github.com:JanHartstra/cstat.git)
Author       : Jan Hartstra
Compile      : Use Makefile
-----------------------------------------------------------------------------*/

#define _GNU_SOURCE // Use asprintf() function?
#include <stdio.h>
#include <stdlib.h>
#include "cdist.h"
#include "cdata.h"
#include "cstat.h"
#include "clogs.h"

int main(int argc, char *argv[])
{
   printf("Program name %s\n", argv[0]);
   
   log_open(argv[0]);

   // log_write("This is a message.\n");
   // log_note("This is a note.\n");
   // log_warning("This is a warning.\n");
   // log_error("This is an error.\n");

   char* m;
   // int e;
   /*if(0 > asprintf(&m, "%d lines read from %s\n", i, data_file_name)) return error;*/
   int e = asprintf(&m, "%s run.\n", argv[0]);
   log_note(m);
   free(m); 

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
   // y = test_vector();
   y = load_vector();
   printf("Data\n");
   printf("----\n");
   print_vector(y);
   printf("\n");
   /* Calculate descriptive statistics for the data in data vector */
   /* Print the descriptive statistics to standard out (or file?) */
   summary(y);
   printf("----\n");
   printf("tinv(0.95,5)    = %9.4f\n", tinv(0.95,5));
   printf("\n");
   printf("Test\n");
   printf("----\n");
   printf("loggamma(5)     = %9.6f\n", loggamma(5));
   printf("R: lgamma(5)    =  3.178054\n");
   printf("beta(2,3)       = %9.6f\n", beta(2,3));
   printf("R: beta(2,3)    =  0.08333333\n");
   printf("erf(2)          = %9.6f\n", erf(2));
   printf("normalCDF(2)    = %9.6f\n", normalCDF(2));
   printf("normalCDF(1.96) = %9.6f\n", normalCDF(1.96));
   printf("R: pnorm(1.96)  =  0.9750021\n");
   printf("zinv(1)         = %9.4f\n", zinv(1));
   printf("zinv(0.95)      = %9.4f\n", zinv(0.95));
   printf("R: qnorm(0.95)  =  1.644854\n");
   printf("zinv(0.975)     = %9.4f\n", zinv(0.975));
   printf("tinv(0.95,8)    = %9.4f\n", tinv(0.95,8));
   printf("----\n");

   Vector z, sz;
   z = rand_vector(10);
   print_vector(z);
   printf("----\n");
   // sort_vector(&z);
   sz = vector_sort(z);
   print_vector(sz);

   log_close();
   return 0;
} 

