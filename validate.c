/*-----------------------------------------------------------------------------
Program name : dscstat.c
Description  : Commandline program to check several function in several 
               libraries within the cstat c program collection
Author       : Jan Hartstra
Compile      : 1) Compile the libraries used and/or validated: 
                  $ gcc -o cdist.o cdist.c -lm
                  $ gcc -o glogs.o clogs.c 
               2) Compile the validation program, linking the in the libraries:
                  $ gcc -o validate validate.c cdist.o clogs.o -lm
------------------------------------------------------------------------------*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cdist.h"
// #include "cdata.h"
// #include "cstat.h"
#include "clogs.h"

/* 
Function comparing the test value against a specified reference value
*/
void comparing (double ref_val, double test_val)
{
   double adiff, rdiff, pdiff;
   adiff = fabs(test_val - ref_val);
   rdiff = adiff / ref_val;
   pdiff = rdiff*100;
   /*
   printf("Reference value = %f\n", ref_val);
   printf("Test value      = %f\n", test_val);
   */
   printf("Absolute difference between test and reference value: %f (%f6.2 %%)\n", adiff, pdiff); 
}

double test_Pt (double t, int df) 
{
   double a, b, x;
   a = df / 2; 
   b = 1.0 / 2.0; 
   x = df / (df + pow(t,2)); 
   printf("a = %f\n", a);
   printf("b = %f\n", b);
   printf("x = %f\n", x);
   return 1 - (incbeta(a,b,x) / 2);
} 




int main(int argc, char *argv[])
{
   printf("Program name %s\n", argv[0]);
   
   log_open();

   // log_write("This is a message.\n");
   // log_note("This is a note.\n");
   // log_warning("This is a warning.\n");
   // log_error("This is an error.\n");

   char* m;
   int e;
   /*if(0 > asprintf(&m, "%d lines read from %s\n", i, data_file_name)) return error;*/
   e = asprintf(&m, "%s run.\n", argv[0]);
   log_note(m);
   free(m); 

   if( argc >= 2 )
   {
      printf("Command line arguments ignored.");
   }

   double test;

   printf("Validating cdist libarary\n");
   printf("-------------------------\n\n");

   /*
   printf("R: gamma(2.5) -> 1.32934\n");
   printf("cdist: gamma(2.5) = %9.6f\n", gamma(2.5));
   */

   printf("R: lgamma(5) -> 3.178054\n");
   printf("cdist: loggamma(5) = %9.6f\n", loggamma(5));
   comparing(3.178054, loggamma(5));
   printf("\n");
   
   printf("R: beta(2,3) -> 0.08333333\n");
   printf("cdist: beta(2,3) = %9.6f\n", beta(2,3));
   comparing(0.08333333, beta(2,3));
   printf("\n");
   
   printf("R: pt(2,5) -> 0.94903030\n");
   printf("cdist: Pt(2,5) = %9.6f\n", Pt(2,5));
   comparing(0.94903030, Pt(2,5));
   printf("\n");

   printf("cdist: At(2,5) = %9.6f\n", At(2,5));
   printf("cdist: Qt(2,5) = %9.6f\n", Qt(2,5));
   printf("\n");

   /*
   https://keisan.casio.com/exec/system/1180573396
   a = 2 
   b = 0.5
   x = 0.5
   Bx(a,b) = 0.154822031355...
   Ix(a,b) = 0.116116523516...
   */

   printf("Keisan: Bx(a=2, b=0.5, x=0.5) -> 0.154822031355\n");
   printf("Keisan: Ix(a=2, b=0.5, x=0.5) -> 0.154822031355\n");
   printf("cdist: incbeta(2,0.5,0.5) = %9.6f\n", incbeta(2,0.5,0.5));
   printf("zlib: zlib_incbeta(2,0.5,0.5) = %9.6f\n", zlib_incbeta(2,0.5,0.5));
   // comparing(0.94903030, Pt(2,5));

   printf("R: pt(2,5) -> 0.94903030\n");
   printf("cdist: student_t_cdf(2,5) = %9.6f\n", student_t_cdf(2,5));
   comparing(0.94903030, student_t_cdf(2,5));
   printf("\n");

/*
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
*/
   log_close();
   return 0;
} 

