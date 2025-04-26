#pragma once
#include "item.h"
#include "buyer.h"

void addToCart(vector<Item*> items, Item* item);
void deleteFromCart(vector<Item*> items, string id);
void purchaseItem(Item* item, Buyer& buyer);