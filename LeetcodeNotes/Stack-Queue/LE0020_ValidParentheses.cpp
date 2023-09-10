#include "../Headers.h"

/*

Example 1:

    Input: s = "()"
    Output: true

Example 2:

    Input: s = "()[]{}"
    Output: true

Example 3:

    Input: s = "(]"
    Output: false

*/

bool isValid(string s) {

    stack<char> pairs;

    for (auto &&c: s) {
        if (c == '{' || c == '[' || c == '(') {
            pairs.push(c);
        } else {
            if (pairs.empty()) return false;

            char top = pairs.top();
            pairs.pop();

            if ((c == '}' && top != '{') ||
                (c == ']' && top != '[') ||
                (c == ')' && top != '(')) {
                return false;
            }
        }
    }

    return pairs.empty();
}