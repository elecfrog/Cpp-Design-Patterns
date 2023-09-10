#include "../Headers.h"

/*

Example 1:

    Input: nums = [1,1,1,2,2,3], k = 2
    Output: [1,2]

Example 2:

    Input: nums = [1], k = 1
    Output: [1]

*/


vector<int> topKFrequent(vector<int> &nums, int k) {
    // map => value, times
    unordered_map<int, size_t> topKMap;

    for (auto &&value: nums) {
        topKMap[value]++;
    }

    vector<pair<int, size_t>> frequencyVec(topKMap.begin(), topKMap.end());

    sort(frequencyVec.begin(), frequencyVec.end(),
         [](const pair<int, size_t> &a, const pair<int, size_t> &b) {
             return b.second < a.second; // sorting
         });

    vector<int> result;
    for (int i = 0; i < k; ++i) {
        result.push_back(frequencyVec[i].first);
    }

    return result;
}


namespace solution2 {
    vector<int> topKFrequent(vector<int> &nums, int k) {
        
        // Step 1: Create a hashmap to store the frequency of each number
        unordered_map<int, size_t> frequencyMap;
        for (const auto &value: nums) {
            frequencyMap[value]++;
        }
        
        // Step 2: Define a min heap of size k to keep track of the top k frequent elements
        auto comp = [&frequencyMap](int num1, int num2) {
            return frequencyMap[num1] > frequencyMap[num2];  // Note: We define the comparator to create a min heap
        };
        priority_queue<int, vector<int>, decltype(comp)> minHeap(comp);


        // Step 3: Iterate over the unique numbers in the array
        for (const auto &[num, freq]: frequencyMap) {
            minHeap.push(num);
            // If the size of the heap exceeds k, remove the least frequent element
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }

        // Step 4: Retrieve the top k frequent elements from the min heap
        vector<int> result(k);  // Note: We know the size of the result, so we initialize the vector with size k
        for (int i = k - 1; i >= 0; --i) {
            result[i] = minHeap.top();
            minHeap.pop();
        }

        return result;
    }
}
