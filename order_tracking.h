#pragma once
#include "item.h"
#include "buyer.h"
#include <map>
#include <string>

// Function to add an order to the order tracking file
void addOrder(Item* item, Buyer buyer);

// Function to get the count of each purchased item
std::map<std::string, int> getOrderCounts();

// Function to display order counts
void displayOrderCounts();
