/*
Program  : cdist.c
Author   : Jan Hartstra
*/

#include <math.h> 

double zinv (float p)
{
   float c[] = {2.515517, 0.802853, 0.010328};
   float d[] = {1.432788, 0.189269, 0.001308};
   float z, q, t, a, b; 
   p = fabs(p); 
   if ((p<.5) || (p>1.0)) 
   { 
      return -9999; 
   }
   else 
   {
      q = 1-p; 
      t = sqrt(log(1/(q*q)));
      a = c[0]+c[1]*t+c[2]*t*t;
      b = 1+d[1]*t+d[2]*t*t+d[3]*t*t*t;
      return round((t-a/b)*1.0E+3)/1.0E+3;
   } 
}

double tinv (float p, int df)
{
   double g1, g2, g3, g4, tp;
   double x = zinv(p);
   g1 = 1/4*(pow(x,3)+x);
   g2 = 1/96*(5*pow(x,5)+16*pow(x,3)+3*x); 
   g3 = 1/384*(3*pow(x,7)+19*pow(x,5)+17*pow(x,3)-15*x);
   g4 = 1/92160*(79*pow(x,9)+776*pow(x,7)+1482*pow(x,5)-1920*pow(x,3)-945*x); 
   tp = x+g1/df+g2/pow(df,2)+g3/pow(df,3)+g4/(df,4); 
   return tp;
}

/*
My Lua implementation
---------------------

function zINV (p) 
   --Inverse standard normal distribution alternative 
   --HH Schutte, Basic-programma's voor wetenschap en techniek, Kluwer, 1983, p24 
   --Abramowitz & Stegun, p.933, 26.2.23 
   --|eta(p)|<4.5*10^-4 
   local c={[0]=2.515517, 
            [1]=0.802853, 
            [2]=0.010328} 
   local d={[1]=1.432788, 
            [2]=0.189269, 
            [3]=0.001308} 
   local z, q, t, a, b 
   p=math.abs(p) 
   if (p<.5) or (p>1.0) then 
      return 0/0 -- -1#IND? 
   else 
      q=1-p 
      t=math.sqrt(math.log(1/(q*q))) 
      a=c[0]+c[1]*t+c[2]*t*t 
      b=1+d[1]*t+d[2]*t*t+d[3]*t*t*t 
      return round(t-a/b,.001) 
   end 
end 
--SAS: 
--probit(0.975)=1.95996 
--probit(0.95) =1.64485 


function tINV(p,df) 
   --Inverse t-distribution, returns quantiles of Student's t-distrution 
   --Source: Abramowitz and Stegun, HANDBOOK OF MATHEMATICAL FUCTIONS, p 949 
   local g1, g2, g3, g4, tp 
   x=zINV(p) 
   g1=1/4*(x^3+x) 
   g2=1/96*(5*x^5+16*x^3+3*x) 
   g3=1/384*(3*x^7+19*x^5+17*x^3-15*x) 
   g4=1/92160*(79*x^9+776*x^7+1482*x^5-1920*x^3-945*x) 
   tp=x+g1/df+g2/df^2+g3/df^3+g4/df^4 
   return tp 
end 
--print(tinv(0.95,2))=   2.9122920527631 
--SAS x=tinv(.95,2) -->  2.9199855804 
--print(tinv(0.95,2))=   1.8597378873181 
--SAS x=tinv(.95,8) -->  1.85955 
*/
