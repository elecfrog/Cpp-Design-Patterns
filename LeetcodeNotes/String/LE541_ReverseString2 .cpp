#include "../Headers.h"

/*
Example 1:

    Input: s = "abcdefg", k = 2
    Output: "bacdfeg"

Example 2:

    Input: s = "abcd", k = 2
    Output: "bacd"
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
    for (int i = 0, j = s.size() - 1; i < s.size() / 2; i++, j--) {
        swap(s[j], s[i]);
    }
}


string reverseStr(string s, int k) {

    int left = 0;
    int size = s.size();
    // while the length > k, continue looping
    while (size - left > k) {
        // update right index as the  => left + k
        auto right = left + k;

        // 2 / 2 == 1 1 % 2 == 1 => do swap  
        // 4 / 2 == 2 2 % 2 == 0 => ignore  
        if ((right / k) % 2 == 1) {
            char tmp;
            for (int i = left, j = right - 1; i < left + (right - left) / 2; i++, j--) {
                tmp = std::move(s[j]);
                s[j] = std::move(s[i]);
                s[i] = std::move(tmp);
            }
        }

        left = right;
    }
    
    return s;
}


string reverseStr(string s, int k) {
    int n = s.size();
    for (int i = 0; i < n; i += 2 * k) {
        // Find the end of the substring to reverse
        int end = min(i + k, n);
        reverse(s.begin() + i, s.begin() + end);
    }
    return s;
}