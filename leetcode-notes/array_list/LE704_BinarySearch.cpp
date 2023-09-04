#include <vector>
#include <iostream>

using namespace std;

/*
Example 1:

    Input: nums = [-1,0,3,5,9,12], target = 9
    Output: 4
    Explanation: 9 exists in nums and its index is 4

Example 2:

    Input: nums = [-1,0,3,5,9,12], target = 2
    Output: -1
    Explanation: 2 does not exist in nums so return -1
 */

int search(vector<int> nums, int target) {

    // using two index, one loop left, and one loop right
    // [ ) -- left close, right open
    int left = 0, right = nums.size();
    // while left and right did not meet, continue to find
    while (left < right) {

        // cuz the array has been sorted, so we can
        // calculate the middle index of current basket
        int middle = (left + right) / 2;
        if (nums[middle] > target) // if the array[middle] > target
        {
            // set right as the middle
            right = middle;
        } else if (nums[middle] < target) // if the array[middle] < target
        {
            // set left as the middle
            left = middle + 1;
        } else // if the array[middle] == target
        {
            // return the middle index
            return middle;
        }
    }

    // by default
    return -1;
}