#pragma once

#include <utility>

#include "Person.h"

class PersonBuilder {
    Person p;
protected:
    Person &person;

    explicit PersonBuilder(Person &person)
            : person{person} {
    }

public:
    PersonBuilder() : person{p} {}

    static PersonBuilder create() {
        return PersonBuilder{};
    }

    Person getPerson() {
        return std::move(person);
    }

    // builder facets
    class PersonAddressBuilder lives();

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