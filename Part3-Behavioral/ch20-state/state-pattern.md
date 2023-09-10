I don't like the implementation in the example.

I think state pattern should mix up the composite pattern, anc command or CoR pattern to create a FSM, or a graph.


```cpp
enum class CurrentState
{
    ...
    active,
    unactive,
    ...
};
enum class TransactionType
{
    Int,
    Float,
    Bool,
    Trigger,
    ...
};

struct Node
{
    vector<Node*> in, out;
    value_type value;
    CurrentState state;
    void ExecuteMethod();
};

struct Edge
{
    Node* start, end;
    TransactionType transaction;
    void TransactionMethod(){}
};

int main()
{
    // .. execute node method
}
```