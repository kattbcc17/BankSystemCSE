//
//  account.cpp
//  BankSystem
//
//  Created by kattia contreras on 7/6/24.
//

#include "account.hpp"
#include "account.h"
#include <iostream>
#include <limits>

// Initialize the static member variable
int Account::nextID = 0;

// Constructor
Account::Account() : accountID(nextID++), accountName(""), accountBalance(0.0f) {}

// Method to prompt user for account details
void Account::initialize() {
    std::cout << "Enter the name: ";
    std::getline(std::cin, accountName);
    std::cout << "Enter the balance: ";
    std::cin >> accountBalance;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
}

// Method to display account information
void Account::display() const {
    std::cout << "Account ID: " << accountID
              << "  Name: " << accountName
              << "  Balance: $" << accountBalance << std::endl;
}

// Overloaded operator+= to add deposit
Account& Account::operator+=(float deposit) {
    this->accountBalance += deposit;
    return *this;
}

// Overloaded operator-= to subtract withdrawal
Account& Account::operator-=(float withdrawal) {
    if (withdrawal <= this->accountBalance) {
        this->accountBalance -= withdrawal;
    } else {
        std::cout << "Insufficient balance.\n";
    }
    return *this;
}

// Method to display account info via output stream
std::ostream& Account::display(std::ostream& out) const {
    out << "Account ID: " << this->accountID
        << " Name: " << this->accountName
        << " Balance: $" << this->accountBalance;
    return out;
}

// Overloaded operator<< to use display method
std::ostream& operator<<(std::ostream& out, const Account& account) {
    return account.display(out);
}

// Method to withdraw from account
void Account::withdraw(float amount) {
    if (amount <= accountBalance) {
        accountBalance -= amount;
    } else {
        std::cout << "Insufficient balance.\n";
    }
}

// Getters
int Account::getID() const {
    return accountID;
}

std::string Account::getName() const {
    return accountName;
}

float Account::getBalance() const {
    return accountBalance;
}

// Added for Part 4: Apply dividend to account
void Account::applyDividend(float factor) {
    accountBalance *= factor;
}
