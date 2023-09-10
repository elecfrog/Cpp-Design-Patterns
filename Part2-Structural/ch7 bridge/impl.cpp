//
// Created by elecfrog on 2023/8/31.
//
#include "Pimpl.h"

class Person::PersonImpl {
public:
    void greet(Person *p)
    {
        puts(p->name);
    }
    

};


Person::Person()
        : impl(new PersonImpl) {

}

Person::~Person() {
    delete impl;
}

void Person::greet() {
    impl->greet(this);
}


