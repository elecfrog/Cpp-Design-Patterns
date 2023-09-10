# Iterator Pattern

Iterator is a core functionalities of STL containers.

It is a class that facilitates the traversal.
- Keeps a reference to the current element
- Knows how to move to a different element

Can be used implicitly 
- Range-bsed for 
- Coroutine

binary tree

begin and end

```cpp
template<typename T>
struct BinaryTree {
    // ...

    template<typename U>
    struct PreOrderIterator {
        Node<U> *current;

        // ...
        bool operator!=(const PreOrderIterator<U> &other) {
            return current != other.current;
        }

        PreOrderIterator<U> &operator++() { /* ... */ }

        Node<U> &operator*() { return *current; }
    };

    using iterator = PreOrderIterator<T>;

    iterator end() {
        return iterator{nullptr};
    }

    iterator begin() {
        // return left leaf node ...
        return iterator{the_leaf_node};
    }
    
    class pre_order_traversal {
        BinaryTree<T> &tree;
    public:
        pre_order_traversal(BinaryTree<T> &tree) : tree{tree} {}

        iterator begin() { return tree.begin(); }

        iterator end() { return tree.end(); }
    } pre_order;
};

// in order traversal
void binary_tree_iterator() {
    
    // pre order traversal
    for (auto it = family.begin(); it != family.end(); ++it) {
        cout << (*it).value << "\n";
    }

    cout << "=== and now, through a dedicated object:\n";

    // use iterator name
    for (const auto &it: family.pre_order) {
        cout << it.value << "\n";
    }

    cout << "=== postorder travesal with coroutines:\n";

    // use coroutines (yields pointers!)
    // postorder: m'm, m'f m f me
    for (auto it: family.post_order()) {
        cout << it->value << endl;
    }
}


int main() {
    //std_iterators();
    binary_tree_iterator();

    getchar();
    return 0;
}

```