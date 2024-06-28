#include <iostream>
#include <queue>
#include <stack>
#include <utility> // For std::swap
#include <vector>

/*

Leetcode 226 Invert Binary Tree
Given the root of a binary tree, invert the tree, and return its root.
*/


// Definition for a binary tree node.
struct TreeNode {
    // Tree Node value
    int val;

    // Pointer to left child.
    TreeNode *left;

    // Pointer to right child.
    TreeNode *right;

    /**
     * @brief Constructor of TreeNode struct.
     * Initializes val, left and right.
     */
    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    /**
     * @brief Constructor of TreeNode struct.
     * Initializes val, left and right.
     * @param x Integer for initializing val.
     */
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    /**
     * @brief Constructor of TreeNode struct.
     * Initializes val, left and right.
     * @param x Integer for initializing val.
     * @param *left Pointer to the left child of the node.
     * @param *right Pointer to the right child of the node.
     */
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:

    /**
     * @brief Invert the binary tree.
     * @param root Root of the binary tree to be inverted.
     * @returns TreeNode* root of the inverted binary tree.
     */
    TreeNode* invertTree(TreeNode* root) {
        // If root is a null pointer, return immediately.
        if (!root) { return root;}

        // Swap left and right pointers of root.
        auto temp = root->left;
        root->left = root->right; root->right = temp;

        // Invert tree downstream of left and right.
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};