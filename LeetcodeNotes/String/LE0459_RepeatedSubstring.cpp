#include "../Headers.h"

/*
Example 1:

    Input: s = "abab"
    Output: true
    Explanation: It is the substring "ab" twice.

Example 2:

    Input: s = "aba"
    Output: false

Example 3:

    Input: s = "abcabcabcabc"
    Output: true
    Explanation: It is the substring "abc" four times or the substring "abcabc" twice.

*/


bool repeatedSubstringPattern(string s) {
    string t = s + s;
    t.erase(t.begin()); t.erase(t.end() - 1);
    if (t.find(s) != std::string::npos) return true; // r
    return false;
}