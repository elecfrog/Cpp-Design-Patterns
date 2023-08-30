#include <iostream>
#include <cstdio>
#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <memory>
#include "ch2/GrooveBuilder.h"
#include "ch2/my-facet-builders/PersonBuilder.h"

int main() {

    auto&& p = PersonBuilder::create()
            .lives().at("XXXX").in("XX").with_postcode("XXXX")
            .works().at("xxx").as_a("xxxx").earning(123)
            .getPerson();

    cout << p << endl;

}