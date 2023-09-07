#include "../Headers.h"

/*
Example 1:

    Input: 
        nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
    Output: 2
    Explanation:
    The two tuples are:
    1. (0, 0, 0, 1) 
        -> nums1[0] + nums2[0] + nums3[0] + nums4[1] = 1 + (-2) + (-1) + 2 = 0
    2. (1, 1, 0, 0) 
        -> nums1[1] + nums2[1] + nums3[0] + nums4[0] = 2 + (-1) + (-1) + 0 = 0

Example 2:

    Input: nums1 = [0], nums2 = [0], nums3 = [0], nums4 = [0]
    Output: 1

*/

int fourSumCount(vector<int> &nums1, vector<int> &nums2,
                 vector<int> &nums3, vector<int> &nums4) {

    // a+b,  count(a + b)
    unordered_map<int, int> umap;
    for (int a: nums1) {
        for (int b: nums2) {
            umap[a + b]++;
        }
    }

    int count = 0;
    // counting remains times
    for (int c: nums3) {
        for (int d: nums4) {
            int remains = c + d;
            if (umap.find(0 - remains) != umap.end()) {
                count += umap[0 - remains];
            }
        }
    }
    return count;
}


int main() {
    auto nums = vector<int>{2, 7, 11, 15};
    auto ret = twoSum(nums, 9);
    for (auto &&n: ret) {
        cout << n << endl;
    }
}