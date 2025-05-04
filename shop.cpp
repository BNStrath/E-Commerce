#include "shop.h"
#include "order_tracking.h"


// passes in cart vector and item to be added to cart
// pushes item to the back of the cart
void addToCart(vector<Item*>& items, Item* item) {
	items.push_back(item);
}

// user selects an item they wish to delete from cart by id
// deletes all items in the cart with that id
// loops pushing relevant item to the back of the vector and removing with pop() function
void deleteFromCart(vector<Item*> items, string id) {
	for (Item* item : items) {
		if (item->id == id) {
			items.push_back(item);
			items.pop_back();
		}
	}
}

// purchases one item
// handles shipping and notifying buyer and busienss of purchase
void purchaseItem(Item* item, Buyer& buyer) {

    // dynamic cast to determine wether item passed in is a product or service
    // if cast is completed determines the appropriate code is executed for product or service 

    Product* product = dynamic_cast<Product*>(item);
    Service* service = dynamic_cast<Service*>(item);


    //prompts user to enter delivery address for item purchasses
    string shippingLabel;
    cout << "Enter delivery address:\n";
    cin.ignore();
    getline(cin, shippingLabel);

    if (product) {
        // check buyer has sufficient balance for purchase
        if (buyer.balance >= product->price && product->stock > 0) {
            buyer.balance -= product->price;
            product->stock--;
            cout << "Purchase successful! Remaining balance: " << buyer.balance << endl;

            //Buyer Section
            // create notification for purchase and record order
            Notification notif;
            notif.read = 0;
            notif.text = "Order: " + product->itemName + " Item has been shipped!";
            buyer.notifications.push_back(notif);
            updateBuyer(buyer);
            addOrder(product, buyer, shippingLabel);
            //

            //Business Section
            //create notification for business
            Notification businessNotif;
            businessNotif.read = 0;
            businessNotif.text = "Your product: " + product->itemName + " has been ordered!";
            Business business;
            business = findBusiness(product->supplier);
            if (business.id == -1) {
                cout << "\ncouldn't find business";
                return;
            }
            business.notifications.push_back(businessNotif);
            updateBusiness(business);
        }
        else {
            cout << "Purchase failed: Insufficient funds or stock.\n";
        }
    }
    else if (service) {
        if (buyer.balance >= service->fee) {
            buyer.balance -= service->fee;
            cout << "Service purchased successfully! Remaining balance: " << buyer.balance << endl;
            

            //Buyer Section
            Notification notif;
            notif.read = 0;
            notif.text = "Order: " + service->itemName + ", Service has been confirmed!";
            buyer.notifications.push_back(notif);
            updateBuyer(buyer);
            addOrder(service, buyer, shippingLabel);
            //

            //Business Section
            Notification businessNotif;
            businessNotif.read = 0;
            businessNotif.text = "Your service: " + service->itemName + " has been ordered!";
            Business business;
            business = findBusiness(service->supplier);
            if (business.id == -1) {
                cout << "\ncouldn't find business";
                return;
            }
            business.notifications.push_back(businessNotif);
            updateBusiness(business);
        }
        else {
            cout << "Purchase failed: Insufficient funds.\n";
        }
    }
}