#include <gtest/gtest.h>
#include <cmath>
#include "BinModel.h"
#include "Options.h"
#include "DefInt.h"
#include "Oracle.h"

using namespace std;

double f(double x){return x*x*x-x*x+1;}
double f2(double x) { return pow(x, 2); }

// Exercise 2.1
TEST(C2Tests, IntegralTests) {

    double a = 1.0;
    double b = 2.0;
    int N = 100;
    DefInt MyInt(a, b, f);
    double trapeziodal = MyInt.ByTrapeziod(N);
    double simpson = MyInt.BySimpson(N);

    TrueInt Oracle(a, b, f);
    double trueTrapezoid = Oracle.ByTrapezoid(N);
    double trueSimpson = Oracle.BySimpson(N);

    EXPECT_DOUBLE_EQ(trueTrapezoid, trapeziodal);
    EXPECT_DOUBLE_EQ(trueSimpson, simpson);

}

//Exercise 2.2
TEST(C2Tests, SpreadsTest) {

    double K1=50, K2=200;
    double S0 = 100, U = 0.3, D = 0.1, R = 0.15;

    BinModel Model(S0, U, D, R);

    BullSpreadOracle trueBull(K1, K2);
    BearSpreadOracle trueBear(K1, K2);

    BullSpread MyBull(K1, K2);
    BearSpread MyBear(K1, K2);

    double trueBullPrice = trueBull.Payoff(S0);
    double MyBullPrice = MyBull.Payoff(S0);

    double trueBearPrice = trueBear.Payoff(S0);
    double MyBearPrice = MyBear.Payoff(S0);

    EXPECT_DOUBLE_EQ(trueBullPrice, MyBullPrice);
    EXPECT_DOUBLE_EQ(trueBearPrice, MyBearPrice);

    double trueBullCRR = trueBull.PriceByCRR(Model);
    double trueBearCRR = trueBear.PriceByCRR(Model);
    double MyBullCRR = MyBull.PriceByCRR(Model);
    double MyBearCRR = MyBear.PriceByCRR(Model);

    EXPECT_DOUBLE_EQ(trueBullCRR, MyBullCRR);
    EXPECT_DOUBLE_EQ(trueBearCRR, MyBearCRR);

}

// Exercise 2.3
TEST(C2Tests, VirtualFunctionIntegral) {

    double a = 1.0;
    double b = 2.0;
    int N = 100;

    TrueInt Oracle(a, b, f2);
    double trueTrapezoid = Oracle.ByTrapezoid(N);
    double trueSimpson = Oracle.BySimpson(N);

    DefIntX_Squared MyInt(a, b);
    double trapeziodal = MyInt.ByTrapeziod(N);
    double simpson = MyInt.BySimpson(N);

    EXPECT_DOUBLE_EQ(trueTrapezoid, trapeziodal);
    EXPECT_DOUBLE_EQ(trueSimpson, simpson);

}

TEST(C2Tests, ExoticOptionsTests) {

    double K1=50, K2=200;
    double S0 = 100, U = 0.3, D = 0.1, R = 0.15;

    BinModel Model(S0, U, D, R);

    StrangleOpt trueStrangle(K1, K2);
    ButterflyOpt trueButterfly(K1, K2);

    Strangle MyStrangle(K1, K2);
    Butterfly MyButterfly(K1, K2);

    double trueStranglePrice = trueStrangle.Payoff(S0);
    double MyStranglePrice = MyStrangle.Payoff(S0);

    double trueButterflyPrice = trueButterfly.Payoff(S0);
    double MyButterflyPrice = MyButterfly.Payoff(S0);

    EXPECT_DOUBLE_EQ(trueStranglePrice, MyStranglePrice);
    EXPECT_DOUBLE_EQ(trueButterflyPrice, MyButterflyPrice);

    double trueStrangleCRR = trueStrangle.PriceByCRR(Model);
    double trueButterflyCRR = trueButterfly.PriceByCRR(Model);
    double MyStrangleCRR = MyStrangle.PriceByCRR(Model);
    double MyButterflyCRR = MyButterfly.PriceByCRR(Model);

    EXPECT_DOUBLE_EQ(trueStrangleCRR, MyStrangleCRR);
    EXPECT_DOUBLE_EQ(trueButterflyCRR, MyButterflyCRR);

}
