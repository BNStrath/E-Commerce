#include "buyer.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>  // For numeric limits
#include <vector>


// Funct. to get a buyer by ID
bool getBuyer(int id, Buyer& buyer) {
     std::ifstream file("buyers.txt");

    if (!file) {
        std::cout << "ERROR opening file!\n";
        return false;
    }

    while (file >> buyer.id >> buyer.name >> buyer.age >> buyer.balance >> buyer.discount) {
        if (buyer.id == id) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void updateBuyer(Buyer buyer) {
    std::ifstream ifs("buyers.txt");
    std::vector<Buyer> buyers;
    Buyer tempBuyer;

    
    while (ifs >> tempBuyer.id >> tempBuyer.name >> tempBuyer.age >> tempBuyer.balance >> tempBuyer.discount) {
        
        if (tempBuyer.id == buyer.id) {
            tempBuyer.balance = buyer.balance;
        }        
        
        buyers.push_back(tempBuyer);
    }

    ifs.close();

    std::ofstream outputFile("buyers.txt");

    // for testing:
    //for (auto& buyer : buyers) {
    //    std::cout << "\n" << buyer.discount;
    //}
    
    for (auto& buyer : buyers) {
        outputFile << buyer.id << " " << buyer.name << " " << buyer.age << " " << buyer.balance << " " << buyer.discount << std::endl;
    }

    outputFile.close();
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
    }

    newBuyer.balance = 0;
    std::cout << "Your initial balance for your account is 0\n";

    newBuyer.discount = 1;
    char askDiscount;

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
            std::cout << "would you like to purchase a premium account? (costs 20, reduces price of all purchases by 10%) (y/n)\n";
            std::cin >> askDiscount;
            if (deposit < 20) {
                std::cout << "insufficient funds, premium account has not been applied\n";
            }
            else if (askDiscount == 'y') {
                newBuyer.discount = 0.9;
                "premium account applied\n";
            }
            else { std::cout << "premium account has not been applied\n"; }
            break;  // Exit the loop if valid amount is deposited
        }
    }

    newBuyer.balance += deposit;

    // Save the new buyer data to the txt file
    file << newBuyer.id << " " << newBuyer.name << " " << newBuyer.age << " " << newBuyer.balance << " " << newBuyer.discount << std::endl;
    std::cout << "You have signed up successfully! Your ID: " << newBuyer.id << "\nYour current balance is: £" << newBuyer.balance << "\nHappy shopping!" << std::endl;

    file.close();
}

// Funct. for existing buyer login
Buyer logInBuyer() {
    int id = 0;
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
        std::cout << "\nYour current balance is: " << buyer.balance << std::endl;
        return buyer;
    }
    else {
        std::cout << "Buyer with ID " << id << " not found.\n";
    }

    return Buyer{"", -1, BuyerUserType, 0, 0 , 0};
}

void addBalance(Buyer& buyer) {
    int num;
    std::cout << "\nYour current balance is: " << buyer.balance << ", how much would you like to add to your balance?\n";
    std::cin >> num;

    buyer.balance += num;
    updateBuyer(buyer);
}
