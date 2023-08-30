## Gamma Categorization

Creation Patterns
Deal with creation of objects
Explicit (Constructor) vs.Implicit(DI, relection, etc..)

Structural Pattens
Concerned with the structure, class members
wrappers, interfaces, API design

Behavioral Patterns
No central theme, for specific problem

## Builder Pattern

The main idea is piecewise building, piece by piece, children by children, block by block avoid the directly touching
from detail and the abstraction.

Make a detailed object like `BVH` Animation file, or `HTMLElement` here.

Make a build wrapper to execuate and wrapper methods of the real objects.

Keep the consistency of some key APIs, like `str()` in `HTMLElement` and `HTMLBuilder`.

```cpp
// Detail Object
string str(int indent = 0) const {
// ..
for (const auto &e: elements)
oss << e.str(indent + 1);

return oss.str();
}

// Builder
string str() const {
return root.str(); }
```

### Fluent Interface

```cpp
// void to start with
HtmlBuilder &add_child(const string &child_name, const string &child_text) {
HtmlElement e{
child_name, child_text
};
root.elements.emplace_back(e);
return *this;
}

// use this, we can directly call HtmlElement and ignore HtmlBuilder in the main code
static unique_ptr<HtmlBuilder> build(const string &root_name) {
return make_unique<HtmlBuilder>(root_name);
}

```

Besides

```cpp
HtmlElement e = HtmlElement::build("ul")->add_child("li", "hello").add_child("li", "world")
HtmlElement e = HtmlElement::build("ul")->add_child("li", "hello").add_child("li", "world").operator HtmlElement();
```

both lines are valid while register this function `operator HtmlElement() const { return root; }`

### InitializeList

```cpp

```

## Facet Builders

The thing I only want to talk about is `fact builders`.

When I seen the lecturer wrote the code of this pattern, my did not get anything, but what holy shit, why should I code
like this?

But I found this useful later when I slight changed this code, the only thing I do, is remove all builder `friend` class
identifier from the `Person` class.
And make PersonBuilder as the only services provider for person building process. It much mor better!

And I think it is quite useful when using something like database.

While I was reading a movie row. It has unicode, prefix and suffix. It could provide a mechanism, while inserting data,
while check the validation and text split or something. 

Another idea is not always use operator() to do implicit things. It will make the code confusing to readers.


TODO: Using Builder Pattern to write a modern toml reader.