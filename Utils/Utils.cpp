#include "Utils.h"
#include <iostream>
#include <cmath>
using namespace std;

void interchange(double& a, double& b) {

    double temp = b;
    b = a;
    a = temp;

}

void bubblesort(double *A, int A_size) {
    for (int i=0;i < A_size - 1;i++) {
        for (int j=0;j < A_size - i - 1;j++) {
            if (A[j] > A[j+1]) {
                interchange(A[j], A[j+1]);
            }
        }
    }
}