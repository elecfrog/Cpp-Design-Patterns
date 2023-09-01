#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <map>
#include <algorithm>
using namespace std;

class Person
{
  friend class ResponsiblePerson;
  int age;
public:
  Person(int age) : age(age) {}

  int get_age() const { return age; }
  void set_age(int age) { this->age=age; }

  string drink() const { return "drinking"; }
  string drive() const { return "driving"; }
  string drink_and_drive() const { return "driving while drunk"; }
};

struct ResponsiblePerson
{
  ResponsiblePerson(const Person &person) : person(person) {}

  int get_age() const { return person.age; }
  void set_age(int value) { person.age = value; }

  string drink() const {
    if (get_age() >= 18)
      return person.drink();
    else return "too young";
  }

  string drive() const {
    if (get_age() >= 16)
      return person.drive();
    else return "too young";
  }

  string drink_and_drive() const
  {
    return "dead";
  }

private:
  Person person;
};