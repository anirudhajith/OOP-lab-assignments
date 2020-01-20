#ifndef __PEN_H_INCLUDED__
#define __PEN_H_INCLUDED__

#include <string>
#include <set>

struct comparePen {
    bool operator() (const Pen& lhs, const Pen& rhs) const {
        return lhs.getId() < rhs.getId();
    }
};
    
class Pen {
    private:
    int _id;
    float _width;
    string _color;
    string _style;
    static set<Pen, comparePen> _pens;

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
