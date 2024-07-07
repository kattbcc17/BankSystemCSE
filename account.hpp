//
//  account.hpp
//  BankSystem
//
//  Created by kattia contreras on 7/6/24.
//

#ifndef account_hpp
#define account_hpp

#include <string>
#include <iostream>

class Account {
private:
    static int nextID;
    int accountID;
    std::string accountName;
    float accountBalance;

public:
    Account();
    void initialize();
    void display() const;
    void deposit(float amount);
    void withdraw(float amount);
    void applyDividend(float factor); // Added for Part 4

    // Overloaded operators
    Account& operator+=(float deposit);
    Account& operator-=(float withdrawal);
    std::ostream& display(std::ostream& out) const;

    // Getters
    int getID() const;
    std::string getName() const;
    float getBalance() const;
};

// Declaration of the operator<< overload
std::ostream& operator<<(std::ostream& out, const Account& account);

#endif // account_hpp
