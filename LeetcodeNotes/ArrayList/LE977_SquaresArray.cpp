#include <vector>

using namespace std;

/*
Example 1:

    Input: nums = [-4,-1,0,3,10]
    Output: [0,1,9,16,100]
    Explanation: After squaring, the array becomes [16,1,0,9,100].
    After sorting, it becomes [0,1,9,16,100].

Example 2:

    Input: nums = [-7,-3,2,3,11]
    Output: [4,9,9,49,121]
 */

vector<int> sortedSquares(vector<int> &nums) {

    // using two pointers, one for forward, and one for backward

    // initialize an array as the input size with 0 at the beginning
    vector<int> ret(nums.size(), 0);
    int idx = nums.size() - 1;
    // left close, right close
    // []
    int left = 0, right = nums.size() - 1;
    // while first and right did not meet
    while (left <= right) {
        // cuz the array has been sorted,
        // so, the bigger number either the most left or the most right
        // find a bigger one, and move this pointer
        if (abs(nums[left]) > abs(nums[right])) {
            // fill the return array from end to begin
            ret[idx--] = nums[left] * nums[left];
            left++;
        } else {
            // same as above
            ret[idx--] = nums[right] * nums[right];
            right--;
        }
    }
    return ret;
}