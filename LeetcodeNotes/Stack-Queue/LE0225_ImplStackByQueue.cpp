#include "../Headers.h"

/*
Implement a last-in-first-out (LIFO) stack using only two queues. 

Implement the MyStack class:

    void push(int x) 
    int pop() 
    int top()
    boolean empty() 

Notes:

    You must use only standard operations of a queue, which means that only push to back, peek/pop from front, size and is empty operations are valid.
    Depending on your language, the queue may not be supported natively. You may simulate a queue using a list or deque (double-ended queue) as long as you use only a queue's standard operations.


Example 1:

    Input
        ["MyStack", "push", "push", "top", "pop", "empty"]
        [[], [1], [2], [], [], []]
    Output
        [null, null, null, 2, 2, false]
    
    Explanation
        MyStack myStack = new MyStack();
        myStack.push(1);
        myStack.push(2);
        myStack.top(); // return 2
        myStack.pop(); // return 2
        myStack.empty(); // return False

*/

namespace solution1 {
    class MyStack {
    public:
        MyStack() = default;

        // Pushes element x to the top of the stack.
        void push(int x) {
            front.push(x);
        }

        // Removes the element on the top of the stack and returns it.
        int pop() {
            auto size = front.size();
            while (size--) {
                storage.push(front.front());
                front.pop();
            }

            auto result = front.front();
            front.pop();
            front = storage;
            while (!storage.empty()) {
                storage.pop();
            }
            return result;
        }

        // Returns the element on the top of the stack.
        int top() {
            return front.back();
        }

        // Returns true if the stack is empty, false otherwise.
        bool empty() {
            return front.empty();
        }

        queue<int> storage;
        queue<int> front;
    };
}


namespace solution2 {
    class MyStack {
    public:
        MyStack() = default;

        // Pushes element x to the top of the stack.
        void push(int x) {
            data.push(x);
        }

        // Removes the element on the top of the stack and returns it.
        int pop() {
            auto size = data.size();
            size--;
            while (size--) {
                data.push(data.front());
                data.pop();
            }

            auto result = data.front();
            data.pop();
            return result;
        }
        

        // Returns the element on the top of the stack.
        int top() {
            return data.back();
        }

        // Returns true if the stack is empty, false otherwise.
        bool empty() {
            return data.empty();
        }

        queue<int> data;
    };
}

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */