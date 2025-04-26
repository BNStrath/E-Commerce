#include "item.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void Item::saveData(vector<Item*>& items, string& filename) {

    //for each element in the item vector, this function calls the save function

    ofstream ofs(filename);
    for (auto& item : items) {
        item->save(ofs);
    }
}

void Item::readData(vector<Item*>& items, string& filename) {

    //iterates through each line in the itemData.txt file. each item has a type identifier before it in the file, this function uses it to determine which type of item to create
    //a new instantiation of. If an item is successfully created (when there is sufficient formatted data in the file for it) the load function is called which reads the file in a
    //specific format inverse to the way it was saved using the fstream, before assigning the read values to the newly created item. Finally, once the values are all assigned, this item
    //is added to the back of the vector of items

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

void Item::printItems(vector<Item*> items) {

    //products and services have their own print() method, use of auto ensures that the appropriate version is called for each element of the vector

    for (auto x : items) {
        x->print();
        cout << "\n";
    }
}

//  Product Methods 
void Product::save(ofstream& ofs) {

    //writes an individual item to the file along with the appropriate identifier, "Product"

    ofs << "Product\n" << id << "\n" << supplier << "\n" << itemName << "\n" << ageLim << "\n" << stock << "\n" << price << "\n";
}

void Product::load(ifstream& ifs) {
    getline(ifs, id);
    getline(ifs, supplier);
    getline(ifs, itemName);
    ifs >> ageLim >> stock >> price;
    ifs.ignore();
}

void Product::print() {
    cout << "Product ID: " << id << "\nSupplier: " << supplier << "\nName: " << itemName << "\nAgeLim:" << ageLim << "\nStock: " << stock << "\nPrice: " << price << "\n";
}

Product* Product::create(Business& business) {

    //Function passes in a business to create a new product associated with it. Name, price and stock are determined via user input whereas id is created via random number gen.
    //to ensure more authentic randomness, computer clock is used and limits are specified to ensure a 6 digit ID number, this does have the potential to create repeats, how ever this
    //is very low with small data sets. It is necessary to convert this id to a string as functions such as the shop equate this id as a string to verify a purchase

    string id;
    string supplier;
    string itemName;
    int ageLim;
    double stock;
    double price;

    supplier = business.name;
    cout << "Enter product name: ";
    cin >> itemName;
    cout << "Enter the age requirement for this product:";
    cin >> ageLim;
    cout << "Enter stock: ";
    cin >> stock;
    cout << "Enter price: ";
    cin >> price;


    srand(time(0));
    id = to_string(rand() % 999999 + 100000);

    return new Product(id, supplier, itemName, ageLim, stock, price);
}

void Product::addStock(vector<Item*>& items, Business business) {

    //Edits the stock of a product associated with a business. Dynamic cast is used to ensure the item selected is a product and then a security check is performed to make sure that only
    //the supplier of this item can access the stock

    string productID;
    int num;

    cout << "\nEnter the id of the product you would like to change the stock of:\n";
    cin >> productID;

    for (auto x : items) {
        if (x->id == productID) {
            Product* product = dynamic_cast<Product*>(x);

            if (product) {
                if (product->supplier == business.name) {
                    cout << "\nHow much would you like to add to the stock?\n";
                    cin >> num;

                    product->stock = product->stock + num;
                    cout << "stock added\n";
                    return;
                }
                else {
                    cout << "failed to add stock\n";
                    return;
                }
            }
        }
        else {
            cout << "ID entered does not match a product\n";
            return;
        }
    }
}

//  Service Methods 
void Service::save(ofstream& ofs) {
    ofs << "Service\n" << id << "\n" << supplier << "\n" << itemName << "\n" << ageLim << "\n" << description << "\n" << fee << "\n";
}

void Service::load(ifstream& ifs) {
    getline(ifs, id);
    getline(ifs, supplier);
    getline(ifs, itemName);

    ifs >> ageLim;
    ifs.ignore(); //for ifs >> , ifs.ignore() is necessary to delete invisible \n character or following getline will read a blank

    getline(ifs, description);

    ifs >> fee;
    ifs.ignore();
}

void Service::print() {
    cout << "Service ID: " << id << "\nSupplier: " << supplier << "\nItemname: " << itemName << "\nAge Limit: " << ageLim << "\nDescription: " << description << "\nFee: " << fee << "\n";
}

Service* Service::create(Business& business) {
    string id;
    string supplier;
    string itemName;
    int ageLim;
    string description;
    double fee;

    supplier = business.name;
    cout << "Enter service name: ";
    cin >> itemName;
    cin.ignore();
    cout << "Enter the age requirement for this service: ";
    cin >> ageLim;
    cin.ignore();
    cout << "Enter description: ";
    getline(cin, description);
    cout << "Enter fee: ";
    cin >> fee;

    srand(time(0));
    id = to_string(rand() % 999999 + 100000);

    return new Service(id, supplier, itemName, ageLim, description, fee);
}