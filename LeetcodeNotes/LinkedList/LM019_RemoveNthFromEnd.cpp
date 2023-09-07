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

ListNode *removeNthFromEnd(ListNode *head, int n) {

    if (!head)
        return head;

    // using two pointers
    ListNode *left = head;
    ListNode *right = head;

    for (int i = 0; i < n; ++i) {
        if (right) {
            right = right->next;
        } else break;
    }

    // when the length of the list < right, which is n
    if (!right) {
        ListNode *newNode = head->next;
        delete head;
        return newNode;
    }

    // traverse the list using left and right at same time, 
    // find the node should be deleted!
    while (right->next) {
        left = left->next;
        right = right->next;
    }

    // do the deletion
    ListNode *tmp = left->next;
    left->next = left->next->next;
    delete tmp;

    return head;
}