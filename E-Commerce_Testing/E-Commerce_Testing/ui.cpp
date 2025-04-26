#include "item.h"
#include "business.h"
#include "buyer.h"
#include "login.h"
#include "shop.h"
using namespace std;

int ui() {
	cout << "Welcome, are you customer or a business? (1/2)\n";
	char ans;
	cin >> ans;
	string usertype;
	Buyer customer;
	Business business;
	if (ans == '1') {
		cout << "select:\n1.Login\n2sign up\n";
		cin >> ans;
		if (ans == '1') {
			customer = logInBuyer();
			usertype = "buyer";
		}
		else if (ans == '2') {
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
		cin >> ans;
		if (ans == '1') {
			Business user = logInBusiness();
			usertype = "business";
		}
		else if (ans == '2') {
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
		vector<Item*> items;
		vector<Item*> cart;
		string filename = "itemData";
		Item::readData(items, filename);
		for (auto x : items) {
			x->print();
		}
		while (true) {
			char buyOrCart;
			cout << "Would you like to make a purchase, add to the cart, or neither? (1/2/3)\n";
			cin >> buyOrCart;
			if (buyOrCart != '1' && buyOrCart != '2' && buyOrCart != '3') {
				cout << "invalid input";
				break;
			}
			cout << "\nEnter the id of the product you would like to purhcase:\n";
			string purchase_id;
			cin >> purchase_id;
			if (buyOrCart == '1') {
				for (auto x : items) {
					if (x->id == purchase_id) {
						int price;
						cout << "\nHow many would you like to purchase?\n";
						cin >> price;
						if (!price) {
							cout << "\ninvalid entry\n";
						}
						else {
							for (int i = 0; i++; i < price) {
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
							for (int i = 0; i++; i < price) {
								addToCart(cart, x);
							}

						}

					}
				}
			}
			char optionSelect;
			cout << "select an option\n1.Continue Shopping\n2.Purchase Cart\n3.Delete an item from the cart\n4.Cancel Shop\n";
			cin >> optionSelect;
			if (optionSelect != ('1' || '2' || '3')) {
				cout << "\ninvalid input, please select again:\n";
				cin >> optionSelect;
			}
			if (optionSelect == '2') {
				for (auto x : cart) {
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
			return 0;
}