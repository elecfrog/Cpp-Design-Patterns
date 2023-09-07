#include "../Headers.h"

using namespace std;

/*

Example 1:

    Input: head = [1,2,3,4,5], n = 2
    Output: [1,2,3,5]

Example 2:

    Input: head = [1], n = 1
    Output: []

Example 3:

    Input: head = [1,2], n = 1
    Output: [1]

 */

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {

    // (A + C) + B = (B + C) + A
    ListNode *currA = headA;
    ListNode *currB = headB;

    // cuz there is no cycle,
    // when currA == currB , the node is their intersection
    while (currA != currB)
    {
        // redirect to B if arrive the end, otherwise going forward
        currA = currA ? currA->next : headB;

        // same as above
        currB = currB ? currB->next : headA;
    }

    // intersection or nullptr
    return currA;
}