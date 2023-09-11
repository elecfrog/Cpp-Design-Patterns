#include "../Headers.h"

/*

Example 1:

    Input: groupSizes = [3,3,3,3,3,1,3]
    Output: [[5],[0,1,2],[3,4,6]]
    Explanation: 
    The first group is [5]. The size is 1, and groupSizes[5] = 1.
    The second group is [0,1,2]. The size is 3, and groupSizes[0] = groupSizes[1] = groupSizes[2] = 3.
    The third group is [3,4,6]. The size is 3, and groupSizes[3] = groupSizes[4] = groupSizes[6] = 3.
    Other possible solutions are [[2,1,6],[5],[0,4,3]] and [[5],[0,6,2],[4,3,1]].

Example 2:

    Input: groupSizes = [2,1,3,3,3,2]
    Output: [[1],[0,5],[2,3,4]]


 */

//vector<vector<int>> groupThePeople(vector<int> &groupSizes) {
//    // basket capacity -- current size
//    map<int, struct Group> lookupTable;
//
//    struct Group {
//        size_t size{0};
//        vector<int> people{};
//    };
//
//    for (int idx = 0; idx < groupSizes.size(); ++idx) {
//        // 3
//        auto &pGroupSize = groupSizes[idx];
//
//        if (lookupTable[pGroupSize].size < pGroupSize) {
//            ++lookupTable[pGroupSize].size;
//        } else {
//            lookupTable[pGroupSize].size = 1;
//        }
//        lookupTable[pGroupSize].people.emplace_back(idx);
//    }
//
//    vector<vector<int>> result;
//    result.reserve(lookupTable.size());
//
//    for (auto &[capacity, pGroup]: lookupTable) {
//        result.emplace_back(pGroup.people);
//    }
//    return result;
//}


vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
    unordered_map<int, vector<int>> lookupTable;
    vector<vector<int>> result;

    for (int i = 0; i < groupSizes.size(); ++i) {
        auto& groupSize = groupSizes[i];
        if(lookupTable[groupSize].empty())
            lookupTable[groupSize].reserve(groupSize);

        lookupTable[groupSize].emplace_back(i);

        if (lookupTable[groupSize].size() == groupSize) {
            result.emplace_back(std::move(lookupTable[groupSize]));
            lookupTable[groupSize].clear();
        }
    }

    return result;
}
