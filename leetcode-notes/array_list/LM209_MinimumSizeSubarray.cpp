#include <vector>
#include <iostream>

using namespace std;

/*
Example 1:

    Input: target = 7, nums = [2,3,1,2,4,3]
    Output: 2
    Explanation: The subarray [4,3] has the minimal length under the problem constraint.

Example 2:

    Input: target = 4, nums = [1,4,4]
    Output: 1

Example 3:

    Input: target = 11, nums = [1,1,1,1,1,1,1,1]
    Output: 0
 */

int minSubArrayLen(int target, vector<int>& nums)
{
    // using sliding window
    
    // define the result as the maximum value
    int ret = INT_MAX;

    // define basket and sum value
    int left = 0, right = 0, sum = 0;
    // loop each element
    while(right < nums.size())
    {
        // adding the right basket
        sum += nums[right];
        
        while(sum >= target)
        {
            // current sub length
            int subLength = right - left + 1;
            // compare with current length with stored value 
            ret = min(ret, subLength);
            // remove elements from left-most
            sum -= nums[left++];
        }
        // moving the right basket
        right++;
    }

    return ret == INT_MAX ? 0 : ret;
}