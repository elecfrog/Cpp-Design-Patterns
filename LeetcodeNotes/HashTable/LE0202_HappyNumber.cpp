#include "../Headers.h"

/*
Example 1:

    Input: n = 19  =>   19 / 10 = 1 19 % 10  = 9 
    Output: true
    Explanation:
    1^2 + 9^2 = 82
    8^2 + 2^2 = 68
    6^2 + 8^2 = 100
    1^2 + 0^2 + 02 = 1

Example 2:

    Input: n = 2
    Output: false
*/

bool isHappy(int n) {

    // the key of this question is determined by the condition 
    // when we should exit the loop 
    // while cannot find a happy number to avoid infinite loop


    unordered_set<int> occurs;

    for (;;) {
        int sum = 0;
        while (n) {
            int last = n % 10;
            sum += (last * last);
            n /= 10;
        }
        if (sum == 1) return true;

        if (occurs.find(sum) != occurs.end()) {
            return false;
        } else {
            occurs.insert(sum);
        }
        n = sum;
    }
}

int main() {
    cout << isHappy(19);
}