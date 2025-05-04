#include "item.h"
#include "business.h"
#include "buyer.h"
#include "shop.h"
#include "order_tracking.h"
#include "user.h"
#include "ui.h"

using namespace std;



int main() {

	// this section covers first question
	// determines wether the user is a buyer or a business and then wether they wish to log in or sign up as a new account
	// runs different functions depending on user input:
	// loginbuyer(), signupbuyer(), loginbusiness(), signupbusiness()

	vector<Item*> items;
	string filename = "itemData.txt";
	UserType usertype;
	Buyer customer;
	Business business;
	

	char ans = ' ';

	char loginAns = ' ';

	while (ans != '1' && ans != '2')
	{
		std::cout << "Welcome, are you customer or a business? (1/2)\n";
		std::cin >> ans;
	}

	if (ans == '1')
		usertype = BuyerUserType;
	else
		usertype = BusinessUserType;

	bool  userFound = false;
	while (loginAns != '1' && loginAns != '2' ) 
	{
		while(userFound == false)
		{

			std::cout << "select:\n1.Login\n2.sign up\n";
			std::cin >> loginAns;

			if (usertype == BuyerUserType) {
				if (loginAns == '1') {
					customer = logInBuyer();
				}
				else if (loginAns == '2') {
					signUpBuyer();
					std::cout << "\nYou may now log in\n";
					customer = logInBuyer();
				}
				else {
					std::cout << "\nInvalid output";			
					continue;
				}

				if (customer.id != -1) {
					userFound = true;
					usertype = BuyerUserType;
				}
			}

			if (usertype == BusinessUserType) {
				if (loginAns == '1') {
					business = logInBusiness();
				}
				else if (loginAns == '2') {
					signUpBusiness();
					std::cout << "\nYou may now log in\n";
					business = logInBusiness();
				}
				else {
					std::cout << "\nInvalid output";
				}

				if (business.id != -1) {
					userFound = true;
					usertype = BusinessUserType;
				}
			}
		}
	}


    // switch statement based on usertype defined in previous question
	// will take the user to the buyer or business side of the shop and
	// allow them access to the respective features
	switch (usertype)
	{
	case BuyerUserType:
		HandleBuyer(items, filename, customer);
		break;
	case BusinessUserType:
		HandleBusiness(items, filename, business);
		break;
	default:
		break;
	}


	Item::saveData(items, filename);
	return 0;
}

void HandleBusiness(std::vector<Item*>& items, std::string& filename, Business& business)
{

	// covers the shop options for a user logged in as a business
	// allows for adding products and services, adding to balance, viewing sales data on items and viewing notifications
	// loops until the user wishes to exit

	Item::readData(items, filename);
	for (auto x : items) {
		x->print();
	}
	while (true) {
		char optionSelect;
		std::cout << "\nWhat would you like to do?\n1.Create a new product/service\n2.Add to the stock of an item\n3.View item purchase data\n4.View Notifications\n5.Exit\n";
		std::cin >> optionSelect;
		if (optionSelect != '1' && optionSelect != '2' && optionSelect != '3' && optionSelect != '4' && optionSelect != '5') {
			std::cout << "\ninvalid selection, please try again\n";
		}
		if (optionSelect == '1') {
			char addedItem;
			std::cout << "\nWhat would you like to add?\n1.Product\n2.Service\n";
			std::cin >> addedItem;
			if (addedItem != '1' && addedItem != '2') {
				std::cout << "\nInvalid Selection\n";
			}
			if (addedItem == '1') {
				std::cout << business.name << endl;
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
			displayOrderCounts();
		}
		if (optionSelect == '4') {
			getNotifs(business);
		}
		if (optionSelect == '5') {
			break;
		}
	}
}

void HandleBuyer(std::vector<Item*>& items, std::string& filename, Buyer& customer)
{

	// includes all shop options for a user logged in as a buyer including:
	// purchase item: buys on of the items available
	// add to cart: stores items in a cart that can be bought collectively with purchase cart option
	// add to balance: adds to user's personal balance
	// view notifications: shows unread shipping notifications
	//
	// loops until the user exits

	vector<Item*> cart;
	string purchase_id;
	Item::readData(items, filename);
	while (true) {
		char buyOrCart;
		//new
		std::cout << "Would you like to make a purchase, add to the cart, add to your balance, view notifications, or exit? (1/2/3/4/5)\n";
		//new
		std::cin >> buyOrCart;

		if (buyOrCart != '1' && buyOrCart != '2' && buyOrCart != '3' && buyOrCart != '4' && buyOrCart != '5') {
			std::cout << "invalid input";
			continue;  // Keep prompting for valid input
		}

		if (buyOrCart == '1') {

			Item::printItems(items);
			std::cout << "\nEnter the id of the product you would like to purchase:\n";
			std::cin >> purchase_id;

			for (auto& x : items) {
				if (x->id == purchase_id) {
					int price;
					std::cout << "\nHow many would you like to purchase?\n";
					std::cin >> price;
					if (!price) {
						std::cout << "\ninvalid entry\n";
					}
					else {
						for (int i = 0; i < price; i++) {
							purchaseItem(x, customer);
						}
					}
					break;  // Exit the loop once the purchase is made
				}
			}
			bool check = false;
			for (auto& x : items) {
				if (x->id == purchase_id) {
					check = true;
				}
			}
			if (check == false) {
				std::cout << "\nid entered does not match a product or service\n";
			}

		}
		else if (buyOrCart == '2') {

			Item::printItems(items);
			std::cout << "\nEnter the id of the product you would like to purchase:\n";
			std::cin >> purchase_id;

			for (auto x : items) {
				if (x->id == purchase_id) {
					int num;
					std::cout << "\nHow many would you like to purchase?\n";
					std::cin >> num;
					if (!num) {
						std::cout << "\ninvalid entry\n";
					}
					else {
						for (int i = 0; i < num; i++) {
							addToCart(cart, x);
						}
					}
					break;  // Exit the loop once the item is added to the cart
				}
			}
		}
		else if (buyOrCart == '3') {
			addBalance(customer);
		}
		//new
		else if (buyOrCart == '4') {
			getNotifs(customer);
		}
		else if (buyOrCart == '5') {
			break;  // Exit the entire shopping loop
		}

		// Only ask for the next set of options after the user is done with the current operation
		char optionSelect;
		std::cout << "select an option\n1.Continue Shopping\n2.Purchase Cart\n3.Delete an item from the cart\n4.Exit Shop\n";
		std::cin >> optionSelect;

		if (optionSelect != '1' && optionSelect != '2' && optionSelect != '3' && optionSelect != '4') {
			std::cout << "\ninvalid input, please select again:\n";
			std::cin >> optionSelect;
		}

		if (optionSelect == '2') {
			if (cart.empty()) {
				std::cout << "Your cart is empty. Add items to your cart before purchasing.\n";
			}
			else {
				for (auto& x : cart) {
					// Purchase each item in the cart
					purchaseItem(x, customer);
				}
				cart.clear();  // Clear the cart after purchasing all items
			}
		}

		else if (optionSelect == '3') {
			string id;
			std::cout << "\nselect the id of the item you would like to delete\n:";
			std::cin >> id;
			deleteFromCart(cart, id);
		}
		else if (optionSelect == '4') {
			break;  // Exit the shopping process
		}
	}
}
