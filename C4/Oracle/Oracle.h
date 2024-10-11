#ifndef ORACLE_H
#define ORACLE_H

#include <iostream>
#include <vector>

using namespace std;

template<typename Function> double OracleSolveByBisect
   (Function& Fct,
   double Tgt, double LEnd, double REnd, double Acc)
{
   double left=LEnd, right=REnd, mid=(left+right)/2;
   double y_left=Fct.Value(left)-Tgt, y_mid=Fct.Value(mid)-Tgt;
   while (mid-left>Acc)
   {
      if ((y_left>0 && y_mid>0)||(y_left<0 && y_mid<0))
         {left=mid; y_left=y_mid;}
      else right=mid;
      mid=(left+right)/2;
      y_mid=Fct.Value(mid)-Tgt;
   }
   return mid;
}

template<typename Function> double OracleSolveByNR
   (Function& Fct,
   double Tgt, double Guess, double Acc)
{
   double x_prev=Guess;
   double x_next=x_prev
      -(Fct.Value(x_prev)-Tgt)/Fct.Deriv(x_prev);
   while (x_next-x_prev>Acc || x_prev-x_next>Acc)
   {
      x_prev=x_next;
      x_next=x_prev
         -(Fct.Value(x_prev)-Tgt)/Fct.Deriv(x_prev);
   }
   return x_next;
}

class OracleBond
{
   private:
      double F; //face value
      double T; //maturity time
      vector<double> C; //coupons
      vector<double> t; //coupon times
   public:
      OracleBond(double F_, double T_, vector<double>& C_, vector<double>& t_)
         {F=F_; T=T_; C=C_; t=t_;}
      double Value(double y);
      double Deriv(double y);
};

template<typename Fct> class DefIntOracle
{
   private:
      double a,b;
      Fct MyFct;
   public:
      DefIntOracle(double a_, double b_, Fct& MyFct_)
         {a=a_; b=b_; MyFct=MyFct_;}
      double ByTrapezoid(int N);
      double BySimpson(int N);
};

#endif
