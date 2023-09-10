#include "../Headers.h"

// https://zhuanlan.zhihu.com/p/62778410

/*

Example 1:

    Input: root = [1,null,2,3]
    Output: [1,2,3]

Example 2:

    Input: root = []
    Output: []

Example 3:

    Input: root = [1]
    Output: [1]

*/

void preorderTraversalRecursively(vector<int> &ret, TreeNode *node) {
    if (node == nullptr)
        return;
    ret.emplace_back(node->val);
    preorderTraversalRecursively(ret, node->left);
    preorderTraversalRecursively(ret, node->right);
}

vector<int> preorderTraversalIteratively(TreeNode *node) {
    if (node == nullptr) return {};

    stack<TreeNode *> storage;
    vector<int> result;
    storage.push(node);

    while (!storage.empty()) {
        TreeNode *curr = storage.top();
        storage.pop();
        result.push_back(curr->val);
        if (curr->right) storage.push(curr->right);
        if (curr->left) storage.push(curr->left);
    }
    return result;
}

vector<int> preorderTraversalUniversally(TreeNode *root) {
    vector<int> result;
    stack<TreeNode *> storage;
    if (root != nullptr) storage.push(root);
    while (!storage.empty()) {
        TreeNode *node = storage.top();
        if (node != nullptr) {
            // pop a particle
            storage.pop();

            // add right node
            if (node->right) storage.push(node->right);
            // add left node
            if (node->left) storage.push(node->left);
            // add parent node back
            storage.push(node);
            // add a empty tag node
            storage.push(nullptr);

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

vector<int> preorderTraversal(TreeNode *root) {
    
    return preorderTraversalUniversally(root);
}