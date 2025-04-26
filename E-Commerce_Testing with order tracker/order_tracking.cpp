#include "order_tracking.h"
#include <iostream>   // For console output
#include <fstream>    // For file handling
#include <map>        // For tracking item purchase counts

using namespace std;

// Function to record an order in "orders.txt"
void addOrder(Item* item, Buyer buyer) {
    ofstream ofs("orders.txt", ios::app);  // Open file in append mode to preserve existing orders

    if (!ofs) {  // Check if file opened successfully
        cout << "Error opening orders.txt for writing!" << endl;
        return;
    }

    // Write order details to file
    ofs << "Item ID: " << item->id
        << "\nSupplier: " << item->supplier
        << "\nBuyer ID: " << buyer.id << "\n\n";

    ofs.close();  // Close file after writing
}

// Function to count how many times each item has been purchased
map<string, int> getOrderCounts() {
    ifstream ifs("orders.txt");  // Open file for reading
    map<string, int> orderCounts;  // Map to store item purchase counts
    string line, itemID;

    if (!ifs) {  // Check if file opened successfully
        cout << "Error opening orders.txt for reading!" << endl;
        return orderCounts;  // Return empty map
    }

    // Read file line by line
    while (getline(ifs, line)) {
        if (line.find("Item ID: ") == 0) {  // Look for lines containing item IDs
            itemID = line.substr(9);  // Extract item ID
            orderCounts[itemID]++;  // Increment count for this item
        }
    }

    ifs.close();  // Close file after reading
    return orderCounts;  // Return the map of item purchase counts
}

// Function to display order counts in the console
void displayOrderCounts() {
    map<string, int> orderCounts = getOrderCounts();  // Retrieve order counts

    if (orderCounts.empty()) {  // Check if there are no orders
        cout << "No orders have been recorded yet." << endl;
        return;
    }

    cout << "\nOrder Summary:\n";  // Print header

    // Loop through the map and print each item's purchase count
    for (const auto& pair : orderCounts) {
        cout << "Item ID: " << pair.first << " | Total Purchases: " << pair.second << endl;
    }
}
