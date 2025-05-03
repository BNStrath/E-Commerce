#include "business.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>  // For numeric limits

// Funct. to get business by ID
//bool getBusiness(int id, Business& business) {
//    std::ifstream file("businesses.txt");
//    if (!file) {
//        std::cout << "ERROR: Could not open file.\n";
//        return false;
//    }
//
//    int notif_num;
//
//    while (file >> business.id >> business.name) {
//        file >> notif_num;
//        vector<Notification> notifs;
//
//        for (int i = 0;i < notif_num;i++) {
//            Notification notif;
//            file >> notif.read >> notif.text;
//            notifs.push_back(notif);
//        }
//
//        business.notifications = notifs;
//
//        if (business.id == id) {
//            file.close();
//            return true;
//        }
//    }
//    file.close();
//    return false;
//}

bool getBusiness(int id, Business& business) {
    int notif_num;
    bool found = false;

    std::ifstream file("businesses.txt");

    if (!file) {
        std::cout << "ERROR opening file!\n";
        return false;
    }

    try
    {
        // loop and look for the record untill we reach eof.
        int readCount = 0;
        while (!found)
        {
            Business tempBusiness;

            ReadRecord(file, tempBusiness);

            readCount++;

            found = (tempBusiness.id == id);

            if (found)
            {
                business.id = tempBusiness.id;
                business.name = tempBusiness.name;
                business.notifications = tempBusiness.notifications;
            }

            if (file.eof())
                break;
        }
    }
    catch (exception ex)
    {

    }

    file.close();
    return found;
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
    addBusiness(newBusiness);
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
    for (Notification& notif : business.notifications) {
        notif.readNotif();
        cout << endl;
    }
    updateBusiness(business);
}

void SaveBusinesses(std::vector<Business>& businesses)
{
    std::ofstream outputFile("businesses.txt");

    for (auto& business : businesses) {
        outputFile << business.id << " " << business.name << endl;

        int size = business.notifications.size();
        outputFile << size << endl;
        for (auto notif : business.notifications) {
            outputFile << notif.read << endl << notif.text << endl;
        }
    }

    outputFile.close();
}

void readBusinesses(std::vector<Business>& businesses) {
    ifstream ifs("businesses.txt");

    while (true) {
        Business tempBusiness;

        ReadRecord(ifs, tempBusiness);

        if (tempBusiness.id == -1)
            break;

        businesses.push_back(tempBusiness);

        if (ifs.eof())
            break;
    }

    ifs.close();
}

void updateBusiness(Business business) {
    std::ifstream ifs("businesses.txt");
    std::vector<Business> businesses;

    readBusinesses(businesses);

    //
    // Find the business and update
    //
    for (Business& loopBusiness : businesses)
    {

        if (loopBusiness.id == business.id)
        {
            loopBusiness.name = business.name;
            loopBusiness.notifications = business.notifications;
        }

    }

    // Save Changes
    SaveBusinesses(businesses);
}

void addBusiness(Business business)
{
    std::vector<Business> businesses;

    // Read businesses from file
    readBusinesses(businesses);

    businesses.push_back(business);

    // Save Changes
    SaveBusinesses(businesses);
}

void ReadRecord(std::ifstream& file, Business& business)
{
    int notif_num = 0;

    // read the business
    file >> business.id >> business.name;

    // read the notifications   
    file >> notif_num;

    for (int i = 0;i < notif_num;i++) {
        Notification notif;
        file >> notif.read;
        file.ignore();
        getline(file, notif.text);

        business.notifications.push_back(notif);
    }        
}

//use name to find business for shop function
//adds all businesses to a vector and matches supplier name to business in the data
Business findBusiness(string Businessname) {
    std::ifstream ifs("businesses.txt");
    std::vector<Business> businesses;
    Business business;
    business.id = -1;
    int notif_num;


    int readCount = 0;
    while (true)
    {
        Business business;
        ReadRecord(ifs, business);

        readCount++;

        
        if (business.id == -1)
            break;

        businesses.push_back(business);
        if (ifs.eof())
            break;
    }



    for (auto x : businesses) {
        if ( x.name == Businessname) {
            return x;
        }
    }

    return business;

    ifs.close();
}