#include "program.hpp"
#include <algorithm>
#include <iostream>
#include <limits>
#include <list>  // For std::list
#include <numeric>
#include "account.hpp"

std::list<Account> accounts;  // List to store accounts

void displayMenu() {
    std::cout << "\nAccount Menu:\n";
    std::cout << "0. Quit Program\n";
    std::cout << "1. Display Account Information\n";
    std::cout << "2. Add a deposit to an account\n";
    std::cout << "3. Withdraw from an account\n";
    std::cout << "4. Add new account\n";
    std::cout << "5. Find account by ID\n";
    std::cout << "6. Remove account\n";                       
    std::cout << "7. Show total balance for all accounts\n";
    std::cout << "8. Add a dividend to all accounts\n";
    std::cout << "9. Add contact information to an account\n";
    std::cout << "10. Search for accounts by balance range\n";  // New option
    std::cout << "11. Transfer funds between accounts\n";       // New option
    std::cout << "Your choice: ";
}

// Function to find account by ID and return iterator
std::list<Account>::iterator findAccountByID(int id) {
    for (auto it = accounts.begin(); it != accounts.end(); ++it) {
        if (it->getID() == id) {
            return it;
        }
    }
    return accounts.end();  // Return end iterator if account not found
}

// Function to search accounts by balance range
void searchAccountsByBalanceRange(float minBalance, float maxBalance) {
    std::cout << "Accounts within balance range $" << minBalance << " - $" << maxBalance << ":\n";
    bool found = false;
    for (const auto& acc : accounts) {
        float balance = acc.getBalance();
        if (balance >= minBalance && balance <= maxBalance) {
            std::cout << acc << std::endl;  // Uses overloaded operator<<
            found = true;
        }
    }
    if (!found) {
        std::cout << "No accounts found within this balance range.\n";
    }
}

// Function to transfer funds between accounts
void transferFunds(int fromID, int toID, float amount) {
    auto fromIt = findAccountByID(fromID);
    auto toIt = findAccountByID(toID);

    if (fromIt != accounts.end() && toIt != accounts.end()) {
        if (fromIt->getBalance() >= amount) {
            *fromIt -= amount;  // Withdraw from the source account
            *toIt += amount;    // Deposit into the destination account
            std::cout << "Transfer successful.\n";
        } else {
            std::cout << "Insufficient funds in the source account.\n";
        }
    } else {
        std::cout << "One or both accounts not found.\n";
    }
}

int main() {
    int choice;
    float amount;

    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                        '\n');  // Clear input buffer

        switch (choice) {
            case 0:
                std::cout << "Exiting program.\n";
                break;
            case 1:
                if (accounts.empty()) {
                    std::cout << "No accounts to display.\n";
                } else {
                    std::cout << "All Accounts:\n";
                    for (const auto& acc : accounts) {
                        std::cout << acc
                                  << std::endl;  // Uses overloaded operator<<
                    }
                }
                break;
            case 2: {
                int id;
                std::cout << "Enter the ID of the account to deposit into: ";
                std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                '\n');

                auto it = findAccountByID(id);
                if (it != accounts.end()) {
                    std::cout << "Amount to deposit: ";
                    std::cin >> amount;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                    '\n');

                    *it += amount;
                } else {
                    std::cout << "Account not found.\n";
                }
            } break;
            case 3: {
                int id;
                std::cout << "Enter the ID of the account to withdraw from: ";
                std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                '\n');

                auto it = findAccountByID(id);
                if (it != accounts.end()) {
                    std::cout << "Amount to withdraw: ";
                    std::cin >> amount;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                    '\n');

                    *it -= amount;
                } else {
                    std::cout << "Account not found.\n";
                }
            } break;
            case 4: {  // Create a new scope for local variables
                Account newAccount;
                newAccount.initialize();  // Prompt user for account details
                accounts.push_back(newAccount);  // Add new account to the list
                std::cout << "Account added successfully.\n";
            } break;
            case 5: {
                int id;
                std::cout << "Enter the ID of the account to find: ";
                std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                '\n');

                auto it = findAccountByID(id);
                if (it != accounts.end()) {
                    std::cout << "Found account:\n";
                    std::cout << *it << std::endl;
                } else {
                    std::cout << "Account not found.\n";
                }
            } break;
            case 6: {
                int id;
                std::cout << "Enter account ID to remove: ";
                std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                '\n');

                auto newEnd = std::remove_if(
                    accounts.begin(), accounts.end(),
                    [id](const Account& acc) { return acc.getID() == id; });

                    accounts.erase(newEnd, accounts.end());
                    std::cout << "Account removed.\n";
            } break;
            case 7: {
                float total =
                    std::accumulate(accounts.begin(), accounts.end(), 0.0f,
                                    [](float acc, const Account& a) {
                                        return acc + a.getBalance();
                                    });

                std::cout << "Total in all accounts: $" << total << std::endl;
            } break;
            case 8: {
                float percentage;
                std::cout << "Enter the dividend as a percentage: ";
                std::cin >> percentage;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                '\n');

                float factor = (percentage / 100.0f) + 1.0f;

                std::transform(accounts.begin(), accounts.end(),
                               accounts.begin(), [factor](Account& acc) {
                                   acc.applyDividend(factor);
                                   return acc;
                               });

                std::cout << "Dividend added to all accounts.\n";
            } break;
            case 9: {
                int id;
                std::cout << "Enter the ID of the account to add contact information to: ";
                std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                auto it = findAccountByID(id);
                if (it != accounts.end()) {
                    it->addContactInfo();
                } else {
                    std::cout << "Account not found.\n";
                }
            } break;
            case 10: {
                float minBalance, maxBalance;
                std::cout << "Enter minimum balance: ";
                std::cin >> minBalance;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter maximum balance: ";
                std::cin >> maxBalance;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                searchAccountsByBalanceRange(minBalance, maxBalance);
            } break;
            case 11: {
                int fromID, toID;
                float amount;
                std::cout << "Enter the ID of the account to transfer from: ";
                std::cin >> fromID;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter the ID of the account to transfer to: ";
                std::cin >> toID;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter the amount to transfer: ";
                std::cin >> amount;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                transferFunds(fromID, toID, amount);
            } break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
