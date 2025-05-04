#pragma once
//new
#include "Notifications.h"
#include <string>
#include <vector>

// user is a struct for buyer and business to inherit from
// contains enum UserType to ensure any user is guaranteed to have one of the types necessary for the ui

enum  UserType {
	BuyerUserType,
	BusinessUserType
};


struct User
{
	std::string name;
	int id;
	UserType userType;
	
	vector<Notification> notifications;
	
	//default constructor before a buyer or business is given their relevant data
	User() : name(""), id(-1)  {}
};
