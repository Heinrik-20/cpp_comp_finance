#include <iostream>
#include <cmath>
#include "Oracle.h"
#include "Functions.h"

using namespace std;

double OracleBond::Value(double y) {
    double P=0;
    for (unsigned int n=0; n<C.size(); n++)
    P+=C[n]*exp(-y*t[n]);
    P+=F*exp(-y*T);
    return P;
}

double OracleBond::Deriv(double y){
    double D=0;
    for (unsigned int n=0; n<C.size(); n++)
    D+=-C[n]*t[n]*exp(-y*t[n]);
    D+=-F*T*exp(-y*T);
    return D;
}

template<typename Fct>
double DefIntOracle<Fct>::ByTrapezoid(int N)
{
   double h=(b-a)/N;
   double Result=0.5*MyFct.f(a);
   for (int n=1; n<N; n++) Result+=MyFct.f(a+n*h);
   Result+=0.5*MyFct.f(b);
   return Result*h;
}

template<typename Fct>
double DefIntOracle<Fct>::BySimpson(int N)
{
   double h=(b-a)/N;
   double Result=MyFct.f(a);
   for (int n=1; n<N; n++)
      Result+=4*MyFct.f(a+n*h-0.5*h)+2*MyFct.f(a+n*h);
   Result+=4*MyFct.f(b-0.5*h)+MyFct.f(b);
   return Result*h/6;
}

template class DefIntOracle<Funct>;