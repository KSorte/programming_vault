#include <iostream>
#include <climits>

/*
    Leetcode 98 Validate Binary Search Tree
    Given the root of a binary tree, determine if it is a valid binary search tree (BST).

    A valid BST is defined as follows:

        The left subtree of a node contains only nodes with keys less than the node's key.
        The right subtree of a node contains only nodes with keys greater than the node's key.
        Both the left and right subtrees must also be binary search trees.

    Algorithm:
    call new function inside validateBST
        new fn(node, ll, ul) {
            if (node.left.val < node.val AND ll < node.left.val < ul) {
                ul = node.val
                new fn(node, ll, ul)
            }

            if (node.right.val > node.val AND ll < node.right.val < ul) {
                ll = node.val
                new fn(node, ll, ul)
            }

            return false;
        }

    Use int64_t, long or long long for defining limits. If you use int, it may happen that a test case
    has values beyond the possible limits of int and some test cases don't pass.
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
     * @brief Determines whether the BST given by root is valid.
     * @param root TreeNode* pointer to the root of the subtree to validate
     * @returns Boolean indicating whether the BST is valid.
     */
    bool isValidBST(TreeNode* root) {
        return isSubtreeValid(root, LONG_MIN, LONG_MAX);
    }

private:
    /**
     * @brief Determines whether the subtree given by root is valid given the limits for node values.
     * This method validates the values of the root itself before recursively calling itself
     * on left and right nodes with new limits.
     * This method is slightly more efficient because of less number of comparisons per call.
     * @param root TreeNode* pointer to the root of the subtree to validate.
     * @param lower_limit Long lower limit for all nodes in the subtree given by root.
     * @param lower_limit Long upper limit for all nodes in the subtree given by root.
     * @returns Boolean indicating whether the subtree given by root and node value limits is valid.
     */
    bool isSubtreeValid(TreeNode* root, int64_t lower_limit, int64_t upper_limit) {
        if (!root) {
            return true;
        }

        if (root->val > lower_limit && root->val < upper_limit) {
            return isSubtreeValid(root->left, lower_limit, root->val) && isSubtreeValid(root->right, root->val, upper_limit);
        }
        return false;
    }

    /**
     * @brief Determines whether the subtree given by root is valid given the limits for node values.
     * This method validates the values of left and right children before recursively calling itself
     * on left and right nodes with new limits.
     * This method is slightly less efficient because of more number of comparisons per call.
     * @param root TreeNode* pointer to the root of the subtree to validate.
     * @param lower_limit Long lower limit for all nodes in the subtree given by root.
     * @param lower_limit Long upper limit for all nodes in the subtree given by root.
     * @returns Boolean indicating whether the subtree given by root and node value limits is valid.
     */
    bool isSubtreeValid2(TreeNode* root, long lower_limit, long upper_limit) {
        if (root->left) {
            if (root->left->val >= root->val ||
                root->left->val <= lower_limit) {
                // Left node out of bounds.
                return false;
            }

            if (!isSubtreeValid2(root->left, lower_limit, root->val)) {
                // Left subtree invalid.
                return false;
            }
        }

        if (root->right) {
            if (root->right->val <= root->val ||
                root->right->val >= upper_limit) {
                // Right node out of bounds.
                return false;
            }

            if (!isSubtreeValid2(root->right, root->val, upper_limit)) {
                // Right subtree invalid.
                return false;
            }
        }

        return true;
    }
};