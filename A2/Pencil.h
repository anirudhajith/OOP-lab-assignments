#ifndef __PENCIL_H_INCLUDED__
#define __PENCIL_H_INCLUDED__

#include <string>
#include <set>

struct comparePencil {
    bool operator() (const Pencil& lhs, const Pencil& rhs) const {
        return lhs.getId() < rhs.getId();
    }
};
    
class Pencil {
    private:
    int _id;
    float _width;
    string _hardness_mark;
    string _point_size;
    static set<Pencil, comparePencil> _pencils;

    public:
    Pencil(int id, float width, string hardness_mark, string point_size);
    ~Pencil();
    int getId();
    float getWidth();
    string getHMark();
    string getPointSize();
    static void print();
};

#endif 
