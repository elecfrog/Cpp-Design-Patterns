#include "../Headers.h"

/*

Example 1:

    Input: root = [1,3,2,5,3,null,9]
    Output: [1,3,9]

Example 2:
    
    Input: root = [1,2,3]
    Output: [1,3]

*/

namespace solution1 {
    vector<int> largestValues(TreeNode* root) {

        // using a queue, FIFO, easy for BFS

        queue<TreeNode *> que;
        if (root != nullptr) que.push(root);
        vector<int> vec;
        while (!que.empty()) {
            int size = que.size();
            int biggest = INT_MIN;
            for (int i = 0; i < size; i++) {
                TreeNode *node = que.front();
                que.pop();
                biggest = max(biggest, node->val);
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
            vec.emplace_back(biggest);
        }
        return vec;
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