#pragma once
#include <string>
#include <iostream>
using namespace std;

struct Notification {
	bool read;
	string text;

	static void readNotif(Notification notif) {
		if (notif.read == 0) {
			cout << "Order label: " << notif.text << ", Item has been shipped!\n";
		}
	}
};