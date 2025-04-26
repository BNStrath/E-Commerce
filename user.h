#pragma once

#include <string>

enum  UserType {
	BuyerUserType,
	BusinessUserType
};


struct User
{
	std::string name;
	int id;
	UserType userType;

	User() : name(""), id(-1)  {}
};
