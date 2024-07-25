#ifndef contact_hpp
#define contact_hpp

#include <iostream>
#include <string>

class Contact {
   private:
    std::string streetAddress;
    std::string city;
    std::string state;
    std::string zipCode;
    std::string phoneNumber;

   public:
    Contact();
    void initialize();
    void display(std::ostream& out) const;
};

std::ostream& operator<<(std::ostream& out, const Contact& contact);

#endif  // contact_hpp
