#include "../Headers.h"

/*
Example 1:

    Input: s = ["h","e","l","l","o"]
    Output: ["o","l","l","e","h"]

Example 2:
    
    Input: s = ["H","a","n","n","a","h"]
    Output: ["h","a","n","n","a","H"]


*/


/*

void reverseString(vector<char> &s) {
    stack<char> ret; 
    for (char &c: s) {
        ret.push(c);
    }
    for (int idx = 0; idx < s.size(); ++idx) {
        s[idx] = ret.top();
        ret.pop();
    }
}

*/


void reverseString(vector<char> &s) {
    char tmp;
    for (int i = 0, j = s.size() - 1; i < s.size() / 2; i++, j--) {
        tmp = std::move(s[j]);
        s[j] = std::move(s[i]);
        s[i] = std::move(s[tmp]);
    }
}

/*

void reverseString(vector<char> &s) {
    for (int i = 0, j = s.size() - 1; i < s.size() / 2; i++, j--) {
        swap(s[j], s[i]);
    }
}
 
*/
