#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "business.h"
using namespace std;

class Item {
public:
    string id;
    string supplier;
    string itemName;

    Item() = default;
    Item(string id, string supplier, string itemName) : id(id), supplier(supplier), itemName(itemName) {}

    virtual void save(ofstream& ofs) = 0;
    virtual void load(ifstream& ifs) = 0;
    virtual void print() = 0;

    static void printItems(vector<Item*> items);

    virtual ~Item() {}

    static void saveData(vector<Item*>& items, string& filename);
    static void readData(vector<Item*>& items, string& filename);
};

class Product : public Item {
public:
    double stock;
    double price;

    Product() : stock(0), price(0) {};
    Product(string id, string supplier, string itemName, double stock, double price) : Item(id, supplier, itemName), stock(stock), price(price) {}

    void save(ofstream& ofs) override;
    void load(ifstream& ifs) override;
    void print() override;

    static void addStock(vector<Item*>&, Business business);

    static Product* create(Business business);
};

class Service : public Item {
public:
    string description;
    double fee;

    Service() : fee(0) {};
    Service(string id, string supplier, string description, string itemName, double fee) : Item(id, supplier, itemName), description(description), fee(fee) {}

    void save(ofstream& ofs) override;
    void load(ifstream& ifs) override;
    void print() override;

    static Service* create(Business business);
};