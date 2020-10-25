/*
Program: cstat.c
Purpose: Calculate a set of simple destriptive statistics
Author:  Jan Hartstra
Date:    2020-10-24
*/

#include <stdio.h>
#include <float.h>
#include <math.h>
#include "cdata.h"
// #include "cdist.h"}

/* Function returning the minumum of the elements of the data vector x. */
double min (Vector x)
{
   int i;
   double m = DBL_MAX;
   for (i = 0; i < x.n; i++)
   {
      if (x.data[i] < m) m = x.data[i];
   }
   return m;
}

/* Function returning the miximum of the elements of the data vector x. */
double max (Vector x)
{
   int i;
   double m = DBL_MIN;
   for (i = 0; i < x.n; i++)
   {
      if (x.data[i] > m) m = x.data[i];
   }
   return m;
}

/* Function returning the sum of the elements of the data vector x. */
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

/* Function returning the sum of the squared elements of the data vector x. */
double sum2 (Vector x)
{
   int i;
   double S = 0;
   for (i = 0; i < x.n; i++)
   {
      S += pow(x.data[i],2);
   }
   return S;
}

/* Function returning the arithmetic mean of the data vector x. 
   Depends on the sum() and sum2() functions.
*/
double mean (Vector x)
{
   return sum(x)/x.n;
}

/* Function returning the variance of the data vector x. 
   Parameter d is loss in degrees of freedom:
      0 for population variance
      1 for sample variance
   Depends on the sum() and sum2() functions.
*/
double var (Vector x, int d)
{
   return (sum2(x)-pow(sum(x),2)/x.n)/(x.n-d);
}

/* Function returning the standard deviation of the data vector x. 
   Parameter d is loss in degrees of freedom:
     0 for population standard deviation
     1 for sample standard deviation
   Depends on the var() function.
*/
double sd (Vector x, int d)
{
   return sqrt(var(x,d));
}

/* Function returning the standard error of the data vector x. 
   Depends on the sd() function.
*/
double se (Vector x)
{
   return sd(x,1)/sqrt(x.n);
}
