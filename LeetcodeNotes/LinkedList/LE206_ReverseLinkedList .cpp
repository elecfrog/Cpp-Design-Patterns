#include "../Headers.h"

using namespace std;

/*
Example 1:

    Input: head = [1,2,3,4,5]
    Output: [5,4,3,2,1]

Example 2:

    Input: head = [1,2]
    Output: [2,1]

Example 3:

    Input: head = []
    Output: []
*/



ListNode *reverseList(ListNode *head) {

    // we just need to reverse the direction of edges, not the nodes in memory
    ListNode *prev = nullptr;
    ListNode *curr = head;
    while (curr) {
        // get the original next node of current 
        ListNode *next = curr->next;
        // replace next node with previous node
        curr->next = prev;
        prev = curr;
        curr = next;

        size--;
        
    }

    // return real node
    return prev;
}