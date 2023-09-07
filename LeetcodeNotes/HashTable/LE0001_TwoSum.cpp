#include "../Headers.h"

/*
Example 1:

    Input: nums = [2,7,11,15], target = 9
    Output: [0,1]
    Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

Example 2:

    Input: nums = [3,2,4], target = 6
    Output: [1,2]

Example 3:

    Input: nums = [3,3], target = 6
    Output: [0,1]
*/

vector<int> twoSum(vector<int> &nums, int target) {

    // remains, index 
    unordered_map<int, int> record;

    for (int idx = 0; idx < nums.size(); idx++) {

        // if it has found 7
        if (record.find(nums[idx]) != record.end()) {
            int previousIdx = record.at(nums[idx]);
            return {previousIdx, idx};
        }

        // remains = 7
        int remains = target - nums[idx];

        // [7,0] wait  7
        record[remains] = idx;
    }

    return {};
}

int main() {
    auto nums = vector<int>{2, 7, 11, 15};
    auto ret = twoSum(nums, 9);
    for (auto &&n: ret) {
        cout << n << endl;
    }
}