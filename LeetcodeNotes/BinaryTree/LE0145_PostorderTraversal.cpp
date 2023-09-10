#include "../Headers.h"

// https://zhuanlan.zhihu.com/p/62778410

/*

Example 1:

    Input: root = [1,null,2,3]
    Output: [3,2,1]

Example 2:

    Input: root = []
    Output: []

Example 3:

    Input: root = [1]
    Output: [1]

*/


void postorderTraversalRecursively(vector<int> &ret, TreeNode *node) {
    if (node == nullptr)
        return;
    postorderTraversalRecursively(ret, node->left);
    postorderTraversalRecursively(ret, node->right);
    ret.emplace_back(node->val);
}


vector<int> postorderTraversalIteratively(TreeNode *node) {
    if (node == nullptr) return {};

    stack<TreeNode *> storage;
    vector<int> result;
    storage.push(node);

    while (!storage.empty()) {
        TreeNode *curr = storage.top();
        storage.pop();
        result.push_back(curr->val);
        if (curr->left) storage.push(curr->left);
        if (curr->right) storage.push(curr->right);
    }
    
    reverse(result.begin(), result.end());

    return result;
}

vector<int> postorderTraversalUniversally(TreeNode *root) {
    vector<int> result;
    stack<TreeNode *> storage;
    if (root != nullptr) storage.push(root);
    while (!storage.empty()) {
        TreeNode *node = storage.top();
        if (node != nullptr) {
            // pop a particle
            storage.pop();

            // add parent node back
            storage.push(node);
            // add a empty tag node
            storage.push(nullptr);

            // add right node
            if (node->right) storage.push(node->right);
            // add left node
            if (node->left) storage.push(node->left);

        } else {
            storage.pop();
            // real parent node
            node = storage.top();
            storage.pop();
            // add to result
            result.push_back(node->val);
        }
    }
    return result;
}

vector<int> postorderTraversal(TreeNode *root) {
    vector<int> ret;
    postorderTraversalRecursively(ret, root);

    return ret;
}