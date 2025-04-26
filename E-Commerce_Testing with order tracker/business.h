#ifndef BUSINESS_H
#define BUSINESS_H

#include <string>

struct Business {
    std::string name;
    int id;
};

// Function for business operations
bool getBusiness(int id, Business& business);
bool isValidBusiness(const std::string& businessName);
void signUpBusiness();
Business logInBusiness();

#endif 