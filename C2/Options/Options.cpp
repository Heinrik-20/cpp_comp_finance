#include "Options.h"
#include "BinModel.h"
#include <iostream>
#include <cmath>
using namespace std;

double EurOption::PriceByCRR(BinModel Model)
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

int Call::GetInputData()
{
   cout << "Enter call option data:" << endl;
   int N;
   cout << "Enter steps to expiry N: "; cin >> N;
   SetN(N);
   cout << "Enter strike price K:    "; cin >> K;
   cout << endl;
   return 0;
}

double Call::Payoff(double z)
{
   if (z>K) return z-K;
   return 0.0;
}

int Put::GetInputData()
{
   cout << "Enter put option data:" << endl;
   int N;
   cout << "Enter steps to expiry N: "; cin >> N;
   SetN(N);
   cout << "Enter strike price K:    "; cin >> K;
   cout << endl;
   return 0;
}

double Put::Payoff(double z)
{
   if (z<K) return K-z;
   return 0.0;
}

double BullSpread::Payoff(double z)
{
   if (z<=K1) return 0;
   if (z<K2) return z - K1;
   return K2 - K1;
}

double BearSpread::Payoff(double z)
{
   if (z<=K1) return K2 - K1;
   if (z<K2) return K2 - z;
   return 0.0;
}

double Strangle::Payoff(double z)
{
   if (z<=K1) return K1 - z;
   if (z<=K2) return 0;
   return z - K2;
}

double Butterfly::Payoff(double z)
{
   double intermediate = (K1 + K2)/2;
   
   if ((z > K1) && z <= intermediate) return z - K1;
   if ((z > intermediate) && z <= K2) return K2 - z;
   return 0;

}
