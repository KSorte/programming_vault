#include <algorithm>
#include <iostream>
#include <vector>

/*
    Leetcode 572 Subtree of Another Tree.
    Given the roots of two binary trees root and subRoot, return true if there is a subtree of root with the same
    structure and node values of subRoot and false otherwise.

    A subtree of a binary tree tree is a tree that consists of a node in tree and all of this node's descendants.
    The tree tree could also be considered as a subtree of itself.

    Algorithm: Basic logic
        isSubroot(root, subroot):
        if isIdentical(root, subRoot) :
            return true; // Base case.

        return isSubtree(root.left, subRoot) AND isSubtree(root.right, subRoot)

        isIdentical(root, subroot):
            if (root, subroot == NULL) :
                return true; // Base case

            if (root.val not equal to subroot.val):
                return false;

            return isIdentical(root.left, subroot.left) AND isIdentical(root.right, subroot.right)

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
     * @brief Checks if the binary tree subRoot is a equal to a subtree of the binary tree root.
     * @param root TreeNode* pointer to the main tree.
     * @param subRoot TreeNode* pointer to a subtree whose identical counterpart is checked in main tree.
     * @returns Boolean indicating whether subRoot is a subtree of a root.
     */
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (isIdentical(root, subRoot)) {
            return true;
        }

        if (subRoot == nullptr) {
            return true;
        }

        if (root == nullptr) {
            return false;
        }

        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }

private:
    /**
     * @brief Checks if the two binary trees represented by TreeNode* pointers are equal.
     * @param root1 TreeNode* pointer to tree1.
     * @param root2 TreeNode* pointer to tree2.
     * @returns Boolean indicating whether the two trees are identical.
     */
    bool isIdentical(TreeNode* root1, TreeNode* root2) {
        if (root1 == nullptr && root2 == nullptr) {
            return true;
        }

        // False if only one of them is null.
        if (root1 == nullptr || root2 == nullptr) {
            return false;
        }

        if (root1->val != root2->val) {
            return false;
        }

        return isIdentical(root1->left, root2->left) && isIdentical(root1->right, root2->right);
    }
};
