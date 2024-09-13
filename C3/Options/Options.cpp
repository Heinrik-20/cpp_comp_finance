#include "Options.h"
#include "BinModel.h"
#include "BinLattice.h"
#include <iostream>
#include <cmath>
using namespace std;

double EurOption::PriceByCRR(
   BinModel Model, 
   BinLattice<double>& PriceTree,
   BinLattice<double>& moneyAccount,
   BinLattice<double>& stockAccount,
)
{
   double q=Model.RiskNeutProb();
   int N=GetN();
   PriceTree.setN(N);
   moneyAccount.setN(N);
   stockAccount.setN(N);

   for (int i=0; i<=N; i++)
   {
      PriceTree.SetNode(N,i,Payoff(Model.S(N,i)));
   }
   for (int n=N-1; n>=0; n--)
   {
      for (int i=0; i<=n; i++)
      {
         
         stockAccount.SetNode(
            n,
            i,
            (PriceTree.GetNode(n, i) - PriceTree.GetNode(n, i+1)) / (Model.S(n, i+1) - Model.S(n, i))
         );

         moneyAccount.SetNode(
            n,
            i,
            (PriceTree.GetNode(n-1, i) - (stockAccount.GetNode(n, i) * Model.S(n-1, i))) / (1 + Model.GetR())
         );

         PriceTree.SetNode(
            n,
            i,
            (q*PriceTree.GetNode(n+1,i+1) +(1-q)*PriceTree.GetNode(n+1,i)) / (1+Model.GetR())
         );
      }
   }
   return Price[0];
}

double AmOption::PriceBySnell(BinModel Model,
   BinLattice<double>& PriceTree,
   BinLattice<bool>& StoppingTree)
{
   double q=Model.RiskNeutProb();
   int N=GetN();
   PriceTree.SetN(N);
   StoppingTree.SetN(N);
   double ContVal;
   for (int i=0; i<=N; i++)
   {
      PriceTree.SetNode(N,i,Payoff(Model.S(N,i)));
      StoppingTree.SetNode(N,i,1);
   }
   for (int n=N-1; n>=0; n--)
   {
      for (int i=0; i<=n; i++)
      {
         ContVal=(q*PriceTree.GetNode(n+1,i+1)
            +(1-q)*PriceTree.GetNode(n+1,i))
            /(1+Model.GetR());
         PriceTree.SetNode(n,i,Payoff(Model.S(n,i)));
         StoppingTree.SetNode(n,i,1);
         if (ContVal>PriceTree.GetNode(n,i))
         {
            PriceTree.SetNode(n,i,ContVal);
            StoppingTree.SetNode(n,i,0);
         }
         else if (PriceTree.GetNode(n,i)==0.0)
         {
            StoppingTree.SetNode(n,i,0);
         }
      }
   }
   return PriceTree.GetNode(0,0);
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
