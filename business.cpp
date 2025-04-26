#include "business.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>  // For numeric limits

// Funct. to get business by ID
bool getBusiness(int id, Business& business) {
    std::ifstream file("businesses.txt");
    if (!file) {
        std::cout << "ERROR: Could not open file.\n";
        return false;
    }

    while (file >> business.id >> business.name) {
        if (business.id == id) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// Function to check if a business name already exists
bool isValidBusiness(const std::string& businessName) {
    std::ifstream file("businesses.txt");
    if (!file) {
        std::cout << "ERROR: Could not open file.\n";
        return false;
    }

    Business business;
    while (file >> business.id >> business.name) {
        if (business.name == businessName) {
            file.close();
            return true;  // Business was found
        }
    }
    file.close();
    return false;  // Business was not found
}

// Function to sign up a new business account
void signUpBusiness() {
    Business newBusiness;
    std::ofstream file("businesses.txt", std::ios::app);
    if (!file) {
        std::cout << "ERROR: Could not open file.\n";
        return;
    }

    std::srand(std::time(0));
    newBusiness.id = std::rand() % 999999 + 100000;  // Generate random 6-digit business ID
    std::cout << "Please enter the name of your business: ";
    std::cin.ignore();
    std::getline(std::cin, newBusiness.name);

    // Check if the business name already exists
    if (isValidBusiness(newBusiness.name)) {
        std::cout << "Sorry, this business already exists in our database.\n";
        return;
    }


    // Save the new business information to the file
    file << newBusiness.id << " " << newBusiness.name << " " << std::endl;
    std::cout << "You have signed up to the shop successfully. Your ID: " << newBusiness.id << "\nHappy shopping!" << std::endl;

    file.close();
}

// Function for existing business login
Business logInBusiness() {
    int id;
    Business business;
    business.userType = BusinessUserType;

    std::cout << "Please enter your business account ID number: ";
    std::cin >> id;

    if (getBusiness(id, business)) {
        std::cout << "Welcome " << business.name << " (ID: " << business.id << ")! ";
    }
    else {
        std::cout << "Business account with ID " << id << " not found.\n";
    }
    return business;
}