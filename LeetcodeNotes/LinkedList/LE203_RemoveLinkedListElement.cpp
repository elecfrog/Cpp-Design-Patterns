#include <vector>
#include "../Headers.h"

using namespace std;

/*
Example 1:
    Input: dummy = [1,2,6,3,4,5,6], val = 6
    Output: [1,2,3,4,5]

Example 2:

    Input: dummy = [], val = 1
    Output: []

Example 3:

    Input: dummy = [7,7,7,7], val = 7
    Output: []

 */



ListNode *removeElements(ListNode *head, int val) {
    // define a dummy dummy, and a current pointer
    ListNode *dummy = new ListNode(-1, head);
    ListNode *curr = dummy;
    
    // cuz we have a dummy node, the next node is real node
    while (curr->next != nullptr) {
        // not equal continue to find next element
        if (curr->next->val != val) {
            curr = curr->next;
        } else {
            // adding delete operation to avoid memory issues in development
            auto&& tmpDelete = curr->next;
            // skip the element
            curr->next = curr->next->next;
            delete tmpDelete;
        }
    }
    
    // return real dummy
    return dummy->next;
}

int main()
{
    ListNode* tail  = new ListNode{2, nullptr};
    ListNode* n4  = new ListNode{3, tail};
    ListNode* n3  = new ListNode{3, n4};
    ListNode* n2  = new ListNode{2, n3};
    ListNode* n1  = new ListNode{4, n2};
    ListNode* root = new ListNode{5, n1};

    removeElements(root, 2);
    
}