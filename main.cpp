#include <fstream>
#include <iostream>
#include "Products.h"
#include "Datafile.h"
using namespace std;

int main() {
	vector<Product> products;
	Product::read(products);
	Product testprod;
	testprod = products.front();
	cout << testprod.supplier;
	Product::saveData(products);
	return 0;
}