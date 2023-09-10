#include "../Headers.h"

/*

Example 1:

    Input: root = [1,null,3,2,4,null,5,6]
    Output: [[1],[3,2,4],[5,6]]

Example 2:

    Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
    Output: [[1],[2,3,4,5],[6,7,8,9,10],[11,12,13],[14]]

*/



// Definition for a Node.
namespace solution1 {
    class Node {
    public:
        int val;
        Node *left;
        Node *right;
        Node *next;

        Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

        Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

        Node(int _val, Node *_left, Node *_right, Node *_next)
                : val(_val), left(_left), right(_right), next(_next) {}
    };

    Node *connect(Node *root) {

        // using a queue, FIFO, easy for BFS
        // in-place connect linkages

        queue<Node *> que;
        if (root != nullptr) que.push(root);

        while (!que.empty()) {
            int size = que.size();

            Node *prev = nullptr;
            for (int i = 0; i < size; i++) {
                Node *curr = que.front();
                que.pop();

                if (prev != nullptr) prev->next = curr;

                prev = curr;

                if (curr->left) que.push(curr->left);
                if (curr->right) que.push(curr->right);
            }

            if (prev != nullptr) prev->next = nullptr;
        }

        return root;
    }
}
