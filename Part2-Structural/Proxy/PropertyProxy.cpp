#include <iostream>

template<typename T>
struct Property {
    T value;

    // constructor to set the initial value
    explicit Property(const T initialValue) {
        *this = initialValue;
    }

    // Implicit conversion operator
    operator T() {
        std::cout << "Implicitly Get the Value! \n";
        return value;
    }

    // Assignment operator
    T operator=(T newValue) {
        std::cout << "Assign the Value! \n";
        return value = newValue;
    }
};

// Creature class with two properties: strength and agility
struct Creature {
    Property<int> strength{10};
    Property<int> agility{5};
};

void propertyProxy() {
    Creature creature;
    creature.agility = 20;
    std::cout << creature.agility << std::endl;
}

int main() {
    propertyProxy();
    return 0;
}
