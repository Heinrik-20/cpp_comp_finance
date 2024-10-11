#include "DefInt.h"
#include "Functions.h"
#include <iostream>
#include <cmath>
using namespace std;

double DefInt::ByTrapeziod(int N) {

    double h = (getUBound() - getLBound())/N;
    double lbound = getLBound();
    double ubound = getUBound();
    double x_n = 0, integral = 0, intermediate = 0;
    for (int i=0;i <= N;i++) {
        x_n = lbound + (i * h);
        intermediate = evalIntegrand(x_n);
        if ((i != 0) && (i != N)) {
            integral += intermediate;
        } else {
            integral += intermediate / 2;
        }

    }
    
    return h * integral;

}

double DefInt::BySimpson(int N) {

    double lbound = getLBound();
    double ubound = getUBound();
    double h = (ubound - lbound)/N;
    double integral = evalIntegrand(lbound);
    for (int i=1;i < N;i++) {
       integral += 4 * evalIntegrand(lbound + (i * h) - (0.5 * h)) + 2 * evalIntegrand(lbound + (i * h));

    }
    integral += evalIntegrand(ubound) + evalIntegrand(ubound - 0.5 * h) * 4;

    return (h/6) * integral;

}

double DefIntVirtual::ByTrapeziod(int N) {

    double h = (getUBound() - getLBound())/N;
    double lbound = getLBound();
    double ubound = getUBound();
    double x_n = 0, integral = 0, intermediate = 0;
    for (int i=0;i <= N;i++) {
        x_n = lbound + (i * h);
        intermediate = integrand(x_n);
        if ((i != 0) && (i != N)) {
            integral += intermediate;
        } else {
            integral += intermediate / 2;
        }

    }
    
    return h * integral;

}

double DefIntVirtual::BySimpson(int N) {

    double lbound = getLBound();
    double ubound = getUBound();
    double h = (ubound - lbound)/N;
    double integral = integrand(lbound);
    for (int i=1;i < N;i++) {
       integral += 4 * integrand(lbound + (i * h) - (0.5 * h)) + 2 * integrand(lbound + (i * h));

    }
    integral += integrand(ubound) + integrand(ubound - 0.5 * h) * 4;

    return (h/6) * integral;

}

double DefIntX_Squared::integrand(double x) {
    return pow(x, 2);
}

template<typename Function> double DefIntTemplate<Function>::ByTrapeziod(int N) {

    double h = (getUBound() - getLBound())/N;
    double lbound = getLBound();
    double ubound = getUBound();
    double x_n = 0, integral = 0, intermediate = 0;
    for (int i=0;i <= N;i++) {
        x_n = lbound + (i * h);
        intermediate = integrand.f(x_n);
        if ((i != 0) && (i != N)) {
            integral += intermediate;
        } else {
            integral += intermediate / 2;
        }

    }
    
    return h * integral;

}

template<typename Function> double DefIntTemplate<Function>::BySimpson(int N) {

    double lbound = getLBound();
    double ubound = getUBound();
    double h = (ubound - lbound)/N;
    double integral = integrand.f(lbound);
    for (int i=1;i < N;i++) {
       integral += 4 * integrand.f(lbound + (i * h) - (0.5 * h)) + 2 * integrand.f(lbound + (i * h));

    }
    integral += integrand.f(ubound) + integrand.f(ubound - 0.5 * h) * 4;

    return (h/6) * integral;
}

template class DefIntTemplate<Funct>;