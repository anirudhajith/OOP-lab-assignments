#ifndef __INVENTORY_ITEM_H_INCLUDED__
#define __INVENTORY_ITEM_H_INCLUDED__

#include <string>
#include <set>

struct compareInventoryItem {
    bool operator() (const InventoryItem& lhs, const InventoryItem& rhs) const {
        return lhs.getId() < rhs.getId();
    }
};

class InventoryItem {
    private:
    int _id;
    float _price;
    string _manufacturer;
    string _type;

    public:
    InventoryItem(int id, float price, string manufacturer, string type);
    ~InventoryItem();
    int getId();
    float getPrice();
    string getManufacturer();
    string getType();
    static void print();
    static set<InventoryItem, compareInventoryItem> items;
};

#endif 
