#include "../Headers.h"

using namespace std;

/*
Example 1:

    Input: head = [1,2,3,4]
    Output: [2,1,4,3]

Example 2:

Input: head = []
Output: []

Example 3:

    Input: head = [1]
    Output: [1]

*/



ListNode *swapPairs(ListNode *head) {

    // check the situation of nodes
    if (!head || !head->next)
        return head;

    ListNode *dummy = new ListNode(-1, head);
    ListNode *prev = dummy;
    ListNode *curr = head;

    /* 
     * A->B->C->D 
     * => 
     * B->A->D->C 
     */
    while (curr && curr->next) {

        // get the next pair start point
        ListNode *nextPair = curr->next->next;
        ListNode *pairLeft = curr;
        ListNode *pairRight = curr->next;

        prev->next = pairRight;
        curr->next->next = pairLeft;
        curr->next = nextPair;

        prev = curr;

        // recover next pair as the current node
        curr = nextPair;
    }

    // return real node
    return prev;
}