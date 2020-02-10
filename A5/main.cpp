#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <math.h>

#define POLY_LIMIT 10

using namespace std;

class Polynomial {   

    private:
    int coefficients[2 * POLY_LIMIT + 1];
        
    public:    
    Polynomial() {
        for(int i=0; i <= 2 * POLY_LIMIT; i++) {
            coefficients[i] = 0;
        }
    }
    
    Polynomial(int* coeff) {
        for(int i=0; i <= 2 * POLY_LIMIT; i++) {
            coefficients[i] = coeff[i];
        }
    }
    
    Polynomial operator +(Polynomial p) {
        Polynomial res;
        for(int i=0; i<= 2 * POLY_LIMIT; i++) {
            res.coefficients[i] = coefficients[i] + p.coefficients[i];
        }
        
        return res;
    }
    
    Polynomial operator -(Polynomial p) {
        Polynomial res;
        for(int i=0; i<= 2 * POLY_LIMIT; i++) {
            res.coefficients[i] = coefficients[i] - p.coefficients[i];
        }
        
        return res;
    }

    Polynomial operator *(Polynomial p) {
        Polynomial res;
        
        for(int i=0; i<= POLY_LIMIT; i++) {
            for(int j=0; j <= POLY_LIMIT; j++) {
                res.coefficients[i + j] += coefficients[i] * p.coefficients[j];
            }
        }
        
        return res;
    }

    void print() {
        bool firstTerm = true;
        
        for(int i=0; i <= 2 * POLY_LIMIT; i++) {
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

template <class T>
class stack {
    private:
    list<T> S;

    public:
    void push(T item);
    void pop();
    T top();
    bool empty();
    void print();
};

template <class T>
void stack<T>::push(T item) {
    S.push_back(item);
}

template <class T>
void stack<T>::pop() {
    if (S.size() > 0) {
        S.pop_back();
    }
}

template <class T>
T stack<T>::top() {
    return S.back();
}

template <class T>
bool stack<T>::empty() {
    return S.empty();
}

template <class T>
void stack<T>::print() {
    cout << "Stack: ";
    for(typename list<T>::iterator i = S.begin(); i != S.end(); i++) {
        cout << *i << " ";
    }
    cout << endl;
}

int precedence(char op){ 
    if(op == '+'|| op == '-') {
        return 1;
    } else if(op == '*'||op == '/') {
        return 2;
    }
    return 0; 
} 

void processIntInput() {

    string line, token;
    cin.ignore();
    getline(std::cin, line);

    stringstream ss(line);
    
    stack<int> valueStack;
    stack<char> operStack;

    while(ss >> token) {
        //cout << "PROCESSING '" << token << "'" << endl; 
        // process each token
        // this will either be an oper, a parenthesis or an integer
        if (token == "*" || token == "+" || token == "-") {
            char newOper = token[0];
            while (!operStack.empty() && (precedence(operStack.top()) >= precedence(newOper))) {
                char oper = operStack.top(); operStack.pop();
                int b = valueStack.top(); valueStack.pop();
                int a = valueStack.top(); valueStack.pop();
                
                int res;
                switch(oper) {
                    case '+':
                        res = a + b;
                        break;
                    case '-':
                        res = a - b;
                        break;
                    case '*':
                        res = a * b;
                }

                valueStack.push(res);
            }
            operStack.push(newOper);
        } else if (token == "(") {
            operStack.push('(');
        } else if (token == ")") {
            while(operStack.top() != '(') {
                char oper = operStack.top(); operStack.pop();
                int b = valueStack.top(); valueStack.pop();
                int a = valueStack.top(); valueStack.pop();
                
                int res;
                switch(oper) {
                    case '+':
                        res = a + b;
                        break;
                    case '-':
                        res = a - b;
                        break;
                    case '*':
                        res = a * b;
                }

                valueStack.push(res);
            }
            operStack.pop();
        } else {
            valueStack.push(stoi(token));
        }
        //valueStack.print();
        //operStack.print();
    }
    //cout << "Finished reading" << endl;
    while (!operStack.empty()) {
        char oper = operStack.top(); operStack.pop();
        int b = valueStack.top(); valueStack.pop();
        int a = valueStack.top(); valueStack.pop();
        
        int res;
        switch(oper) {
            case '+':
                res = a + b;
                break;
            case '-':
                res = a - b;
                break;
            case '*':
                res = a * b;
        }

        valueStack.push(res);
    }

    cout << valueStack.top() << endl;
}

void processPolyInput() {
    int num;
    std::cin >> num;

    std::string line;

    std::cin.ignore();

    stack<Polynomial> valueStack;
    stack<char> operStack;

    for(int i = 0; i < num; i++) {
        std::getline(std::cin, line);

        if(line.size() == 1) {
            string token = line;
            // process the line
            // this will be either an oper or a parenthesis
            if (token == "*" || token == "+" || token == "-") {
                char newOper = token[0];
                while (!operStack.empty() && (precedence(operStack.top()) >= precedence(newOper))) {
                    char oper = operStack.top(); operStack.pop();
                    Polynomial b = valueStack.top(); valueStack.pop();
                    Polynomial a = valueStack.top(); valueStack.pop();
                    
                    Polynomial res;
                    switch(oper) {
                        case '+':
                            res = a + b;
                            break;
                        case '-':
                            res = a - b;
                            break;
                        case '*':
                            res = a * b;
                    }

                    valueStack.push(res);
                }
                operStack.push(newOper);
            } else if (token == "(") {
                operStack.push('(');
            } else if (token == ")") {
                while(operStack.top() != '(') {
                    char oper = operStack.top(); operStack.pop();
                    Polynomial b = valueStack.top(); valueStack.pop();
                    Polynomial a = valueStack.top(); valueStack.pop();
                    
                    Polynomial res;
                    switch(oper) {
                        case '+':
                            res = a + b;
                            break;
                        case '-':
                            res = a - b;
                            break;
                        case '*':
                            res = a * b;
                    }

                    valueStack.push(res);
                }
                operStack.pop();
            }
        } else {
            // this will be a polynomial
            std::stringstream ss(line);

            int coefficients[2 * POLY_LIMIT + 1];

            int exponent;
            long long coeff;
            while(ss >> exponent, ss >> coeff) {
                // process the exponent and coefficient appropriately
                coefficients[exponent] = coeff;
            }

            valueStack.push(Polynomial(coefficients));
        }
    }

    while (!operStack.empty()) {
        char oper = operStack.top(); operStack.pop();
        Polynomial b = valueStack.top(); valueStack.pop();
        Polynomial a = valueStack.top(); valueStack.pop();
        
        Polynomial res;
        switch(oper) {
            case '+':
                res = a + b;
                break;
            case '-':
                res = a - b;
                break;
            case '*':
                res = a * b;
        }

        valueStack.push(res);
    }

    valueStack.top().print();
}


int main() {

    int n; // number of expressions;
    cin >> n;
    string queryType;
    for(int testcase = 0; testcase < n; testcase++) {
        cin >> queryType;

        if (queryType == "int") {
            processIntInput();
        } else if (queryType == "poly") {
            processPolyInput();
        }
    }

    return 0;
}