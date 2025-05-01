#pragma once
//new
#include "Notifications.h"
#include <string>
#include <vector>
//new

enum  UserType {
	BuyerUserType,
	BusinessUserType
};


struct User
{
	std::string name;
	int id;
	UserType userType;
	//new
	vector<Notification> notifications;
	//new

	User() : name(""), id(-1)  {}
};
