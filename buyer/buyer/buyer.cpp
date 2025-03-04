#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>  // For numeric_limits

using namespace std;

struct Buyer {
    int id;
    int age;
    double balance;
    string name;
};

//creating an account
void signUp() {
    Buyer newBuyer;
    ofstream file("buyers.txt", ios::app);  // Opens the file in append mode to prevent overwritng existing file.

    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    srand(time(0));
    newBuyer.id = rand() % 999999 + 100000;

    cout << "Your ID number is: " << newBuyer.id << "Please remember this number for when you come to log in next time! " <<"\n";

    cout << "Enter your name: ";
    cin.ignore();  // To ignore any leftover newline character in the buffer
    getline(cin, newBuyer.name);  // Read the full name (including spaces)

    cout << "Enter your age: ";
    cin >> newBuyer.age;
    if (newBuyer.age < 18) {
        cout << "You can only buy certain products because of your age. ";
        return;
    }

    newBuyer.balance = 0;
    cout << "Your initial balance for your account is £0 ";

    double deposit;
    while (true) {
        cout << "How much money would you like to deposit initially? ";
        cin >> deposit;

        // Check if the deposit is a valid number and greater than 0
        if (cin.fail()) {
            // Clear the error flag and ignore invalid input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number for the deposit.\n";
        }
        else if (deposit <= 0) {
            cout << "The deposit must be greater than 0.\n";
        }
        else {
            break;  // Exit loop if the deposit is valid
        }
    }

    newBuyer.balance += deposit;

    // Save the new buyer data to the file
    file << newBuyer.id << " " << newBuyer.name << " " << newBuyer.age << " " << newBuyer.balance << endl;
    cout << "You have signed up to the shop successfully. Your ID: " << newBuyer.id <<"\n"<< ". Your current balance is: £" << newBuyer.balance <<"\n" << ". Happy shopping!" << endl;

    file.close();  // Close the file
}

// Check if customer already exists
bool getBuyer(int id, Buyer& buyer) {
    ifstream file("buyers.txt");
    if (!file) {
        cout << "ERROR opening file!";
        return false;
    }

    while (file >> buyer.id >> buyer.name >> buyer.age >> buyer.balance) {
        if (buyer.id == id) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// Existing buyer log in 
void logIn() {
    int id;
    Buyer buyer;

    cout << "Please enter your buyer ID number: ";
    cin >> id;

    if (getBuyer(id, buyer)) {
        cout << "Welcome " << buyer.name << " (ID: " << buyer.id << ")! ";
        if (buyer.age < 18) {
            cout << "Due to your age, you are restricted from certain purchases.";
        }
        else {
            cout << "There are no restrictions on what you can buy.";
        }
        cout << "\nYour current balance is: £" << buyer.balance << endl;
    }
    else {
        cout << "Buyer with ID " << id << " not found." << endl;
    }
}

int main() {
    int choice;
    while (true) {
        cout << "What would you like to do?\n 1. Log in? \n 2. Sign up?\nPlease select 1 or 2: ";
        cin >> choice;

        if (choice == 1) {
            logIn();
            break;
        }
        else if (choice == 2) {
            signUp();
            break;
        }
        else {
            cout << "This option is not valid. Please select 1 or 2.\n";
        }
    }
    return 0;
}
