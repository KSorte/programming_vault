#include <algorithm>
#include <iostream>
#include <vector>

/*
Leetcode 543 Diameter of Binary Tree
Given the root of a binary tree, return the length of the diameter of the tree.

The diameter of a binary tree is the length of the longest path between any two nodes in a tree.
This path may or may not pass through the root.

The length of a path between two nodes is represented by the number of edges between them.

Create DFS function that gets the depth of from a node.
Apply DFS on each child (left and right) and get its depth.
Then calculate the diameter of the tree as left child depth + right child depth.
Update the diameter variable declared in the class.
Return the max(left child depth, right child depth) + 1 from the DFS function.

initialize the diameter through the root as 0.
Call DFS function with the root.

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
     * @brief Calculate diameter of binary tree.
     * @param root TreeNode* pointer pointing to root node of tree.
     * @returns Integer diameter of the tree.
     */
    int diameterOfBinaryTree(TreeNode* root) {
        // If root pointer non existent, return -1.
        if (!root) { return -1;}

        diameter = 0;
        dfs(root);
        return diameter;
    }

    /**
     * @brief Depth First Search on root
     * @param TreeNode* pointer pointing to root node of tree.
     * @returns Integer depth of the tree from the root.
     */
    int dfs(TreeNode* root) {

        // If root is a null pointer, return depth as 0.
        if (!root) { return 0;}

        // Get the depth of the left and right nodes.
        int left_depth = dfs(root->left);
        int right_depth = dfs(root->right);

        // Get the diameter of the tree passing through the root.
        int diameter_through_root = left_depth + right_depth;

        // Update the diameter attribute.
        diameter = std::max(diameter, diameter_through_root);

        // Return the depth at the root as the max of left and right depths + 1.
        // The + 1 adds the edge between the root and whichever child has max depth to complete depth
        // calculation.
        return 1 + std::max(left_depth, right_depth);
    }

private:
    // Diameter of the binary tree.
    int diameter;
};