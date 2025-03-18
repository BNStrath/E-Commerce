#include <iostream>
#include "business.h"
#include "buyer.h"
#include "login.h"

int loginOrSignup() {
    int choice;
    while (true) {
        std::cout << "What would you like to do?\n";
        std::cout << "1. Business account login/signup\n";
        std::cout << "2. Buyer account login/signup\n";
        std::cout << "Please select 1 or 2: ";
        std::cin >> choice;

        if (choice == 1) {
            int accountChoice;
            std::cout << "1. Business log in\n2. Business sign up\n";
            std::cout << "Choose option: ";
            std::cin >> accountChoice;

            if (accountChoice == 1) {
                logInBusiness();
                break;
            }
            else if (accountChoice == 2) {
                signUpBusiness();
                break;
            }
            else {
                std::cout << "Invalid option, please choose 1 or 2.\n";
            }
        }
        else if (choice == 2) {
            int accountChoice;
            std::cout << "1. Buyer log in\n2. Buyer sign up\n";
            std::cout << "Choose option: ";
            std::cin >> accountChoice;

            if (accountChoice == 1) {
                logInBuyer();
                break;
            }
            else if (accountChoice == 2) {
                signUpBuyer();
                break;
            }
            else {
                std::cout << "Invalid option, please choose 1 or 2.\n";
            }
        }
        else {
            std::cout << "Invalid option, please choose 1 or 2.\n";
        }
    }
    return 0;
}
