#ifndef __PEN_H_INCLUDED__
#define __PEN_H_INCLUDED__

#include <string>
#include <set>
    
class Pen {
    private:
    int _id;
    float _width;
    string _color;
    string _style;
    static set<Pen> _pens;

    public:
    Pen(int id, float width, string color, string style);
    ~Pen();
    int getId();
    float getWidth();
    string getColor();
    string getStyle();
    static void print();
};

#endif 
