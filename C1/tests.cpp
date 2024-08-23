#include <gtest/gtest.h>
#include "Options01.h"
#include "Utils.h"

// Exercise 1.2
TEST(C1Tests, Interchange) {

    double U = 0.2, D = 0.1;
    interchange(U, D);
    EXPECT_DOUBLE_EQ(U, 0.1);
    EXPECT_DOUBLE_EQ(D, 0.2);

}

// Exercise 1.3 
TEST(C1Tests, PriceByCRRLoops) {

    double S0 = 100, U = 0.3, D = 0.1, R = 0.15, K = 80;
    int N = 5;

    double oracle = PriceByCRR(S0, U, D, R, N, K);
    double test = PriceByCRRWhile(S0, U, D, R, N, K);

    EXPECT_DOUBLE_EQ(oracle, test);
}

// Exercise 1.5
TEST(C1Tests, PriceByCRRFormula) {

    double S0 = 100, U = 0.3, D = 0.1, R = 0.15, K = 80;
    int N = 5;

    double oracle = PriceByCRR(S0, U, D, R, N, K);
    double test = PriceByCRRFormula(S0, U, D, R, N, K);

    EXPECT_DOUBLE_EQ(oracle, test);
}

// Exercise 1.6
TEST(C1Tests, BubbleSort) {

    double A[] = {
        7,1,5,1,0
    };

    bubblesort(A, 5);

    double trueA[] = {
        0,1,1,5,7
    };

    for (int i=0;i < 5;i++) {
        EXPECT_DOUBLE_EQ(A[i], trueA[i]);
    }
}