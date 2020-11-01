/*-----------------------------------------------------------------------------
Program name : cdist.h
Description  : Header file for the "cdist" library providing several 
               statistical distribution functions
Author       : Jan Hartstra
Repository   : https://github.com/JanHartstra/cstat.git (git@github.com:JanHartstra/cstat.git)
-----------------------------------------------------------------------------*/

double erf (double x);
double normalCDF(double x);
double zinv (double p);
double tinv (double p, int df);
double loggamma (double x);
double beta (double a, double b);
double betacf(double a, double b, double x);
double incbeta (double a, double b, double x);
double At (double t, int df);
double Qt (double t, int df);
double Pt (double t, int df);
double zlib_incbeta(double a, double b, double x);
double student_t_cdf(double t, double v);

