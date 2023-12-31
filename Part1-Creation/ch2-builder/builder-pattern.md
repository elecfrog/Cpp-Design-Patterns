# Builder Pattern

## Introduction

It is pattern allows for the step-by-step(piecewise) creation of complex objects using the correct sequence of actions.
The construction is controlled by a director object, we call it as `builder`, which only needs to know the type of
object it is to create.

The main advantage of this pattern is to **decouple the process of construction and its data representation**.

In the `HTMLBuilder.cc`, I created a `HTMLElement` as the data representation and `HTMLBuilder` as the construction
instructor.
By the power of **Fluent Interface**, the building process looks very nicely.

```cpp
HtmlElement e = HtmlBuilder::BuildHTML("ul")
            ->addChild("li", "hello")
            ->addChild("li", "world")
            ->toHtmlElement();
```

## What I Learnt

### How to construct a Fluent Interface

Obviously, it is a trick to return a object in the class to support the next construction, it is simple, but quite
useful

```cpp
// A static function to initiate the building process, 
// remove from HtmlElement, cuz I don't like insert logic into data structures
static std::unique_ptr<HtmlBuilder> BuildHTML(const string &root_name) {
return std::make_unique<HtmlBuilder>(root_name);
}

// void to start with
HtmlBuilder *addChild(const string &childName, const string &childText) {
HtmlElement e{
childName, childText
};
root.elements.emplace_back(e);
return this;
}

// void to start with
HtmlBuilder *addChild(HtmlElement&& e) {
root.elements.emplace_back(std::move(e));
return this;
}
```

### `std::initializer_list`

An initializer list is used to initialize the elements of a container.
It's frequently seen in constructors to allow for easy setup, like `std::vector<int> v = {1, 2, 3, 4, 5}`;

When `std::initializer_list` as a function parameter, it could initialize the elements directly.

```cpp
P(std::initializer_list<Tag> children)
    : Tag("p", children) {
}

P{
      IMG{"https://pokemon.com/",},
      IMG{"https://www.pokemoncenter.com/",},
      CODE{"int x = 1", "language", "cpp"}
}
```

### Implicit `operator()`, "call operator", "function call operator"

The operator() is a special member function that allows an object of a class to be called like a function.
When you define the operator() for your class, you can specify parameters for it, allowing you to pass arguments when
you call the object as if it were a function.
This is useful for creating functor objects (objects that can be used as functions) which can maintain state across
several calls.

### Faceted Builders

Faceted Builders is broke down the process of construction of a complex object into different types.

In the example, one person could have address and job. So we can use a address builder and a job builder to decouple
the construction process of them. It looks helpful when the object has different parts, like construct am object from
database from major table and foreign tables.

The implementation in the example used interhanince solution to generate two classes. One for address and one for job
```cpp
class PersonBuilder {
    Person p;
protected:
    Person &person;
    // ...
    // builder facets
    class PersonAddressBuilder lives();
    class PersonJobBuilder works();
};

class PersonAddressBuilder : public PersonBuilder{ ... }; 
class PersonJobBuilder : public PersonBuilder{ ... };

PersonAddressBuilder PersonBuilder::lives() {
    return PersonAddressBuilder(person);
}

PersonJobBuilder PersonBuilder::works() {
    return PersonJobBuilder{person};
}
```

## Inspiration Future Work
- [ ] Using Builder Pattern to write a modern toml reader.
  - [ ] support XML Parsing Qt .qrc files into a toml
  - [ ] read toml into runtime, and extract path

- [ ] Using Builder Pattern to setup a GLSL shader building.

- [ ] Sparrow Renderer application building process!