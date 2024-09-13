#ifndef BSMODEL_H
#define BSMODEL_H

#include <cmath>
#include "BinModel.h"

class BSModel {

    private:
        double r, sigma;

    public:
        BSModel(double r_, double sigma_) {r=r_; sigma=sigma_;};
        BinModel approximate(double S0, double T, double N) {
            double h = T/N;

            double U = exp(((r - pow(sigma, 2)/2) * h) + (sigma * sqrt(h))) - 1;
            double D = exp(((r - pow(sigma, 2)/2) * h) - (sigma * sqrt(h))) - 1;
            double R = exp(r*h) - 1;
            BinModel bs_model(S0, U, D, R);
            return bs_model;
        };

};

#endif