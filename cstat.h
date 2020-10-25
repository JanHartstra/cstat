/*
Program: cstat.h
Purpose: Calculate a set of simple destriptive statistics
Author:  Jan Hartstra
Date:    2020-10-24
*/

/* Function returning the minumum of the elements of the data vector x. */
double min (Vector x);

/* Function returning the miximum of the elements of the data vector x. */
double max (Vector x);

/* Function returning the sum of the elements of the data vector x. */
double sum (Vector x);

/* Function returning the sum of the squared elements of the data vector x. */
double sum2 (Vector x);

/* Function returning the arithmetic mean of the data vector x. */
double mean (Vector x);

/* Function returning the variance of the data vector x. 
   Parameter d is loss in degrees of freedom:
      0 for population variance
      1 for sample variance
   Depends on the sum() and sum2() functions.
*/
double var (Vector x, int d);

/* Function returning the standard deviation of the data vector x. 
   Parameter d is loss in degrees of freedom:
     0 for population standard deviation
     1 for sample standard deviation
   Depends on the var() function 
*/
double sd (Vector x, int d);

/* Function returning the standard error of the data vector x. 
   Depends on the sd() function.
*/
double se (Vector x);

