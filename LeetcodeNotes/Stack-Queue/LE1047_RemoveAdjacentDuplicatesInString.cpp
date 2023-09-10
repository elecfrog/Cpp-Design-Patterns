#include "../Headers.h"

/*

Example 1:

    Input: s = "abbaca"
    Output: "ca"
    Explanation: 
    For example, in "abbaca" we could remove "bb" since the letters are adjacent and equal, and this is the only possible move.  The result of this move is that the string is "aaca", of which only "aa" is possible, so the final string is "ca".

Example 2:

    Input: s = "azxxzy"
    Output: "ay"

*/

namespace solution1 {
    string removeDuplicates(string s) {
        stack<char> record;
        for (auto &c: s) {
            if (!record.empty() && c == record.top()) {
                record.pop();
            } else {
                record.push(c);
            }
        }

        string result;
        while (!record.empty()) {
            result.push_back(record.top());
            record.pop();
        }

        reverse(result.begin(), result.end());
        return result;
    }
}

namespace solution2 {
    string removeDuplicates(string S) {
        string result;
        for (auto&& c: S) {
            if (result.empty() || result.back() != c) {
                result.push_back(c);
            } else {
                result.pop_back();
            }
        }
        return result;
    }
}