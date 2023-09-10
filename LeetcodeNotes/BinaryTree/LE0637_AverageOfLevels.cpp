#include "../Headers.h"

/*

Example 1:

    Input: root = [3,9,20,null,null,15,7]
    Output: [3.00000,14.50000,11.00000]
    Explanation: The average value of nodes on level 0 is 3, on level 1 is 14.5, and on level 2 is 11.
    Hence return [3, 14.5, 11].

Example 2:

    Input: root = [3,9,20,15,7]
    Output: [3.00000,14.50000,11.00000]

*/

namespace solution1 {
    vector<double> averageOfLevels(TreeNode *root) {

        // using a queue, FIFO, easy for BFS

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

        vector<double> ret;
        for_each(result.begin(), result.end(), [&](auto &level) {
            double levelSum = .0;
            for_each(level.begin(), level.end(), [&](auto &val) {
                levelSum += val;
            });
            ret.emplace_back(levelSum / level.size());
        });

        return ret;
    }

}

namespace solution2 {
    vector<double> averageOfLevels(TreeNode *root) {

        // using a queue, FIFO, easy for BFS

        queue<TreeNode *> que;
        if (root != nullptr) que.push(root);
        vector<double> result;
        while (!que.empty()) {
            int size = que.size();
            double levelSum = .0;
            for (int i = 0; i < size; i++) {
                TreeNode *node = que.front();
                que.pop();
                levelSum += node->val;     
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
            result.emplace_back(levelSum / size);
        }

        return result;
    }
}
