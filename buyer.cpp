#include "buyer.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>  // For numeric limits
#include <vector>


// Funct. to get a buyer by ID
//passes in one buyer as reference as well as id
//populates buyer with relevant data from file if a matching id is found
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
	}
}

void ReadFileHeader(std::ifstream& file, int& version)
{

	// read the file version from the head of the file 
	file >> version;

	//implemented for updating file format to avoid doing manually
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


void addBuyer(Buyer buyer)
{
	std::vector<Buyer> buyers;
	int version = 0;
	
	// Read Buyers from file
	version = readBuyersFromFile(buyers);

	buyers.push_back(buyer);

	// Save Changes
	SaveBuyers(version, buyers);
}



//for updating the data of 1 buyer in the file
//reads all buyers from file stores them in a vector and updates the detail of the intended buyer
//saves updated vector once finished
void updateBuyer(Buyer buyer) {

	int version = 0;

	std::vector<Buyer> buyers; // = GetBuyers();

	// Read Buyers from file
    version =readBuyersFromFile(buyers);

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
	
	// Save Changes
	SaveBuyers(version, buyers);
}

//reads all buyers from "buyers.txt" and stores them in a vector
int readBuyersFromFile( std::vector<Buyer>& buyers)
{
	int version = 0;
	std::ifstream ifs("buyers.txt");
	int notif_num;
	bool found = false;


	if (!ifs) {
		std::cout << "ERROR opening file!\n";
		return version;
	}

	ReadFileHeader(ifs, version);

	// loop and look for the record untill we reach eof.
	int readCount = 0;
	while (true)
	{
		Buyer tempBuyer;
		ReadRecord(version, ifs, tempBuyer);

		readCount++;

		if (ifs.eof())
			break;

		buyers.push_back(tempBuyer);
	}

	ifs.close();

	return version;
}

//passes in a vector of buyers and saves them into file
//version is passed in to allow different saving formats if the format is updated
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

	addBuyer(newBuyer);

	std::cout << "You have signed up successfully! Your ID: " << newBuyer.id << "\nYour current balance is: " << newBuyer.balance << "\nHappy shopping!" << std::endl;
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

//adds chosen amount to a logged in buyers balance
void addBalance(Buyer& buyer) {
	int num;
	std::cout << "\nYour current balance is: " << buyer.balance << ", how much would you like to add to your balance?\n";
	std::cin >> num;

	buyer.balance += num;
	updateBuyer(buyer);
}

//reads out unread notifications to logged in buyer
void getNotifs(Buyer& buyer) {
	for (Notification& notif : buyer.notifications) {
		notif.readNotif();
	}
	updateBuyer(buyer);
	cout << "\n";
}