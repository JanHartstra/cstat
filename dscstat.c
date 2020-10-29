/*
Program: dscstat.c
Purpose: Calculate a set of simple destriptive statistics
Author:  Jan Hartstra
Date:    2020-10-19
Compile: Use Makefile
*/

#include <stdio.h>
#include "cdist.h"
#include "cdata.h"
#include "cstat.h"
#include "clogs.h"

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

   log_open();

   log_write("This is a message.\n");
   log_note("This is a note.\n");
   log_warning("This is a warning.\n");
   log_error("This is an error.\n");

   Vector y;
   // y = test_vector();
   y = load_vector();
   printf("Data\n");
   printf("----\n");
   print_vector(y);
   printf("\n");
   /* Calculate descriptive statistics for the data in data vector */
   /* Print the descriptive statistics to standard out (or file?) */

   printf("Summary Statistics\n");
   printf("------------------\n");
   double s = sum(y);
   printf("Sum             = %9.4f\n", s);
   printf("Minimum         = %9.4f\n", min(y));
   printf("Maximum         = %9.4f\n", max(y));
   printf("Range (max-min) = %9.4f\n", range(y));
   printf("Mean            = %9.4f\n", mean(y));
   printf("Geometric mean  = %9.4f\n", geomean(y));
   printf("Variance (n-1)  = %9.4f\n", var(y,1));
   printf("SD (n-1)        = %9.4f\n", sd(y,1));
   printf("SE              = %9.4f\n", se(y));
   printf("Variance (n)    = %9.4f\n", var(y,0));
   printf("SD (n)          = %9.4f\n", sd(y,0));
   printf("\n");
   printf("Test\n");
   printf("----\n");
   printf("lgamma(5)       = %9.6f\n", lgamma(5));
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

   log_close();
   return 0;
} 

