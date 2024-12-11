#include <cstdlib>
#include <iostream>
#include <vector>

/*

Leetcode 110 Balanced Binary Tree
Given a binary tree, determine if it is height-balanced.
https://leetcode.com/problems/balanced-binary-tree/description/

Solution similar to solution of Leetcode 543

Create DFS function that gets the depth from a node.
Apply DFS on each child (left and right) and get its depth.
if (left and right depth are imbalanced) return false.
Return the max(left child depth, right child depth) + 1 from the DFS function.

DFS function (is_balanced)
    left_depth = dfs(left child, is_left_balanced)
    right_depth = dfs(right child, is_right_balanced)
    if (bigger - smaller) > 1 or if one of the subtree is unbalanced
        is_balanced = false

    height = max(left, right) + 1
    return height

def is_balanced( )
    is_balanced = false;
    dfs(root, is_balanced)
    return is_balanced
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
     * @brief Determines whether the binary tree is balanced.
     * @param root TreeNode* pointer pointing to root node of tree.
     * @returns Boolean indicating whether the binary tree is balanced.
     */
    bool isBalanced(TreeNode* root) {
        bool is_balanced;
        dfs(root, is_balanced);
        return is_balanced;
    }

    /**
     * @brief Depth First Search on root to calculate depth and determine balance.
     * @param TreeNode* pointer pointing to root node of tree.
     * @param [out] is_balanced Boolean indicating whether the tree is balanced.
     * @returns Integer depth of the tree from the root.
     */
    int dfs(TreeNode* root, bool & is_balanced) {

        if (!root) {
            // If root is a null pointer, tree is balanced and depth 0.
            is_balanced = true;
            return 0;
        }

        // Initialize the booleans indicating whether the left and right subtrees are balanced.
        bool is_left_balanced, is_right_balanced;

        // Get left and right heights and whether they are balanced.
        int left_height = dfs(root->left, is_left_balanced);
        int right_height = dfs(root->right, is_right_balanced);

        if ((std::abs(left_height - right_height) > 1) ||
            !is_left_balanced ||
            !is_right_balanced) {
                // If the left and right subtree heights differ by more than 1 or if the subtrees
                // are imbalanced themselves, set is_balanced to false
                is_balanced = false;
            } else {
                // Else return true.
                is_balanced = true;
            }

        // Return the height of the subtree from the parent of root downwards as
        // 1 + max of left and right heights of the root.
        return std::max(left_height, right_height) + 1;
    }
};