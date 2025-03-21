#include "buyer.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>  // For numeric limits

// Funct. to get a buyer by ID
bool getBuyer(int id, Buyer& buyer) {
    std::ifstream file("buyers.txt");
    if (!file) {
        std::cout << "ERROR opening file!\n";
        return false;
    }

    while (file >> buyer.id >> buyer.name >> buyer.age >> buyer.balance) {
        if (buyer.id == id) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// Funct. to sign up a new buyer 
void signUpBuyer() {
    Buyer newBuyer;
    std::ofstream file("buyers.txt", std::ios::app);  // Open in append mode

    if (!file) {
        std::cout << "Error opening file!" << std::endl;
        return;
    }

    std::srand(std::time(0));
    newBuyer.id = std::rand() % 999999 + 100000;  // Generate random 6-digit buyer ID

    std::cout << "Your ID number is: " << newBuyer.id << " Please remember this number for next time!\n";

    std::cout << "Enter your name: ";
    std::cin.ignore();  // To ignore leftover newline character
    std::getline(std::cin, newBuyer.name);

    std::cout << "Enter your age: ";
    std::cin >> newBuyer.age;
    if (newBuyer.age < 18) {
        std::cout << "You can only buy certain products because of your age. ";
        return;
    }

    newBuyer.balance = 0;
    std::cout << "Your initial balance for your account is �0\n";

    double deposit;
    while (true) {
        std::cout << "How much money would you like to deposit initially? ";
        std::cin >> deposit;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid number for the deposit.\n";
        }
        else if (deposit <= 0) {
            std::cout << "The deposit must be greater than 0.\n";
        }
        else {
            break;  // Exit the loop if valid amount is deposited
        }
    }

    newBuyer.balance += deposit;

    // Save the new buyer data to the txt file
    file << newBuyer.id << " " << newBuyer.name << " " << newBuyer.age << " " << newBuyer.balance << std::endl;
    std::cout << "You have signed up successfully! Your ID: " << newBuyer.id << "\nYour current balance is: �" << newBuyer.balance << "\nHappy shopping!" << std::endl;

    file.close();
}

// Funct. for existing buyer login
void logInBuyer() {
    int id;
    Buyer buyer;

    std::cout << "Please enter your buyer ID number: ";
    std::cin >> id;

    if (getBuyer(id, buyer)) {
        std::cout << "Welcome " << buyer.name << " (ID: " << buyer.id << ")! ";
        if (buyer.age < 18) {
            std::cout << "Due to your age, you are restricted from certain purchases.";
        }
        else {
            std::cout << "There are no restrictions on what you can buy.";
        }
        std::cout << "\nYour current balance is: �" << buyer.balance << std::endl;
    }
    else {
        std::cout << "Buyer with ID " << id << " not found.\n";
    }
}
