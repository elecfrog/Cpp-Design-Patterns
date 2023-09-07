#include <vector>
#include "../Headers.h"

using namespace std;

/*
Example 1:

    Input: s = "anagram", t = "nagaram"
    Output: true

Example 2:

    Input: s = "rat", t = "car"
    Output: false


 */



bool isAnagram(string s, string t) {

    if (s.size() != t.size())
        return false;

    // simply using a dict and number counting!
    vector<int> dict(26, 0);

    for (int c = 0; c < s.size(); ++c) {
        // convert from a char to a number, 
        // and minus 'a'
        auto sIndex = static_cast<int>(s[c]) - 97;
        dict[sIndex]++;
        auto tIndex = static_cast<int>(t[c]) - 97;
        dict[tIndex]--;
    }

    for (auto &&idx: dict) {
        if (idx != 0) return false;
    }

    return true;
}

int main() {
    cout << isAnagram("rat", "car") << endl;
}