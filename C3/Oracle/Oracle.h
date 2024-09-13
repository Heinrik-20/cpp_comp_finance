#ifndef Oracle_h
#define Oracle_h

#include "BinLattice.h"
#include "BinModel.h"

class OracleOption
{
   private:
      int N; //steps to expiry

   public:
      void SetN(int N_){N=N_;}
      int GetN(){return N;}
      virtual double Payoff(double z)=0;
};

class OracleEurOption: public virtual OracleOption
{
   public:
      //pricing European option
      double PriceByCRR(BinModel Model,
         BinLattice<double>& PriceTree,
         BinLattice<double>& XTree,
         BinLattice<double>& YTree);
};

class OracleAmOption: public virtual OracleOption
{
   public:
      //pricing American option
      double PriceBySnell(BinModel Model,
         BinLattice<double>& PriceTree,
         BinLattice<bool>& StoppingTree);
};

class OracleCall: public OracleEurOption, public OracleAmOption
{
   private:
      double K; //strike price

   public:
      void SetK(double K_){K=K_;}
      int GetInputData();
      double Payoff(double z);
};

class OraclePut: public OracleEurOption, public OracleAmOption
{
   private:
      double K; //strike price

   public:
      void SetK(double K_){K=K_;}
      int GetInputData();
      double Payoff(double z);
};

class OracleBSModel
{
   private:
      double S0, r, sigma;
   public:
      OracleBSModel(double S0_, double r_, double sigma_)
         {S0 = S0_; r = r_; sigma = sigma_;}
      BinModel ApproxBinModel(double h)
      {
         double U=exp((r-sigma*sigma/2)*h+sigma*sqrt(h))-1;
         double D=exp((r-sigma*sigma/2)*h-sigma*sqrt(h))-1;
         double R=exp(r*h)-1;
         BinModel ApproxModel(S0,U,D,R);
         return ApproxModel;
      }
};

#endif
