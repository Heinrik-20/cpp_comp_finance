#include <gtest/gtest.h>
#include "BinModel.h"
#include "Options.h"
#include "Oracle.h"
#include "BinLattice.h"
#include "BSModel.h"

using namespace std;

TEST(C3Tests, Exercise1Test) {
    int K = 90;
    int N = 2;
    double S0 = 100, U = 0.3, D = 0.1, R = 0.15;

    BinModel Model(S0, U, D, R);

    Call MyEur;
    OracleCall OracleEur;

    MyEur.SetN(N);
    OracleEur.SetN(N);

    BinLattice<double> MyPriceTree;
    BinLattice<double> OraclePriceTree;

    BinLattice<double> MyMoneyAccount;
    BinLattice<double> MyStockAccount;

    BinLattice<double> OracleMoneyAccount;
    BinLattice<double> OracleStockAccount;
   

    MyEur.PriceByCRR(
        Model,
        MyPriceTree,
        MyStockAccount,
        MyMoneyAccount
    );

    OracleEur.PriceByCRR(
        Model,
        OraclePriceTree,
        OracleStockAccount,
        OracleMoneyAccount
    );

    for (int n=0; n < N; n++) {
        for (int i=0;i<=n;i++) {
            EXPECT_DOUBLE_EQ(MyPriceTree.GetNode(n, i), OraclePriceTree.GetNode(n, i));
            EXPECT_DOUBLE_EQ(MyMoneyAccount.GetNode(n, i), OracleMoneyAccount.GetNode(n, i));
            EXPECT_DOUBLE_EQ(MyStockAccount.GetNode(n, i), OracleStockAccount.GetNode(n, i));
        }
    }
}

TEST(C3Tests, BSModelTest) {

    int K = 90;
    int N = 3;
    double S0 = 100, T = 10;
    double sigma = 0.1, r = 0.05;

    BSModel myBS(r, sigma);
    OracleBSModel OracleBS(S0, r, sigma);

    BinModel myApprox = myBS.approximate(S0, T, N);
    BinModel OracleApprox = OracleBS.ApproxBinModel(T/N);

    for (int n=N-1;n>=0;n--){
        for (int i=0;i<=n;i++) {
            EXPECT_DOUBLE_EQ(myApprox.S(n, i), OracleApprox.S(n, i));
        }
    }

}