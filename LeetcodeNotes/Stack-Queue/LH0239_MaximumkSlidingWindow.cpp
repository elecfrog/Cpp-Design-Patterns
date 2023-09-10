#include "../Headers.h"

/*

Example 1:

    Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
    Output: [3,3,5,5,6,7]
    Explanation: 
    Window position                Max
    ---------------               -----
    [1  3  -1] -3  5  3  6  7       3
     1 [3  -1  -3] 5  3  6  7       3
     1  3 [-1  -3  5] 3  6  7       5
     1  3  -1 [-3  5  3] 6  7       5
     1  3  -1  -3 [5  3  6] 7       6
     1  3  -1  -3  5 [3  6  7]      7

Example 2:

    Input: nums = [1], k = 1
    Output: [1]

*/


vector<int> maxSlidingWindow(vector<int>& nums, int k) {

    deque<int> window;
    vector<int> result;

    for (int idx = 0; idx < nums.size(); ++idx) {

        // remove left indices over the window
        if (!window.empty() && window.front() == idx - k) {
            window.pop_front();
        }

        // remove all elements smaller than the current 
        // keeping the window sorted from big => small
        while (!window.empty() && nums[window.back()] < nums[idx]) {
            window.pop_back();
        }

        // add current index
        window.push_back(idx);

        // add results
        if (idx >= k - 1) {
            result.emplace_back(nums[window.front()]);
        }
    }
    return result;
}