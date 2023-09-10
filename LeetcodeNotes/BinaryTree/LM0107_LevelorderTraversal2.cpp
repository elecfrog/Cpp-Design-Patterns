#include "../Headers.h"

/*

Example 1:

    Input: root = [3,9,20,null,null,15,7]
    Output: [[15,7],[9,20],[3]]

Example 2:

    Input: root = [1]
    Output: [[1]]

Example 3:

    Input: root = []
    Output: []

*/


namespace solution1 {
    vector<vector<int>> levelOrderBottom(TreeNode *root) {

        // using a queue, FIFO, easy for BFS and simply reverse

        queue<TreeNode *> que;
        if (root != nullptr) que.push(root);
        vector<vector<int>> result;
        vector<int> vec;
        while (!que.empty()) {
            int size = que.size();
            for (int i = 0; i < size; i++) {
                TreeNode *node = que.front();
                que.pop();
                vec.emplace_back(node->val);
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
            result.emplace_back(std::move(vec));
        }
        reverse(result.begin(), result.end());
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

    vector<vector<int>> levelOrderBottom(TreeNode *root) {
        vector<vector<int>> result;
        int depth = 0;
        order(root, result, depth);
        reverse(result.begin(), result.end());
        return result;
    }
}