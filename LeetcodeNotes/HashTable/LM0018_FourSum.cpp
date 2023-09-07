#include "../Headers.h"

/*
Example 1:

    Input: nums = [1,0,-1,0,-2,2], target = 0
    Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

Example 2:

    Input: nums = [2,2,2,2,2], target = 8
    Output: [[2,2,2,2]]

*/

vector<vector<int>> fourSum(vector<int> &nums, int target) {
    
    // similar with 0015threeSum, 
    // we need to fix two numbers, 
    // then do stuff afterward

    vector<vector<int>> result;
    sort(nums.begin(), nums.end());

    for (int k = 0; k < nums.size(); k++) {

        // filtering
        if (nums[k] > target && nums[k] >= 0) {
            break;
        }

        // skipping redundant number
        if (k > 0 && nums[k] == nums[k - 1]) {
            continue;
        }
        // inner loop
        for (int i = k + 1; i < nums.size(); i++) {

            int sumLeft = nums[k] + nums[i];

            // filtering
            if (sumLeft > target && sumLeft >= 0) {
                break;
            }

            // skipping redundant number again
            if (i > k + 1 && nums[i] == nums[i - 1]) {
                continue;
            }
            int left = i + 1;
            int right = nums.size() - 1;
            while (right > left) {
                // prevent nums[k] + nums[i] + nums[left] + nums[right] > target overflow
                long sum = sumLeft + nums[left] + nums[right];
                if (sum > target) {
                    right--;
                } else if (sum < target) {
                    left++;
                } else {
                    result.push_back(vector<int>{nums[k], nums[i], nums[left], nums[right]});

                    while (right > left && nums[right] == nums[right - 1]) right--;
                    while (right > left && nums[left] == nums[left + 1]) left++;

                    right--;
                    left++;
                }
            }

        }
    }
    return result;
}

int main() {
    auto nums = vector<int>{2, 7, 11, 15};
    auto ret = twoSum(nums, 9);
    for (auto &&n: ret) {
        cout << n << endl;
    }
}