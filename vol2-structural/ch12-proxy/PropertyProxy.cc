#include <iostream>

template<typename T>
struct Property {
    T value;

    explicit Property(const T initialValue) {
        *this = initialValue;
    }

    operator T() {
        std::cout << "Implicitly Get the Value! \n";
        return value;
    }

    T operator=(T newValue) {
        std::cout << "Assign the Value! \n";
        return value = newValue;
    }
};

// ===========================================

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
