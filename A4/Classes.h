#ifndef __CLASSES_H__
#define __CLASSES_H__

using namespace std;

class Complex {
    protected:
    double real;
    double imaginary;

    public:    
    Complex(double r, double i);
    void add(Complex &d);
    void sub(Complex &d);
    void mult(Complex &d);
    virtual void print();
};

class Rational: public Complex {
    private:
    int GCD();

    protected:
    int numerator;
    int denominator;

    public:
    Rational(int n, int d): Complex((double) n / (double) d, 0);
    void reduce();
    virtual void print();

};

class Natural: public Rational {
    public:
    Natural(int n): Rational(n, 1);
    bool checkPrime();
    int getInverse(int p);
}   virtual void print();

#endif
