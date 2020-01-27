#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__

using namespace std;

class Polynomial {   
    private:
    double coefficients[21];
        
    public:    
    Polynomial();
    Polynomial(int* coeff);
    Polynomial operator +(Polynomial& p);
    Polynomial operator -(Polynomial& p);
    Polynomial operator *(Polynomial& p);
    Polynomial add(Polynomial& p);
    Polynomial subtract(Polynomial& p);
    Polynomial multiply(Polynomial& p);    
    double evaluate(double x);    
    void print();
};

#endif
