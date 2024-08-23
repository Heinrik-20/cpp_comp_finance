#include "Options01.h"
#include "BinModel01.h"
#include <iostream>
#include <cmath>
using namespace std;

int GetInputData(int& N, double& K)
{
   cout << "Enter steps to expiry N: "; cin >> N;
   cout << "Enter strike price K:    "; cin >> K;

   // Exercise 1.4
   if (K <= 0) {
      cout << "Invalid Strike Price, must be positive!" << endl;
      return 1;
   }
   
   if (N <= 0) {
      cout << "Invalid N, must be positive!" << endl;
      return 1; 
   }

   cout << endl;
   return 0;
}

double PriceByCRR(double S0, double U, double D,
                  double R, int N, double K)
{
   double q=RiskNeutProb(U,D,R);
   double Price[N+1];
   for (int i=0; i<=N; i++)
   {
      Price[i]=CallPayoff(S(S0,U,D,N,i),K);
   }
   for (int n=N-1; n>=0; n--)
   {
      for (int i=0; i<=n; i++)
      {
         Price[i]=(q*Price[i+1]+(1-q)*Price[i])/(1+R);
      }
   }
   return Price[0];
}

double CallPayoff(double z, double K)
{
   if (z>K) return z-K;
   return 0.0;
}

// Exercise 1,3
double PriceByCRRWhile(
   double S0, 
   double U, 
   double D, 
   double R, 
   int N, 
   double K
) 
{
   double q = RiskNeutProb(U, D, R);
   double Price[N+1];
   int index = 0;
   while (index <= N) {
      Price[index] = CallPayoff(S(S0, U, D, N, index), K);
      index += 1;
   }

   index = N-1;

   while (index >=0) {

      int j = 0;
      while (j <= index) {
         Price[j] = (q * Price[j+1] + (1-q) * Price[j])/(1 + R);
         j += 1;
      }

      index -= 1;
   }

   return Price[0];
}

double PriceByCRRFormula(double S0, double U, double D, double R, int N, double K) {
   double q = RiskNeutProb(U, D, R);
   double price = 0;

   double N_fact = tgamma(N + 1);
   
   for (int i=0;i <= N;i++) {
      price += (N_fact / (tgamma(i + 1) * tgamma(N - i + 1))) * pow(q, i) * pow(1 - q, N - i) * CallPayoff(S(S0, U, D, N, i), K);
   }

   return price / pow(1 + R, N);

}