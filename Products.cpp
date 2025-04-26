#include "Products.h"
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

Product::Product() {
}

void Product::save(ofstream& ofs) const{
	ofs << product_id << "\n" << supplier << "\n" << stock << "\n" << price << "\n";
}

void Product::read(vector<Product>& products) {
	string product_id;
	string supplier;
	double stock;
	double price;
	ifstream ifs("testdata.txt");

	while (getline(ifs, product_id)) {
		cout << "id:" << product_id << "\n";
		getline(ifs, supplier);
		cout << "supplier:" << supplier << "\n";
		ifs >> stock;
		cout << "stock:" << stock << "\n";
		ifs >> price;
		cout << "price:" << price << "\n";
		ifs.ignore();
		products.push_back(Product(product_id, supplier, stock, price));
	}
}

void Product::saveData(const vector<Product> products) {
	ofstream ofs("testdata.txt");
	for (const auto& product : products) {
		product.save(ofs);
	}
}