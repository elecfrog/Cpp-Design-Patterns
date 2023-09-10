#include "../Headers.h"

/*

Example 1:

    Input: root = [1,2,3,null,5,null,4]
    Output: [1,3,4]

Example 2:

    Input: root = [1,null,3]
    Output: [1,3]

Example 3:

    Input: root = []
    Output: []

*/

vector<int> rightSideView(TreeNode *root) {

    // using a queue, FIFO, easy for BFS

    queue<TreeNode *> que;
    if (root != NULL) que.push(root);
    vector<int> result;
    while (!que.empty()) {
        int size = que.size();
        for (int i = 0; i < size; i++) {
            TreeNode *node = que.front();
            que.pop();
            // add very right node into result
            if (i == (size - 1)) result.emplace_back(node->val);
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
    }
    return result;
}
