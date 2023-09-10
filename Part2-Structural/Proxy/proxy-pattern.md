# Proxy Patterns

The proxy pattern is a design pattern where a class represents and controls access to another class, effectively serving as a placeholder or surrogate for it, which can add additional functionalities, control access, or delay the creation of the original object until necessary.

## Property Proxy

### Smart Pointers

Smart Pointers in STL are implementations of proxy pattern. The implementation of "proxy", smart pointers overload operators for raw pointers so that smart pointers would behave as raw pointers, like, `*`, `->`, `bool()`, etc...

- `std::unique_ptr` could be seen a proxy of the raw pointer, and transfer a unique ownership.
  - My simple implementation in the `SmartPointer/UniquePtr`, with 3 versions
  - `UniquePtr` is a simple wrapper without deleter.
  - `UniqueDeletePtr` is a simple wrapper with deleter.
  - `UniqueDeletePtr` is a wrapper with deleter and use `std::tuple` for EBO optimize the size of the class. 
- `std::shard_ptr` and  `std::weak_ptr` could be seen a proxy of the raw pointer and a control block (Reference Count) 
    - My simple implementation in the `SmartPointer/SharedPtr`, with 4 Parts
    - `RefCount` could be seen a simulation of referencing count. It should be the most complex part in STL. I made much simplification. 
    - `SmartPtrBase` is the common parent class of `SharedPtr` (simulation of `std::shared_ptr`) and `ReadonlyPtr` (simulation of `std::weak_ptr`)
    - `SharedPtr` could be seen as a write/read smart pointer, and it points to a common reference count that other pointers could also point to. 
    - `ReadonlyPtr` could be seen as a readonly smart pointer, it could not modify the pointer data inside, but modify the "weak", reference count inside. While the "weak "reference count, The reference count will destroy itself after.

### Simple Property Proxy Example

Here is another example of proxy attributes, could be implemented like this way:

```cpp
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

struct Creature {
    Property<int> strength{10};
    Property<int> agility{5};
};

void propertyProxy() {
    Creature creature;
    creature.agility = 20;
    std::cout << creature.agility << std::endl;
}
```

The `Property` class, could be seen as the real manager of the raw data, here the raw data type is int.

The data type was wrapped in a template. and Usage like `Property<int> strength{10}`. And it must be initialized at
first, cuz it was a specialized data type.

So run the `propertyProxy()`, `"Assign the Value"` would be printed three times! twice for initialing, one time for
assignment.

While print the attribute to the console, there is a implicit `operator()` was executed!

From this view, Proxy pattern is a powerful method to wrap a raw value, and give the wrapper class a right to directly
manipulating and make rules to the real data.

## Virtual Proxy

Virtual Proxy is a idea that I could hold the value while I need it, I use it and I still hold it.

```cpp
using namespace std;

struct Image {
    virtual ~Image() = default;

    virtual void draw() = 0;
};

struct Bitmap : Image {
    Bitmap(const string &filename) {
        cout << "Loading image from " << filename << endl;
    }

    void draw() override {
        cout << "Drawing image" << endl;
    }
};

struct LazyBitmap : Image {
    LazyBitmap(const string &filename) : filename(filename) {}

    ~LazyBitmap() { delete bmp; }

    void draw() override {
        if (!bmp)
            bmp = new Bitmap(filename);
        bmp->draw();
    }

private:
    Bitmap *bmp{nullptr};
    string filename;
};
```

### Dependency Injection Proxy
Here, the class of `ResponsiblePerson` ia a proxy of `Person`, while it provides protection and control for the raw `Person`.
```cpp
struct Person {
    int age;
    string drink() const { return "drinking"; }
    string drive() const { return "driving"; }
    string drink_and_drive() const { return "driving while drunk"; }
};

struct ResponsiblePerson {
    ResponsiblePerson(const Person &person) : person(person) {}

    string drink() const {
        if (person.age >= 18)
            return person.drink();
        else return "too young";
    }

    string drive() const {
        if (person.age >= 16)
            return person.drive();
        else return "too young";
    }

    string drink_and_drive() const {
        return "dead";
    }

private:
    Person person;
};
```

### Communication Proxy

Here is an example of Communication Proxy Example. Though I have little experience about network developement.
But as the code shows, it keep the API of `ping()`. `Pong()` is a local simulation and `RemtoePong()` depends on a
network communication.

```cpp
struct Pingable {
    virtual wstring ping(const wstring &message) = 0;
};

struct Pong : Pingable {
    wstring ping(const wstring &message) override {
        return message + L" pong";
    }
};

// ...

struct RemotePong : Pingable {
    wstring ping(const wstring &message) override {
        // ..NETWORK THINGS...
        return task.get();
    }
};
```

## Proxy vs. Decorator

They both provide extra functionalities and controls for the original classes by creating a class wrapper. 

**Proxy** 

- Keep the original interface, and change the functionality.

**Decorator**

- Enhance an interface, and add the functionality.