#include <gtest/gtest.h>
#include "BinModel.h"
#include "Options.h"
#include "Oracle.h"
#include "BinLattice.h"

TEST(C3Tests, Exercise1Test) {
    int K = 100,
    int N = 5
    double S0 = 100, U = 0.3, D = 0.1, R = 0.15;

    BinModel Model(S0, U, D, R);

    Call MyEur;
    OracleCall Oracle;

    MyEur.setN(N);
    OracleEur.setN(N);

    BinLattice MyPriceTree;
    BinLattice OraclePriceTree;

    BinLattice MyMoneyAccount;
    BinLattice MyStockAccount;

    BinLattice OracleMoneyAccount;
    BinLattice OracleStockAccount;

    MyEur.PriceByCRR(
        Model,
        MyPriceTree,
        MyMoneyAccount,
        MyStockAccount,
    );

    MyEur.PriceByCRR(
        Model,
        OraclePriceTree,
        OracleMoneyAccount,
        OracleStockAccount,
    );

    for (int n=0; n < N; n++) {
        for (int i=0;i<=n;i++) {
            EXPECT_DOUBLE_EQ(MyPriceTree.GetNode(n, i), OraclePriceTree.GetNode(n, i));
            EXPECT_DOUBLE_EQ(MyMoneyAccount.GetNode(n, i), OracleMoneyAccount.GetNode(n, i));
            EXPECT_DOUBLE_EQ(MyStockTree.GetNode(n, i), OracleStockTree.GetNode(n, i));
        }
    }


}