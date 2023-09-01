/*
 * description: Abstract factory implementation
 * author@elecfrog
 */
#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>
#include <functional>

// Base class representing a hot drink
struct HotDrink {
    HotDrink() = default;

    virtual ~HotDrink() = default;

    // Virtual method to prepare the drink, needs to be implemented by concrete types.
    virtual void Prepare(int volume) = 0;
};

// Tea drink implementation
struct Tea : HotDrink {
    void Prepare(int volume) override {
        std::cout << "Drink my Tea! " << volume << " and Put some stuff!\n";
    }
};

// Coffee drink implementation
struct Coffee : HotDrink {
    void Prepare(int volume) override {
        std::cout << "Drink my coffee! " << volume << " and Put some stuff!\n";
    }
};

// Base class for hot drink factories
struct HotDrinkFactory {
    // Virtual method to produce the drink, needs to be implemented by concrete factories.
    virtual std::unique_ptr<HotDrink> MakeHotDrink() const = 0;
};

// Tea factory implementation
struct TeaFactory : HotDrinkFactory {
    std::unique_ptr<HotDrink> MakeHotDrink() const override {
        return std::make_unique<Tea>();
    }
};

// Coffee factory implementation
struct CoffeeFactory : HotDrinkFactory {
    std::unique_ptr<HotDrink> MakeHotDrink() const override {
        return std::make_unique<Coffee>();
    }
};

// Factory for drinks which maintains a mapping of drink names to their respective factories
class DrinkFactory {
    std::unordered_map<std::string, std::unique_ptr<HotDrinkFactory>> hotDrinksFactories;
public:
    DrinkFactory() {
        hotDrinksFactories["coffee"] = std::make_unique<CoffeeFactory>();
        hotDrinksFactories["tea"] = std::make_unique<TeaFactory>();
    }

    // Make a drink based on its name
    std::unique_ptr<HotDrink> MakeHotDrink(const std::string &name) {
        auto drink = hotDrinksFactories[name]->MakeHotDrink();
        drink->Prepare(200);
        return drink;
    }
};

// Functional Factories
class DrinkFactoryLambda {
    std::unordered_map<std::string, std::function<std::unique_ptr<HotDrink>()>> hotDrinksFactories;
public:
    DrinkFactoryLambda() {
        hotDrinksFactories["tea"] = [] {
            auto drink = std::make_unique<Tea>();
            drink->Prepare(200);
            return drink;
        };

        hotDrinksFactories["coffee"] = [] {
            auto drink = std::make_unique<Coffee>();
            drink->Prepare(200);
            return drink;
        };
    }

    std::unique_ptr<HotDrink> MakeHotDrink(const std::string &name) {
        return hotDrinksFactories[name]();
    }
};


// Testing function for our hot drinks
bool Testing() {
    // Lambda to make a drink based on the type
    auto aCupOfCoffee = [](const std::string &type) {
        std::unique_ptr<HotDrink> drink;
        if (type == "tea") {
            drink = std::make_unique<Tea>();
            drink->Prepare(10);
        }

        if (type == "coffee") {
            drink = std::make_unique<Coffee>();
            drink->Prepare(50);
        }

        return drink;
    }("coffee");

    DrinkFactory drinkFactory;
    drinkFactory.MakeHotDrink("tea");

    DrinkFactoryLambda drinkFactoryLambda;
    drinkFactoryLambda.MakeHotDrink("tea");

    return true;
}

int main() {
    return Testing();
}