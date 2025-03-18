#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class Item {
public:
    string id;
    string supplier;

    Item() = default;
    Item(string id, string supplier) : id(id), supplier(supplier) {}

    virtual void save(ofstream& ofs) = 0;
    virtual void load(ifstream& ifs) = 0;
    virtual void print() = 0;

    virtual ~Item() {}

    static void saveData( vector<Item*>& items,  string& filename);
    static void readData(vector<Item*>& items, string& filename);
};

class Product : public Item {
public:
    double stock;
    double price;

    Product() : stock(0), price(0) {};
    Product(string id, string supplier, double stock, double price) : Item(id, supplier), stock(stock), price(price) {}

    void save(ofstream& ofs) override;
    void load(ifstream& ifs) override;
    void print() override;

    static Product* create();
};

class Service : public Item {
public:
    string description;
    double fee;

    Service() : fee(0) {};
    Service(string id, string supplier, string description, double fee) : Item(id, supplier), description(description), fee(fee) {}

    void save(ofstream& ofs) override;
    void load(ifstream& ifs) override;
    void print() override;

    static Service* create();
};