#include "../Headers.h"

/*
Example 1:

    Input: strs = ["flower","flow","flight"]
    Output: "fl"

Example 2:

    Input: strs = ["dog","racecar","car"]
    Output: ""
    Explanation: There is no common prefix among the input strings.


*/

string longestCommonPrefix(vector<string> &strs) {
    string result{strs[0]};
    for (size_t idx = 1; idx < strs.size(); idx++) {
        for (size_t character = 0; character < result.size(); character++) {
            if (strs[idx][character] != result[character]) {
                result = result.substr(0, character);
            }
        }
    }
    return result;
}
