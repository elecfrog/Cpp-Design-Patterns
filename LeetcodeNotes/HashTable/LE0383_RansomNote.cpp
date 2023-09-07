#include "../Headers.h"

/*
Example 1:

    Input: ransomNote = "a", magazine = "b"
    Output: false

Example 2:

    Input: ransomNote = "aa", magazine = "ab"
    Output: false

Example 3:

    Input: ransomNote = "aa", magazine = "aab"
    Output: true


*/


bool canConstruct(string t, string s) {
    vector<int> magazine(26, 0);
    for (char i: s)
        magazine[i - 'a']++;

    for (char i: t)
        if (--magazine[i - 'a'] < 0)
            return false;
    return true;
}