#include "../Headers.h"

/*
Example 1:

    Input: nums = [-1,0,1,2,-1,-4]
    Output: [[-1,-1,2],[-1,0,1]]
    Explanation: 
    nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
    nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
    nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
    The distinct triplets are [-1,0,1] and [-1,-1,2].
    Notice that the order of the output and the order of the triplets does not matter.

Example 2:

    Input: nums = [0,1,1]
    Output: []
    Explanation: The only possible triplet does not sum up to 0.

Example 3:
    
    Input: nums = [0,0,0]
    Output: [[0,0,0]]
    Explanation: The only possible triplet sums up to 0.

*/

vector<vector<int>> threeSum(vector<int> &nums) {
    vector<vector<int>> result;
    // sort them by going up
    sort(nums.begin(), nums.end());
    for (int k = 0; k < nums.size(); k++) {

        // after sorting, if the first element bigger than 0 ,
        // it is not possible to combine a tuple
        if (nums[k] > 0) {
            break;
        }

        // skipping redundant number
        if (k > 0 && nums[k] == nums[k - 1]) {
            continue;
        }

        // define right and left
        int left = k + 1;
        int right = nums.size() - 1;

        while (right > left) {
            // prevent nums[k] + nums[i] + nums[left] + nums[right] > target overflow
            long sum = nums[k] + nums[left] + nums[right];
            if (sum > 0) {
                right--;
            } else if (sum < 0) {
                left++;
            } else {
                result.emplace_back(vector<int>{nums[k], nums[left], nums[right]});
                // do deduplication to nums[left] && nums[right]
                while (right > left && nums[right] == nums[right - 1]) right--;
                while (right > left && nums[left] == nums[left + 1]) left++;

                // shrink the range
                right--;
                left++;
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