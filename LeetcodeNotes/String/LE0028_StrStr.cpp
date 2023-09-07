#include "../Headers.h"

/*
Example 1:

    Input: haystack = "sadbutsad", needle = "sad"
    Output: 0
    Explanation: "sad" occurs at index 0 and 6.
    The first occurrence is at index 0, so we return 0.

Example 2:

    Input: haystack = "leetcode", needle = "leeto"
    Output: -1
    Explanation: "leeto" did not occur in "leetcode", so we return -1.

*/


int strStr(string haystack, string needle) {

    int needleSize = needle.size();
    if (needleSize == 0) {
        return 0;
    }

    for (int idx = 0; idx < haystack.size(); ++idx) {
        int innerCount = 0;
        while (innerCount < needleSize && haystack[idx + innerCount] == needle[innerCount]) {
            innerCount++;
        }

        if (innerCount == needleSize) { return idx; }
        else idx += innerCount;
    }

    return -1;
}