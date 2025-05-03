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

void updateBusiness(Business business);
void getNotifs(Business& business);
void ReadRecord(std::ifstream& file, Business& business);
void readBusinesses(std::vector<Business>& businesses);
void SaveBusinesses(std::vector<Business>& businesses);
Business findBusiness(string Businessname);
void addBusiness(Business business);

#endif 