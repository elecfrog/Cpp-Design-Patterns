#pragma once

#include <utility>
#include <vector>
#include <stack>
#include <iostream>
#include <queue>
#include <deque>
#include <list>
#include <format>
#include <forward_list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <string>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    explicit ListNode(int x) : val(x), next(nullptr) {}

    explicit ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    explicit TreeNode(int x, TreeNode *left, TreeNode *right)
            : val(x), left(left), right(right) {}
};

// Definition for a Node.
class Node {
public:
    int val{};
    vector<Node *> children;

    Node() = default;

    explicit Node(int _val) {
        val = _val;
    }

    explicit Node(int _val, vector<Node *> _children) {
        val = _val;
        children = std::move(_children);
    }
};
