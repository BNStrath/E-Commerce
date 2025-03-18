#include "item.h"

void addToCart(vector<Item*> items, Item* item) {
	items.push_back(item);
}

void deleteFromCart(vector<Item*> items, string id) {
	for (Item* item : items) {
		if (item->id == id) {
			items.push_back(item);
			items.pop_back();
		}
	}
}

void purchaseItem(Item* item) {

}