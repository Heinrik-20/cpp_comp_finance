#include <iostream>
#include <gtest/gtest.h>
#include <cmath>
#include "Functions.h"
#include "Solver.h"
#include "Oracle.h"
#include "DefInt.h"

using namespace std;

TEST(C4Tests, Exercise1Test) {

    class F1 {
        public:
            double Value(double x){return x*x-2;}
            double Deriv(double x){return 2*x;}
    } MyF1;

    class F2 {
        private:
            double a; //parameter
        public:
            F2(double a_){a=a_;}
            double Value(double x){return x*x-a;}
            double Deriv(double x){return 2*x;}
    } MyF2(3.0);

    double Acc=0.001;
    double LEnd=0.0, REnd=2.0;
    double Tgt=0.0;

    double mySolvebyBissectF1 = SolveByBisect(MyF1,Tgt,LEnd,REnd,Acc);
    double mySolvebyNRF1 = SolveByNR(MyF1,Tgt,1.0,Acc);
    double mySolvebyBissectF2 = SolveByBisect(MyF2,Tgt,LEnd,REnd,Acc);
    double mySolvebyNRF2 = SolveByNR(MyF2,Tgt,1.0,Acc);

    double OracleSolvebyBissectF1 = OracleSolveByBisect(MyF1,Tgt,LEnd,REnd,Acc);
    double OracleSolvebyNRF1 = OracleSolveByNR(MyF1,Tgt,1.0,Acc);
    double OracleSolvebyBissectF2 = OracleSolveByBisect(MyF2,Tgt,LEnd,REnd,Acc);
    double OracleSolvebyNRF2 = OracleSolveByNR(MyF2,Tgt,1.0,Acc);

    EXPECT_DOUBLE_EQ(mySolvebyBissectF1, OracleSolvebyBissectF1);
    EXPECT_DOUBLE_EQ(mySolvebyNRF1, OracleSolvebyNRF1);
    EXPECT_DOUBLE_EQ(mySolvebyBissectF2, OracleSolvebyBissectF2);
    EXPECT_DOUBLE_EQ(mySolvebyNRF2, OracleSolvebyNRF2);

}

TEST(C4Tests, Exercise2Test) {

    double F=100.0; //face value
    double T=3.0; //maturity time
    vector<double> C; //coupons
    C.push_back(1.2); C.push_back(1.2); C.push_back(1.2);
    vector<double> t; //coupon times
    t.push_back(1.0); t.push_back(2.0); t.push_back(3.0);

    class Bond {
        private:
            double face_value;
            vector<double> coupons;
            vector<double> times;
        
        public:

            Bond(double F, vector<double>& coupons_, vector<double>& times_) {
                face_value = F;
                coupons = coupons_;
                times = times_;
            }

            double Value(double yield) {
                int N = coupons.size();
                double price = 0;
                for (int i=0;i < N;i++) {
                    price += coupons[i] * exp(-yield * times[i]);
                }
                return price + face_value * exp(-yield * times[N-1]);

            }

            double Deriv(double yield) {
                int N = coupons.size();
                double deriv = 0;
                for (int i=0;i < N;i++) {
                    deriv -= (times[i] * coupons[i] * exp(-yield * times[i]));
                }
                return deriv - (times[N-1] * face_value * exp(-yield * times[N-1]));
            }
    } MyBond(F, C, t);

    OracleBond oracle(F, T, C, t);

    double LEnd=0.0, REnd=2.0;
    double Tgt=98.56;
    double Acc=0.0001;

    double myYield = OracleSolveByBisect(MyBond,Tgt,LEnd,REnd,Acc);
    double OracleYield = OracleSolveByBisect(oracle,Tgt,LEnd,REnd,Acc);

    EXPECT_DOUBLE_EQ(myYield, OracleYield);

    double myYieldNR = OracleSolveByNR(MyBond,Tgt,0.5,Acc);
    double OracleYieldNR = OracleSolveByNR(oracle,Tgt,0.5,Acc);

    EXPECT_DOUBLE_EQ(myYieldNR, OracleYieldNR);
}

TEST(C4Tests, Exercise3Test) {

    double a = 1.0;
    double b = 2.0;
    int N = 100;

    Funct MyFunc;
    Funct OracleFunc;

    DefIntTemplate<Funct> MyInt(a, b, MyFunc);
    double trapeziodal = MyInt.ByTrapeziod(N);
    double simpson = MyInt.BySimpson(N);

    DefIntOracle<Funct> Oracle(a, b, OracleFunc);
    double trueTrapezoid = Oracle.ByTrapezoid(N);
    double trueSimpson = Oracle.BySimpson(N);

    EXPECT_DOUBLE_EQ(trueTrapezoid, trapeziodal);
    EXPECT_DOUBLE_EQ(trueSimpson, simpson);
}