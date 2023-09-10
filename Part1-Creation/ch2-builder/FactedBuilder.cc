#pragma once

#include <utility>
#include <string>
#include <iostream>

struct Person {
    // Address details
    std::string street_address, post_code, city;

    // Employment details
    std::string company_name, position;
    int annual_income = 0;

    // Default constructor
    Person() = default;

    // Move constructor
    Person(Person &&other) noexcept
            : street_address{std::move(other.street_address)},
              post_code{std::move(other.post_code)},
              city{std::move(other.city)},
              company_name{std::move(other.company_name)},
              position{std::move(other.position)},
              annual_income{other.annual_income} {
    }

    // Move assignment operator
    Person &operator=(Person &&other) noexcept {
        if (this == &other)
            return *this;
        street_address = std::move(other.street_address);
        post_code = std::move(other.post_code);
        city = std::move(other.city);
        company_name = std::move(other.company_name);
        position = std::move(other.position);
        annual_income = other.annual_income;
        return *this;
    }

    // Output stream operator for printing the details of a person
    friend std::ostream &operator<<(std::ostream &os, const Person &obj) {
        return os
                << "street_address: " << obj.street_address
                << " post_code: " << obj.post_code
                << " city: " << obj.city
                << " company_name: " << obj.company_name
                << " position: " << obj.position
                << " annual_income: " << std::to_string(obj.annual_income);
    }
};


class PersonBuilder {
    Person p;
protected:
    Person &person;

    explicit PersonBuilder(Person &person)
            : person{person} {
    }

public:
    PersonBuilder() : person{p} {}

    // Factory method to create a new PersonBuilder instance
    static PersonBuilder create() {
        return PersonBuilder{};
    }

    // Retrieves the constructed person object
    Person getPerson() {
        return std::move(person);
    }

    // Nested builder for address details
    class PersonAddressBuilder lives();

    // Nested builder for employment details
    class PersonJobBuilder works();
};


class PersonAddressBuilder : public PersonBuilder {
    using Self = PersonAddressBuilder;
public:
    explicit PersonAddressBuilder(Person &person)
            : PersonBuilder{person} {
    }

    Self &at(std::string street_address) {
        person.street_address = std::move(street_address);
        return *this;
    }

    Self &with_postcode(std::string post_code) {
        person.post_code = std::move(post_code);
        return *this;
    }

    Self &in(std::string city) {
        person.city = std::move(city);
        return *this;
    }
};


class PersonJobBuilder : public PersonBuilder {
    using Self = PersonJobBuilder;
public:
    explicit PersonJobBuilder(Person &person)
            : PersonBuilder{person} {
    }

    Self &at(std::string company_name) {
        person.company_name = std::move(company_name);
        return *this;
    }

    Self &as_a(std::string position) {
        person.position = std::move(position);
        return *this;
    }

    Self &earning(int annual_income) {
        person.annual_income = annual_income;
        return *this;
    }
};

// Define the nested builders
PersonAddressBuilder PersonBuilder::lives() {
    return PersonAddressBuilder(person);
}

PersonJobBuilder PersonBuilder::works() {
    return PersonJobBuilder{person};
}


bool Testing() {
    // Create a person object using the fluent interface
    Person p = PersonBuilder::create()
            .lives().at("BP").with_postcode("LS2").in("Leeds")
            .works().as_a("student").at("Uol").earning(0)
            .getPerson();

    std::cout << p << std::endl;
    return true;
}

int main() {
    return Testing();
}
