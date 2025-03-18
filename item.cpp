#include "item.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void Item::saveData(vector<Item*>& items, string& filename) {
    ofstream ofs(filename);
    for (auto& item : items) {
        item->save(ofs);
    }
}

void Item::readData(vector<Item*>& items, string& filename) {
    ifstream ifs(filename);
    string type;
    while (getline(ifs, type)) {
        Item* item = nullptr;
        if (type == "Product") item = new Product();
        else if (type == "Service") item = new Service();

        if (item) {
            item->load(ifs);
            items.push_back(item);
        }
    }
}

//  Product Methods 
void Product::save(ofstream& ofs)  {
    ofs << "Product\n" << id << "\n" << supplier << "\n" << stock << "\n" << price << "\n";
}

void Product::load(ifstream& ifs) {
    getline(ifs, id);
    getline(ifs, supplier);
    ifs >> stock >> price;
    ifs.ignore();
}

void Product::print()  {
    cout << "Product ID: " << id << "\nSupplier: " << supplier
        << "\nStock: " << stock << "\nPrice: " << price << "\n";
}

Product* Product::create() {
    string id;
    string supplier;
    double stock;
    double price;

    cout << "Enter product supplier: ";
    cin >> supplier;
    cout << "Enter stock: ";
    cin >> stock;
    cout << "Enter price: ";
    cin >> price;

    id = to_string(rand() % 999999);
    return new Product(id, supplier, stock, price);
}

//  Service Methods 
void Service::save(ofstream& ofs)  {
    ofs << "Service\n" << id << "\n" << supplier << "\n" << description << "\n" << fee << "\n";
}

void Service::load(ifstream& ifs) {
    getline(ifs, id);
    getline(ifs, supplier);
    getline(ifs, description);
    ifs >> fee;
    ifs.ignore();
}

void Service::print()  {
    cout << "Service ID: " << id << "\nSupplier: " << supplier << "\nDescription: " << description << "\nFee: " << fee << "\n";
}

Service* Service::create() {
    string id;
    string supplier;
    string description;
    double fee;

    cout << "Enter service supplier: ";
    cin >> supplier;
    cin.ignore();
    cout << "Enter description: ";
    getline(cin, description);
    cout << "Enter fee: ";
    cin >> fee;

    id = to_string(rand() % 999999);
    return new Service(id, supplier, description, fee);
}