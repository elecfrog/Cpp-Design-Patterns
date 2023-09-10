# Effective STL Reading Notes
STL doesn't have an official definition; it is a subset of the C++ standard library. Components typically included in the STL are containers, algorithms, and iterators.

The STL consists of several main parts:
- **Containers**: These are class templates used to store data. For example, `vector`, `list`, `deque`, `set`, etc.
- **Algorithms**: These are function templates used to perform specific tasks such as sorting or searching. For instance, `sort`, `find`, etc.
- **Iterators**: These are objects used to traverse containers. For example, `vector<int>::iterator`.
- **Function objects**: These are objects that can be used like functions, also known as functors.
- **Allocators**: These are objects used to control container memory allocation. It encompasses standard containers (including strings), a portion of the iostream library, function objects, and algorithms.

## Chapter I: Containers

### Item 1: Choose your containers with care

Containers are used to store and manage multiple data elements, which are generally divided into several types:

1. Standard STL sequence containers:
    - `vector`, `array`(C++11), `string`, `wstring`, `deque`, `forward_list`(C++11), and `list`.
    - Maintain the order of elements.
2. Standard STL associative containers:
    - `set`, `multiset`, `map`, `multimap`.
    - Automatically sort elements according to specific sorting criteria.
3. Standard STL unordered associative containers (From C++11):
    - `unordered_set`, `unordered_multiset`, `unordered_map`, `unordered_multimap`.
    - Do not guarantee the order of elements.
4. Container adaptors:
    - Implemented based on existing containers, offering a different interface or API. There are three types of container adaptors:
        - `stack`: offers a LIFO (Last In First Out) data structure.
        - `queue`: offers a FIFO (First In First Out) data structure.
        - `priority_queue`: offers a priority queue data structure.
5. Special containers:
    - `bitset`, `valarray`

### Item 2: Beware the illusion of container-independent code

Even though many STL containers share the same APIs (e.g., all STL containers have `begin()`, `end()`, `size()`, etc.), their performance characteristics can vastly differ.

Example: If you have an algorithm heavily reliant on random access, and you choose a list as your container, you'll find your algorithm is very slow because lists do not support fast random access. Conversely, if you opt for a vector, your algorithm will run much faster.

You can't instantiate your container with `bool` as the type of objects to store because, as explained in Item 18, `vector<bool>` doesn't always behave like a vector, and it never actually stores `bool`s. You cannot assume list insertions and deletions are constant time operations because vector and deque require linear time to perform these operations.

```cpp
vector<bool> vec{true, false, true, false, true};
bitset<5> bitset("10101");

// Accessing and modifying vector<bool>
vec[2] = false;
cout << "vector<bool>: ";
for (bool val : vec) {
    cout << val << " ";
}
cout << "\n";

// Accessing and modifying bitset
bitset[2] = false;
cout << "bitset: " << bitset << "\n";
```

### Item 5: Prefer range member functions to their single-element counterparts

This principle emphasizes that using member functions that can operate on a range of elements (i.e., multiple elements) is generally more efficient and safer compared to functions that can only operate on a single element. Let's delve deeper into this:

#### Range Insertion

- **Efficiency**: Inserting a range of elements is generally more efficient than inserting elements one by one. This is because range insertions can allocate enough memory to accommodate all new elements at once, while single-element insertions might require multiple memory allocations.
- **Convenience**: Inserting a range of elements by providing a start iterator and an end iterator facilitates the insertion of multiple elements more easily than repeatedly calling single-element insertion functions.

#### Range Erasure

- **Efficiency**: Erasing a range of elements is generally faster than erasing them one by one, because it only requires one operation to reorganize the memory.
- **Safety**: Erasing a range of elements can reduce the risk of errors due to iterator invalidation. If you erase elements one by one in a loop, you might encounter undefined behavior due to iterator invalidation.

Here is a simple example illustrating this:

```cpp
vector<int> vec = {1, 2, 3, 4, 5, 6};

// Range insertion
vector<int> to_insert = {7, 8, 9};
vec.insert(vec.end(), to_insert.begin(), to_insert.end());

// Range erasure
vec.erase(vec.begin(), vec.begin() + 3);

return 0;
```

### Item 9: Choose carefully among erasing options

In STL, "erasing" typically refers to removing one or several elements from a container. And the specific method available depends on the type of container. 

#### 1. `std::vector`

- `erase`: Remove an element by specifying an iterator or a range of elements by specifying an iterator range.

    ```cpp
    std::vector<int> vec = {1, 2, 3, 4, 5};
    vec.erase(vec.begin() + 2);          // Removes the third element (3)
    vec.erase(vec.begin() + 1, vec.end() - 1); // Removes elements from the second to the second last
    ```

- `pop_back`: Remove the last element but does not return it.

    ```cpp
    vec.pop_back(); // Removes the last element
    ```

#### 2. `std::list`

- `erase`: Similar to `std::vector`'s `erase`, it can be used to remove an element or a range of elements.

    ```cpp
    std::list<int> lst = {1, 2, 3, 4, 5};
    auto it = std::next(lst.begin(), 2);
    lst.erase(it);             // Removes the third element (3)
    ```

- `remove` / `remove_if`: Remove elements by value or those satisfying a specific condition.

    ```cpp
    lst.remove(2);     // Removes all elements equal to 2
    lst.remove_if([](int n){ return n % 2 == 0; }); // Removes all even numbers
    ```

- `pop_front` / `pop_back`: Remove the first or the last element.

    ```cpp
    lst.pop_front(); // Removes the first element
    lst.pop_back();  // Removes the last  element
    ```

#### 3. `std::set`

- `erase`: Remove an element by specifying a key or an iterator. It can also remove a range of elements by specifying an iterator range.

    ```cpp
    std::set<int> myset = {1, 2, 3, 4, 5};
    myset.erase(3);               // Removes the element with the key 3
    myset.erase(myset.begin());   // Removes the first element
    ```

#### 4. `std::map`

- `erase`: Similar to `std::set`, it allows removal of elements based on the key or an iterator. It can also remove a range of elements by specifying an iterator range.

    ```cpp
    std::map<int, std::string> mymap = {{1, "one"}, {2, "two"}, {3, "three"}};
    mymap.erase(2);               // Removes the element with the key 2
    mymap.erase(mymap.begin());   // Removes the first element
    ```

**A Few Tips**

- **Efficiency**: Erasing elements in the middle of a vector or deque is generally slow because it involves moving elements to fill the hole left by the erased element(s). Erasing elements at the end or the beginning (for deque) is fast.
- **Iterator invalidation**: Erasing elements from a container might invalidate existing iterators. Be careful when erasing elements in a loop, as you might end up with invalidated iterators, leading to undefined behavior.


## Chapter 2: Vectors and Strings

### Item 14: Use `reserve` to avoid unnecessary reallocations

STL containers have the ability to dynamically grow to accommodate the amount of data being stored in them. This is especially true for `vector` and `string` classes. However, the growth mechanism includes a realloc-like operation that essentially has four stages:

1. Allocating a new block of memory, a process that is larger by some multiples of the current capacity. In MSVC, this is referred to as "Geometric Growth," often 1.5 times the existing size.
2. Copying existing elements from the old memory block to the new one.
3. Destroying objects residing in the old memory space.
4. Deallocating the old memory space.

This process, albeit necessary, can slow down operations. A solution to avoid this is to use the `reserve` function, which helps to minimize the number of reallocations, hence reducing the overheads associated with reallocation and avoiding iterator/pointer/reference invalidation.

Here is a brief overview of four interconnected member functions that sometimes can be perplexing:

- `size()`: Retrieves the number of elements in the container.
- `capacity()`: Determines the maximum number of elements that can be held in the allocated memory space.
- `resize(Container::size_type n)`: Modifies the number of elements held in the container to `n`.
- `reserve(Container::size_type n)`: Changes the container’s capacity to at least `n`, as long as `n` is not less than the current size.

**Pro tip:** Use file size as a heuristic to predict the requisite vector size and accordingly reserve the capacity.

### Item 16: Know how to pass vector and string data to legacy APIs

#### Conversion between Vector and C-Array

```cpp
// Converting vector to array
std::vector<int> vec = {1, 2, 3, 4, 5};
int* arr = &vec[0];
    
// Converting array to vector
int arr2[] = {6, 7, 8, 9, 10};
std::vector<int> vec2(arr2, arr2 + std::size(arr2));
```

#### Conversion between `string` and `char*`

```cpp
// Converting string to char*
std::string str = "Hello";
const char* cstr = str.c_str();

// Converting char* to string
const char* cstr2 = "World";
std::string str2(cstr2);
```

### Item 18: Avoid using `vector<bool>`

A known historical problem in C++ is the special case of `vector<bool>`, which, contrary to expectations, is not a container. This specialization has been designed to efficiently store boolean values, utilizing a single bit per value instead of a whole byte. Despite its space efficiency, it's generally recommended to avoid using `vector<bool>` and to use `bitset` instead.

However, it has its uses, such as in the implementation of a bitmap:

```cpp
// Creating a bitmap with 10 elements
std::vector<bool> bitmap(10, false);

// Setting the 3rd and 7th bits to true
bitmap[2] = true;
bitmap[6] = true;

// Displaying the content of the bitmap
for(bool bit : bitmap) {
    std::cout << bit << " ";
}
```

**Advanced Topic:** Implementing a Boolean Array with Bit Operations and `vector<uint8_t>`

For a more granular and flexible approach, one can use `vector<uint8_t>` coupled with bit operations to create a boolean array:

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<uint8_t> bitmap(2, 0);  // 2 * 8 = 16 bits

    // Setting the 3rd and 7th bits to true
    bitmap[0] |= (1 << 2);
    bitmap[0] |= (1 << 6);

    // Checking the status of the 3rd and 7th bits
    bool bit3 = bitmap[0] & (1 << 2);
    bool bit7 = bitmap[0] & (1 << 6);

    // Displaying the results
    std::cout << "bit3: " << bit3 << ", bit7: " << bit7 << std::endl;

    // Printing the entire bitmap
    for(size_t i = 0; i < bitmap.size(); ++i) {
        for(int j = 0; j < 8; ++j) {
            std::cout << ((bitmap[i] & (1 << j)) ? '1' : '0');
        }
        std::cout << " ";
    }

    return 0;
}
```

In this script:
- A `vector<uint8_t>` is utilized to store the bitmap data, where each `uint8_t` can hold 8 bits (or boolean values).
- Bit operations (`|`, `&`, `<<`) are used to set and inspect individual bits.


## Chapter 3. Associative Containers

### Item 19: Understand the difference between equality and equivalence

In the context of associative containers in C++, "equality" generally means that `a == b` holds true, whereas "equivalence" pertains to the sorting predicate of the container which doesn't necessarily require `a == b` to be true. Instead, it is founded on the logic that “a is not less than b” and “b is not less than a”.

Associative containers like sets and maps rely on a comparison function or predicate to organize and store elements. The predicate defines a sorting order rather than just determining if two elements are equal. This predicate can be a user-defined function object, accepting two elements and returning a boolean value.

Here is a snippet illustrating the concept using a custom comparator:

```cpp
struct MyComparator {
    bool operator() (int a, int b) const {
        return (a % 10) < (b % 10);
    }
};

std::set<int, MyComparator> mySet;

mySet.insert(11);
mySet.insert(12);
mySet.insert(21);
mySet.insert(22);

for (int elem : mySet) {
    std::cout << elem << ' ';
}
// Output: 11 21 12 22

auto comp = mySet.key_comp();
bool equivalent = !comp(11, 21) && !comp(21, 11);
std::cout << "\n11 and 21 are equivalent: " << equivalent << '\n'; // Output: true
```

### Item 20: Specify comparison types for associative containers of pointers
When you have associative containers (like sets or maps) that store pointers, it is necessary to provide a custom comparison function to dictate how the pointers should be compared, because by default, the pointers themselves (the addresses they hold) would be compared, not the objects they point to.

Here's an illustrative example:
```cpp
struct Person {
  std::string name;
  int age;
};

struct ComparePersons {
  bool operator()(const Person* lhs, const Person* rhs) const {
    return lhs->age < rhs->age;
  }
};

int main() {
  std::set<Person*, ComparePersons> people;
  Person alice = {"Alice", 30};
  Person bob = {"Bob", 40};

  people.insert(&alice);
  people.insert(&bob);

  for(const Person* person : people) {
      std::cout << person->name << ": " << person->age << '\n';
  }

  // Output (in sorted order of ages):
  // Alice: 30
  // Bob: 40

  return 0;
}
```

In this example, we defined a ComparePersons functor that compares Person pointers based on the age of the persons they point to. This allows us to have a set of Person pointers that is sorted based on age, not based on the addresses of the pointers.

### Item 21: Always have comparison functions return false for equal values

When defining comparison functions for types, it is crucial to ensure that the function returns false for equal values
to maintain a strict weak ordering, which is required by many standard library algorithms and containers. Here are a
couple of examples:

```cpp
struct Person {
    string name;
    int age;
    // A less-than operator that meets the requirements
    bool operator<(const Person& other) const {
        return age < other.age;
    }
};

int main() {
    set<Person> people = { {"Alice", 30}, {"Bob", 40}, {"Charlie", 30} };

    for(const auto& person : people) {
        cout << person.name << ": " << person.age << '\n';
    }

    // Output (in sorted order of ages):
    // Alice: 30
    // Charlie: 30
    // Bob: 40

    return 0;
}
```

In the above example, even though Alice and Charlie have the same age, the set can still contain both because the
less-than operator returns false when it compares two equal values.

### Item 24: Choose carefully between `operator[]`, `insert` and `at` functions

- `operator[]`: When you use this operator, if the key does not exist in the map, it will automatically create a new
  element with that key and default initialize the value. This means that even if you are using it to just check if a
  key exists, it might end up modifying the map.
- `insert`: This method adds a new element to the map only if the key does not exist already; otherwise, it does not
  modify the existing value. It also returns a pair where the second element is a boolean indicating whether the
  insertion took place.
- `at`: Throws an exception if the key does not exist in the map, which is different from operator[] which would just
  create a new element with a default value.

Here is a small example showcasing the difference between operator[] and insert:

```cpp
// Using operator[]
my_map[5] = 10;
my_map[5] = 20; // Replaces the value associated with key 5

// Using insert
my_map.insert({ 6, 30 });
my_map.insert({ 6, 40 }); // Does nothing, key 6 already has a value

// Display the map
for (const auto&[key, value] : my_map) {
cout << key << ": " << value << '\n';
}

// Output:
// 5: 20
// 6: 30
```


## Chapter 4. Iterators

### Intro of iterators
STL has 5 types of iterators:

1. **Input Iterator**

   Used to read elements in a sequence but can only move forward.

   **Example**:
   ```cpp
   istream_iterator<int> i(cin);
   ```

2. **Output Iterator**

   Used to write elements in a sequence but can only move forward.

   **Example**:
   ```cpp
   ostream_iterator<int> o(cout, " ");
   ```

3. **Forward Iterator**

   In addition to the functionalities of input and output iterators, it also allows the traversal of each element in a sequence multiple times.

   **Example**:
   ```cpp
   forward_list<int>::iterator it = my_forward_list.begin();
   ```

4. **Bidirectional Iterator**

   Besides the functionalities of a forward iterator, it also allows backward movement.

   **Example**:
   ```cpp
   list<int>::iterator it = my_list.begin();
   ```

5. **Random Access Iterator**

   Apart from the functionalities of a bidirectional iterator, it also enables direct access to any element in the sequence.

   **Example**:
   ```cpp
   vector<int>::iterator it = my_vector.begin();
   ```

When choosing an iterator, it is very important to understand the capabilities of each type of iterator because they determine which STL algorithms you can use.

### Item 27: Use distance and advance to convert a container’s const_iterators to iterators

`distance` and `advance` are two highly useful functions in C++ STL that are utilized for handling iterators. Here, we take a detailed look at the utilities and working methodologies of these functions.

#### `distance`

The `distance` function is used to calculate the "distance" between two iterators, essentially the number of elements between them. It can work with input iterators, forward iterators, bidirectional iterators, or random access iterators. For random access iterators, it can quickly calculate the distance, while for other types of iterators, it might require linear time.

Below is an example illustrating the use of `distance`:

```cpp
std::vector<int> v = {1, 2, 3, 4, 5, 6};
auto first = v.cbegin();
auto last = v.cend();

auto dist = std::distance(first, last);
std::cout << "Distance: " << dist << '\n';  // Output: Distance: 6
```

#### `advance`

The `advance` function is utilized to "advance" an iterator to a new position. It can accept forward iterators, bidirectional iterators, or random access iterators. Similar to `distance`, its performance is contingent upon the type of iterator being used.

Here is an example demonstrating the use of `advance`:

```cpp
std::vector<int> v = {1, 2, 3, 4, 5, 6};
auto it = v.begin();

std::advance(it, 3);
std::cout << "Value after advancing: " << *it << '\n';  // Output: Value after advancing: 4

```

When there is a necessity to obtain a non-const iterator from a `const_iterator`, these two functions can be employed to "copy" the position of a `const_iterator` to a new iterator. For instance:

```cpp
auto it = vec.begin();
advance(it, distance(vec.cbegin(), some_const_iterator));
```

In this snippet, we first obtain the `begin` iterator of `vec`, then use the `advance` and `distance` functions to advance it to the position indicated by `some_const_iterator`.

By using `distance` and `advance`, it is possible to acquire a regular iterator corresponding to a `const_iterator`, as these functions allow you to ascertain the position of the `const_iterator` within the container, and use this positional information to set a regular iterator.

Here is how it can be done:

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    auto const_iter = vec.cbegin() + 2;  // Acquiring a const_iterator

    auto iter = vec.begin();
    std::advance(iter, std::distance(vec.cbegin(), const_iter)); // Setting a regular iterator using distance and advance

    std::cout << *iter << '\n'; // Output: 3

    return 0;
}
```

In the above code:

1. We initially acquire a `const_iterator` pointing to the third element in the container.
2. Next, we craft a regular iterator and set it to the beginning of the container.
3. We use `distance` to determine the distance between the `const_iterator` and the starting position of the container.
4. Following that, we use this distance and `advance` to shift the regular iterator to the same position as the `const_iterator`.

Now, `iter` and `const_iter` point to the same element in the container. However, `iter` is an iterator that can be used to modify the element, while `const_iter` can only be used to read the element's value.

Note: In this example, we leveraged the vector's random access iterator to simplify the code. If you are working with a container that does not support random access (like a `list`), you will need to use `next` or `advance` to establish the `const_iterator`.

## Chapter 5. Algorithms

### Item 31: Know your sorting options
1. **sort**: Sorts the elements in the range [first, last) into ascending order.
2. **stable_sort**: Sorts the elements in a way that the relative order of equal elements is preserved.
3. **partial_sort**: Sorts the first "n" elements in ascending order.
4. **nth_element**: Partially sorts the range such that the element at the nth position is the element that would be there if the entire range were sorted.
5. **partition**: Partitions the range into two groups: those for which the predicate returns true and those for which it returns false. The order within the two groups is not guaranteed to be preserved.

```cpp
{ /* sort */  
    vector<int> vec = {3, 1, 4, 1, 5, 9};
    sort(vec.begin(), vec.end());
}    

{ /* stable_sort */  
vector<pair<int, int>> vec = {{3, 1}, {1, 2}, {4, 0}, {1, 3}, {5, 0}, {9, 1}};
stable_sort(vec.begin(), vec.end(), [](const auto& a, const auto& b)
    { return a.first < b.first; });
}

{ /* partial_sort */  
    vector<int> vec = {3, 1, 4, 1, 5, 9};
    partial_sort(vec.begin(), vec.begin() + 3, vec.end());
}

{ /* nth_element */  
    vector<int> vec = {3, 1, 4, 1, 5, 9};
    nth_element(vec.begin(), vec.begin() + 2, vec.end());
}

{ /* partition */  
    vector<int> vec = {3, 1, 4, 1, 5, 9};
    partition(vec.begin(), vec.end(), [](int num){ return num < 5; });
}
```

### Item 32: Follow remove-like algorithms by erase if you really want to remove something

_`remove` does not “really” remove anything, because it can’t._

The `remove` and `remove_if` algorithms in the STL (Standard Template Library) are used to shift elements that need to be "removed" to the end of the container and return an iterator to the new end of the container. However, it is important to note that these algorithms do not actually remove the elements from the container; they merely move the elements that do not satisfy the removal criteria to the beginning of the container, thereby overwriting the elements that should be removed. The actual removal of the elements from the container needs to be done using the erase method of the container. This pattern of usage is often referred to as "erase-remove" idiom.

The reason it doesn't actually remove elements is to allow for more efficient algorithms. Erasing elements from the middle of a vector, for instance, can be very inefficient because all elements after the erased element must be moved to fill the gap, which has a linear complexity. By separating the removal and erasure processes, it allows you to minimize the number of element moves, thus potentially speeding up your code.

Here are a few examples using `remove` and `remove_if`:

#### Example 1: `remove`

```cpp
vector<int> vec = {3, 1, 4, 1, 5, 9};
auto new_end = remove(vec.begin(), vec.end(), 1);
vec.erase(new_end, vec.end()); // Output: 3 4 5 9
```

#### Example 2: `remove_if`

```cpp
vector<int> vec = {3, 1, 4, 1, 5, 9};
auto new_end = remove_if(vec.begin(), vec.end(), [](int x){ return x < 4; });
vec.erase(new_end, vec.end()); // Output: 4 5 9
```

In both examples, we first use `remove` or `remove_if` to move the elements that should be "removed" to the end of the container and then use `erase` to actually remove them. This way, we only perform the "expensive" erasing operation once, instead of potentially many times, which would be the case if we were erasing elements one by one in a loop.


## Chapter 7. Programming with the STL

### Item 43: Prefer Algorithm Calls to Hand-Written Loops

Using STL algorithms instead of handwritten loops can benefit code efficiency, correctness, and maintainability. Below is a demonstration of how to utilize `for_each` algorithm with lambda functions to iterate over a `vector` and perform operations on each element:

```cpp
vector<int> nums = {1, 2, 3, 4, 5};

// Utilize for_each and lambda function
for_each(nums.begin(), nums.end(), [](int& num) { ++num; });

for_each(nums.begin(), nums.end(), [](int num) {
    cout << num << ' ';
});
```

### Item 44: Prefer Member Functions to Algorithms with the Same Names

When a member function can accomplish what you're trying to do, it is often better to use it instead of a global algorithm. It might be more optimized, simpler, and intuitive. Many STL containers have member functions that share names with global algorithm functions but can behave slightly differently.

Consider this example where `vector::erase` member function is utilized along with `remove` algorithm:

```cpp
vector<int> vec = {1, 2, 3, 4, 5};
// Incorrect way: it doesn't actually remove elements from the vector
remove(vec.begin(), vec.end(), 3);
// Correct way: it actually removes elements from the vector
vec.erase(remove(vec.begin(), vec.end(), 3), vec.end());
for (int i : vec) { cout << i << " "; }
```

### Item 45: Distinguish Among `count`, `find`, `binary_search`, `lower_bound`, `upper_bound`, and `equal_range`

Understanding the distinctions between various algorithm functions and utilizing them properly can aid in writing efficient and clean code. Below are some examples:

#### 1. `count` and `count_if`
Count the occurrences of a value or the number of elements satisfying a predicate:

```cpp
vector<int> vec = {1, 2, 2, 3, 4, 4, 4};

int num_twos = count(vec.begin(), vec.end(), 2);
int num_evens = count_if(vec.begin(), vec.end(), [](int x){ return x % 2 == 0; });

cout << "Number of 2s: " << num_twos << "\n";
cout << "Number of evens: " << num_evens << "\n";
```

#### 2. `find` and `find_if`
Find the first element equal to a given value or satisfying a predicate:

```cpp
// The rest of your query is preserved, only this section is revised
vector<int> vec = {1, 2, 3, 4, 5};

auto it = find(vec.begin(), vec.end(), 3);
auto it_if = find_if(vec.begin(), vec.end(), [](int x){ return x > 3; });

if(it != vec.end()) cout << "Found the element: " << *it << "\n";
if(it_if != vec.end())  cout << "Found the element: " << *it_if << "\n";
```

#### 3. `binary_search`
Verify if a given value exists in a sorted range:

```cpp
vector<int> vec = {1, 2, 3, 4, 5};
cout << "Element exists: " << binary_search(vec.begin(), vec.end(), 3) << "\n";
```

#### 4. `lower_bound` and `upper_bound`
Find the first element not less than or greater than a given value in a sorted range:

```cpp
vector<int> vec = {1, 2, 3, 4, 5};
auto it = lower_bound(vec.begin(), vec.end(), 3);
if(it != vec.end()) cout << "Lower bound: " << *it << "\n";

it = upper_bound(vec.begin(), vec.end(), 3);
if(it != vec.end())  cout << "Upper bound: " << *it << "\n";
```

#### 5. `equal_range`
Find the range of elements equivalent to

a given value in a sorted range:

```cpp
vector<int> vec = {1, 2, 2, 3, 3, 3, 4, 5};

auto pair = equal_range(vec.begin(), vec.end(), 3);
cout << "Range of elements equal to 3: [" << *pair.first << ", " << *pair.second << ")\n";
```

### Item 46: Consider Function Objects Instead of Functions as Algorithm Parameters

From C++11 onwards, it's encouraged to use lambdas more frequently as opposed to function pointers. Here are the examples using both methods:

**Using Functions:**

```cpp
bool compare(int a, int b) { return a > b; }
vector<int> vec = {1, 3, 5, 2, 4, 6};
sort(vec.begin(), vec.end(), compare);
```

**Using Lambdas:**

```cpp
vector<int> vec = {1, 3, 5, 2, 4, 6};
sort(vec.begin(), vec.end(), [](int a, int b) {
    return a > b;
});
```

## Removed Items

I removed some of the items from the book and list them here. Some of them are out of date thanks to C++11. Some of them have been my coding conversions before reading and make no inspirations for me. Though It was an old book and I have thrown more than half of them, it is also a useful book in 2023 to remind and benefit programming.

- Item 03: Make copying cheap and correct for objects in containers
- Item 04: Call `empty` instead of checking `size()` against zero
- Item 06: Be alert for C++’s most vexing parse
- Item 07: When using containers of newed pointers, remember to delete the pointers before the container is destroyed
- Item 08: Never create containers of `auto_ptrs`
- Item 10: Be aware of allocator conventions and restrictions
- Item 11: Understand the legitimate uses of custom allocators
- Item 12: Have realistic expectations about the thread safety of STL containers
- Item 13: Prefer `vector` and `string` to dynamically allocated arrays
- Item 15: Be aware of variations in `string` implementations
- Item 17: Use “the swap trick” to trim excess capacity
- Item 22: Avoid in-place key modification in `set` and `multiset`
- Item 23: Consider replacing associative containers with sorted vectors
- Item 25: Familiarize yourself with the nonstandard hashed containers
- Item 26: Prefer `iterator` to `const_iterator`, `reverse_iterator`, and `const_reverse_iterator`
- Item 28: Understand how to use a `reverse_iterator`
- Item 29: Consider `istreambuf_iterators` for character-by-character input
- Item 30: Make sure destination ranges are big enough
- Item 33: Be wary of remove-like algorithms on containers of pointers
- Item 34: Note which algorithms expect sorted ranges
- Item 35: Implement simple case-insensitive string comparisons via `mismatch` or `lexicographical_compare`
- Item 36: Understand the proper implementation of copy_if
- Item 37: Use `accumulate` or `for_each` to summarize ranges
- Item 38: Design functor classes for pass-by-value
- Item 39: Make predicates pure functions
- Item 40: Make functor classes adaptable
- Item 41: Understand the reasons for `ptr_fun`, `mem_fun`, and `mem_fun_ref`
- Item 42: Make sure `less<T>` means `operator<`
- Item 47: Avoid producing write-only code
- Item 48: Always `#include` the proper headers
- Item 49: Learn to decipher STL-related compiler diagnostics
- Item 50: Familiarize yourself with STL-related websites
