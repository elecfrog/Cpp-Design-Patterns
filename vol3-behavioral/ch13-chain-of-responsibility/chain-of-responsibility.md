# Chain of Responsibility(CoR) Pattern

Examples:
1. Button click and handle
2. buffer and damage computation formula

CoR a chain of component, each get a chance to process it.

### CoR using Pointer (Deprecated)

```cpp

struct Creature {
    string name;
    int attack, defense;
};

// singled linked list
class CreatureModifier {
    CreatureModifier *next{nullptr}; // unique_ptr
protected:
    Creature &creature; // pointer or shared_ptr
public:
    explicit CreatureModifier(Creature &creature)
            : creature(creature) {
    }

    void add(CreatureModifier *cm) {
        if (next) next->add(cm);
        else next = cm;
    }

    virtual void handle() {
        if (next) next->handle();
    }
};

class DoubleAttackModifier : public CreatureModifier {
    // ctor() ... 
    
    void handle() override {
        creature.attack *= 2;
        CreatureModifier::handle();
    }
};

class IncreaseDefenseModifier : public CreatureModifier {
    // ctor() ... 
    
    void handle() override {
        if (creature.attack <= 2)
            creature.defense += 1;
        CreatureModifier::handle();
    }
};

class NoBonusesModifier : public CreatureModifier {
    // ctor() ... 
    
    void handle() override {
    // stop the CoR
    }
};
```

The whole code based on a single linked list. 
But why don't we use `std::vector` or other things directly?
So, people don't use it anymore!

### CoR Broker by Qt signals-slots
This example in code, looks like a simple event passing path.

It totally implemented by Qt signals-slots method, rewrite from boost signals implementation.

So... Qt is perfect in implementing this design pattern?