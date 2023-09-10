#include "../Headers.h"

/*
Implement a first in first out (FIFO) queue using only two stacks. 
The implemented queue should support all the functions of a normal queue (push, peek, pop, and empty).

Implement the MyQueue class:

    void push(int x) Pushes element x to the back of the queue.
    int pop() Removes the element from the front of the queue and returns it.
    int peek() Returns the element at the front of the queue.
    boolean empty() Returns true if the queue is empty, false otherwise.

Example 1:

    Input
        ["MyQueue", "push", "push", "peek", "pop", "empty"]
        [[], [1], [2], [], [], []]
    Output
        [null, null, null, 1, 1, false]

    Explanation
        MyQueue myQueue = new MyQueue();
        myQueue.push(1); // queue is: [1]
        myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
        myQueue.peek(); // return 1
        myQueue.pop(); // return 1, queue is [2]
        myQueue.empty(); // return false
*/


namespace solution1 {
    class MyQueue {
    public:
        MyQueue() = default;

        // Pushes element x to the back of the queue.
        void push(int x) {
            while (!front.empty()) {
                storage.push(front.top());
                front.pop();
            }
            storage.push(x);
            while (!storage.empty()) {
                front.push(storage.top());
                storage.pop();
            }
        }

        // Removes the element from the front of the queue and returns it.
        int pop() {
            int x = front.top();
            front.pop();
            return x;
        }

        // Returns the element at the front of the queue.
        int peek() {
            return front.top();
        }

        // Returns true if the queue is empty, false otherwise.
        bool empty() {
            return front.empty();
        }

        stack<int> storage;
        stack<int> front;
    };
}


namespace solution2 {
    class MyQueue {
    public:
        MyQueue() = default;

        // Pushes element x to the back of the queue.
        void push(int x) {
            storage.push(x);
        }

        // Removes the element from the front of the queue and returns it.
        int pop() {
            if (front.empty()) {
                while (!storage.empty()) {
                    front.push(storage.top());
                    storage.pop();
                }
            }
            int x = front.top();
            front.pop();
            return x;
        }

        // Returns the element at the front of the queue.
        int peek() {
            int res = this->pop();
            front.push(res);
            return res;
        }

        // Returns true if the queue is empty, false otherwise.
        bool empty() {
            return front.empty() && storage.empty();
        }

    private:
        stack<int> storage;
        stack<int> front;
    };
}


/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

int main() {
    using namespace solution2;
    MyQueue *obj = new MyQueue();
    obj->push(2);
    obj->push(3);
    int param_2 = obj->pop();
    cout << param_2 << endl;
    int param_3 = obj->peek();
    cout << param_3 << endl;
    obj->pop();
    bool param_4 = obj->empty();
    cout << param_4 << endl;
}