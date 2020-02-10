#ifndef __DESIGN_H__
#define __DESIGN_H__

#include <list>
#define POLY_LIMIT 10

template <class T>
class stack {
    private:
    list<T> S;

    public:
    void push(T item);
    void pop();
    T top();
    bool empty();
};

class Polynomial {   
    private:
    int coefficients[2 * POLY_LIMIT + 1];
        
    public:    
    Polynomial();
    Polynomial(int* coeff);
    Polynomial operator +(Polynomial& p);
    Polynomial operator -(Polynomial& p);
    Polynomial operator *(Polynomial& p);
    void print();
};


#endif