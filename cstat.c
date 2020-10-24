/*
Program: cstat.c
Purpose: Calculate a set of simple destriptive statistics
Author:  Jan Hartstra
Date:    2020-10-24
*/

#include <stdio.h>
#include <math.h>
#include "cdata.h"
// #include "cdist.h"}

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

double SS (Vector x)
{
   int i;
   double S = 0;
   for (i = 0; i < x.n; i++)
   {
      S += pow(x.data[i],2);
   }
   return S;
}

double mean (Vector x)
{
   return sum(x)/x.n;
}

double sd (Vector x)
{
   return 0;
}
