#include "../Headers.h"

/*
Example 1:

    Input: words = ["bella","label","roller"]
    Output: ["e","l","l"]

Example 2:

    Input: words = ["cool","lock","cook"]
    Output: ["c","o"]

*/



//vector<string> commonChars(vector<string> &words) {
//
//    // initialize into big numbers, 
//    // cuz we need to find the min occurs
//    vector<int> hash(26, INT_MAX);
//
//    for (auto &&word: words) {
//        // "cool", "col", "abo"
//        // current word occurs times
//        vector<int> currWordHash(26, 0);
//
//        // 121, 111, 010
//        for (auto &&c: word)
//            currWordHash[c - 97]++;
//
//        // 010
//        // the common word has occurs in history
//        for (int i = 0; i < 26; i++) {
//            hash[i] = min(hash[i], currWordHash[i]);
//        }
//    }
//
//    vector<string> ret;
//    for (int i = 0; i < 26; i++) {
//        while (hash[i]-- > 0)
//            ret.emplace_back(1, i + 'a');
//    }
//    return ret;
//}

vector<string> commonChars(vector<string> &words) {
    vector<int> comparedHash(26, 0);

    // base hash to make comparison
    for (auto &&i: words[0])
        comparedHash[i - 'a']++;

    // words afterwards
    for (int i = 1; i < words.size(); i++) {
        vector<int> tmp(26, 0);
        // current hash counting
        for (auto ch: words[i]) {
            tmp[ch - 'a']++;
        }
        for (int i = 0; i < 26; i++) {
            comparedHash[i] = min(comparedHash[i], tmp[i]);
        }
    }

    vector<string> ret;
    for (int i = 0; i < 26; i++) {
        while (comparedHash[i]-- > 0) {
            ret.emplace_back(1, i + 'a');
        }
    }
    return ret;
}

int main() {
    auto vec = vector<string>{"rat", "car"};
    auto res = commonChars(vec);
    for (auto &&name: res) {
        cout << name << endl;
    }
}