# Factory Pattern

## What I Learnt
### Static Factory Methods
The `PointFactory` namespace in the `Geometry` code provides static methods to create `Point` objects using different representations:
```cpp
namespace PointFactory {
  static Point PointFromVector3(float x, float y) { ... }
  static Point PointFromPolar(float rho, float theta) { ... }
}
```

### Factory Method Pattern
The Factory Pattern provide interfaces for creating instances of a class, with its subclasses deciding which class to instantiate.
It promotes loose coupling, as the client doesn't need to know about the concrete class it is instantiating.
```cpp
// Base class representing a hot drink
struct HotDrink {
    ...
    // Virtual method to prepare the drink, needs to be implemented by concrete types.
    virtual void Prepare(int volume) = 0;
};

// Tea drink implementation
struct Tea : HotDrink {
    void Prepare(int volume) override { ... }
};

// Coffee drink implementation
struct Coffee : HotDrink {
    void Prepare(int volume) override { ... }
};
```

### Abstract Factory Pattern
The Abstract Factory Pattern provides an interface for creating families of related or dependent objects without specifying their concrete classes.

It helps in creating system families of related objects without needing to specify or know about the actual concrete classes being used.

The `HotDrinkFactory` provides a method for creating drinks. Concrete factories like `TeaFactory` and `CoffeeFactory` determine which type of drink to create.

```cpp
  struct HotDrinkFactory {
      virtual std::unique_ptr<HotDrink> MakeHotDrink() const = 0;
  };
  
  struct TeaFactory : HotDrinkFactory { ... }
  struct CoffeeFactory : HotDrinkFactory { ... }
```

#### Factory Method Pattern vs. Abstract Factory Pattern

They are both factories. They both aim to create instances. They are related.

#### Factory with Maps

Factory with Maps looks like follows. It holds a map storing the instances of factory objects. It is an optional optimization of code structure.

```cpp
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
```

## Factory vs Builder
- **Factory Pattern**: It focuses on creating a group of instances of objects. 
- **Builder Pattern**: It focuses on constructing a complex object step by step, and the final step will return the object.
- **Comparison**:
    - Factories are typically used when the creation is a one-step process. It simply returns a fully initialized object.
    - Builders are used when an object needs multiple steps to be created. It can be thought of as a multistep initialization.
- 
## Inspiration Future Work
It was general in the coding process, notice and remember whether should I use it!