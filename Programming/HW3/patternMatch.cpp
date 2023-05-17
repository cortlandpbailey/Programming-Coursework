#include <iostream>
using namespace std;

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
};

bool SubtreeMatch(TreeNode* tree, TreeNode* pattern) {
    if (!tree && !pattern) 
        return true;
    
    if (!tree || !pattern) 
        return false;
    
    if (tree->data != pattern->data) 
        return false;
    
    if (pattern->left == nullptr)
        return SubtreeMatch(tree->right, pattern->right);

    if (pattern->right == nullptr)
        return SubtreeMatch(tree->left, pattern->left);

    return SubtreeMatch(tree->left, pattern->left) && SubtreeMatch(tree->right, pattern->right);
}

bool patternMatch(TreeNode* tree, TreeNode* pattern) {
    if (!pattern) 
        return true;
    
    if (!tree) 
        return false;

    if (SubtreeMatch(tree, pattern)) 
        return true;

    return patternMatch(tree->left, pattern) || patternMatch(tree->right, pattern);
}
