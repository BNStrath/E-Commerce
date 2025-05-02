#pragma once
#include <string>
#include <iostream>
using namespace std;

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