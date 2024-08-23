#ifndef Options06_h
#define Options06_h

#include "BinModel.h"

class EurOption
{
   private:
      int N; //steps to expiry
   public:
      void SetN(int N_){N=N_;}
      //Payoff defined to return 0.0
      //for pedagogical purposes.
      //To use a pure virtual function replace by
      //virtual double Payoff(double z)=0;
      virtual double Payoff(double z){return 0.0;}
      //pricing European option
      double PriceByCRR(BinModel Model);
};

class Call: public EurOption
{
   private:
      double K; //strike price
   public:
      void SetK(double K_){K=K_;}
      int GetInputData();
      double Payoff(double z);
};

class Put: public EurOption
{
   private:
      double K; //strike price
   public:
      void SetK(double K_){K=K_;}
      int GetInputData();
      double Payoff(double z);
};

class BullSpread : public EurOption {
   private: 
      double K1;
      double K2;

   public:
      BullSpread(double K1_, double K2_) : EurOption() {K1 = K1_; K2 = K2_;}
      void SetK(double K1_, double K2_){K1=K1_; K2=K2_;}
      double Payoff(double z);
};

class BearSpread : public EurOption {
   private: 
      double K1;
      double K2;

   public:
      BearSpread(double K1_, double K2_) : EurOption() {K1 = K1_; K2 = K2_;}
      void SetK(double K1_, double K2_){K1=K1_; K2=K2_;}
      double Payoff(double z);
};

#endif
