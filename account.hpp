#ifndef account_hpp
#define account_hpp

#include <iostream>
#include <memory>
#include <string>
#include "contact.hpp"

class Account {
   private:
    static int nextID;
    int accountID;
    std::string accountName;
    float accountBalance;
    std::shared_ptr<Contact> contactInfo;

   public:
    Account();
    void initialize();
    void display() const;
    void deposit(float amount);
    void withdraw(float amount);
    void applyDividend(float factor);
    void addContactInfo();

    Account& operator+=(float deposit);
    Account& operator-=(float withdrawal);
    std::ostream& display(std::ostream& out) const;

    int getID() const;
    std::string getName() const;
    float getBalance() const;
    std::shared_ptr<Contact> getContactInfo() const;
};

std::ostream& operator<<(std::ostream& out, const Account& account);

#endif  // account_hpp
