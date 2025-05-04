#ifndef BUYER_H
#define BUYER_H

#include <string>
#include "user.h"
#include <iostream>
#include <fstream>
#include <cstdlib>


// Buyer usertype

struct Buyer : public User {
    int age;
    double balance;
    double discount;

    Buyer() = default;

    Buyer(std::string name, int id, UserType userType, vector<Notification>  notifications, int age, double balance, double discount) :  age(age), balance(balance), discount(discount) {};

    void writeToFile(std::ofstream file)
    {
        if (file.is_open()) {
            file << id <<  name <<  age  << balance <<  discount << std::endl;
            file << sizeof(notifications) << std::endl;
            for (Notification notif : notifications) {
                file << notif.read << notif.text;
            }
        }  
    }

    void readFromFile(std::ofstream file)
    {
        if (file.is_open()) {
            file << id << name << age << balance << discount << std::endl;
            file << sizeof(notifications) << std::endl;
            for (Notification notif : notifications) {
                file << notif.read << notif.text;
            }
        }
    }
};

// Function for buyer operations
bool getBuyer(int id, Buyer& buyer);
void addBuyer(Buyer buyer);
void ReadRecord(int version, std::ifstream& file, Buyer& buyer);
void ReadFileHeader(std::ifstream& file, int& version);
void signUpBuyer();
Buyer logInBuyer();
void updateBuyer(Buyer buyer);
int  readBuyersFromFile( std::vector<Buyer>& buyers);
void SaveBuyers(int version, std::vector<Buyer>& buyers);
void addBalance(Buyer& buyer);
void getNotifs(Buyer& buyer);


#endif 