#ifndef BUSINESS_H
#define BUSINESS_H

#include <string>
#include "user.h"

struct Business : User {
	
	Business()  = default;

	Business(std::string name, int id, UserType userType, vector<Notification> notifs) {};

};

// Function for business operations
bool getBusiness(int id, Business& business);
bool isValidBusiness(const std::string& businessName);
void signUpBusiness();
Business logInBusiness();
void getNotifs(Business& business);

#endif 