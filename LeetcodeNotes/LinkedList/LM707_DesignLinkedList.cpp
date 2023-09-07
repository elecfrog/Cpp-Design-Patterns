#include <vector>
#include "../Headers.h"

/*

Example 1:

    Input
        ["MyLinkedList", "addAtHead", "addAtTail", "addAtIndex", "get", "deleteAtIndex", "get"]
        [[], [1], [3], [1, 2], [1], [1], [1]]
    Output
        [null, null, null, null, 2, null, 3]

Explanation
    MyLinkedList myLinkedList = new MyLinkedList();
    myLinkedList.addAtHead(1);
    myLinkedList.addAtTail(3);
    myLinkedList.addAtIndex(1, 2);    // linked list becomes 1->2->3
    myLinkedList.get(1);              // return 2
    myLinkedList.deleteAtIndex(1);    // now the linked list is 1->3
    myLinkedList.get(1);              // return 3

 */

struct MyLinkedList {
    using Node = ListNode;
public:
    MyLinkedList()
            : dummy{new Node{-1}}, size{0} {

    }

    ~MyLinkedList() {
        delete dummy;
    }

    Node *getNode(int index) {
        if (index < 0 || index >= size) return nullptr;

        auto &&curr = dummy->next;
        int count = 0;
        while (count < index) {
            auto &next = curr->next;
            if (next) {
                curr = next;
                count++;
            } else return nullptr;
        }
        return curr;
    }

    //  Get the value of the indexth node in the linked list. If the index is invalid, return -1.
    int get(int index) {
        return getNode(index)->val;
    }


    //  Add a node of value val before the indexth node in the linked list. If index equals the length of the linked list, the node will be appended to the end of the linked list. If index is greater than the length, the node will not be inserted.
    void addAtIndex(int index, int val) {
        if (index < 0 || index > size) return;

        Node *prev = dummy->next;
        int prevIndex = index - 1;
        if (prevIndex >= 0) {
            prev = getNode(prevIndex);
        }

        Node *next = prev->next;
        Node *curr = new Node(val, next);
        prev->next = curr;
        size++;
    }

    //  Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list.
    void addAtHead(int val) {
        addAtIndex(0, val);
    }

    // Append a node of value val as the last element of the linked list.
    void addAtTail(int val) {
        addAtIndex(size, val);
    }

    // Delete the indexth node in the linked list, if the index is valid.
    void deleteAtIndex(int index) {
        if (index < 0 || index > size) return;

        Node *prev = dummy->next;
        int prevIndex = index - 1;
        if (prevIndex >= 0) {
            prev = getNode(prevIndex);
        }

        Node *del = prev->next;
        Node *next = del->next;
        prev->next = next;

        delete del;
        size--;
    }


private:
    // dummy dummy pointer to the first element
    Node* dummy;
    int size;
};