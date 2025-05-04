#pragma once
#include <string>
#include <iostream>
using namespace std;

//notification used in business and buyer
//contains 2 elements:
//read: bool indicating if notification has been read or not
//text: contents of notification

struct Notification {
	bool read;
	string text;

	void readNotif() {
		if (!read) {
			cout << text;
			read = true;
			cout << "\n";
		}
	}
};