#pragma once

#include <string>
#include <iostream>

struct Person{
    // address
    std::string street_address, post_code, city;

    // employment
    std::string company_name, position;
    int annual_income = 0;

    Person() = default;

    Person(Person &&other) noexcept
            : street_address{std::move(other.street_address)},
              post_code{std::move(other.post_code)},
              city{std::move(other.city)},
              company_name{std::move(other.company_name)},
              position{std::move(other.position)},
              annual_income{other.annual_income} {
    }

    Person &operator=(Person &&other) {
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

    friend std::ostream &operator<<(std::ostream &os, const Person &obj) {
        using namespace std::literals;
        return os
                << "street_address: "s << obj.street_address
                << " post_code: "s << obj.post_code
                << " city: "s << obj.city
                << " company_name: "s << obj.company_name
                << " position: "s << obj.position
                << " annual_income: "s << std::to_string(obj.annual_income);
    }
};
