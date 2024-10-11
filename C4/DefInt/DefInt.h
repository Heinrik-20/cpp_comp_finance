#ifndef DefInt_h
#define DefInt_h

class DefInt {

    private:
        double lbound, ubound;
        double (*integrand)(double x);

    public:
        DefInt(double lbound_, double ubound_, double (*f)(double x)) {
            lbound = lbound_;
            ubound = ubound_;
            integrand = f;
        };

        double ByTrapeziod(int N);
        double BySimpson(int N);

        double getLBound() { return lbound; }
        double getUBound() { return ubound; }

        double evalIntegrand(double x) { return integrand(x); }

};

class DefIntVirtual {

    private:
        double lbound, ubound;

    public:
        DefIntVirtual(double lbound_, double ubound_) {
            lbound = lbound_;
            ubound = ubound_;
        };

        double ByTrapeziod(int N);
        double BySimpson(int N);
        virtual double integrand(double x)=0;

        double getLBound() { return lbound; }
        double getUBound() { return ubound; }

        void setLBound(double lbound_) { lbound = lbound_; }
        void setUBound(double ubound_) { ubound = ubound_; }

};

class DefIntX_Squared : public DefIntVirtual {
    public:
        DefIntX_Squared(double lbound_, double ubound_) : DefIntVirtual(lbound_, ubound_) {}
        double integrand(double x);
};

template<typename Function> class DefIntTemplate {
    private:
        double lbound, ubound;
        Function integrand;

    public:
        DefIntTemplate(double lbound_, double ubound_, Function& integrand_) {
            lbound = lbound_;
            ubound = ubound_;
            integrand = integrand_;
        }

    double ByTrapeziod(int N);
    double BySimpson(int N);

    double getLBound() { return lbound; }
    double getUBound() { return ubound; }

    double evalIntegrand(double x) { return integrand.f(x); }
};

#endif