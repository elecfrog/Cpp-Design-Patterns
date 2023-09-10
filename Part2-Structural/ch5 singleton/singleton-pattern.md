# Singleton Pattern

Traditionally, the Singleton pattern is a creation pattern because it deals with how to create a single instance of a
class. However, in modern programming practices, the Singleton pattern is more about maintaining and managing a single,
globally accessible instance rather than just creating it. From this perspective, the core of the Singleton pattern is
no longer "creation" but "structure" and "management". Therefore, it has been reclassified as a structural pattern.

### Singleton and Logic Separation

Singleton, which is a pattern about the instance lifetime management.
But using the inheritance directly from the Singleton, it will integrate Singleton responsible and business requirements
of this Singleton class.
as follows:

```cpp
class SqliteDriver : public Singleton<SqliteDriver> {
public:
    // ...
    bool connect(const std::string &dbPath) override {
        // ... implementation of logic
    }
};
```

`connect` is a function from the Database but not `Singleton`.

We made the change of generating an interface

```cpp
class DatabaseDriver {
public:
    virtual bool connect(const std::string &dbPath) = 0;
};

// A fake sql
class DummyDatabase : public DatabaseDriver {
    bool connect(const std::string &dbPath) override { /* ... impl */ }
};
```

and multiple inheritance as follows:

```cpp
class SqliteDriver : public Singleton<SqliteDriver>, public DatabaseDriver {
public:
    bool connect(const std::string &dbPath) override { /* ... same implementation */ }
};
```

It could support the test for Singleton and business logic of the Database class.

### MonoState

Monostate is a bad idea, while multiple instances will share one state, it is implemented by introducing static
variables in the code. Here is an example of using Monostate.

```cpp
class Printer {
    static int id;
public:
    int getId() const { return id;}
    void setId(int value) { id - value; }
};
```

Because all instances of `Printer` class share `id`, it will make the code logic confusing.

It is better to prevent it in the class design.

### Multiton

One variant of Singleton Pattern is Multiton, which uses a `std::(unordered_)map` object stores static instances.

It is quite similar to Singleton Pattern.