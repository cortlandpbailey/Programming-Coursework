#include <iostream>
#include <queue>

using namespace std;

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
};

bool isMaxHeap(TreeNode* t) {
    if (!t) 
        return true;
    

    queue<TreeNode*> q;
    q.push(t);
    bool end = false;

    while (!q.empty()) {
        int size = q.size();
        bool null = false;

        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();

            if (node == nullptr)
                null = true;
            
            else {
                if (end || null)
                    return false;

                if (node->left && node->left->data > node->data)  
                    return false;
                
                if (node->right && node->right->data > node->data) 
                    return false;

                q.push(node->left);
                q.push(node->right);
            }
        }
        if (null)
            end = true;
    }

    return true;
}
