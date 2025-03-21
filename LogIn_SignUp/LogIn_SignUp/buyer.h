#ifndef BUYER_H
#define BUYER_H

#include <string>

struct Buyer {
    int id;
    int age;
    double balance;
    std::string name;
};

// Function for buyer operations
bool getBuyer(int id, Buyer& buyer);
void signUpBuyer();
void logInBuyer();

#endif 
