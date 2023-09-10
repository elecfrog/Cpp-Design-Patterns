#include "../Headers.h"

/*

Example 1:

    Input: root = [1,null,3,2,4,null,5,6]
    Output: [[1],[3,2,4],[5,6]]

Example 2:

    Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
    Output: [[1],[2,3,4,5],[6,7,8,9,10],[11,12,13],[14]]

*/



/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
namespace solution1 {
    vector<vector<int>> levelOrder(Node *root) {

        // using a queue, FIFO, easy for BFS

        queue<Node *> que;
        if (root != nullptr) que.push(root);
        vector<vector<int>> result;
        vector<int> vec;
        while (!que.empty()) {
            int size = que.size();
            for (int i = 0; i < size; i++) {
                Node *node = que.front();
                que.pop();
                vec.emplace_back(node->val);
                for (auto &&c: node->children) {
                    if(c) que.push(c);
                }
            }
            result.emplace_back(std::move(vec));
        }
        return result;
    }
}


namespace solution2 {
    void order(TreeNode *cur, vector<vector<int>> &result, int depth) {
        if (cur == nullptr) return;
        if (result.size() == depth)
            result.emplace_back(vector<int>{});
        result[depth].emplace_back(cur->val);
        order(cur->left, result, depth + 1);
        order(cur->right, result, depth + 1);
    }

    vector<vector<int>> levelOrder(TreeNode *root) {
        vector<vector<int>> result;
        int depth = 0;
        order(root, result, depth);
        return result;
    }
}