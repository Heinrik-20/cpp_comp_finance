#ifndef Oracle_H
#define Oracle_H

#include "BinModel.h"

class TrueInt
{
   private:
      double a,b;
      double (*f)(double x);
   public:
      TrueInt(double a_, double b_, double (*f_)(double x))
         {a=a_; b=b_; f=f_;}
      double ByTrapezoid(int N);
      double BySimpson(int N);
};

class EurOptionOracle
{
   private:
      int N; //steps to expiry
   public:
      void SetN(int N_){N=N_;}

      virtual double Payoff(double z)=0;

      //pricing European option
      double PriceByCRR(BinModel Model);
};

class BullSpreadOracle: public EurOptionOracle
{
   private:
      double K1; //parameter 1
      double K2; //parameter 2
   public:
      BullSpreadOracle(double K1_, double K2_) : EurOptionOracle() {K1 = K1_; K2 = K2_;}
      int GetInputData();
      double Payoff(double z);
};

class BearSpreadOracle: public EurOptionOracle
{
   private:
      double K1; //parameter 1
      double K2; //parameter 2
   public:
      BearSpreadOracle(double K1_, double K2_) : EurOptionOracle() {K1 = K1_; K2 = K2_;}
      int GetInputData();
      double Payoff(double z);
};

#endif