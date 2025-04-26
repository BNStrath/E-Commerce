#ifndef BUYER_H
#define BUYER_H

#include <string>
#include "user.h"
#include <iostream>
#include <fstream>
#include <cstdlib>


struct Buyer : public User {
    int age;
    double balance;
    double discount;

    Buyer() = default;

    Buyer(std::string name, int id, UserType userType, int age, double balance, double discount) :  age(age), balance(balance), discount(discount) {};

    void writeToFile(std::ofstream file)
    {
        if (file.is_open()) {
            file << id <<  name <<  age  << balance <<  discount << std::endl;
        }  
    }
};

// Function for buyer operations
bool getBuyer(int id, Buyer& buyer);
void signUpBuyer();
Buyer logInBuyer();
void updateBuyer(Buyer buyer);
void addBalance(Buyer& buyer);


#endif 