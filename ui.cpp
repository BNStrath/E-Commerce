#include "item.h"
#include "business.h"
#include "buyer.h"
#include "login.h"
using namespace std;

int ui() {
	cout << "Welcome, are you customer or a business? (1/2)\n";
	char ans;
	cin >> ans;
	string usertype;
	if (ans == '1') {
		cout << "select:\n1.Login\n2sign up\n";
		cin >> ans;
		if (ans == '1') {
			Buyer user = logInBuyer();
			usertype = "buyer";
		}
		else if(ans == '2') {
			signUpBuyer();
			cout << "\nYou may now log in\n";
			Buyer user = logInBuyer();
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
		string filename = "itemData";
		Item::readData(items, filename);
		for (auto x : items) {
			x->print();
		}
		while (true) {
			char buyOrCart;
			cout << "Would you like to make a purchase or add to the cart? (1/2)\n";
			cin >> buyOrCart;
			if (buyOrCart != '1' || buyOrCart != '2') {
				cout << "invalid input";
				break;
			}
			cout << "\nEnter the id of the product you would like to purhcase:\n";
			string purchase_id;
			cin >> purchase_id;
			if (buyOrCart == '1') {
				for (auto x : items) {
					if (x->id == purchase_id) {
						
					}
				}
			}
			
		}

	}

	return 0;
}