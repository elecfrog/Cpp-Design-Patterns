#include "../Headers.h"

/*

Example 1:

    Input: root = [3,9,20,null,null,15,7]
    Output: 3

Example 2:

    Input: root = [1,null,2]
    Output: 2

*/

int maxDepth(TreeNode *root) {
    if (root == nullptr) return 0;
    int depth = 0;
    queue<TreeNode *> que;
    que.push(root);
    while (!que.empty()) {
        int size = que.size();
        depth++; // record the depth
        for (int i = 0; i < size; i++) {
            TreeNode *node = que.front();
            que.pop();
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
    }
    return depth;
}
