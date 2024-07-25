#include "contact.hpp"
#include <iostream>

Contact::Contact() : streetAddress(""), city(""), state(""), zipCode(""), phoneNumber("") {}

void Contact::initialize() {
    std::cout << "Enter Address: ";
    std::getline(std::cin, streetAddress);
    std::cout << "Enter City: ";
    std::getline(std::cin, city);
    std::cout << "Enter State: ";
    std::getline(std::cin, state);
    std::cout << "Enter Zip Code: ";
    std::getline(std::cin, zipCode);
    std::cout << "Enter Phone Number: ";
    std::getline(std::cin, phoneNumber);
}

void Contact::display(std::ostream& out) const {
    out << "Address: " << streetAddress << "\n"
        << "City: " << city << "\n"
        << "State: " << state << "\n"
        << "Zip: " << zipCode << "\n"
        << "Phone: " << phoneNumber << "\n";
}

std::ostream& operator<<(std::ostream& out, const Contact& contact) {
    contact.display(out);
    return out;
}
