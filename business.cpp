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

    int notif_num;

    while (file >> business.id >> business.name) {
        file >> notif_num;
        vector<Notification> notifs;

        for (int i = 0;i < notif_num;i++) {
            Notification notif;
            file >> notif.read >> notif.text;
            notifs.push_back(notif);
        }

        business.notifications = notifs;

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

    int notif_num;

    Business business;
    while (file >> business.id >> business.name) {

        file >> notif_num;
        vector<Notification> notifs;

        for (int i = 0;i < notif_num;i++) {
            Notification notif;
            file >> notif.read >> notif.text;
            notifs.push_back(notif);
        }


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

void getNotifs(Business& business) {
    for (Notification notif : business.notifications) {
        notif.readNotif();
        notif.read = true;
    }
}



void updateBusiness(Business business) {
    std::ifstream ifs("buyers.txt");
    std::vector<Business> businesses;
    Business tempBuyer;
    int notif_num;


    while (ifs >> business.id >> business.name) {
        ifs >> notif_num;
        vector<Notification> notifs;

        for (int i = 0;i < notif_num;i++) {
            Notification notif;
            ifs >> notif.read >> notif.text;
            notifs.push_back(notif);
        }
        business.notifications = notifs;

        businesses.push_back(business);
    }

    ifs.close();

    std::ofstream outputFile("buyers.txt");

    for (auto& business : businesses) {
        outputFile << business.id << " " << business.name << " " << endl;
        outputFile << sizeof(business.notifications) << endl;
        for (auto notif : business.notifications) {
            outputFile << notif.read << notif.text << endl;
        }
    }

    outputFile.close();
}