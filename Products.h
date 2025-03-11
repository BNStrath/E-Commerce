#pragma once
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Product {
public:
	string product_id;
	string supplier;
	double stock;
	double price;

	Product();
	Product(string id, string supplier, double stock, double price) : product_id(id), supplier(supplier), stock(stock), price(price) {};

	void save(ofstream& ofs) const;

	static void read(vector<Product>& products);
	static void saveData(const vector<Product> products);
};

