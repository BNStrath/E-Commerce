#include "order_tracking.h"

void addOrder(Item* item, Buyer buyer) {
	ofstream ofs;
	ofs.open("orders.txt");
	ofs << "item: " << item->id << "\nsupplier: " << item->supplier << "\nBuyer: " << buyer.id << "\n";
}