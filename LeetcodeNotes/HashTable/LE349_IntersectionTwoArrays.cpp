#include "../Headers.h"

/*
Example 1:

    Input: nums1 = [1,2,2,1], nums2 = [2,2]
    Output: [2]

Example 2:

    Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
    Output: [9,4]
    Explanation: [4,9] is also accepted.
*/

vector<int> intersection(vector<int> &nums1, vector<int> &nums2) {

    // using std unordered set simply to solve it!

    // initialize the left hand side set 
    unordered_set<int> compared(nums1.begin(), nums1.end());

    // store the final result
    unordered_set<int> ret;

    // compare one by one
    for (auto &&num: nums2) {
        // if the number appears on the right hand side set, insert into the final set
        if (compared.find(num) != compared.end()) {
            ret.insert(num);
        }
    }

    // recover into a vector
    return vector<int>(ret.begin(), ret.end());
}

int main() {
    return 0;
}