#include <iostream>
#include <cmath>
#include "Oracle.h"
#include "BinModel.h"

using namespace std;

double TrueInt::ByTrapezoid(int N)
{
   double h=(b-a)/N;
   double Result=0.5*f(a);
   for (int n=1; n<N; n++) Result+=f(a+n*h);
   Result+=0.5*f(b);
   return Result*h;
}

double TrueInt::BySimpson(int N)
{
   double h=(b-a)/N;
   double Result=f(a);
   for (int n=1; n<N; n++) Result+=4*f(a+n*h-0.5*h)+2*f(a+n*h);
   Result+=4*f(b-0.5*h)+f(b);
   return Result*h/6;
}

double EurOptionOracle::PriceByCRR(BinModel Model)
{
   double q=Model.RiskNeutProb();
   double Price[N+1];
   for (int i=0; i<=N; i++)
   {
      Price[i]=Payoff(Model.S(N,i));
   }
   for (int n=N-1; n>=0; n--)
   {
      for (int i=0; i<=n; i++)
      {
         Price[i]=(q*Price[i+1]+(1-q)*Price[i])
            /(1+Model.GetR());
      }
   }
   return Price[0];
}

int BullSpreadOracle::GetInputData()
{
   cout << "Enter European bull spread data:" << endl;
   int N;
   cout << "Enter steps to expiry N: "; cin >> N; SetN(N);
   cout << "Enter parameter K1:      "; cin >> K1;
   cout << "Enter parameter K2:      "; cin >> K2;
   cout << endl;
   return 0;
}

double BullSpreadOracle::Payoff(double z)
{
   if (K2<=z) return K2-K1;
   else if (K1<z) return z-K1;
   return 0.0;
}

int BearSpreadOracle::GetInputData()
{
   cout << "Enter European bear spread data:" << endl;
   int N;
   cout << "Enter steps to expiry N: "; cin >> N; SetN(N);
   cout << "Enter parameter K1:      "; cin >> K1;
   cout << "Enter parameter K2:      "; cin >> K2;
   cout << endl;
   return 0;
}

double BearSpreadOracle::Payoff(double z)
{
   if (K2<=z) return 0.0;
   else if (K1<z) return K2-z;
   return K2-K1;
}

double StrangleOpt::Payoff(double z)
{
   if (z<=K1) return K1-z;
   else if (K2<z) return z-K2;
   return 0.0;
}

double ButterflyOpt::Payoff(double z)
{
   if (K1<z && z<=(K1+K2)/2) return z-K1;
   else if ((K1+K2)/2<z && z<=K2) return K2-z;
   return 0.0;
}