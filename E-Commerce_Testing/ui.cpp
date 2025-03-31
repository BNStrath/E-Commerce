#include "item.h"
#include "business.h"
#include "buyer.h"
#include "login.h"
#include "shop.h"
using namespace std;

int main() {
	vector<Item*> items;
	string filename = "itemData.txt";
	cout << "Welcome, are you customer or a business? (1/2)\n";
	char ans;
	char loginAns;
	cin >> ans;
	string usertype;
	Buyer customer;
	Business business;
	if (ans == '1') {
		cout << "select:\n1.Login\n2sign up\n";
		cin >> loginAns;
		if (loginAns == '1') {
			customer = logInBuyer();
			if (customer.id == -1) {
				return 0;
			}
			usertype = "buyer";
		}
		else if (loginAns == '2') {
			signUpBuyer();
			cout << "\nYou may now log in\n";
			customer = logInBuyer();
			usertype = "buyer";
		}
		else {
			cout << "\nInvalid output";
		}
	}
	if (ans == '2') {
		cout << "select:\n1.Login\n2sign up\n";
		cin >> loginAns;
		if (loginAns == '1') {
			Business user = logInBusiness();
			usertype = "business";
		}
		else if (loginAns == '2') {
			signUpBusiness();
			cout << "\nYou may now log in\n";
			Business user = logInBusiness();
			usertype = "business";
		}
		else {
			cout << "\nInvalid output";
		}
	}

	if (usertype == "buyer") {
		vector<Item*> cart;
		string purchase_id;
		Item::readData(items, filename);
		while (true) {
			char buyOrCart;
			cout << "Would you like to make a purchase, add to the cart, add to your balance, or exit? (1/2/3/4)\n";
			cin >> buyOrCart;
			if (buyOrCart != '1' && buyOrCart != '2' && buyOrCart != '3' && buyOrCart != '4') {
				cout << "invalid input";
				break;
			}
			else {
				Item::printItems(items);
				cout << "\nEnter the id of the product you would like to purhcase:\n";
				cin >> purchase_id;
			};
			if (buyOrCart == '1') {
				for (auto& x : items) {
					if (x->id == purchase_id) {
						int price;
						cout << "\nHow many would you like to purchase?\n";
						cin >> price;
						if (!price) {
							cout << "\ninvalid entry\n";
						}
						else {
							for (int i = 0; i < price; i++) {
								purchaseItem(x, customer);
							}
						}

					}
				}
			}
			if (buyOrCart == '2') {
				for (auto x : items) {
					if (x->id == purchase_id) {
						int price;
						cout << "\nHow many would you like to purchase?\n";
						cin >> price;
						if (!price) {
							cout << "\ninvalid entry\n";
						}
						else {
							for (int i = 0; i < price; i++) {
								addToCart(cart, x);
							}

						}

					}
				}
			}
			if (buyOrCart == '3') {
				addBalance(customer);
			}
			if (buyOrCart == '4') {
				break;
			}
			char optionSelect;
			cout << "select an option\n1.Continue Shopping\n2.Purchase Cart\n3.Delete an item from the cart\n4.Cancel Shop\n";
			cin >> optionSelect;
			if (optionSelect != '1' && optionSelect != '2' && optionSelect != '3' && optionSelect != '4') {
				cout << "\ninvalid input, please select again:\n";
				cin >> optionSelect;
			}
			if (optionSelect == '2') {
				for (auto& x : cart) {
					purchaseItem(x, customer);
					break;
				}
			}
			if (optionSelect == '3') {
				string id;
				cout << "\nselect the id of the item you would like to delete\n:";
				cin >> id;
				deleteFromCart(cart, id);
			}
			if (optionSelect == '4') {
				break;
			}
		}
	}
	if (usertype == "business") {
		Item::readData(items, filename);
		for (auto x : items) {
			x->print();
		}
		while (true) {
			char optionSelect;
			cout << "\nWhat would you like to do?\n1.Create a new product/service\n2.Add to the stock of an item\n3.Exit\n";
			cin >> optionSelect;
			if (optionSelect != '1' && optionSelect != '2' && optionSelect != '3') {
				cout << "\invalid selection, please try again\n";
			}
			if (optionSelect == '1') {
				char addedItem;
				cout << "\nWhat would you like to add?\n1.Product\n2.Service\n";
				cin >> addedItem;
				if (addedItem != '1' && addedItem != '2') {
					cout << "\nInvalid Selection\n";
				}
				if (addedItem == '1') {
					items.push_back(Product::create(business));
				}
				if (addedItem == '2') {
					items.push_back(Service::create(business));
				}
			}
			if (optionSelect == '2') {
				Product::addStock(items, business);
			}
			if (optionSelect == '3') {
				break;
			}
		}
	}
	Item::saveData(items, filename);
	return 0;
}