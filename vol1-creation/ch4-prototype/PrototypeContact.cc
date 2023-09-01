#pragma once

#include <string>
#include <ostream>
#include <memory>
#include <utility>
#include <iostream>

// Represents a physical address.
struct Address {
    std::string street, city;
    int suite;

    // Construct an address with the given street, city, and suite number.
    Address(std::string street, std::string city, int suite)
            : street(std::move(street)), city(std::move(city)), suite(suite) {
    }

    // Copy constructor for Address.
    Address(const Address &other) = default;

    // Overload the << operator for easy printing of Address.
    friend std::ostream &operator<<(std::ostream &os, const Address &address) {
        os << "street: " << address.street << " city: " << address.city << " suite: " << address.suite;
        return os;
    }
};

// Represents a person's contact information.
struct Contact {
    std::string name;
    Address *address;

    // Construct a contact with the given name and address.
    Contact(std::string name, Address *address) : name(std::move(name)), address(address) {}

    // Copy constructor for Contact. It clones a new Address for the new Contact.
    Contact(const Contact &other) : name(other.name), address(new Address{*other.address}) {}

    // Destructor to clean up the dynamically allocated memory.
    virtual ~Contact() {
        delete address;
    }

    // Overload the << operator for easy printing of Contact.
    friend std::ostream &operator<<(std::ostream &os, const Contact &contact) {
        os << "name: " << contact.name << " address: " << *contact.address;  // Note: Dereferencing the address pointer.
        return os;
    }
};

// Provides methods to create Employee contacts.
struct EmployeeFactory {
    // Creates a new employee with the given name and suite number for the main office.
    static std::unique_ptr<Contact> newMainOfficeEmployee(
            const std::string &name, int suite) {
        static Contact p{"", new Address{"ABC", "Leeds", 0}};
        return NewEmployee(name, suite, p);
    }

private:
    // Private method to create a new employee based on a prototype contact.
    static std::unique_ptr<Contact> NewEmployee(
            const std::string &name, int suite, const Contact &prototype) {
        auto ret = std::make_unique<Contact>(prototype);
        ret->name = name;
        ret->address->suite = suite;
        return ret;
    }
};

// Global contact for demonstration.
Contact g{"John Doe", new Address{"BP", "Leeds", 12}};

// Test function to validate the functionality.
bool Testing() {

    Contact john{"John Doe", new Address{"ABC", "Leeds", 0}};
    Contact jane{john};
    Contact localContact{g};

    std::cout << john << "\n" << jane << "\n";
    std::cout << &john.address->street << "\n" << &jane.address->street << "\n";

    EmployeeFactory::newMainOfficeEmployee("Sparrow", 2);
    
    return true;
}

int main() {
    return Testing();
}