#pragma once

#include <memory>
#include <map>
#include <iostream>

// Enum to define the importance levels
enum class Importance {
    Primary,
    Secondary,
    Tertiary
};

// Multiton pattern template class.
// It ensures a class has only one instance for each key of a given type.
template<typename T, typename Key = std::string>
class Multiton {
public:
    // Static method to get an instance of the Multiton pattern.
    // Creates a new one if it doesn't exist for the given key.
    static std::shared_ptr<T> get(const Key &key) {
        auto item = instances.find(key);
        if (item != instances.end()) {
            return item->second;
        }

        auto instance = std::make_shared<T>();
        instances[key] = instance;
        return instance;
    }

protected:
    // Protected constructor to prevent direct instantiation
    Multiton() = default;

    // Virtual destructor to enable derived classes to clean up
    virtual ~Multiton() = default;

private:
    // A static map to store the single instances for each key
    static std::map<Key, std::shared_ptr<T>> instances;
};

template<typename T, typename Key>
std::map<Key, std::shared_ptr<T>> Multiton<T, Key>::instances;

// Example class to demonstrate the Multiton pattern
class Printer {
public:
    Printer() {
        ++Printer::totalInstanceCount;
    }
    
    static int getCount() {return totalInstanceCount;}

private:
    static int totalInstanceCount;
};

int Printer::totalInstanceCount = 0;

bool Testing() {
    using mt = Multiton<Printer, Importance>;
    using mt_str = Multiton<Printer>;

    auto x = mt_str::get("sstring");
    std::cout << Printer::getCount() << "\n";
    auto main = mt::get(Importance::Primary);
    std::cout << Printer::getCount() << "\n";
    auto aux = mt::get(Importance::Secondary);
    std::cout << Printer::getCount() << "\n";
    auto aux2 = mt::get(Importance::Tertiary);
    std::cout << Printer::getCount() << "\n";

    return true;
}

int main()
{
    return Testing();
}