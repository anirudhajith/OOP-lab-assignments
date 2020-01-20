#ifndef __INVENTORY_ITEM_H_INCLUDED__
#define __INVENTORY_ITEM_H_INCLUDED__

#include <string>
#include <set>

class InventoryItem {
    private:
    int _id;
    float _price;
    string _manufacturer;
    string _type;
    static set<InventoryItem> _items;

    public:
    InventoryItem(int id, float price, string manufacturer, string type);
    ~InventoryItem();
    int getId();
    float getPrice();
    string getManufacturer();
    string getType();
    static void print();
};

#endif 
