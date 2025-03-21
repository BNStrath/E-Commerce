#ifndef BUSINESS_H
#define BUSINESS_H

#include <string>

struct Business {
    std::string businessNumber;
    std::string regNumber;
    double balance;
    std::string name;
    int id;
};

// Function for business operations
bool getBusiness(int id, Business& business);
bool isValidBusiness(const std::string& businessName);
void signUpBusiness();
void logInBusiness();

#endif 
