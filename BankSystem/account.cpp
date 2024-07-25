#include "account.hpp"
#include "contact.hpp"
#include <iostream>
#include <limits>

int Account::nextID = 0;

Account::Account() : accountID(nextID++), accountName(""), accountBalance(0.0f), contactInfo(nullptr) {}

void Account::initialize() {
    std::cout << "Enter the name: ";
    std::getline(std::cin, accountName);
    std::cout << "Enter the balance: ";
    std::cin >> accountBalance;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Account::display() const {
    std::cout << "Account ID: " << accountID
              << "  Name: " << accountName
              << "  Balance: $" << accountBalance << std::endl;
    if (contactInfo) {
        std::cout << "+ Contact Information: " << *contactInfo << std::endl;
    }
}

Account& Account::operator+=(float deposit) {
    this->accountBalance += deposit;
    return *this;
}

Account& Account::operator-=(float withdrawal) {
    if (withdrawal <= this->accountBalance) {
        this->accountBalance -= withdrawal;
    } else {
        std::cout << "Insufficient balance.\n";
    }
    return *this;
}

std::ostream& Account::display(std::ostream& out) const {
    out << "Account ID: " << this->accountID
        << " Name: " << this->accountName
        << " Balance: $" << this->accountBalance;
    if (contactInfo) {
        out << "\n+ Contact Information: " << *contactInfo;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const Account& account) {
    return account.display(out);
}

void Account::withdraw(float amount) {
    if (amount <= accountBalance) {
        accountBalance -= amount;
    } else {
        std::cout << "Insufficient balance.\n";
    }
}

int Account::getID() const {
    return accountID;
}

std::string Account::getName() const {
    return accountName;
}

float Account::getBalance() const {
    return accountBalance;
}

void Account::applyDividend(float factor) {
    accountBalance *= factor;
}

void Account::addContactInfo() {
    contactInfo = std::make_shared<Contact>();
    contactInfo->initialize();
}
