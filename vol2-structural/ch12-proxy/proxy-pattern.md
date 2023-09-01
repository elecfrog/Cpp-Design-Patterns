foo.bar()

same process

but want to put all foo-related operations into a separate process

same interface, but entrily different behavior

communication proxy

## What I Learnt

### Smart Pointers and Raw Data Wrapper

Smart Pointers is a implementation of proxy pattern.
For example(MSVC C++17), the class of `std::shard_ptr` and  `std::weak_ptr`. They are both inhertanced from a _Ptr_base
class. While the _Ptr_base holds a raw pointer and the reference count.

```cpp
element_type* _Ptr{nullptr};
_Ref_count_base* _Rep{nullptr};
```

It looks like a simple wrapper, could be implemented like this way:

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

It might be useful, but I could not find a good example.

### Keep API but Change inside

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

Proxy 

- Keep an interface

Decorator

- Enhance an interface


*Note* Currently, for me, I prefer proxy, keeping much better inserting a lot of parameters...
    