/*
Program  : cdist.c
Author   : Jan Hartstra
*/

#include <stdio.h>
#include <math.h> 

double erf (double x)
{
   /*
   """
   error function approximation
   Ambramowitz and Stegun, 7.1.28, p. 299
   """
   */
   double a[] = {1, 0.0705230784, 0.0422820123, 0.0092705272, 0.0001520143, 0.0002765672, 0.0000430638};
   double S = 0;
   double t;
   for (int i = 0; i <= 6; i++)
   {
      t = a[i] * pow(x,i);
      S += t;
   }
   return 1-1/pow(S,16);
}
   
/* Standard normal cumulative distribution function */
/* R function qnorm(p) */
double normalCDF (double x)
{
   return (1+erf(x/sqrt(2)))/2;
}

/* Inverse normal distribution */
/* R function qnorm(p) */
double zinv (double p)
{
   float c[] = {2.515517, 0.802853, 0.010328};
   float d[] = {1.432788, 0.189269, 0.001308};
   float q, t, a, b; 
   p = fabs(p); 
   if (p < 0.5 || p > 1.0)
   { 
      return -9999; 
   }
   else 
   {
      q = 1-p; 
      t = sqrt(log(1/(q*q)));
      a = c[0]+c[1]*t+c[2]*t*t;
      b = 1+d[0]*t+d[1]*t*t+d[2]*t*t*t;
      /*return round((t-a/b)*1.0E+3)/1.0E+3;*/
      return (t-a/b);
   } 
}

/* Inverse Students t distributions */
/* R function qt(p,df) */
double tinv (double p, int df)
{
   double g1, g2, g3, g4, tp;
   double x = zinv(p);
   g1 = 1/4*(pow(x,3)+x);
   g2 = 1/96*(5*pow(x,5)+16*pow(x,3)+3*x); 
   g3 = 1/384*(3*pow(x,7)+19*pow(x,5)+17*pow(x,3)-15*x);
   g4 = 1/92160*(79*pow(x,9)+776*pow(x,7)+1482*pow(x,5)-1920*pow(x,3)-945*x); 
   tp = x+g1/df+g2/pow(df,2)+g3/pow(df,3)+g4/pow(df,4); 
   return tp;
}

/* Log gamma function  */
/* Returns the value ln[Gamma(x)] for x > 0. */
/* See Numerical recipes in C, Section 6.1, page 214. */
double lgamma(double x)
{
   int j;
   double z, y, tmp, ser;
   static double cof[6] = {76.18009172947146, 
                          -86.50532032941677, 
                           24.01409824083091, 
                           -1.231739572450155, 
                            0.1208650973866179e-2, 
                           -0.5395239384953e-5
                           };
   z = y = x;                        
   tmp = z + 5.5; 
   tmp -= (z+0.5)*log(tmp);
   ser = 1.000000000190015;
   for (j=0; j<=5; j++) ser += cof[j]/++y;
   return -tmp+log(2.5066282746310005*ser/z); 
}

/* Beta function */
/* See: Numerical recipes in C, Section 6.1, page 216. */
/* Uses: lgamma() */
double beta(double a, double b)
{
   return exp(lgamma(a)+lgamma(b)-lgamma(a+b));
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

def erf (x):
   """
   error function approximation
   Ambramowitz and Stegun, 7.1.28, p. 299
   """
   a=[1, 
   0.0705230784,
   0.0422820123,
   0.0092705272,
   0.0001520143,
   0.0002765672,
   0.0000430638
   ]
   s=0
   for i in range(len(a)):
      print('i=', i)
      print('x^i= ', x**i)
      print('a[i]=', a[i])
      t=a[i]*x**i
      print('a[i]*x**i= ', t)
      s=s+t
      print('s= ', s)
   return 1-1/s**16

*/

/*

------------------------------------------------------------------------------

function gammln(x) 
   -- Log Gamma function 
   --Returns the value ln[Gamma(x)] for x > 0. 
   --Adapted from numerical recipes in C, Section 6.1, page 214. 
   --Used by 
   local cof={ [1]=76.18009172947146, 
               [2]=-86.50532032941677, 
               [3]=24.01409824083091, 
               [4]=-1.231739572450155, 
               [5]=0.1208650973866179e-2, 
               [6]=-0.5395239384953e-5} 

   local y, z =x, x 
   local tmp=z+5.5 
   tmp = tmp - (z+0.5)*math.log(tmp) 
   local ser=1.000000000190015 
   for j,c in ipairs(cof) do 
      y=y+1 
      ser=ser+c/y 
   end 
   return -tmp+math.log(2.5066282746310005*ser/z); 
end 

function factfl(n) 
   --Faculty function for floating point numbers. 
   --Returns the value n! as floating point number. 
   --Adapted from numerical recipes in C, Section 6.1, page 214. 
   --Uses  : gammln 
   if n<0 then 
      error('n<0') 
   else 
      return math.exp(gammln(n+1.0)) 
   end 
end 
--print(factfl(5))=120 = 1*2*3*4*5 

function beta(z, w) 
   -- Beta function 
   --Returns the value of the beta function B(z;w). 
   --Adapted from numerical recipes in C, Section 6.1, page 216. 
   --Uses  : gammln 
   return math.exp(gammln(z)+gammln(w)-gammln(z+w)) 
end 

function betacf(a, b, x) 
   --Beta continued fraction evaluation function 
   --Used by: <betai> 
   --Evaluates continued fraction for incomplete beta function by modifid Lentz's method (x5.2). 

   --Define "constants" 
   local MAXIT=100 
   local EPS=3.0e-7 
   local FPMIN=1.0e-30 --Use lua -math.huge? 
   local m, m2                             -- integers 
   local qab, qap, qam, aa, c, d, del, h   -- floats 
   qab=a+b    --These q's will be used in factors that occur 
   qap=a+1.0  --in the coeffients (6.4.6). 
   qam=a-1.0 
   c  =1.0      --First step of Lentz's method. 
   d  =1.0-qab*x/qap 
   if math.abs(d)<FPMIN then d=FPMIN end 
   d  =1.0/d 
   h  =d 
   m=1 
   while m<MAXIT do 
      m2 = 2*m 
      aa = m*(b-m)*x/((qam+m2)*(a+m2)) 
      d  =1.0+aa*d                --One step (the even one) of the recurrence. 
      if math.abs(d)< FPMIN then d=FPMIN end 
      c  = 1.0+aa/c 
      if math.abs(c)< FPMIN then c=FPMIN end 
      d  = 1.0/d 
      h  = h*(d*c) 
      aa = -(a+m)*(qab+m)*x/((a+m2)*(qap+m2)); 
      d  = 1.0+aa*d                --Next step of the recurrence (the odd one). 
      if math.abs(d)<FPMIN then d=FPMIN end 
      c  = 1.0+aa/c 
      if math.abs(c)<FPMIN then c=FPMIN end 
      d  = 1.0/d 
      del=d*c 
      h  =h*del 
      if math.abs(del-1.0)<EPS then break end --Are we done? 
      m=m+1 
   end 
   if m>MAXIT then 
      error("a or b too big, or MAXIT too small in betacf") 
   else 
      return h 
   end 
end 

function betai (a, b, x) 
   --Returns the incomplete beta function Ix(a; b). 
   --Uses  : <betacf> and <gammln> functions 
   local bt --float 
   if (x<0.0) or (x>1.0) then 
      error("Bad x in routine betai") 
   elseif (x==0.0) or (x==1.0) then 
      bt=0.0 
   else --Factors in front of the continued fraction. 
      bt=math.exp(gammln(a+b)-gammln(a)-gammln(b)+a*math.log(x)+b*math.log(1.0-x)) 
   end 
   if (x<(a+1.0)/(a+b+2.0)) then 
      --Use continued fraction directly. 
      return bt*betacf(a,b,x)/a; 
   else 
      --Use continued fraction after making the symmetry transformation. 
      return 1.0-bt*betacf(b,a,1.0-x)/b 
   end 
end 

function gser(a, x) 
   --Returns the incomplete gamma function P(a; x) evaluated by its series representation as gamser. 
   --Source: Numerical Recipes in C, 
   --Used by: <gammp> and <gammq> 

   local ITMAX=100          -- pseudo constant 
   local EPS=3.0e-7 
   local n                 -- int 
   local sum, del, ap, gln  -- float 

   gln=gammln(a) 
   if (x<=0.0) then 
      if (x<0.0) then 
         error("x less than 0 in routine gser") 
         return 0 
      else 
         ap =a 
         sum=1.0/a 
         del=sum 
         for n=1,ITMAX,1 do 
            ap=ap+1; 
            del=del*x/ap; 
            sum=sum+del; 
            if (math.abs(del)<math.abs(sum)*EPS) then 
               return sum*exp(-x+a*math.log(x)-(gln)) 
            end 
         end 
         error("a too large, ITMAX too small in routine gser") 
      end 
   end 
end 

function gcf(a, x) 
   --Returns the incomplete gamma function Q(a; x) evaluated by its continued fraction representation as gammcf. 
   --Source : Numerical Recipes in C 
   --Used by: <gammp> and <gammq> 
   --Uses   : - 
   -- Pseudo constants 
   local ITMAX=100            --Maximum allowed number of iterations. 
   local EPS=3.0e-7           --Relative accuracy. 
   local FPMIN=1.0e-30        --Number near the smallest representable floating-point number. 

   local i                    --int 
   local an, b, c, d, del, h  --float 
   local gln                  --was pointer to float 

   gln=gammln(a); 
   --Set up for evaluating continued fraction by the modified Lentz's method with b_0 = 0. 
   b=x+1.0-a 
   c=1.0/FPMIN 
   d=1.0/b 
   h=d 
   i=0 
   repeat --Iterate to convergence. 
      i=i+1 
      an = -i*(i-a) 
      b  =b+ 2.0 
      d=an*d+b; 
      if math.abs(d)<FPMIN then d=FPMIN end 
      c=b+an/c; 
      if math.fabs(c)<FPMIN then c=FPMIN end 
      d=1.0/d 
      del=d*c 
      h  =h* del 
   until (math.abs(del-1.0)<EPS) or (i>ITMAX) 
   if (i>ITMAX) then 
      error("a too large, ITMAX too small in gcf") 
   else 
      return math.exp(-x+a*math.log(x)-(gln))*h     -- Put factors in front. 
   end 
end 

function gammp(a, x) 
   --Returns the incomplete gamma function P(a; x). 
   --Source : Numerical Recipes in C 
   --Uses   : <gser> and <gcf> 
   --Used by: <PX2> (Chi-square) 

   local gamser, gammcf, gln    -- float 
   if (x<0.0) or (a<=0.0) then 
      error("Invalid arguments in routine gammp") 
   elseif (x<(a+1.0)) then 
      return gser(a,x);         --Use the series representation. 
   else 
      return 1.0-gcf(a,x)       --Use the continued fraction representation and take its complement. 
   end 
end 

function gammq(a, x) 
   --Returns the incomplete gamma function Q(a; x)  1 - P(a; x). 
   --Source : Numerical Recipes in C 

   local gamser,gammcf,gln       --float 
   if (x<0.0) or (a<=0.0) then 
      rerror("Invalid arguments in routine gammq") 
   elseif (x<(a+1.0)) then 
      return 1.0-gser(a,x)       --Use the series representationand take its complement. 
   else 
      return gcf(a,x)            --Use the continued fraction representation. 
   end 
end 

function erf(x) 
   --Error function 
   --Source: adapted from klib.lua) 
   --LaTeX equation: \[ erf(x) = \frac{2}{\sqrt{\pi}} \int_0^x \varepsilon ^{-z^2} dz \] 
   --Used by: <probnorm> 
   local a={[0]=.03526249659989109, 
            [1]=.7003830644436881, 
            [2]=6.37396220353165, 
            [3]=33.912866078383, 
            [4]=112.0792914978709, 
            [5]=221.2135961699311, 
            [6]=220.2068679123761 
           } 
   local b={[0]=.08838834764831844, 
            [1]=1.755667163182642, 
            [2]=16.06417757920695, 
            [3]=86.78073220294608, 
            [4]=296.5642487796737, 
            [5]=637.3336333788311, 
            [6]=793.8265125199484, 
            [7]=440.4137358247522 
           } 
   local c, z, expntl, p 
   c=2.506628274631001 
   z = math.abs(x)*math.sqrt(2) 
   if z > 37 then return (x > 0 and 0) or 2 end 
   expntl = math.exp(-0.5*z*z) 
   if z<10./math.sqrt(2) then -- for small z 
      p=expntl*((((((a[0]*z+a[1])*z+a[2])*z+a[3])*z+a[4])*z+a[5])*z+a[6]) 
      /(((((((b[0]*z+b[1])*z+b[2])*z+b[3])*z+b[4])*z+b[5])*z+b[6])*z+ b[7]) 
   else 
      p=expntl/c/(z+1./(z+ 2./(z+ 3./(z+4./(z+.65))))) 
   end 
   --return (x>0 and 2*p) or 2*(1-p) 
   --Adapt to SAS definition? 
   return (x>0 and 1-(2*p)) or (1-(2*p))*-1 
end 
-- SAS: 
-- erf(1.0)       = 0.8427007929 
-- erf(-1.0)      = -0.842700793 
-- print(erf(1))  = 0.84270079294971 
-- print(erf(-1)) = -0.84270079294971 

------------------------------------------------------------------------------- 
-- Statistical Distribution Functions 
------------------------------------------------------------------------------- 

function normalPDF (x,mu,sigma) 
   --Returns the value for the normal distubtion function 
   --R equivalent: dnorm(x,mean=,sd=) 
   --Used by: <zPDF> 
   return 1/math.sqrt(2*math.pi*sigma^2)*math.exp(-1*(x-mu)^2/(2*sigma^2)) 
end 

function zPDF (x) 
   --Standard normal distribution function 
   --R equivalent: dnorm(x) 
   --Uses   : normalPDF 
   return normalPDF(x,0,1) 
end 

function zCDF (x) 
   --Standard normal cummulative distribution function (CDF) 
   --R: pnorm(x) 
   --HASTINGS.  MAX ERROR = .000001 
   local t=1/(1+.2316419*math.abs(x)); 
   local d=.3989423*math.exp(-x*x/2); 
   local Prob=d*t*(.3193815+t*(-.3565638+t*(1.781478+t*(-1.821256+t*1.330274)))); 
   if (x>0) then 
      Prob=1-Prob 
   end 
   return round(Prob, .000001) 
end 

function normalCDF (x,mu,sigma) 
   --Normal CDF 
   --R: pnorm(x,mean=,sd=) 
   --Uses   : <zCDF> 
   z=(x-mu)/sigma 
   return zCDF(z) 
end 

function probnorm(x) 
   --Standard normal CDF - 
   --Uses  : <erf> 
   --probnorm(x) - p=.5+.5*erf(x/sqrt(2)); 
   return .5+.5*erf(x/math.sqrt(2)) 
end 
--SAS: probnorm(1.96)   =0.9750021049 
--print(probnorm(1.96)) =0.97500210485178 

--Alternative, See J.M. Buhrman, Statisitsche formules en tabellen, 
--Wolters-Noordhoff, Groningen, 1993, p72-73 
--Accuracy: |eta(z)|<7.5E-8 
--assumption Z>0? 
function zCDFa (z) 
   local a={0.319381530, 
            0.356563782, 
            1.781477937, 
            1.821255978, 
            1.330274429} 
   local p, t, Prob 
   p=0.2316419 
   t=1/(1+p*z) 
   Prob=t*(a[1]-t*(a[2]-t*(a[3]-t*(a[4]-t*a[5]))))/math.sqrt(2*math.pi*math.exp(z*z)) 
   return round(Prob, .0000001) 
end 

--Inverse standard normal distribution 
--See J.M. Buhrman, Statisitsche formules en tabellen, 
--Wolters-Noordhoff, Groningen, 1993, p74-75 
--Accuracy: |eta(p)|<0.00045 
--assumption Z>0? 
--INCORRECT!? 
--[[ 
function zINV (p) 
   local a={[0]=2.515517, 
            [1]=0.802853, 
            [2]=0.010328} 
   local b={[1]=1.432788, 
            [2]=0.189269, 
            [3]=0.001308} 
   local t=math.sqrt(-2*math.log(p)) 
   local aa=a[0]*t*(a[1]+t*a[2]) 
   local bb=1+t*(b[1]+t*(b[2]+t*b[3])) 
   local z=t-aa/bb; 
   return round(z, .001) 
end 
]]-- 

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

---------------------------------------------------------------- 
-- Chi-square distribution 
---------------------------------------------------------------- 

function PX2 (X2, df) 
   --Chi-square (right side tail) 
   --Source: Numerical Recipes in C, p 221 
   --Uses   : <gammq> 
   --Used by: 
   gammp (df/2,X2/2) 
end 

function QX2 (X2, df) 
   --Chi-square (left side tail) 
   --Source : Numerical Recipes in C, p 221 
   --Uses   : <gammq> 
   --Used by: 
   gammq (df/2,X2/2) 
end 

---------------------------------------------------------------- 
-- Student's T distribution 
---------------------------------------------------------------- 

function At(t,df) 
   --Student t-distribution: 2-sided tails 
   --Source : Numerical recipes in C 
   --Uses   : <betai> (incompleta Beta funtion) 
   local a, b, x 
   a=df/2 
   b=1/2 
   x=df/(df+t^2) 
   return 1-betai(a,b,x) 
end 
--print(At(3,8)) 
--R: 1-2*(1-pt(3,8))=0.9829283 

function Qt(t,df) 
   --Student t-distribution: Left side tail 
   --Uses   : <betai> (incompleta Beta funtion) 
   local a, b, x 
   a=df/2 
   b=1/2 
   x=df/(df+t^2) 
   return betai(a,b,x)/2 
end; 

function Pt(t,df) 
   ----Student t-distribution: Right side tail 
   --Uses   : <betai> (incompleta Beta funtion) 
   local a, b, x 
   a=df/2 
   b=1/2 
   x=df/(df+t^2) 
   return 1-(betai(a,b,x)/2) 
end; 
--print(Pt(3,8)) 
--R: pt(3,8)=0.9914642 

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

--------------------------------------------------------------- 
-- Fisher's F distribution 
---------------------------------------------------------------- 

function QF(f,df1,df2) 
   --Fisher's F-distribution: Left side tail 
   --Uses   : <betai> (incompleta Beta funtion) 
   local a, b, x 
   a=df2/2 
   b=df1/2 
   x=df2/(df2+df1*f) 
   return betai(a,b,x) 
end; 

function PF(f,df1,df2) 
   --Fisher's F-distribution: Right side tail 
   --Uses   : <betai> (incompleta Beta funtion) 
   local a, b, x 

   a=df2/2 
   b=df1/2 
   x=df2/(df2+df1*f) 
   return 1-betai(a,b,x) 
end; 
--print(PF(7,8,9)) 
--R: pf(7,8,9)=0.9957318 


*/
