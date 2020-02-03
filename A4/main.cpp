#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Complex {
    protected:
    double real;
    double imaginary;

    public:    
    Complex(double r, double i) {
        real = r;
        imaginary = i;
    }
    
    void add(Complex &d) {
        real += d.real;
        imaginary += d.imaginary;
    }
    
    void sub(Complex &d) {
        real -= d.real;
        imaginary -= d.imaginary;
    }
    
    void mult(Complex &d) {
        double r = real;
        real = (real * d.real) - (imaginary * d.imaginary);
        imaginary = (r * d.imaginary) + (imaginary * d.real);
    }
    
    virtual void print() {
        cout << real << " " << imaginary << endl;
    }
};

class Rational: public Complex {
    private:
    int GCD(int a, int b) {
        return __gcd(a, b);
    }

    protected:
    int numerator;
    int denominator;

    public:
    Rational(int n, int d): Complex((double) n / (double) d, 0) {
        numerator = n;
        denominator = d;
    }
    
    void reduce() {
        int gcd = GCD(numerator, denominator);
        if ((numerator < 0 && denominator > 0) || (numerator > 0 && denominator < 0))
            gcd = -gcd;
            
        cout << (numerator / gcd) << " " << (denominator / gcd) << endl;
    }
    
    virtual void print() {
        cout << real << endl;
    }

};

class Natural: public Rational {
    private:
    int gcdExtended(int a, int b, int *x, int *y) { 
        if (a == 0) { 
            *x = 0, *y = 1; 
            return b; 
        } 
      
        int x1, y1; 
        int gcd = gcdExtended(b%a, a, &x1, &y1); 
      
        *x = y1 - (b/a) * x1; 
        *y = x1; 
      
        return gcd; 
    } 

    public:
    Natural(int n): Rational(n, 1) {}
    
    bool checkPrime() {
        for(int factor = 2; factor * factor <= numerator; factor++) {
            if (numerator % factor == 0) return false;
        }
        
        return true;
    }
    
    int getInverse(int p = 1000000007) {
        int x, y; 
        int g = gcdExtended(numerator, p, &x, &y); 
        int res = (x%p + p) % p; 
        return res;
    }
    
    virtual void print() {
        cout << (int) real << endl;
    }
};

int main() {
    
    std::cout.precision(3); std::cout << std::fixed;
    int T;
    cin >> T;
    string numType, opType;
    
    for(int t=0; t < T; t++) {
        cin >> numType >> opType;
        if (numType == "complex") {
            double a, b, c, d;
            cin >> a >> b >> c >> d;
            Complex z1(a, b), z2(c, d);
            
            if (opType == "add") {
                z1.add(z2);
                z1.print();
            } else if (opType == "sub") {
                z1.sub(z2);
                z1.print();
            } else if (opType == "mult") {
                z1.mult(z2);
                z1.print();
            } else {
                cout << "INVALID" << endl;
            }
            
        } else if (numType == "rational") {
            int a, b, c, d;
            cin >> a >> b;
            Rational r1(a, b);
            
            if (opType == "add") {
                cin >> c >> d;
                Rational r2(c, d);
                r1.add(r2);
                r1.print();
            } else if (opType == "sub") {
                cin >> c >> d;
                Rational r2(c, d);
                r1.sub(r2);
                r1.print();
            } else if (opType == "mult") {
                cin >> c >> d;
                Rational r2(c, d);
                r1.mult(r2);
                r1.print();
            } else if (opType == "reduce") {
                r1.reduce();                                
            } else {
                cout << "INVALID" << endl;
            }
        } else if (numType == "natural") {
            int a;
            cin >> a;
            Natural n(a);
            
            if (opType == "isprime") {
                cout << (n.checkPrime()?1:0) << endl;
            } else if (opType == "inverse") {
                cout << n.getInverse();
            } else {
                cout << "INVALID" << endl;
            }
        } else {
            cout << "INVALID" << endl;
        }
    }
    
    return 0;
}
