#include "../Headers.h"

/*

Example 1:

    Input: root = [3,9,20,null,null,15,7]
    Output: 2

Example 2:

    Input: root = [2,null,3,null,4,null,5,null,6]
    Output: 5


*/

int minDepth(TreeNode *root) {
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
            // early exit
            if (!node->left && !node->right)
                return depth;
        }
    }
    return depth;
}
