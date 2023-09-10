#include "../Headers.h"

// https://zhuanlan.zhihu.com/p/62778410

/*

Example 1:

    Input: root = [1,null,2,3]
    Output: [1,3,2]

Example 2:
    
    Input: root = []
    Output: []

Example 3:

    Input: root = [1]
    Output: [1]

*/

void inorderTraversalRecursively(vector<int> &ret, TreeNode *node) {
    if (node == nullptr)
        return;
    inorderTraversalRecursively(ret, node->left);
    ret.emplace_back(node->val);
    inorderTraversalRecursively(ret, node->right);
}

vector<int> inorderTraversalIteratively(TreeNode *root) {
    vector<int> result;
    stack<TreeNode *> storage;
    TreeNode *curr = root;
    while (curr != nullptr || !storage.empty()) {
        // dive to the very left leave
        if (curr != nullptr) {
            // push then dive
            storage.push(curr);
            curr = curr->left;
        } else {
            curr = storage.top();
            storage.pop();
            result.push_back(curr->val);
            // right
            curr = curr->right;
        }
    }
    return result;
}

vector<int> inorderTraversalUniversally(TreeNode *root) {
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

            // add parent node back
            storage.push(node);
            // add a empty tag node
            storage.push(nullptr);

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

vector<int> inorderTraversal(TreeNode *root) {
    vector<int> ret;
    inorderTraversalRecursively(ret, root);

    return ret;
}

int main() {
    {
        // nullptr -- empty
        int *curr = nullptr;
        stack<int> storage;
        cout << (curr != nullptr || !storage.empty()) << endl;
    }

    {
        // nullptr -- not empty
        int *curr = nullptr;
        stack<int> storage;
        storage.push(1);
        cout << (curr != nullptr || !storage.empty()) << endl;
    }

    {
        // not nullptr -- empty
        int *curr = new int{2};
        stack<int> storage;
        cout << (curr != nullptr || !storage.empty()) << endl;
    }

    {
        // not nullptr -- not empty
        int *curr = new int{2};
        stack<int> storage;
        storage.push(1);
        cout << (curr != nullptr || !storage.empty()) << endl;
    }

    {
        cout << "false || false => " << (false || false) << endl;
        cout << "true  || false => " << (true || false) << endl;
        cout << "false || true  => " << (false || true) << endl;
        cout << "true  || true  => " << (true || true) << endl;

        cout << "false && false => " << (false && false) << endl;
        cout << "true  && false => " << (true && false) << endl;
        cout << "false && true  => " << (false && true) << endl;
        cout << "true  && true  => " << (true && true) << endl;
    }


}