#include "../Headers.h"

using namespace std;

/*

Example 1:

    Input: head = [3,2,0,-4], pos = 1
    Output: tail connects to node index 1
    Explanation: There is a cycle in the linked list, where tail connects to the second node.

Example 2:

    Input: head = [1,2], pos = 0
    Output: tail connects to node index 0
    Explanation: There is a cycle in the linked list, where tail connects to the first node.

Example 3:

    Input: head = [1], pos = -1
    Output: no cycle
    Explanation: There is no cycle in the linked list.
 */

ListNode *detectCycle(ListNode *head) {

    // two questions:
        // 1. if it has a cycle
        // 2. if cycled, where is the entry of this cycle
    // SOLUTIONS
        // using two pointers, one fast and one slow
        // if it has a cycle, slow and fast will meet,
        // if it doesn't have a cycle, they will not meet.
            // L_slow =  x + y
            // L_fast =  x + y + n ( y + z ) = 2 * ( x + y )
            // x = n ( y + z ) - y
            // x = (n - 1) * ( y + z ) + z
            // x = z 
                // NOTE: 
                // it could be considered that the cycle is a unsigned value, 
                // it would be back to the min from max
                // so, (n - 1) * ( y + z ) the length will be circles 
                // slow pointer made when computing the entry
            // Therefore, looping from x(head) and z(slow) at same time! 

    ListNode *slow = head, *fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            ListNode *curr = head;
            // x = z 
            while (curr != slow) {
                curr = curr->next;
                slow = slow->next;
            }
            return curr;
        }
    }
    return nullptr;
}