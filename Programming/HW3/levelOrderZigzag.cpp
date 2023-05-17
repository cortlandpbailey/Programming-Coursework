#include <iostream>
#include <queue>
#include <list>
using namespace std;

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
};

list<int> levelOrderZigzag(TreeNode* t) {
    list<int> result;
    if (!t) {
        return result;
    }

    queue<TreeNode*> q;
    q.push(t);
    bool left_right = false;

    while (!q.empty()) {
        int size = q.size();
        list<int> level;

        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();

            if (left_right)
                level.push_back(node->data);
            else 
                level.push_front(node->data);
            if (node->left) 
                q.push(node->left);
            if (node->right) 
                q.push(node->right);
        }

        result.insert(result.end(), level.begin(), level.end());
        left_right = !left_right;
    }

    return result;
}