#include "../Headers.h"

/*
Example 1:

    Input: s = "the sky is blue"
    Output: "blue is sky the"

Example 2:

    Input: s = "  hello world  "
    Output: "world hello"
    Explanation: Your reversed string should not contain leading or trailing spaces.

Example 3:

    Input: s = "a good   example"
    Output: "example good a"
    Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.

*/


string reverseWords(string s) {
    stack<string> storage;

    for (int idx = 0; idx < s.size(); ++idx) {
        string curr;
        while(idx < s.size() && s[idx] != ' ') {
            curr.push_back(s[idx]);
            idx++;
        }
        if(!curr.empty()) storage.push(curr);
    }
    string  ret;

    while(!storage.empty()) {
        ret += storage.top();
        storage.pop();
        if(!storage.empty()) ret += " ";
    }
    return ret;
}