#include <iostream>
#include <math.h>

#define LIMIT 10

using namespace std;

class Polynomial {   
    private:
    double coefficients[2 * LIMIT + 1];
        
    public:    
    Polynomial() {
        for(int i=0; i <= 2 * LIMIT; i++) {
            coefficients[i] = 0;
        }
    }
    
    Polynomial(double* coeff) {
        for(int i=0; i <= 2 * LIMIT; i++) {
            coefficients[i] = coeff[i];
        }
    }
    
    Polynomial operator +(Polynomial p) {
        Polynomial res;
        for(int i=0; i<= 2 * LIMIT; i++) {
            res.coefficients[i] = coefficients[i] + p.coefficients[i];
        }
        
        return res;
    }
    
    Polynomial operator -(Polynomial p) {
        Polynomial res;
        for(int i=0; i<= 2 * LIMIT; i++) {
            res.coefficients[i] = coefficients[i] - p.coefficients[i];
        }
        
        return res;
    }

    Polynomial operator *(Polynomial p) {
        Polynomial res;
        
        for(int i=0; i<= LIMIT; i++) {
            for(int j=0; j <= LIMIT; j++) {
                res.coefficients[i + j] += coefficients[i] * p.coefficients[j];
            }
        }
        
        return res;
    }
    
    Polynomial add(Polynomial p) {
        return (*this + p);
    }
    
    Polynomial subtract(Polynomial p) {
        return (*this - p);
    }

    Polynomial multiply(Polynomial p) {
        return (*this * p);
    }
    
    double evaluate(double x) {
        double power = 1;
        double sum = 0;
        for(int i=0; i <= 2 * LIMIT; i++) {
            sum += (power * coefficients[i]);
            power *= x;
        }
        
        return sum;
    }
    
    void print() {
        bool firstTerm = true;
        
        for(int i=0; i <= 2 * LIMIT; i++) {
            if(coefficients[i] != 0) {
                cout << (firstTerm ? (coefficients[i] > 0 ? "" : "-") : (coefficients[i] > 0 ? "+ " : "- ")) // sign
                     << fabs(coefficients[i]) // value
                     << "x^" << i << " ";     // term
                firstTerm = false;
            }
        }
        cout << endl;
    }
};

int main() {
    
    cout.precision(3);
    cout << fixed;
    int opCount;
    char opCode;
    cin >> opCount;
    
    for(int i=0; i < opCount; i++) {
        cin >> opCode;
        
        if (opCode == 'a' || opCode == 's' || opCode == 'm') {                    
            double coeff1[2 * LIMIT + 1] = {0}, coeff2[2 * LIMIT + 1] = {0};
            int n1, n2;
            int exponent;
            double c;
            
            cin >> n1;
            for(int i = 0; i < n1; i++) {
                cin >> exponent >> c;
                coeff1[exponent] = c;
            }
            
            cin >> n2;
            for(int i = 0; i < n2; i++) {
                cin >> exponent >> c;
                coeff2[exponent] = c;
            }
            
            if (opCode == 'a') {
                Polynomial p = Polynomial(coeff1) + Polynomial(coeff2);
                p.print();
            } else if (opCode == 's') {
                Polynomial p = Polynomial(coeff1) - Polynomial(coeff2);
                p.print();
            } else if (opCode == 'm') {
                Polynomial p = Polynomial(coeff1) * Polynomial(coeff2);
                p.print();
            }
            
        } else {
            double coeff1[2 * LIMIT + 1] = {0};
            int n1;
            int exponent;
            double c, x;
            
            cin >> n1;
            for(int i = 0; i < n1; i++) {
                cin >> exponent >> c;
                coeff1[exponent] = c;
            }
            cin >> x;
            
            Polynomial p(coeff1);
            
            cout << p.evaluate(x) << endl;
        }
        
        
    }


    return 0;
}
