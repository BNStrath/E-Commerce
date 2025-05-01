#include "buyer.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>  // For numeric limits
#include <vector>


// Funct. to get a buyer by ID
bool getBuyer(int id, Buyer& buyer) {
	int notif_num;
	int version;
	bool found = false;

	std::ifstream file("buyers.txt");

	if (!file) {
		std::cout << "ERROR opening file!\n";
		return false;
	}

	try
	{

		ReadFileHeader(file, version);

		// loop and look for the record untill we reach eof.
		int readCount = 0;
		while (!found)
		{
			Buyer tempBuyer;

			ReadRecord( version, file, tempBuyer);

			readCount++;

			found = (tempBuyer.id == id);

			if (found)
			{
				buyer.id = tempBuyer.id;
				buyer.age = tempBuyer.age;
				buyer.balance = tempBuyer.balance;
				buyer.userType = tempBuyer.userType;
				buyer.discount = tempBuyer.discount;
				buyer.notifications = tempBuyer.notifications;
			}

			if (file.eof())
				break;
		}
	}
	catch (exception ex)
	{

	}

	file.close();
	return found;
}

void ReadRecord( int version, std::ifstream& file, Buyer& buyer)
{
	int notif_num = 0;

	// read the buyer
	file >> buyer.id >> buyer.name >> buyer.age >> buyer.balance >> buyer.discount;

	// read the notifications
	if (version >=1)
	{
		// Notifications added to buyer in version 1 of the buyer.text file
		file >> notif_num;

		for (int i = 0;i < notif_num;i++) {
			Notification notif;
			file >> notif.read;
			file.ignore();
			getline(file, notif.text);

			buyer.notifications.push_back(notif);
		}

		file.ignore();
	}
}

void ReadFileHeader(std::ifstream& file, int& version)
{

	// read the file version from the head of the file 
	file >> version;

	switch (version)
	{
	case 0:
		break;
	case 1:
		// new format
		break;
	default:
		break;
	}

	return;
}




/// <summary>
/// Who Ben Neill
/// 
/// When April 2025
/// 
/// Why
/// Access buyers data file and look up record
/// to update.
/// 
/// Save channges.
/// </summary>
/// <param name="buyer"></param>
void updateBuyer(Buyer buyer) {
	std::ifstream ifs("buyers.txt");
	std::vector<Buyer> buyers;

	int notif_num;
	bool found = false;

	int version = 0;

	ReadFileHeader(ifs, version);

	// loop and look for the record untill we reach eof.
	int readCount = 0;
	while (true)
	{
		Buyer tempBuyer;
		ReadRecord( version, ifs, tempBuyer);

		readCount++;

	/*	 update the record if found 
		found = (tempBuyer.id == buyer.id);
		if (tempBuyer.id == -1) {
			break;
		}
		if (found)
		{
			tempBuyer.balance = buyer.balance;	
			tempBuyer.notifications = buyer.notifications;
			tempBuyer.age = buyer.age;
			tempBuyer.discount = buyer.discount;
		}*/

		buyers.push_back(tempBuyer);
		if (ifs.eof())
			break;
	}


	

	ifs.close();



	//
	// Find the buyer and update
	//
	for(Buyer& loopBuyer : buyers)
	{

		if (loopBuyer.id == buyer.id)
		{
			loopBuyer.balance = buyer.balance;
			loopBuyer.notifications = buyer.notifications;
			loopBuyer.age = buyer.age;
			loopBuyer.discount = buyer.discount;
		}

	}

	// force file upgrade
	version = 1;

	// Save Changes
	SaveBuyers(version, buyers);
}

void SaveBuyers(int version, std::vector<Buyer>& buyers)
{
	std::ofstream outputFile("buyers.txt");

	outputFile << version << endl;

	for (auto& buyer : buyers) {
		outputFile << buyer.id << " " << buyer.name << " " << buyer.age << " " << buyer.balance << " " << buyer.discount << endl;

		if (version >= 1)
		{
			int size = buyer.notifications.size();
			outputFile << size << endl;
			for (auto notif : buyer.notifications) {
				outputFile << notif.read << endl << notif.text << endl;
			}
		}
	}

	outputFile.close();
}

// Funct. to sign up a new buyer 
void signUpBuyer() {
	Buyer newBuyer;
	std::ofstream file("buyers.txt", std::ios::app);  // Open in append mode

	if (!file) {
		std::cout << "Error opening file!" << std::endl;
		return;
	}

	std::srand(std::time(0));
	newBuyer.id = std::rand() % 999999 + 100000;  // Generate random 6-digit buyer ID

	std::cout << "Your ID number is: " << newBuyer.id << " Please remember this number for next time!\n";

	std::cout << "Enter your name: ";
	std::cin.ignore();  // To ignore leftover newline character
	std::getline(std::cin, newBuyer.name);

	std::cout << "Enter your age: ";
	std::cin >> newBuyer.age;
	if (newBuyer.age < 18) {
		std::cout << "You can only buy certain products because of your age. ";
	}

	newBuyer.balance = 0;
	std::cout << "Your initial balance for your account is 0\n";

	newBuyer.discount = 1;
	char askDiscount;

	double deposit;
	while (true) {
		std::cout << "How much money would you like to deposit initially? ";
		std::cin >> deposit;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter a valid number for the deposit.\n";
		}
		else if (deposit <= 0) {
			std::cout << "The deposit must be greater than 0.\n";
		}
		else {
			std::cout << "would you like to purchase a premium account? (costs 20, reduces price of all purchases by 10%) (y/n)\n";
			std::cin >> askDiscount;
			if (deposit < 20) {
				std::cout << "insufficient funds, premium account has not been applied\n";
			}
			else if (askDiscount == 'y') {
				newBuyer.discount = 0.9;
				"premium account applied\n";
			}
			else { std::cout << "premium account has not been applied\n"; }
			break;  // Exit the loop if valid amount is deposited
		}
	}

	newBuyer.balance += deposit;

	// Save the new buyer data to the txt file
	file << newBuyer.id << " " << newBuyer.name << " " << newBuyer.age << " " << newBuyer.balance << " " << newBuyer.discount << std::endl;
	std::cout << "You have signed up successfully! Your ID: " << newBuyer.id << "\nYour current balance is: £" << newBuyer.balance << "\nHappy shopping!" << std::endl;

	file.close();
}

// Funct. for existing buyer login
Buyer logInBuyer() {
	int id = 0;
	Buyer buyer;

	std::cout << "Please enter your buyer ID number: ";
	std::cin >> id;

	if (getBuyer(id, buyer)) {
		std::cout << "Welcome " << buyer.name << " (ID: " << buyer.id << ")! ";
		if (buyer.age < 18) {
			std::cout << "Due to your age, you are restricted from certain purchases.";
		}
		else {
			std::cout << "There are no restrictions on what you can buy.";
		}
		std::cout << "\nYour current balance is: " << buyer.balance << std::endl;
		return buyer;
	}
	else {
		std::cout << "Buyer with ID " << id << " not found.\n";
	}

	vector<Notification> notifications;
	return Buyer{ "", -1, BuyerUserType, notifications,  0, 0 , 0 };
}

void addBalance(Buyer& buyer) {
	int num;
	std::cout << "\nYour current balance is: " << buyer.balance << ", how much would you like to add to your balance?\n";
	std::cin >> num;

	buyer.balance += num;
	updateBuyer(buyer);
}

void getNotifs(Buyer& buyer) {
	for (Notification& notif : buyer.notifications) {
		notif.readNotif();
		cout << endl;
	}
	updateBuyer(buyer);
	cout << "\n";
}