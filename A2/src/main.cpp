#include <iostream>
#include <map>
#include <string>

using namespace std;

class InventoryItem {
   private:
    int _id;
    float _price;
    string _manufacturer;
    string _type;

   public:
    static map<int, InventoryItem> items;

    InventoryItem(int id = -1, float price = -1, string manufacturer = "", string type = "") {
        _id = id;
        _price = price;
        _manufacturer = manufacturer;
        _type = type;
    }

    ~InventoryItem() {}

    int getId() {
        return _id;
    }

    float getPrice() {
        return _price;
    }

    string getManufacturer() {
        return _manufacturer;
    }

    string getType() {
        return _type;
    }

    static void print() {
        for (map<int, InventoryItem>::iterator item = items.begin(); item != items.end(); item++) {
            cout << item->second._id << " " << item->second._price << " " << item->second._manufacturer << " " << item->second._type << endl;
        }
    }
};
map<int, InventoryItem> InventoryItem::items;

class Pen {
   private:
    int _id;
    float _width;
    string _color;
    string _style;

   public:
    static map<int, Pen> pens;

    Pen(int id = -1, float width = -1, string color = "", string style = "") {
        _id = id;
        _width = width;
        _color = color;
        _style = style;
    }

    ~Pen() {
        //InventoryItem::items.find(_id);
    }

    int getId() {
        return _id;
    }

    float getWidth() {
        return _width;
    }

    string getColor() {
        return _color;
    }

    string getStyle() {
        return _style;
    }

    static void print() {
        for (map<int, Pen>::iterator pen = pens.begin(); pen != pens.end(); pen++) {
            cout << pen->second._id << " " << pen->second._width << " " << pen->second._color << " " << pen->second._style << endl;
        }
    }
};
map<int, Pen> Pen::pens;

class Pencil {
   private:
    int _id;
    float _width;
    string _hardness_mark;
    string _point_size;

   public:
    static map<int, Pencil> pencils;
    Pencil(int id = -1, float width = -1, string hardness_mark = "", string point_size = "") {
        _id = id;
        _width = width;
        _hardness_mark = hardness_mark;
        _point_size = point_size;
    }

    ~Pencil() {}

    int getId() {
        return _id;
    }

    float getWidth() {
        return _width;
    }

    string getHMark() {
        return _hardness_mark;
    }

    string getPointSize() {
        return _point_size;
    }

    static void print() {
        for (map<int, Pencil>::iterator pencil = pencils.begin(); pencil != pencils.end(); pencil++) {
            cout << pencil->second._id << " " << pencil->second._width << " " << pencil->second._hardness_mark << " " << pencil->second._point_size << endl;
        }
    }
};
map<int, Pencil> Pencil::pencils;

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;  // number of operation
    char operation;

    int id;
    float price, width;
    string manufacturer, type, hardness_mark, point_size, color, style;

    for (int t = 0; t < T; t++) {
        cin >> operation;

        switch (operation) {
            case 'a':
                cin >> id >> price >> manufacturer >> type;
                InventoryItem::items[id] = InventoryItem(id, price, manufacturer, type);
                break;

            case 'b':
                cin >> id >> width >> color >> style;
                Pen::pens[id] = Pen(id, width, color, style);
                break;

            case 'c':
                cin >> id >> width >> hardness_mark >> point_size;
                Pencil::pencils[id] = Pencil(id, width, hardness_mark, point_size);
                break;

            case 'd':
                cin >> id;
                if (InventoryItem::items.count(id) > 0) InventoryItem::items.erase(id);
                if (Pen::pens.count(id) > 0) Pen::pens.erase(id);
                if (Pencil::pencils.count(id) > 0) Pencil::pencils.erase(id);
                break;

            case 'p':
                InventoryItem::print();
                break;

            case 'q':
                Pen::print();
                break;

            case 'r':
                Pencil::print();
                break;
        }
    }

    return 0;
}