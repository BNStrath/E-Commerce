#include "shop.h"
#include "order_tracking.h"

void addToCart(vector<Item*>& items, Item* item) {
	items.push_back(item);
}

void deleteFromCart(vector<Item*>& items, string id) {
	for (Item* item : items) {
		if (item->id == id) {
			items.push_back(item);
			items.pop_back();
		}
	}
}

void purchaseItem(Item* item, Buyer& buyer) {
    Product* product = dynamic_cast<Product*>(item);
    Service* service = dynamic_cast<Service*>(item);

    if (buyer.age < item->ageLim) {
        cout << "Age requirement not met for this product or Service" << endl;
        return;
    }

    if (product) {
        if (buyer.balance >= product->price && product->stock > 0) {
            buyer.balance -= (product->price * buyer.discount);
            product->stock--;
            cout << "Purchase successful! Remaining balance: " << buyer.balance << endl;
            addOrder(item, buyer);
            updateBuyer(buyer);
        }
        else {
            cout << "Purchase failed: Insufficient funds or stock.\n";
        }
    }
    else if (service) {
        if (buyer.balance >= service->fee) {
            buyer.balance -= (service->fee * buyer.discount);
            cout << "Service purchased successfully! Remaining balance: " << buyer.balance << endl;
            addOrder(item, buyer);
            updateBuyer(buyer);
        }
        else {
            cout << "Purchase failed: Insufficient funds.\n";
        }
    }
}